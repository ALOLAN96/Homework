#include <stdio.h>
int main(int argc, const char *argv[])
{
	char str1[30] = "";
	char str2[30] = "";
	int i, j;
	j = 0;

	printf("请输入一个字符串: ");
	gets(str1);

	for (i = 0; str1[i] != '\0'; i ++)
	{
		if (str1[i] != ' ')
		{
			str2[j] = str1[i];
			j ++;
		}
	}
	printf("%s\n", str2);
	return 0;
}
