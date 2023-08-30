config const cc1 = 111, cc2 = 222, cc3 = 333, cc4 = 1234;
proc wln { writeln(); }
var dummy = 0; proc dm { dummy += 1; }

iter helper() {
  yield 1;
  yield 2;
  yield 3;
}

/////////// yields reference different local symbols, no loop ///////////

// two local vars
iter it11nl() {
  var x = cc1;
  yield x;
  var y = cc2;
  yield y;
  x += cc2;
  yield cc4.locale; dm.locale;
  yield x;
  y += cc3;
  yield y;
}
for va11 in it11nl() do writeln("it11nl ", va11); // 111,222,333,555

// two local consts
iter it12nl() {
  const x = cc1;
  yield x.locale;  wln.locale;
  const y = cc2;
  yield y.locale;  wln.locale;
  yield cc4.locale; wln.locale;
  yield x.locale;  wln.locale;
  yield y.locale;  wln.locale;
}
for va12 in it12nl() do write("it12nl ", va12); // 111,222,111,222

// two const formals
iter it13nl(const in arg: int, const in oth: int) {
  dm.locale;
  yield arg.locale; wln.locale;
  yield oth.locale; wln.locale;
  yield cc4.locale; wln.locale;
  yield arg.locale; wln.locale;
  yield oth.locale; wln.locale;
}
for va13 in it13nl(1313,7777) do write("it13nl ", va13); // 1313,7777,1313,7777

// two var formals
iter it14nl(in arg: int, in oth: int) {
  dm.locale;
  yield arg.locale; wln.locale;
  yield oth.locale; wln.locale;
  arg += cc1;
  yield cc4.locale; wln.locale;
  yield arg.locale; wln.locale;
  oth += cc4;
  yield oth.locale; wln.locale;
}
for va14 in it14nl(1414,6666) do write("it14nl ", va14); // 1414,6666,1525,7900

// a local var and a formal
iter it15nl(in arg: int) {
  var x = cc1;
  yield x.locale;    wln.locale;
  yield arg.locale;  wln.locale;
  x += cc2;
  yield cc4.locale; wln.locale;
  yield x.locale;    wln.locale;
  arg += cc1;
  yield arg.locale;  wln.locale;
}
for va15 in it15nl(909) do write("it15nl ", va15); // 111,909,333,1020

// a local var and a formal plus their constant varieties
iter it16nl(in arg: int, const in oth: int) {
  var x = cc1;
  const y = cc2;
  yield x.locale;   wln.locale;
  yield arg.locale; wln.locale;
  yield cc4.locale; wln.locale;
  yield y.locale;   wln.locale;
  yield oth.locale; wln.locale;
  x += cc2;
  yield x.locale;   wln.locale;
  yield cc4.locale; wln.locale;
  arg += cc1;
  yield arg.locale; wln.locale;
  yield y.locale;   wln.locale;
  yield oth.locale; wln.locale;
}
for va16 in it16nl(909,77) do write("it16nl ", va16); // 111,909,222,77,333,1020,222,77

/////////// all yields reference different local symbols, in a loop

// two local vars
iter it11yl() {
  for lv11 in helper() {
    var x = cc1;
    yield x;
    var y = cc2;
    yield y;
    x += cc2;
    yield cc4.locale; dm.locale;
    yield x;
    y += cc3;
    yield y;
  }
}
for va11 in it11yl() do writeln("it11yl ", va11); // 111,222,333,555

// two local consts
iter it12yl() {
  for lv11 in helper() {
    const x = cc1;
    yield x.locale;  wln.locale;
    const y = cc2;
    yield y.locale;  wln.locale;
    yield cc4.locale; wln.locale;
    yield x.locale;  wln.locale;
    yield y.locale;  wln.locale;
  }
}
for va12 in it12yl() do write("it12yl ", va12); // 111,222,111,222

// two const formals
iter it13yl(const in arg: int, const in oth: int) {
  for lv11 in helper() {
    dm.locale;
    yield arg.locale; wln.locale;
    yield oth.locale; wln.locale;
    yield cc4.locale; wln.locale;
    yield arg.locale; wln.locale;
    yield oth.locale; wln.locale;
  }
}
for va13 in it13yl(1313,7777) do write("it13yl ", va13); // 1313,7777,1313,7777

// two var formals
iter it14yl(in arg: int, in oth: int) {
  for lv11 in helper() {
    dm.locale;
    yield arg.locale; wln.locale;
    yield oth.locale; wln.locale;
    arg += cc1;
    yield cc4.locale; wln.locale;
    yield arg.locale; wln.locale;
    oth += cc4;
    yield oth.locale; wln.locale;
  }
}
for va14 in it14yl(1414,6666) do write("it14yl ", va14); // 1414,6666,1525,7900

// a local var and a formal
iter it15yl(in arg: int) {
  for lv11 in helper() {
    var x = cc1;
    yield x.locale;    wln.locale;
    yield arg.locale;  wln.locale;
    x += cc2;
    yield cc4.locale; wln.locale;
    yield x.locale;    wln.locale;
    arg += cc1;
    yield arg.locale;  wln.locale;
  }
}
for va15 in it15yl(909) do write("it15yl ", va15); // 111,909,333,1020

// a local var and a formal plus their constant varieties
iter it16yl(in arg: int, const in oth: int) {
  for lv11 in helper() {
    var x = cc1;
    const y = cc2;
    yield x.locale;   wln.locale;
    yield arg.locale; wln.locale;
    yield cc4.locale; wln.locale;
    yield y.locale;   wln.locale;
    yield oth.locale; wln.locale;
    x += cc2;
    yield x.locale;   wln.locale;
    yield cc4.locale; wln.locale;
    arg += cc1;
    yield arg.locale; wln.locale;
    yield y.locale;   wln.locale;
    yield oth.locale; wln.locale;
  }
}
for va16 in it16yl(909,77) do write("it16yl ", va16); // 111,909,222,77,333,1020,222,77

/////////// like the above, but declarations outside the loop

// two local vars
iter it11zl() {
  var x = cc1;
  var y = cc2;
  for lv11 in helper() {
    dm.locale;
    yield x;
    dm.locale;
    yield y;
    x += cc2;
    yield cc4.locale; dm.locale;
    yield x;
    y += cc3;
    yield y;
  }
}
for va11 in it11zl() do writeln("it11zl ", va11); // 111,222,333,555

// two local consts
iter it12zl() {
  const x = cc1;
  const y = cc2;
  for lv11 in helper() {
    dm.locale;
    yield x.locale;  wln.locale;
    yield y.locale;  wln.locale;
    yield cc4.locale; wln.locale;
    yield x.locale;  wln.locale;
    yield y.locale;  wln.locale;
  }
}
for va12 in it12zl() do write("it12zl ", va12); // 111,222,111,222

// it13zl == it13yl
// it14zl == it14yl

// a local var and a formal
iter it15zl(in arg: int) {
  var x = cc1;
  for lv11 in helper() {
    dm.locale;
    yield x.locale;    wln.locale;
    yield arg.locale;  wln.locale;
    yield cc4.locale; wln.locale;
    x += cc2;
    yield x.locale;    wln.locale;
    arg += cc1;
    yield arg.locale;  wln.locale;
  }
}
for va15 in it15zl(909) do write("it15zl ", va15); // 111,909,333,1020

// a local var and a formal plus their constant varieties
iter it16zl(in arg: int, const in oth: int) {
  var x = cc1;
  const y = cc2;
  for lv11 in helper() {
    dm.locale;
    yield x.locale;   wln.locale;
    yield arg.locale; wln.locale;
    yield cc4.locale; wln.locale;
    yield y.locale;   wln.locale;
    yield oth.locale; wln.locale;
    x += cc2;
    yield cc4.locale; wln.locale;
    yield x.locale;   wln.locale;
    arg += cc1;
    yield arg.locale; wln.locale;
    yield y.locale;   wln.locale;
    yield oth.locale; wln.locale;
  }
}
for va16 in it16zl(909,77) do write("it16zl ", va16); // 111,909,222,77,333,1020,222,77
