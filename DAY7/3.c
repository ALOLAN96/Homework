#include <stdio.h>
int value(void);

int main(int argc, const char *argv[])
{
	int n, sum;
	sum = 0;
	n = value();
	int arr[n];
	arr[0] = 10;
	arr[1] = 15;

	for (int i = 0; i < n; i ++)
	{
		arr[i + 2] = arr [i] + arr [i + 1];
	}

	for (int i = 0; i < n; i ++)
	{
		printf("%-5d", arr[i]);
	}
	printf("\n");

	for (int i = 0; i < n; i ++)
	{
		sum += arr[i];
	}
	printf("数列%d的和是%d\n", n, sum);

	return 0;
}

int value(void)
{
	int count;
	printf("请输入项数: ");
	scanf("%d", &count);
	return count;
}
