#include <stdio.h>
int main(int argc, const char *argv[])
{
	int length, i;
	length = 0;
	char str[30] = " ";
	char temp;

	printf("请输入若干字符(以回车符为结束): ");

	gets(str);

	for (int i = 0; str[i] != '\0'; i ++)
	{
		length ++;
	}

	for (int i = 0; i < (length / 2); i ++)
	{
		temp = str [i];
		str[i] = str [length - i -1];
		str[length - i - 1] = temp;
	}

	/*for (i = 0; i < length; i++)
	{
		printf("%c",str[i]);
	}
	printf("\n");
    */
   printf("%s\n",str);


	return 0;
}
