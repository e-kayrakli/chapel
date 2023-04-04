use CTypes;

var cPtr = c_malloc(int, 4);

config param case = 1;

select case {
  when 1 do bytes.createWithBorrowedBuffer(cPtr, length=3, size=4);
  when 2 do bytes.createWithOwnedBuffer(cPtr, length=3, size=4);
  when 3 do bytes.createWithNewBuffer(cPtr, length=3, size=4);
}
