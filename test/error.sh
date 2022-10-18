#!/bin/bash

for FILE in test_maps/error/*; do
	echo $FILE:
	.././lem-in < $FILE #> /dev/null 2>&1
	echo "--------------"
done
