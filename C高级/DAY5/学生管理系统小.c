#include <stdio.h>
#include <string.h>
#define MAX_PARTS 50

void insert(void);            //添加插入学生
void find_score(void);        //找到高分学生，并显示
void find_name(void);         //找学生
void sort(void);              //成绩降序打印

int num_parts = 0;            //当前存储的学生个数
struct Stu                    //定义结构体
{
	int numb;                 //学号
	char name[20];            //姓名
	double score;             //分数
} student[MAX_PARTS];         //定义结构体数组

int main(int argc, const char *argv[])
{
	for (;;)
	{
		int code;
		printf("请输入操作命令: ");
		scanf(" %d", &code);
		while (getchar() != '\n');
		switch (code)
		{
		case 1:
			insert();
			break;
		case 2:
			find_score();
			break;
		case 3:
			sort();
			break;
		case 4:
			find_name();
			break;
		case 5:
			return 0;
		default :printf("非法命令，请输入命令:1-5\n");
		}
		printf("\n");
	}
}


void insert(void)                 //添加插入学生
{
	int part_number = 0;          //需要存储的学生个数
	if (num_parts > MAX_PARTS)
	{
		printf("存储已满，无法添加学生.\n");
		return;
	}
	printf("当前已存储%d个学生\n", num_parts);
	printf("请输入需要添加的学生个数: ");
	scanf("%d", &part_number);

	for (int i = 0; i < part_number; i ++)
	{
		printf("请输入第%d个学生的学号: ", i + 1);
		scanf("%d", &student[num_parts + i].numb);
		printf("请输入第%d个学生的姓名: ", i + 1);
		scanf("%s", student[num_parts + i].name);
		printf("请输入第%d个学生的成绩: ", i + 1);
		scanf("%lf", &student[num_parts + i].score);
	}
		num_parts += part_number;

}
void find_score(void)            //找到高分学生，并显示
{	
	printf("当前已存储%d个学生\n", num_parts);
	struct Stu max = student[0];
	for (int i = 0; i < num_parts; i ++)
	{
		if (student[i].score > max.score)
		{
			max = student[i];
		}
	}
	printf("成绩最高的学生:学号:%d\t姓名:%s\t成绩:%.2lf\n", max.numb, max.name, max.score);
}
void find_name(void)                       //找学生
{
	printf("当前已存储%d个学生\n", num_parts);
	char arr[20];
	printf("请输入需要查找的姓名: ");
	gets(arr);
	int flag = 0;
	int search = 0;
	for (int i = 0; i < num_parts; i ++)
	{
		if (strcmp(arr,student[i].name) == 0)
		{
			flag = 1;
			search = i;
			break;
		}
	}
	if (flag == 1)
	{
		printf("该班存在该学生,删除中...\n");
		while (search <= num_parts - 1)
		{
			student[search] = student[search + 1];
			search ++;
		}
		num_parts = num_parts - 1;
		printf("删除完成\n");
		for (int i = 0; i < num_parts; i ++)
		{
			printf("学号:%d\t姓名:%s\t成绩:%.2lf\n", student[i].numb, student[i].name, student[i].score);
		}
	}
	else
	{
		printf("该班不存在该学生\n");
	}
}
void sort(void)                         //成绩降序打印
{
	printf("当前已存储%d个学生\n", num_parts);
	//选择排列
	for (int i = 0; i < num_parts - 1; i ++)
	{
		int index = i;
		for (int j = i + 1; j < num_parts; j ++)
		{
			if(student[index].score < student[j].score)
			{
				index = j;
			}
		}
		if (index != i)
		{
			struct Stu temp = student[i];
			student[i] = student[index];
			student[index] = temp;
		}
	}
	//输出
		for (int i = 0; i < num_parts; i ++)
		{
			printf("学号:%d\t姓名:%s\t成绩:%.2lf\n", student[i].numb, student[i].name, student[i].score);	
		}
}

