#!/bin/bash 
path1=/home/ubuntu/file_dir
path2=/home/ubuntu/dir_dir
if [ -d $path1 ]
then
	read -p "文件存在，是否要对目录清空[Y/N]" var
	if [ $var = Y ]
	then
		echo "开始清空目录"
		rm -rf "$path1"/*
	else
		echo "file_dir文件存在,未清空"
	fi 
else
	echo "开始创建目录"
	mkdir $path1
fi 
if [ -d $path2 ]
then
	read -p "是否要对目录清空[Y/N]" var2
	if [ $var2 = Y ]
	then
		echo "文件存在，开始清空目录"
		rm -rf "$path2"/*
	else
		echo "dir_dir文件存在,未清空"
	fi 
else
	echo "开始创建目录"
	mkdir $path2
fi
num1=0
num2=0
read -p "请输入目录文件路径: " file
if [ -d $file ]
then
	echo "目录文件存在"
	cd $file
	for target in `ls $file`
	do
		if [ -d $target ]
		then
			((num1++))
			cp -r $target /home/ubuntu/dir_dir
		else 
			((num2++))
			cp -r $target /home/ubuntu/file_dir
		fi
	done
	echo $num1,$num2
else
	echo "目录文件不存在"
fi



