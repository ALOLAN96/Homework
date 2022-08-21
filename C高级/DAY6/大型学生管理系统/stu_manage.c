#include "stu.h"
int main(int argc, const char *argv[])
{
	char order;
	help();
	while (1)
	{
		printf("请输入命令=");
		scanf(" %c", &order);
		switch (order)
		{
		case 'H':
			help();
			break;
		case 'T':
			if (n == 0)
				type();
			else
				add();
			break;
		case 'A':
			if (n == 0)
				puts("成绩表为空！请先使用命令T录入学生成绩。");
			else
				average();
			break;
		case 'L':
			if (n == 0)
				puts("成绩表为空！请先使用命令T录入学生成绩。");
			else
				list();
			break;
		case 'P':
			if (n == 0)
				puts("成绩表为空！请先使用命令T录入学生成绩。");
			else
				sort();
			break;
		case 'S':
			if (n == 0)
				puts("成绩表为空！请先使用命令T录入学生成绩。");
			else
				search();
			break;
		case 'C':
			system("clear");
			break;
		case 'Q':
			exit(1);
		}
		getchar(); //用scanf输入字符时，会同时把回车接受到，放在
				   //缓存区中，执行下次while循环时，会打印两次输出语句，
				   //所以使用getcahr来接收垃圾字符
	}

	return 0;
}
