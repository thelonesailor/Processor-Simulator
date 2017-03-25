#!/bin/bash
for i in {1..1};
do
	echo "Test case $i";
	./processor_simulator in$i.hex test$i.svg results$i.txt 
	echo "---------------";
done;
