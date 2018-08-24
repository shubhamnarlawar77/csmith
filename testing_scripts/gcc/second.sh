#!/bin/bash
../../src/./csmith --computed-goto > ../../runtime/gcc_checksum.c
cd ../../runtime
gcc -w -O0 gcc_checksum.c
timeout 10s ./a.out
if [ $? -eq 124 ];then  #if output goes in an infinite loop,then again regenerate the code
	cd ../testing_scripts/gcc
	bash output_checksum_check.sh
fi
var0=$(./a.out)

gcc -w -O1 gcc_checksum.c
#timeout 10s ./a.out
var1=$(./a.out)

gcc -w -O2 gcc_checksum.c
#timeout 10s ./a.out
var2=$(./a.out)

gcc -w -O3 gcc_checksum.c
#timeout 10s ./a.out
var3=$(./a.out)

gcc -w -Ofast gcc_checksum.c
#timeout 10s ./a.out
varfast=$(./a.out)

gcc -w -Os gcc_checksum.c
#timeout 10s ./a.out
vars=$(./a.out)

if [[ $var0 == $var1 &&  $var0 == $var2 && $var0 == $var3 && $var0 == $varfast && $var0 == $vars ]]; then
	echo "check correct"
	exit 0
else
	echo "check wrong"
	exit 3
fi
