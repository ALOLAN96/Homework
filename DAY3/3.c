#include <stdio.h>
int main(int argc, const char *argv[])
{
	int year;

	printf("Please enter a year: ");
	scanf("%d", &year);

	if (year == 0)
	{
		printf("抱歉,没有公元0年\n");
	}
	else
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				printf("闰年\n");
			}
		}
		else if (year % 4 == 0)
		{
			printf("闰年\n" );
		}
		else
		{
			printf("平年\n ");
		}
	}
	return 0;
}
