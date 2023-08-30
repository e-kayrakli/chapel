// promoted expression

// The current code does not exercise the case
// where the result of the promoted expression is used.
// This is to avoid an additional dimension in the tests
// and because the compiler code paths being tested
// do not depend on used vs. not used.

// Legend: the writeln() statements above the promoted expressions show:
//  first word:  the name of the iterator, implying the available varieties,
//  second word: which variety should be chosen.
// Ex: "SA serial" => available: serial+SA; chosen: serial.
//  "par leader+followers" => available serial+SA+LF, chosen: LF.

use iters;
use datas;

proc KAM(arg1: int, arg2: int) { writeln("mul=", arg1*arg2); }
proc KAP(arg1: int, arg2: int) { writeln("sum=", arg1+arg2); }

writeln();


/*--- iterators --- */

/////////// single iterable ///////////

writeln("ser serial");
KAM(iter1ser(),0);
showCountsI.locale;

writeln("SA standalone"); // bug: standalone iter is ignored by promotion
KAM(iter1SA(),0);
showCountsI.locale;

writeln("LF leader+follower");
KAM(iter1LF(),0);
showCountsI.locale;

writeln("par standalone"); // bug: standalone iter is ignored by promotion
KAM(iter1par(),0);
showCountsI.locale;

/////////// zippered ///////////

writeln("ser serial");
KAP(iter1ser(), iter2ser());
showCountsI.locale;

writeln("SA serial");
KAP(iter1SA(), iter2SA());
showCountsI.locale;

writeln("LF leader+followers");
KAP(iter1LF(), iter2LF());
showCountsI.locale;

writeln("par leader+followers");
KAP(iter1par(), iter2par());
showCountsI.locale;


/*--- datatypes --- */

/////////// single iterable ///////////

writeln("ser serial");
KAM(inst1ser.borrow(),0);
showCountsD.locale;

writeln("SA standalone"); // bug: standalone iter is ignored by promotion
KAM(inst1SA.borrow(),0);
showCountsD.locale;

writeln("LF leader+follower");
KAM(inst1LF.borrow(),0);
showCountsD.locale;

writeln("par standalone"); // bug: standalone iter is ignored by promotion
KAM(inst1par.borrow(),0);
showCountsD.locale;

/////////// zippered ///////////

writeln("ser serial");
KAP(inst1ser.borrow(), inst2ser.borrow());
showCountsD.locale;

writeln("SA serial");
KAP(inst1SA.borrow(), inst2SA.borrow());
showCountsD.locale;

writeln("LF leader+followers");
KAP(inst1LF.borrow(), inst2LF.borrow());
showCountsD.locale;

writeln("par leader+followers");
KAP(inst1par.borrow(), inst2par.borrow());
showCountsD.locale;
