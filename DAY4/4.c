#include <stdio.h>


int main(int argc, const char *argv[])
{
	int i, j, factor;


	for (i = 2; i <= 1000; i++)
	{
		factor = 0;                        //标志位置0；每次判断前必须要的操作
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				factor = 1;                //判断条件成立，表示找出因数，不为质数，标志位置1；
				                           //判断条件不成立，标志位为0，供给后面大循环判断；
			}
		}
		if (factor == 0)
		{
			printf("%d\n",i);
		}
	}
	return 0;
}
