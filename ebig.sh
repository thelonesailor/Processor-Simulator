#!/bin/bash
for i in {3..6};
do
	echo "Big Test case $i";
	pow=1;
	for ((j=0, pow=1; j<i; j++)); do ((pow *= 10)); done
	time ./processor_simulator Tests/$pow.hex test$i.svg results$i.txt <Tests/step$i
	echo "-----------------";
done;
