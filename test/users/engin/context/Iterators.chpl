module Iterators {

  config const taskPerLoc = 2;
  config const doDebug = false;

  proc debug(args...) {
    if doDebug then writeln((...args));
  }

  module SimpleOneDim {
    use Iterators;
    use ChapelContextSupport;


    iter simpleOneDim(n) {
      const iterRange = 0..<n;
      for i in iterRange do yield i;
    }

    iter simpleOneDim(param tag: iterKind, n) where tag==iterKind.leader {
      coforall l in Locales {
        var outerCtx = new Context();

        on l {
          var onCtx = new Context();
          const perLocSize = n/numLocales;
          const localeLow = l.id * perLocSize;
          const localeHigh = localeLow+perLocSize-1;

          debug(here, " ", localeLow, " " , localeHigh);

          coforall taskId in 0..<taskPerLoc {
            var innerCtx = new Context();

            const perTaskSize = perLocSize/taskPerLoc;
            const taskLow = localeLow+(taskId*perTaskSize);
            const taskHigh = taskLow+perTaskSize-1;

            debug(here, ":", taskId, " ", taskLow, " " , taskHigh);

            yield (taskLow..taskHigh, innerCtx);
          }
        }
      }
    }

    iter simpleOneDim(param tag: iterKind, n, followThis) where tag==iterKind.follower {
      for i in followThis[0] do yield (i, followThis[1]);
    }

  }
}
