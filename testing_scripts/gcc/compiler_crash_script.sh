#!/bin/sh
set -e
while [ true ]
do
  ../../src/./csmith --computed-goto > ../../runtime/gcc_test.c;
  gcc -I${CSMITH HOME}/runtime -w ../../runtime/gcc_test.c -o /dev/null;
done
