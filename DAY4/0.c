#include <stdio.h>

int main(int argc, const char *argv[])
{
	int sum = 0;
	for (int i = 1; i < 100; i +=2)
	{
		if ((i % 5 == 0) || (i % 7 ==0))
		{
			sum += i;
		}
	}
	printf("Sum is %d\n", sum);


	return 0;
}
