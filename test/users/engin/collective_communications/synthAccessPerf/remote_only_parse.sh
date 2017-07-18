#! /bin/sh

echo Base
echo --------------------
grep Time out/remote_only.0* | cut -d" " -f3
echo
echo Prefetch
echo --------------------
grep Time out/remote_only.1* | cut -d" " -f3
