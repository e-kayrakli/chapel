var r = 1..10;
writeln(r.boundsCheck(11..));
writeln(r.boundsCheck(11..1000));

writeln(r.boundsCheck(..0));
writeln(r.boundsCheck(-1000..0));
