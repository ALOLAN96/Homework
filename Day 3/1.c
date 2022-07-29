#include <stdio.h>

int main(int argc, const char *argv[])
{
	int score;


	printf("Please enter your grades: ");
	scanf("%d", &score);

	if ((score < 0) || (score > 100))
	{
		printf("Input value out of range.\n");
	}
	else
	{
		if (score >= 90)
		{
			printf("A\n");
		}
		else if (score >= 80)
		{
			printf("B\n");
		}
		else if (score >= 70)
		{
			printf("C\n");
		}
		else if (score >= 60)
		{
			printf("D\n");
		}
		else
		{
			printf("不及格\n");
		}
	}


	return 0;
}
