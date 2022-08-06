#include <stdio.h>

int main(int argc, const char *argv[])
{
	for (int i = 1; i <= 5; i ++)        //控制行
	{
		for (int j = 4; j >= i; j --)    //控制列空格输出
		{
			printf(" ");
		}
		for (int k = 1; k <= i; k++)     //控制列左边的“*”的输出               //for (int k = 1; k <= 2 * i - 1; k ++)    奇数输出
		                                                                     //for (int k = 2; k <= 2 * i - 1; k ++)    奇数输出
		{
			printf("*");
		}
		for (int h = 2; h <= i; h++)     //控制列右边s的“*”的输出
		{
			printf("*");
		}
		printf("\n");
	}

	

	return 0;
}
