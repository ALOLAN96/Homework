#include <stdio.h>

int main(int argc, const char *argv[])
{
	char str1[30] = "";
	char str2[30] = "";
	int length1 = 0;
	int length2 = 0;

	printf("请输入第一个字符串: ");
	gets(str1);
	printf("请输入第二个字符串: ");
	gets(str2);

	for (int i = 0; str1[i] != '\0'; i++)
	{
		length1 ++;
	}
	for (int i = 0; str2[i] != '\0'; i ++)
	{
		length2 ++;
	}
	for (int i = 0; i < length2; i ++)
	{
		str1[length1 + i] = str2[i];
	}
	printf("%s\n",str1);



	return 0;
}
