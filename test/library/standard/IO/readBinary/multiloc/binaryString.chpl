use IO;

on Locales[0] {
    var reader = openReader("./input.bin");

    on Locales[1] {
        var s: string = string.createWithNewBuffer("");

        on Locales[2] {
            reader.readBinary(s, 40);
            write(s);
        }
    }
}
