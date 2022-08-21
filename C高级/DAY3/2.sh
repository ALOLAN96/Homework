#!/bin/bash 
arr=($*)
i=1
for((;i<=${#arr[*]}-1;i++))
	{
		cp ${arr[i]} $1
	}
