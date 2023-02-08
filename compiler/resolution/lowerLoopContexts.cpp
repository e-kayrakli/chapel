
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
  std::vector<CallExpr*> localHandleAutoDestroys_;

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

  virtual BaseAST* node() = 0;
  virtual bool defExprIsLocalHandle(DefExpr* def) = 0;

};

class LoopContext: public Context {
  public:
  CForLoop* loop_;
  LoopContext(CForLoop* loop): loop_(loop) {}

  BaseAST* node() override { return loop_; };

  bool defExprIsLocalHandle(DefExpr* def) override {
    return !def->sym->hasFlag(FLAG_TEMP) &&
           def->sym->hasFlag(FLAG_INDEX_VAR) &&
           def->sym->getValType()->symbol->hasFlag(FLAG_CONTEXT_TYPE);
  }


};

class IteratorContext: public Context {
  public:
  FnSymbol* fn_;
  CallExpr* callToInner_ = NULL;

  IteratorContext(FnSymbol* fn): fn_(fn) {}

  BaseAST* node() override { return fn_; };

  bool defExprIsLocalHandle(DefExpr* def) override {
    return !def->sym->hasFlag(FLAG_TEMP) &&
           !isLabelSymbol(def->sym) &&
           !def->sym->hasFlag(FLAG_INDEX_VAR) && // avoid re-finding loop's
           !def->sym->hasFlag(FLAG_EPILOGUE_LABEL) && // same as !isLabelSymbol?
           def->sym->getValType()->symbol->hasFlag(FLAG_CONTEXT_TYPE);
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

  void removeHoistArrayToContextCall(CallExpr* call) {
    call->remove();
  }

  void removeOuterContextCallAndInitShadowHandle(CallExpr* call,
                                                 ArgSymbol* formal) {
    if (CallExpr* parent = toCallExpr(call->parentExpr)) {
      // TODO this may be a little too reckless. At least do some INT_ASSERTS
      Symbol* lhs = toSymExpr(parent->get(1))->symbol();

      parent->remove();
      std::vector<SymExpr*> symExprs;
      collectSymExprsFor(loop(), lhs, symExprs);

      for_vector (SymExpr, symExpr, symExprs) {
        if (formal != NULL) {
          if (CallExpr* call = toCallExpr(symExpr->parentExpr)) {
            if (call->isNamed(astrInitEquals) || // do we need init=?
                call->isPrimitive(PRIM_MOVE)) {
              symExpr->replace(new SymExpr(formal));
              continue;
            }
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
    INT_ASSERT(outerCtxHandle->getValType() ==
               this->loopCtx_.localHandle_->getValType());

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
    Symbol* argToCall = toSymExpr(call->get(1))->symbol();

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

    removeOuterContextCallAndInitShadowHandle(call, formal);

    return outerCtxHandle;
  }

  void handleHoistArrayToContextCall(CallExpr* call) {
    const int debugDepth = 3;

    Symbol* handle = toSymExpr(call->get(1))->symbol();
    int targetCtxIdx = handleMap_[handle];
    IteratorContext* target = &(contextStack_[targetCtxIdx]);
    Symbol* targetHandle = target->localHandle_;
    std::vector<CallExpr*>& autoDestroyAnchors =
        target->getLocalHandleAutoDestroys();

    CONTEXT_DEBUG(debugDepth, "will hoist to ["+std::to_string(target->localHandle_->id)+"]",
                  call);

    // flatten the call block if it only contains this call -- this helps with
    // controlling the behavior with config param. Nothing deep, probably won't
    // need after we have the proper syntax
    if (BlockStmt* parentBlock = toBlockStmt(call->parentExpr)) {
      if (parentBlock->length() == 1) {
        parentBlock->flattenAndRemove();
      }
    }

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

    Symbol* arrSym = toSymExpr(call->get(2))->symbol();
    DefExpr* arrDef = arrSym->defPoint;
    Expr* arrDefPrev = arrDef->prev;

    SET_LINENO(arrDef);

    Expr* cur = call->prev;
    while (cur != arrDefPrev) {
      if (DefExpr* defExpr = toDefExpr(cur)) {
        Symbol* sym = defExpr->sym;
        std::vector<CallExpr*>& symsAutoDestroys = autoDestroysInLoop[sym];

        if (symsAutoDestroys.size() > 0) {
          for_vector (CallExpr, anchor, autoDestroyAnchors) {
            anchor->insertBefore(symsAutoDestroys[0]->copy());
          }
          for_vector (CallExpr, autoDestroy, symsAutoDestroys) {
            autoDestroy->remove();
          }
        }
      }

      targetHandle->defPoint->insertAfter(cur->remove());

      cur = call->prev;
    }

    std::string hoistedName = "hoisted_" + std::string(arrSym->name);

    Symbol* refToArr = new VarSymbol(hoistedName.c_str(), arrSym->getRefType());
    DefExpr* refToArrDef = new DefExpr(refToArr);
    CallExpr* setRef = new CallExpr(PRIM_MOVE, refToArr, new CallExpr(PRIM_ADDR_OF, arrSym));

    target->callToInner_->insertBefore(refToArrDef);
    target->callToInner_->insertBefore(setRef);

    int curAdjustmentIdx = targetCtxIdx;
    //CallExpr* toAdjust = target->callToInner_;

    // we want to use the last added formal after the loop to adjust the loop
    // body
    ArgSymbol* formal = NULL;
    while (CallExpr* toAdjust = contextStack_[curAdjustmentIdx].callToInner_) {
      toAdjust->insertAtTail(new SymExpr(refToArr));

      formal = new ArgSymbol(INTENT_REF, hoistedName.c_str(), arrSym->getRefType());
      toAdjust->resolvedFunction()->insertFormalAtTail(formal);



      curAdjustmentIdx--;
      refToArr = formal;
    }

    removeHoistArrayToContextCall(call);

    SymbolMap updateMap;
    updateMap.put(arrSym, formal);

    update_symbols(loop(), &updateMap);
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

            handleHoistArrayToContextCall(call);
          }
          else if (call->isPrimitive(PRIM_MOVE) ||
                   call->isNamed(astrInitEquals) ||
                   call->resolvedFunction()->hasFlag(FLAG_AUTO_DESTROY_FN)) {
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

      curIdx++;
    }
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
