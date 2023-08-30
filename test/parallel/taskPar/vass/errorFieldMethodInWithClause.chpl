// see also field-in-task-ref-clause.chpl
// see also parallel/forall/vass/errorFieldMethodInWithClause.chpl

const ITER = 1..3;

class myClass {
  var myField = 5;
  proc myProcc do return 6;
}

proc ourProc { return 7; }
iter ourIter { yield 8; }

proc something {}

proc myClass.test {


  // forall testing moved to parallel/forall/vass


  cobegin with (in myField) {
    something.locale;
    something.locale;
  }
  cobegin with (in myProcc) {
    something.locale;
    something.locale;
  }
  cobegin with (ref ourProc, ref ourIter) {
    something.locale;
    something.locale;
  }

  coforall ITER with (in myField) do
    something.locale;
  coforall ITER with (in myProcc) do
    something.locale;
  coforall ITER with (ref ourProc, ref ourIter) do
    something.locale;

 sync {
  begin with (in myField)
    { something.locale;  }
  begin with (in myProcc)
    { something.locale;  }
  begin with (ref ourProc, ref ourIter)
    { something.locale;  }
 }
}

proc main {
  const mc = new owned myClass();
  mc.test;
}
