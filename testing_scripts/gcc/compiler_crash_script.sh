#!/bin/sh
set -e
mkdir stats;
i=0
while [ true ]
do
 ../../src/./csmith --int128 > ../../runtime/int128.c;
 ../../src/./csmith --uint128 > ../../runtime/uint128.c;
 ../../src/./csmith --typeof > ../../runtime/typeof.c;
 ../../src/./csmith --stmt_expr > ../../runtime/stmt_expr.c;
 ../../src/./csmith --computed-goto > ../../runtime/computed_goto.c;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/int128.c &> stats/int128.txt ;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/uint128.c &> stats/uint128.txt;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/typeof.c &> stats/typeof.txt;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/stmt_expr.c &> stats/stmt_expr.txt;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/computed_goto.c &> stats/computed_goto.txt;
  i=$((i+1))
  echo $i&>stats/count.txt
  echo $i
done


