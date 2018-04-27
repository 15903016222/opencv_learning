#!/bin/sh
for files in `find svm/posPlate/train/ -name "*.jpg"`
do 
	echo "$files" >> posPlate.txt
done
for files in `find svm/negPlate/train/ -name "*.jpg"`
do 
	echo "$files" >> negPlate.txt
done
