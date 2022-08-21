#!/bin/bash 
arr=$(find *.c)
echo ${arr[*]}
i=0
for((;i<${#arr[*]};i++))
	{
		mv ${arr[i]} $1;
	}
	ls $1 -lh
