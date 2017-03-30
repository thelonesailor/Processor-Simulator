#!/bin/bash
for i in {6..1};
do
	echo "Test case $i";
	./processor_simulator Testcases/testcase$i/in$i.hex test$i.svg results$i.txt 
	diff Testcases/testcase$i/results.txt results$i.txt
	echo "---------------";
done;
