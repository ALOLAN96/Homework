#include <stdio.h>
#include <stdlib.h>
#define N 10
int n; //此处定义为总人数
typedef struct stu
{
	int num;
	float score[3];
	float ave;
} STU;
void help();
void type();
void list();
void average();
void sort();
void search();
void add();
