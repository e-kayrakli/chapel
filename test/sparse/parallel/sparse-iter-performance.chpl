// This test times the various loops run as 'for' vs. 'forall'.

config var n = 1200000;

use Time;
var tm: stopwatch;

var d1: domain(1) = {1..n};
var d2: domain(2) = {1..n,1..n};

test(1, d1);
test(2, d2);
test(1, d1);
test(2, d2);
test(1, d1);
test(2, d2);

// main test driver

proc test(param dim:int, d: domain(dim)) {
  writeln("=== n=", n, " ", dim, "-d ===");
  // This is our sparse domain that everything will spin around.
  var sd: sparse subdomain(d);
  populateDomain(dim, sd);
//  writeln("sd(", dim, ") = ", sd);

  proc st      {
    tm.clear();
    tm.start();
  }
  proc fi(msg) {
    tm.stop();
    var ms = tm.elapsed() * 1000.0;
    writeln(msg, " : ", ms, " ms");
  }

  var A, B, C: [sd] int;
  var alpha = 10;

  st.locale; forall i in sd { A(i) = 10.locale; }
  fi("ix = const | par");

  st.locale; for    i in sd { B(i) = 20.locale; }
  fi("ix = const | seq");

  st.locale; forall a in A { a = 30.locale; }
  fi("ivar = const | par");

  st.locale; for    b in B { b = 40.locale; }
  fi("ivar = const | seq");

  st.locale; forall i in sd { C(i) = A(i) + alpha * B(i).locale; }
  fi("ix = ix, ix | par");

  st.locale; for    i in sd { A(i) = B(i) + alpha * C(i).locale; }
  fi("ix = ix, ix | seq");

  st.locale; forall (i,j,k) in zip(sd,sd,sd) { C(i) = A(j) + alpha * B(k).locale; }
  fi("ix1 = ix2, ix3 | par");

  st.locale; for    (i,j,k) in zip(sd,sd,sd) { A(i) = B(j) + alpha * C(k).locale; }
  fi("ix1 = ix2, ix3 | seq");

  st.locale; forall (a,b,c) in zip(A,B,C) { c = a + alpha * b.locale; }
  fi("ivar1 = ivar2, ivar3 | par");

  st.locale; for    (a,b,c) in zip(A,B,C) { a = b + alpha * c.locale; }
  fi("ivar1 = ivar2, ivar3 | seq");
}

proc populateDomain(param dim, ref sd) where dim == 1 {
  // for 1-D, use half of the values; domain members are not tuples
  for i in 1..n by 2 do sd += i;
}

proc populateDomain(param dim, ref sd) where dim > 1 {
  for i in 1..n-1 {
    var member: index(sd);
    for param dm in 0..dim-1 do member(dm) =
      // feeble attempt at something more sophisticated than just a diagonal
      if dm % 2 == 1 then i else i + 1;
    sd += member;
  }
}
