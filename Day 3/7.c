#include <stdio.h>
int main(int argc, const char *argv[])
{
	int m, n, sum;



	printf("请输入要购买的上衣数量： ");
	scanf("%d", &m);
	printf("请输入要购买的裤子数量： ");
	scanf("%d", &n);

	if ((m >= 0) && (n >= 0))
	{
	if (m >= n)
	{
		sum = n * 120 + (m - n) * 45;
	}
	else
	{
		sum = m * 120 + (n - m) * 90;
	}
	}
	printf("一共需要花%d元\n", sum);

	return 0;
}
