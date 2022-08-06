#include <stdio.h>
int vaule(void);

int main(int argc, const char *argv[])
{
	int num;
	num = vaule();
	return 0;
}


int vaule(void)
{
	int count, sum;
	printf("请输入项数: ");
	scanf("%d", &count);
	int arr[count];
	arr[0] = 10;
	arr[1] = 15;
	sum = 0;

	for (int i = 0; i < count; i ++)
	{
		arr[i + 2] = arr[i] + arr[i + 1];
	}

	for (int i = 0; i < count; i ++)
	{
		sum += arr[i];
	}
	for (int i = 0; i < count; i ++)
	{
		printf("%-5d", arr[i]);
	}
	printf("SUM=%d\n", sum);
	return 1;

}
