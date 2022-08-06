#include <stdio.h>

int main(int argc, const char *argv[])
{
	char str[30] = "";

	gets(str);

	for (int i = 0; str[i] != '\0'; i ++)
	{
		if (str[i] == ' ')
		{
			i ++;
		}
		printf("%c",str[i]);
	}
	printf("\n");
	return 0;
}
