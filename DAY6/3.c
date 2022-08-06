#include <stdio.h>

int main(int argc, const char *argv[])
{
	char str1[30] = " ";
	char str2[30] = " ";
	int i;

	printf("请输入第一串字符串: ");
	gets(str1);
	printf("请输入第二串字符串: ");
	gets(str2);

	for (i = 0; str1[i] != '\0'; i ++)
	{
		printf("%c", str1[i]);
	}
	if (str1[i] == '\0')
	{
		puts(str2);
	}


	return 0;
}
