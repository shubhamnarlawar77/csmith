#!/bin/sh
set -e
mkdir stats;
i=0
while [ true ]
do
 ../../src/./csmith --computed-goto --typeof > ../../runtime/computed_typeof.c;
 ../../src/./csmith --uint128 --int128 --computed-goto > ../../runtime/int128_goto.c;
 ../../src/./csmith --computed-goto --loc-labels > ../../runtime/goto_local_labels.c;
 ../../src/./csmith --typeof --int128 --uint128 > ../../runtime/typeof_int128.c;
 ../../src/./csmith --typeof --loc-labels > ../../runtime/typeof_loc_labels.c;
 
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/computed_typeof.c &> stats/computed_typeof.txt ;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/int128_goto.c &> stats/int128_goto.txt;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/goto_local_labels.c &> stats/goto_local_labels.txt;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/typeof_int128.c &> stats/typeof_int128.txt;
  gcc -I/home/lab/Downloads/csmith-gcc-extensions/runtime  ../../runtime/typeof_loc_labels.c &> stats/typeof_loc_labels.txt;
  
  i=$((i+1))
  echo $i&>stats/count.txt
  echo $i
done


