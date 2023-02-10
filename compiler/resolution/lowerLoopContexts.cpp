
// probably too much:
#include "astutil.h"
#include "AstVisitorTraverse.h"
#include "CForLoop.h"
#include "driver.h"
#include "errorHandling.h"
#include "expr.h"
#include "ForallStmt.h"
#include "ForLoop.h"
#include "iterator.h"
#include "lowerLoopContexts.h"
#include "optimizations.h"
#include "passes.h"
#include "resolution.h"
#include "resolveIntents.h"
#include "stlUtil.h"
#include "stmt.h"
#include "stringutil.h"
#include "symbol.h"
#include "view.h"
#include "wellknown.h"

#include "global-ast-vecs.h"

static bool isInUserCode(BaseAST* node) {
  if (ModuleSymbol* mod = node->getModule()) {
    return mod->modTag == MOD_USER;
  }
  return false;
}

static bool fnCanHaveContext(FnSymbol* fn) {
  // TODO make sure it is not cobegin ?
  return (fn->hasFlag(FLAG_COBEGIN_OR_COFORALL) ||
          fn->hasFlag(FLAG_ON)) &&
         fn->singleInvocation() != NULL;

}

static void CONTEXT_DEBUG(int indent, std::string msg, BaseAST* node) {
  if (fReportContextAdj) {
    for(int i=0 ; i<indent ; i++) {
      std::cout << " ";
    }
    std::cout << "[" << node->id << "] " << msg << std::endl;
  }
}

class Context {
  public:
  Symbol* localHandle_ = NULL;

  // TODO we can probably populate the bottom two together
  std::vector<CallExpr*> localHandleAutoDestroys_;
  Expr* endOfLocalHandleSetup_ = NULL;
  Expr* upEndCount_ = NULL;

  // this'll need to be differentiated between LoopContext and IteratorContext
  // when we have a proper syntax. The current implementation is more suitable
  // for IteratorContext
  bool findLoopContextHandle() {
    const int debugDepth = 1;
    std::vector<DefExpr*> defExprs;
    collectDefExprs(this->node(), defExprs);

    for_vector (DefExpr, def, defExprs) {
      //CONTEXT_DEBUG(debugDepth+1, "looking at DefExpr", def);

      if (defExprIsLocalHandle(def)) {
        if (localHandle_ == NULL) {
          CONTEXT_DEBUG(debugDepth+2, "found a context handle", def->sym);
          localHandle_ = def->sym;
        }
        else {
          // For now, ignore other context handles. Slight challenge: the innermost
          // coforall_fn also contains the loop in question. So when trying to
          // find the coforall_fn's context handles, we should avoid looking at
          // loop's.

          //CONTEXT_DEBUG(debugDepth+2, "found another context handle?", def->sym);
          //INT_FATAL("found another context handle?");
        }
      }
    }

    return localHandle_ != NULL;
  }

  void collectLocalHandleAutoDestroys() {
    std::vector<CallExpr*> calls;
    collectCallExprs(this->node(), calls);

    for_vector(CallExpr, call, calls) {
      if (FnSymbol* fn = call->resolvedFunction()) {
        if (fn->hasFlag(FLAG_AUTO_DESTROY_FN)) {
          if (toSymExpr(call->get(1))->symbol() == localHandle_) {
            this->localHandleAutoDestroys_.push_back(call);
          }
        }
      }
    }
  }

  std::vector<CallExpr*>& getLocalHandleAutoDestroys() {
    if (localHandleAutoDestroys_.size() == 0) {
      collectLocalHandleAutoDestroys();
    }
    return localHandleAutoDestroys_;
  }

  Expr* getEndOfLocalHandleSetup() {
    if (endOfLocalHandleSetup_ == NULL) {
      // probably can iterate over the body
      std::vector<CallExpr*> calls;
      collectCallExprs(this->node(), calls);

      for_vector (CallExpr, call, calls) {
        if (call->isPrimitive(PRIM_MOVE)) {
          if (Symbol* lhs = toSymExpr(call->get(1))->symbol()) {
            if (lhs == localHandle_) {
              endOfLocalHandleSetup_ = call;
              break;
            }
          }
        }
      }
    }

    return endOfLocalHandleSetup_;
  }

  Expr* getUpEndCount() {
    if (upEndCount_ == NULL) {
      std::vector<CallExpr*> calls;
      collectCallExprs(this->node(), calls);

      for_vector (CallExpr, call, calls) {
        if (call->isNamed("_upEndCount")) {
          upEndCount_ = call;
          break;
        }
      }
    }
    return upEndCount_;
  }

  virtual BaseAST* node() = 0;
  virtual bool defExprIsLocalHandle(DefExpr* def) = 0;

};

class LoopContext: public Context {
  public:
  CForLoop* loop_;
  LoopContext(CForLoop* loop): loop_(loop) {}

  BaseAST* node() override { return loop_; };

  bool defExprIsLocalHandle(DefExpr* def) override {
    if (isArgSymbol(def->sym)) return false;

    return !def->sym->hasFlag(FLAG_TEMP) &&
           def->sym->hasFlag(FLAG_INDEX_VAR) &&
           def->sym->getValType()->symbol->hasFlag(FLAG_CONTEXT_TYPE);
  }


};

class IteratorContext: public Context {
  public:
  FnSymbol* fn_;
  CallExpr* callToInner_ = NULL;
  CForLoop* callToInnerLoop_ = NULL;

  IteratorContext(FnSymbol* fn): fn_(fn) {}

  BaseAST* node() override { return fn_; };

  bool defExprIsLocalHandle(DefExpr* def) override {
    if (isArgSymbol(def->sym)) return false;

    return !def->sym->hasFlag(FLAG_TEMP) &&
           !isLabelSymbol(def->sym) &&
           !def->sym->hasFlag(FLAG_INDEX_VAR) && // avoid re-finding loop's
           !def->sym->hasFlag(FLAG_EPILOGUE_LABEL) && // same as !isLabelSymbol?
           def->sym->getValType()->symbol->hasFlag(FLAG_CONTEXT_TYPE);
  }

  Expr* getInsertBeforeCallToInnerAnchor() {
    if (callToInnerLoop_) {
      return callToInnerLoop_;
    }
    else {
      return callToInner_;
    }
  }
};


class ContextHandler {
  public:
  LoopContext loopCtx_;
  std::vector<IteratorContext> contextStack_;

  // map between any handle used within user's loop body and the indices to
  // contexts within contextStack 
  std::map<Symbol*, int> handleMap_;

  ContextHandler(CForLoop* loop): loopCtx_(loop) {
    const int debugDepth = 1;


    CONTEXT_DEBUG(debugDepth, "looking for the handle", loop);
    if (loopCtx_.findLoopContextHandle()) {
      CONTEXT_DEBUG(debugDepth+1, "found loop context handle", loopCtx_.localHandle_);

      CONTEXT_DEBUG(debugDepth, "collecting context chain", loop);

      if (this->collectOuterContexts()) { }
      else {
        CONTEXT_DEBUG(debugDepth, "couldn't find any context chain", loop);
      }
    }
    else {
      CONTEXT_DEBUG(debugDepth+1, "couldn't find context handle", loop);
    }
  }

  bool collectOuterContexts() {
    const int debugDepth = 2;

    Expr* cur = this->loop();
    CallExpr* callToCurCtx = NULL;
    while (FnSymbol* parentFn = toFnSymbol(cur->parentSymbol)) {
      if (fnCanHaveContext(parentFn)) {
        CONTEXT_DEBUG(debugDepth, "found a candidate parent", parentFn);

        IteratorContext outerCtx(parentFn);
        outerCtx.callToInner_ = callToCurCtx;

        Expr* curParent = callToCurCtx;
        while (curParent) {
          if (CForLoop* loop = toCForLoop(curParent)) {
            outerCtx.callToInnerLoop_ = loop;
            break;
          }
          curParent = curParent->parentExpr;
        }


        if (!outerCtx.findLoopContextHandle()) break;

        contextStack_.push_back(outerCtx);
        cur = callToCurCtx = parentFn->singleInvocation();

      }
      else {
        break;
      }
    }

    return contextStack_.size() > 0;
  }

  void dumpOuterContexts() {
    int debugDepth = 3;
    CONTEXT_DEBUG(debugDepth, "found the following context chain:", this->loop());
    for (auto i = contextStack_.begin() ; i != contextStack_.end() ; i++) {
      std::string msg = "";
      if (i->fn_->hasFlag(FLAG_ON)) {
        msg += "on function with handle ";
      }
      else if (i->fn_->hasFlag(FLAG_COBEGIN_OR_COFORALL)) {
        msg += "coforall function with handle ";
      }
      msg += "[" + std::to_string(i->localHandle_->id) + "]";

      CONTEXT_DEBUG(++debugDepth, msg, i->fn_);
    }
  }

  CForLoop* loop() { return toCForLoop(this->loopCtx_.loop_); }
  Symbol* loopHandle() { return this->loopCtx_.localHandle_; }

  void removeHoistToContextCall(CallExpr* call) {
    call->remove();
  }

  void removeOuterContextCallAndInitShadowHandle(CallExpr* call,
                                                 Symbol* symToSet) {
    INT_ASSERT(symToSet);

    if (CallExpr* parent = toCallExpr(call->parentExpr)) {
      // TODO this may be a little too reckless. At least do some INT_ASSERTS
      Symbol* lhs = toSymExpr(parent->get(1))->symbol();

      parent->remove();
      std::vector<SymExpr*> symExprs;
      collectSymExprsFor(loop(), lhs, symExprs);

      for_vector (SymExpr, symExpr, symExprs) {
        if (CallExpr* call = toCallExpr(symExpr->parentExpr)) {
          if (call->isNamed(astrInitEquals) || // do we need init=?
              call->isPrimitive(PRIM_MOVE)) {
            symExpr->replace(new SymExpr(symToSet));
            continue;
          }
        }
        symExpr->parentExpr->remove();
      }

      lhs->defPoint->remove();
    }
    call->remove();
  }

  Symbol* handleOuterContextCall(CallExpr* call) {
    const int debugDepth = 4;

    Symbol* outerCtxHandle = NULL;
    //
    // TODO better/less fragile pattern matching?
    CallExpr* parentCall = toCallExpr(call->parentExpr);
    INT_ASSERT(parentCall);
    INT_ASSERT(parentCall->isPrimitive(PRIM_MOVE));

    SymExpr* lhsSe = toSymExpr(parentCall->get(1));
    Symbol* lhs = lhsSe->symbol();

    DefExpr* nextDef = toDefExpr(parentCall->next);
    INT_ASSERT(nextDef);

    outerCtxHandle = nextDef->sym;
    if (call->numActuals() == 1) {
      INT_ASSERT(outerCtxHandle->getValType() ==
                 this->loopCtx_.localHandle_->getValType());
    }
    else {
      INT_ASSERT(call->numActuals() == 2);
      INT_ASSERT(outerCtxHandle->getValType() == call->get(1)->getValType());
    }

    CallExpr* callAfterDef = toCallExpr(nextDef->next);
    INT_ASSERT(callAfterDef);
    INT_ASSERT(callAfterDef->isNamed(astrInitEquals) ||
               callAfterDef->isPrimitive(PRIM_MOVE));
    INT_ASSERT(toSymExpr(callAfterDef->get(1))->symbol() == outerCtxHandle);
    INT_ASSERT(toSymExpr(callAfterDef->get(2))->symbol() == lhs);

    CONTEXT_DEBUG(debugDepth, "found an outer context handle",
                  outerCtxHandle);
    INT_ASSERT(handleMap_.count(outerCtxHandle) == 0);

    int outerCtxIdx = -1;
    Symbol* argToCall = toSymExpr(call->argList.last())->symbol();

    if (argToCall == this->loopHandle()) {
      // immediate outer context
      outerCtxIdx = 0;
    }
    else {
      // farther away context
      int j=0;
      for (auto i=contextStack_.begin() ; i!=contextStack_.end() ;
           i++, j++) {
        if (this->handleMap_[argToCall] == j) {
          outerCtxIdx = j+1;
          break;
        }
      }
    }

    handleMap_[outerCtxHandle] = outerCtxIdx;

    CONTEXT_DEBUG(debugDepth+1,
                  "mapped to ["+std::to_string(contextStack_[outerCtxIdx].localHandle_->id)+"]",
                  outerCtxHandle);

    // TODO refactor this into a common helper
    SET_LINENO(nextDef);
    int curAdjustmentIdx = outerCtxIdx;
    Symbol* handle = contextStack_[curAdjustmentIdx].localHandle_;

    ArgSymbol* formal = NULL;
    while (CallExpr* toAdjust = contextStack_[curAdjustmentIdx].callToInner_) {
      toAdjust->insertAtTail(new SymExpr(handle));
      // TODO this is probably the right intent for now. But maybe we want
      // `const ref`?
      formal = new ArgSymbol(INTENT_CONST_IN, handle->name, handle->getValType());
      toAdjust->resolvedFunction()->insertFormalAtTail(formal);

      curAdjustmentIdx--;
      handle = formal;
    }

    Symbol* symToSet = formal!=NULL ? formal : handle;
    removeOuterContextCallAndInitShadowHandle(call, symToSet);

    return outerCtxHandle;
  }

  void handleHoistToContextCall(CallExpr* call) {
    const int debugDepth = 3;

    Symbol* handle = toSymExpr(call->get(1))->symbol();
    int targetCtxIdx = handleMap_[handle];
    IteratorContext* target = &(contextStack_[targetCtxIdx]);
    Symbol* targetHandle = target->localHandle_;
    std::vector<CallExpr*>& autoDestroyAnchors =
        target->getLocalHandleAutoDestroys();
    Symbol* sym = toSymExpr(call->get(2))->symbol();

    bool isBarrier = astr(sym->type->symbol->name) == astr("Barrier");
    if (isBarrier) {
      CONTEXT_DEBUG(debugDepth, "this is a barrier", sym);
    }
    else {
      CONTEXT_DEBUG(debugDepth, "this is an array", sym);
    }

    CONTEXT_DEBUG(debugDepth, "will hoist to ["+std::to_string(target->localHandle_->id)+"]",
                  call);


    // TODO cache this stuff somewhere, but we remove some below. Is that a problem?
    std::vector<CallExpr*> callsInLoop;
    collectCallExprs(this->loop(), callsInLoop);
    std::map<Symbol*, std::vector<CallExpr*>> autoDestroysInLoop;
    for_vector (CallExpr, call, callsInLoop) {
      if (FnSymbol* fn = call->resolvedFunction()) {
        if (fn->hasFlag(FLAG_AUTO_DESTROY_FN)) {
          Symbol* sym = toSymExpr(call->get(1))->symbol();
          autoDestroysInLoop[sym].push_back(call);
        }
      }
    }

    // in the prototype we assume that the primitive comes right after the array
    // defPoint in source and everything in between in the AST needs to be
    // hoisted. With better syntax, things will surely change here. It might be
    // more complicated, though.
    DefExpr* def = sym->defPoint;
    Expr* defPrev = def->prev;

    if (BlockStmt* parentBlock = toBlockStmt(call->parentExpr)) {
      if (parentBlock->length() == 1) {
        parentBlock->flattenAndRemove();
      }
      else if (parentBlock->prev == def) {
        parentBlock->flattenAndRemove();
      }
    }

    SET_LINENO(def);


    // if we are using local shadows of target contexts' handle, we'll need to
    // update the symbol to use what's local in the target
    SymbolMap handleUpdateMap;
    handleUpdateMap.put(handle, targetHandle);

    BlockStmt* mulBlock = NULL; // only meaningful if isBarrier
    Expr* cur = call->prev;
    FnSymbol* parentFn = toFnSymbol(call->parentSymbol);
    INT_ASSERT(parentFn);

    std::map<Symbol*, int> outerActuals;

    while (cur != defPrev) {
      if (DefExpr* defExpr = toDefExpr(cur)) {
        Symbol* sym = defExpr->sym;
        std::vector<CallExpr*>& symsAutoDestroys = autoDestroysInLoop[sym];

        if (symsAutoDestroys.size() > 0) {
          // put auto destroys in all the right places
          for_vector (CallExpr, anchor, autoDestroyAnchors) {
            anchor->insertBefore(symsAutoDestroys[0]->copy());
          }
          // remove all the existing ones
          for_vector (CallExpr, autoDestroy, symsAutoDestroys) {
            autoDestroy->remove();
          }
        }
      }

      update_symbols(cur, &handleUpdateMap);

      // keep track of indices of ArgSymbols here that we are hoisting. They'll
      // need to be updated in that given context. Or we need to error if the
      // user hoisted things way too far.

      std::vector<SymExpr*> symExprsInCur; // why can't I just collect symbols?
      collectSymExprs(cur, symExprsInCur);
      for_vector (SymExpr, symExpr, symExprsInCur) {
        Symbol* sym = symExpr->symbol();

        if (outerActuals.count(sym) == 1) continue;

        if (ArgSymbol* argSym = toArgSymbol(sym)) {
          int formalIdx = findFormalIndex(parentFn, argSym);
          if (formalIdx >= 0) {
            CONTEXT_DEBUG(debugDepth+1,
                          "found a formal at idx " + std::to_string(formalIdx),
                          argSym);

            outerActuals[argSym] = formalIdx;
          }
          else {
            INT_FATAL("how come?");
          }
        }
      }

      if (isBarrier) {
        if (BlockStmt* curBlock = toBlockStmt(cur)) {
          mulBlock = curBlock;
          CONTEXT_DEBUG(debugDepth+1, "found multiply block", mulBlock);
        }
      }

      targetHandle->defPoint->insertAfter(cur->remove());

      cur = call->prev;
    }

    // we have some symbols declared elsewhere in the block that we are hoisting 
    // walk up the context stack to the target to find where they are
    SymbolMap newContextUpdateMap;
    for (auto outerActualToIdx = outerActuals.begin() ;
         outerActualToIdx != outerActuals.end() ; outerActualToIdx++) {

      int actualIdx = outerActualToIdx->second;
      Symbol* curActual = NULL;

      for (int i = 1 ; i <= targetCtxIdx ; i++) {

        if (actualIdx == -1) {
          // we are currently looking for a symbol that was defined in an inner
          // context. IOW, the user wants to hoist a block that has a symbol,
          // to a block where the symbol wasn't defined yet. This is a user
          // error.
          USR_FATAL("Attempt to hoist symbols from an inner context to an outer context");
        }

        // what is the symbol used in this scope?
        curActual = toSymExpr(contextStack_[i].callToInner_->get(actualIdx))->symbol();

        // is it also an argument here?
        if (ArgSymbol* curFormal = toArgSymbol(curActual)) {
          int formalIdx = findFormalIndex(contextStack_[i].fn_, curFormal);
          if (formalIdx >= 0) {
            CONTEXT_DEBUG(debugDepth+2,
                          "which is actually the formal at idx " + std::to_string(formalIdx),
                          curFormal);

            actualIdx = formalIdx; // update to this function's formal idx
          }
          else {
            INT_FATAL("how come?");
          }
        }
        else {
          CONTEXT_DEBUG(debugDepth+2,
                        "which is this symbol",
                        curActual);

          actualIdx = -1; // signal that this variable is local here
        }
      }

      newContextUpdateMap.put(outerActualToIdx->first, curActual);
    }

    std::string hoistedName = "hoisted_" + std::string(sym->name);

    Symbol* refToSym = new VarSymbol(hoistedName.c_str(), sym->getRefType());
    DefExpr* refToSymDef = new DefExpr(refToSym);
    CallExpr* setRef = new CallExpr(PRIM_MOVE, refToSym, new CallExpr(PRIM_ADDR_OF, sym));

    target->getInsertBeforeCallToInnerAnchor()->insertBefore(refToSymDef);
    target->getInsertBeforeCallToInnerAnchor()->insertBefore(setRef);

    // we want to use the last added formal after the loop to adjust the loop
    // body
    ArgSymbol* formal = NULL; // should probably be refToSym

    for (int curCtx = targetCtxIdx ; curCtx >= 0 ; curCtx--) {
      IteratorContext& ctx = contextStack_[curCtx];

      if (CallExpr* toAdjust = ctx.callToInner_) {
        toAdjust->insertAtTail(new SymExpr(refToSym));

        formal = new ArgSymbol(INTENT_REF, hoistedName.c_str(), sym->getRefType());
        toAdjust->resolvedFunction()->insertFormalAtTail(formal);
      }

      if (isBarrier) {
        INT_ASSERT(mulBlock);

        Expr* upEndCount = ctx.getUpEndCount();
        if (upEndCount) {
          CONTEXT_DEBUG(debugDepth+1, "multiply block will be inserted after here", upEndCount);
          Symbol* numTasks = toSymExpr(toCallExpr(upEndCount)->get(2))->symbol();

          CallExpr* mulCall = toCallExpr(mulBlock->body.last()->copy());
          INT_ASSERT(mulCall);
          INT_ASSERT(mulCall->isNamed("multiply"));

          mulCall->get(1)->replace(new SymExpr(refToSym));
          mulCall->get(2)->replace(new SymExpr(numTasks));

          ctx.getInsertBeforeCallToInnerAnchor()->insertBefore(mulCall);
        }
      }

      refToSym = formal;
    }

    removeHoistToContextCall(call);

    SymbolMap updateMap;
    updateMap.put(sym, formal);

    update_symbols(loop(), &updateMap);
    update_symbols(target->node(), &newContextUpdateMap);
  }

  void handleContextUsesWithinLoopBody() {
    std::vector<Symbol*> handles;
    handles.push_back(this->loopHandle());

    std::vector<Symbol*>::size_type curIdx = 0;
    while (curIdx < handles.size()) {
      const int debugDepth = 1;
      std::vector<SymExpr*> handleUses;

      collectSymExprsFor(this->loop(), handles[curIdx], handleUses);

      for_vector (SymExpr, use, handleUses) {
        if (CallExpr* call = toCallExpr(use->parentExpr)) {
          CONTEXT_DEBUG(debugDepth+1, "found a call that uses handle", call);

          if (call->isPrimitive(PRIM_OUTER_CONTEXT)) {
            CONTEXT_DEBUG(debugDepth+2, "PRIM_OUTER_CONTEXT", call);
            if (Symbol* newCtx = handleOuterContextCall(call)) {
              handles.push_back(newCtx);
            }
          }
          else if (call->isPrimitive(PRIM_HOIST_ARRAY_TO_CONTEXT)) {
            CONTEXT_DEBUG(debugDepth+2, "PRIM_HOIST_ARRAY_TO_CONTEXT", call);

            handleHoistToContextCall(call);
          }
        }
        else {
          CONTEXT_DEBUG(debugDepth, "illegal use of context handle", use);
          INT_FATAL("illegal use of context handle");
        }
      }

      curIdx++;
    }
  }

  int findFormalIndex(FnSymbol* fn, ArgSymbol* arg) {
    int ret = -1;

    int i = 1;
    for_formals (formal, fn) {
      if (formal == arg) {
        ret = i;
      }
      i++;
    }

    return ret;
  }

  void handleContextUsesWithinLoopBody(Symbol* handle) {
    const int debugDepth = 1;
    std::vector<SymExpr*> handleUses;
    collectSymExprsFor(this->loop(), handle, handleUses);

    for_vector (SymExpr, use, handleUses) {
      if (CallExpr* call = toCallExpr(use->parentExpr)) {
        CONTEXT_DEBUG(debugDepth+1, "found a call that uses handle", call);

        if (call->isPrimitive(PRIM_OUTER_CONTEXT)) {
          handleOuterContextCall(call);
        }
        else if (call->isPrimitive(PRIM_MOVE)) {
          CONTEXT_DEBUG(debugDepth+2, "ignoring call", call);
        }
        else {
          CONTEXT_DEBUG(debugDepth+2, "call is illegal", call);
          INT_FATAL("call is illegal");
        }
      }
      else {
        CONTEXT_DEBUG(debugDepth, "illegal use of context handle", use);
        INT_FATAL("illegal use of context handle");
      }
    }
  }
};


void lowerContexts() {
  forv_Vec(FnSymbol*, fn, gFnSymbols) {
    if (!isInUserCode(fn)) continue;

    // TODO do something lighter
    std::vector<BaseAST*> asts;
    collect_asts(fn, asts);

    for_vector(BaseAST, ast, asts) {
      if (CForLoop* loop = toCForLoop(ast)) {
        const int debugDepth = 0;

        CONTEXT_DEBUG(debugDepth, "encountered a C loop", loop);

        ContextHandler h(loop);

        h.dumpOuterContexts();

        h.handleContextUsesWithinLoopBody();
      }
    }
  }
}
