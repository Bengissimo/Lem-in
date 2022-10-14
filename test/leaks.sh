#!/bin/bash

#add system("leaks lem-in >> leaks.txt") before return in main
#add system("leaks lem-in >> error_leaks.txt") before exit(1)

.././lem-in < test_maps/is_shortest_way > /dev/null 2>&1

wait

for FILE in test_maps/error/*; do
	echo $FILE:
	.././lem-in < $FILE > /dev/null 2>&1
	echo "--------------"
done

wait

cat leaks.txt | grep "leaked bytes"
cat error_leaks.txt | grep "leaked bytes"