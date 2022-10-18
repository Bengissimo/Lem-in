#!/bin/bash

echo "waiting for results..."

leaks -atExit -- .././lem-in < test_maps/is_shortest_way > /dev/null 2>&1 >> leaks.txt

for FILE in test_maps/error/*
do
	leaks -atExit -- .././lem-in < $FILE > /dev/null 2>&1 >> leaks.txt
done

wait

cat leaks.txt | grep "leaked bytes"
