#include <stdio.h>

int main(int argc, const char *argv[])
{
	int num;

	printf("Please enter a number: ");
	scanf("%d", &num);


	if (num % 2 == 0)
	{
		if (num == 0)
		{
			printf("此数为偶数");
		}
		else 
		{
		if (num % 10 == 0)
		{
			printf("偶数它也是10的倍数\n");
		}
		else
		{
			printf("偶数它不是10的倍数\n");
		}
	}
	}
	else
	{
		printf("此数为奇数");
			if (num % 5 == 0)
			{
				printf("它也是5的倍数\n");
			}
		else
		{
			printf("它不是5的倍数\n");
		}
	}



	return 0;
}
