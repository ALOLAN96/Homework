#include <stdio.h>


int main(int argc, const char *argv[])
{
	char a;
	int count1, count2;
	count1 = 0;
	count2 = 0;

	printf("Enter a string of characters: ");
	scanf("%c", &a);    //此处可以替代      

	while (a != '\n')   //while (getchar () != '\n')
	{
		if ((a >= 'a') && (a <= 'z'))
		{
			count1 ++;
		}
		else if ((a >= 'A') && (a <= 'Z'))
		{
			count2 ++;
		}
		scanf("%c", &a);             //此处可以替代
	}
	printf("小写字母个数为%d,大写字母个数为%d.\n", count1, count2);



	return 0;
}
