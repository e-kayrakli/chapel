on here.getChild(1) {
  var a: [1..10] int; // allocated on UM

  forall elem in a { // will run on GPU
    elem = 2;
  }
}


// this is what happens today:
var a: [1..10] int; // not allocated on UM

on here.getChild(1) {
  forall elem in a { // will run on GPU  -- segfault
    elem = 2;
  }
}
// **** we can make this work if everything is allocated on the UM ****



// or:
var a: [1..10] int; // will be on host memory

on here.getChild(1) {  // could also be `on Locales[1]`
  forall elem in a { // will run on GPU
    elem = 2;  // element-by-element comm between host and the device
  }
}
// we can make this work by communicating elems 1-by-1

// or:
var a: [1..10] int; // will be on host memory
// 0x100 on locale 0.

on Locales[1] {
  forall elem in a { // will run on GPU
    elem = 2;  // element-by-element comm between host and the device
  }
}

elem = { locid = 0, addr=0x100 }
elem = { locid = 0, sublocid=0, addr=0x100 }
