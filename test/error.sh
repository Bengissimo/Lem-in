#!/bin/bash

for FILE in test_maps/error/*; do
	echo $FILE:
	.././lem-in < $FILE
	echo "--------------"
done
