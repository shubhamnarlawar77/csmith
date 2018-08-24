#!/bin/bash

set -e 
while [ true ]
do
bash second.sh
if [ $? -eq 0 ];then
	echo "call success "
	echo ""
	continue
fi

#might not be useful for now as we again called the shell script from the other file.
if [ $? -eq 2]; then
	echo "infinite handle \n"
	continue
fi

if [ $? -eq 3 ]; then
	echo "terminated \n"
	exit 1;
	
fi
done
