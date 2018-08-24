#!/bin/bash
../../src/./csmith --computed-goto > ../../runtime/llvm_checksum.c
cd ../../runtime
clang -w -O0 llvm_checksum.c
timeout 10s ./a.out
if [ $? -eq 124 ];then  #if output goes in an infinite loop,then again regenerate the code
	cd ../testing_scripts/llvm
	bash llvm_output_checksum_check.sh
fi
var0=$(./a.out)

clang -w -O1 llvm_checksum.c
#timeout 10s ./a.out
var1=$(./a.out)

clang -w -O2 llvm_checksum.c
#timeout 10s ./a.out
var2=$(./a.out)

clang -w -O3 llvm_checksum.c
#timeout 10s ./a.out
var3=$(./a.out)

clang -w -Ofast llvm_checksum.c
#timeout 10s ./a.out
varfast=$(./a.out)

clang -w -Os llvm_checksum.c
#timeout 10s ./a.out
vars=$(./a.out)

if [[ $var0 == $var1 &&  $var0 == $var2 && $var0 == $var3 && $var0 == $varfast && $var0 == $vars ]]; then
	echo "check correct"
	exit 0
else
	echo "check wrong"
	exit 3
fi
