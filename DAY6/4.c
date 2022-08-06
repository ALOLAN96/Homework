#include <stdio.h>

int main(int argc, const char *argv[])
{
	char str[30] = " ";
	char a;
	int count = 0;
	printf("请输入一串字符串: ");
	gets(str);
	printf("请输入一个字符: ");
	scanf("%c", &a);


	for (int i = 0; str[i] != '\0'; i ++)
	{
		if (str[i] == a)
		{
			count ++;
		}
	}
	printf("输入的字符串中%c的个数为:%d", a, count);

	return 0;
}
