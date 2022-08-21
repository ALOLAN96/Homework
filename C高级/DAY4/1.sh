#!/bin/bash 
read -p "请输入一个整数:" num
sum=0
while [ $num -ne 0 ]
do
	((sum+=num))
	read -p "请输入一个整数:" num
done
echo SUM=$sum
