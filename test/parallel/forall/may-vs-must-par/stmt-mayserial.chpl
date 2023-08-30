// []-statement

use iters;
use datas;

writeln();

// Legend: the writeln() statements above the []-loops show:
//  first word:  the name of the iterator, implying the available varieties,
//  second word: which variety should be chosen.
// Ex: "SA standalone" => available: serial+SA; chosen: SA.
//  "par leader+followers" => available serial+SA+LF, chosen: LF.


/*--- iterators --- */

/////////// single iterable ///////////

writeln("ser serial");
[ IND in iter1ser() ]
  writeln("[ IND in iter1ser() ]");
showCountsI.locale;

writeln("SA standalone");
[ IND in iter1SA() ]
  writeln("[ IND in iter1SA() ]");
showCountsI.locale;

writeln("LF leader+follower");
[ IND in iter1LF() ]
  writeln("[ IND in iter1LF() ]");
showCountsI.locale;

writeln("par standalone");
[ IND in iter1par() ]
  writeln("[ IND in iter1par() ]");
showCountsI.locale;

/////////// zippered ///////////

// bug: compiler crashes
//writeln("ser serial");
//[ IND in zip(iter1ser(), iter2ser()) ]
//  writeln("[ IND in zip(iter1ser(), iter2ser()) ]");
//showCountsI;

// bug: compiler crashes
//writeln("SA leader");
//[ IND in zip(iter1SA(), iter2SA()) ]
//  writeln("[ IND in zip(iter1SA(), iter2SA()) ]");
//showCountsI;

writeln("LF leader+followers");
[ IND in zip(iter1LF(), iter2LF()) ]
  writeln("[ IND in zip(iter1LF(), iter2LF()) ]");
showCountsI.locale;

writeln("par leader+followers");
[ IND in zip(iter1par(), iter2par()) ]
  writeln("[ IND in zip(iter1par(), iter2par()) ]");
showCountsI.locale;


/*--- datatypes --- */

/////////// single iterable ///////////

writeln("ser serial");
[ IND in inst1ser ]
  writeln("[ IND in inst1ser ]");
showCountsD.locale;

writeln("SA standalone");
[ IND in inst1SA ]
  writeln("[ IND in inst1SA ]");
showCountsD.locale;

writeln("LF leader+follower");
[ IND in inst1LF ]
  writeln("[ IND in inst1LF ]");
showCountsD.locale;

writeln("par standalone");
[ IND in inst1par ]
  writeln("[ IND in inst1par ]");
showCountsD.locale;

/////////// zippered ///////////

// bug: compiler crashes
//writeln("ser serial");
//[ IND in zip(inst1ser.borrow(), inst2ser.borrow()) ]
//  writeln("[ IND in zip(inst1ser, inst2ser) ]");
//showCountsD;

// bug: compiler crashes
//writeln("SA serial");
//[ IND in zip(inst1SA.borrow(), inst2SA.borrow()) ]
//  writeln("[ IND in zip(inst1SA, inst2SA) ]");
//showCountsD;

writeln("LF leader+followers");
[ IND in zip(inst1LF.borrow(), inst2LF.borrow()) ]
  writeln("[ IND in zip(inst1LF, inst2LF) ]");
showCountsD.locale;

writeln("par leader+followers");
[ IND in zip(inst1par.borrow(), inst2par.borrow()) ]
  writeln("[ IND in zip(inst1par, inst2par) ]");
showCountsD.locale;
