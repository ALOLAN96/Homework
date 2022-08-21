#include "stu.h"
extern int n; //总人数
STU st[N];

//******帮助菜单*******
void help()
{
	printf("**************************************\n");
	printf("*     学生成绩管理系统--帮助菜单     *\n");
	printf("**************************************\n");
	printf("*        H = 显示帮助菜单            *\n");
	printf("*        T = 成绩录入                *\n");
	printf("*        A = 计算学生平均成绩        *\n");
	printf("*        L = 列出成绩表              *\n");
	printf("*        P = 按平均成绩由高到低排序  *\n");
	printf("*        S = 按学号查询学生成绩      *\n");
	printf("*        C = 清屏                    *\n");
	printf("*        Q = 退出系统                *\n");
	printf("**************************************\n");
}
//*****成绩录入*******
void type()
{
	printf("请输入学生人数：");
	scanf("%d", &n); //总人数
	printf("请输入%d名学生的三门课成绩:\n", n);
	printf("学号	语文	数学	外语\n");

	for (int i = 1; i <= n; i++)
	{
		st[i - 1].num = i;
		printf("%d	 ", st[i - 1].num);
		scanf("%f	%f	%f", &st[i - 1].score[0], &st[i - 1].score[1], &st[i - 1].score[2]);
	}
	printf("成绩录入完成\n");
}

//*****列出成绩******
void list()
{
	printf("学号 语文 数学 外语 平均成绩\n");
	for (int i = 1; i <= n; i++)
	{
		printf("%d	 ", st[i - 1].num);
		printf("%.2f	%.2f	%.2f	%.2f\n", st[i - 1].score[0], st[i - 1].score[1], st[i - 1].score[2], st[i - 1].ave);
	}
}
//*****求出平均值******
void average()
{
	for (int i = 1; i <= n; i++)
	{
		st[i - 1].ave = (st[i - 1].score[0] + st[i - 1].score[1] + st[i - 1].score[2]) / 3;
	}
	printf("学生平均分计算完成\n");
	printf("学号 语文 数学 外语 平均成绩\n");
	for (int i = 1; i <= n; i++)
	{
		printf("%d	 ", st[i - 1].num);
		printf("%.2f	%.2f	%.2f	%.2f\n", st[i - 1].score[0], st[i - 1].score[1], st[i - 1].score[2], st[i - 1].ave);
	}
}
//*****按平均分从高到低排序*****
void sort()
{
	STU temp;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n - i; j++)
		{
			if (st[j].ave < st[j + 1].ave)
			{
				temp = st[j];
				st[j] = st[j + 1];
				st[j + 1] = temp;
			}
		}
	}
	printf("排序完成\n");
	printf("学号 语文 数学 外语 平均成绩\n");
	for (int i = 1; i <= n; i++)
	{
		printf("%d	 ", st[i - 1].num);
		printf("%.2f	%.2f	%.2f	%.2f\n", st[i - 1].score[0], st[i - 1].score[1], st[i - 1].score[2], st[i - 1].ave);
	}
}
//*****按学号查询******
void search()
{
	int search_num, flag;
	flag = 0;
	printf("输入需要查找的学号： ");
	scanf("%d", &search_num);
	for (int i = 1; i <= n; i++)
	{
		if (st[i - 1].num == search_num)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		printf("已找到该学生,正在打印成绩\n");
		printf("学号 语文 数学 外语 平均成绩\n");
		printf("%d	 ", st[search_num - 1].num);
		printf("%.2f	%.2f	%.2f	%.2f\n", st[search_num - 1].score[0], st[search_num - 1].score[1], st[search_num - 1].score[2], st[search_num - 1].ave);
	}
	else
	{
		printf("未找到该学生\n");
	}
}
//*****新增学生的成绩录入******
void add()
{
	int add_num;
	printf("请输入新增学生人数：");
	scanf("%d", &add_num); //单次更新人数
	printf("请输入%d名学生的三门课成绩:\n", add_num);
	printf("学号	语文	数学	外语\n");

	for (int i = n; i < n + add_num; i++)
	{
		st[i].num = i + 1;
		printf("%d	 ", st[i].num);
		scanf("%f	%f	%f", &st[i].score[0], &st[i].score[1], &st[i].score[2]);
	}
	n += add_num;
	printf("新增学生成绩录入完成\n");
}
