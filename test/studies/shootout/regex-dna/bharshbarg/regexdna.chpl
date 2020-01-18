/* The Computer Language Benchmarks Game
   http://benchmarksgame.alioth.debian.org/

   contributed by Ben Harshbarger
   derived from the GNU C++ RE2 version by Alexey Zolotov
*/
use IO;

use Regexp;

proc main(args: [] string) {
  var variants = [
    b"agggtaaa|tttaccct",
    b"[cgt]gggtaaa|tttaccc[acg]",
    b"a[act]ggtaaa|tttacc[agt]t",
    b"ag[act]gtaaa|tttac[agt]ct",
    b"agg[act]taaa|ttta[agt]cct",
    b"aggg[acg]aaa|ttt[cgt]ccct",
    b"agggt[cgt]aa|tt[acg]accct",
    b"agggta[cgt]a|t[acg]taccct",
    b"agggtaa[cgt]|[acg]ttaccct"
  ];

  var subst = [
    (b"B", b"(c|g|t)"), (b"D", b"(a|g|t)"), (b"H", b"(a|c|t)"), (b"K", b"(g|t)"),
    (b"M", b"(a|c)"), (b"N", b"(a|c|g|t)"), (b"R", b"(a|g)"), (b"S", b"(c|g)"),
    (b"V", b"(a|c|g)"), (b"W", b"(a|t)"), (b"Y", b"(c|t)")
  ];

  var data: bytes;
  stdin.readbytes(data); // read in the entire file
  const initLen = data.length;

  // remove newlines
  data = compile(b">.*\n|\n").sub(b"", data);

  var copy = data; // make a copy so we can perform replacements in parallel

  var results: [variants.domain] int;

  sync {
    // fire off a task to perform replacements
    begin with (ref copy) {
      for (f, r) in subst do
        copy = compile(f).sub(r, copy);
    }

    // count patterns
    forall (pattern, result) in zip(variants, results) do
      for m in compile(pattern).matches(data) do
        result += 1;
  }

  // print results
  for (p,r) in zip(variants, results) do
    writeln(p, " ", r);
  writeln();

  writeln(initLen);
  writeln(data.length);
  writeln(copy.length);
}
