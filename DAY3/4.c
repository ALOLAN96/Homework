#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a, b, c;

	printf("Please enter the length of the three sides of the triangle: ");
	scanf("%d %d %d", &a, &b, &c);


	if (a + b > c)
	{
		if ((a == b) && (b == c))
		{
			printf("此三角形为等边三角形\n");
		}
		else if ((a == b) || (b == c))
		{
			printf("此三角形为等腰三角行\n");
		}
		else 
		{
			printf("此三角形为普通三角形\n");
		}
	}





	return 0;
}
