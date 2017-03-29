#!/bin/bash
for i in {1..5};
do
	echo "Test case $i";
	./processor_simulator Testcases/testcase$i/in$i.hex test$i.svg results$i.txt 
	echo "---------------";
done;
