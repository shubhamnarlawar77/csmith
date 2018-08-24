#!/bin/sh
set -e
while [ true ]
do
  ../../src/./csmith --computed-goto > ../../runtime/clang_test.c;
  clang -I${CSMITH HOME}runtime -w ../../runtime/clang_test.c -o /dev/null;
done
