use Random;

config const nBytes = 1024;
config const useFactory = false;

// create bytes with random bytes
var randomStream = createRandomStream(eltType=uint(8));
var buf = c_malloc(uint(8), nBytes+1);
for i in 0..#nBytes {
  buf[i] = randomStream.getNext();
}
buf[nBytes] = 0;

const randomBytes = createBytesWithOwnedBuffer(buf, length=nBytes,
                                                    size=nBytes+1);

if randomBytes.length != nBytes {
  halt("Error creating bytes object with correct length");
}

var randomEscapedString: string;
try {
   randomEscapedString =
      if useFactory then
        createStringWithNewBuffer(buf, length=nBytes, size=nBytes+1,
                                  errors=decodePolicy.escape)
      else
        randomBytes.decode(errors=decodePolicy.escape);
}
catch e: DecodeError {
  halt("Unexpected decode error");
}
catch {
  halt("Unexpected error");
}

var randomUnescapedString =
randomEscapedString.encode(errors=encodePolicy.unescape);

// unescaped string must be equal to the initial `bytes`
var success = randomUnescapedString == randomBytes;
if success {
  writeln("I recovered non UTF8 bytes: ", success);
}
else {
  writeln("Initial Buffer");
  for i in 0..#nBytes {
    writef("Byte %i: %xu\n", i, buf[i]);
  }

  writeln("Escaped string");
  for i in 0..randomEscapedString.numBytes {
    writef("Byte %i: %xu\n", i, randomEscapedString.buff[i]);
  }

  writeln("Unescaped string");
  for i in 0..randomUnescapedString.numBytes {
    writef("Byte %i: %xu\n", i, randomUnescapedString.buff[i]);
  }

  writeln("Side-by-side bytes");
  for i in 0..randomUnescapedString.numBytes {
    writef("Byte %i: %xu %xu\n", i, buf[i], randomUnescapedString.buff[i]);
  }
}



