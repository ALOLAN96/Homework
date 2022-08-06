#include <stdio.h>
int cum(int a);

int main(int argc, const char *argv[])
{
	int num;
	printf("请输入一个数: ");
	scanf("%d", &num);
	printf("1-%d的和为%d\n", num, cum(num));
	return 0;
}

int cum(int a)
{
	int sum = 0;
	for (int i = 1; i <= a; i ++)
	{
		sum += i; 
	}
	return sum;
}
