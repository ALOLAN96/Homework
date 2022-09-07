#include <stdio.h>
#define ERR_MSG(msg)              \
	{                             \
		printf("%d\n", __LINE__); \
		perror(msg);              \
	}

int main(int argc, const char *argv[])
{
	FILE *fp_r = fopen("./1.txt", "r");
	FILE *fp_w = fopen("./2.txt", "w");

	if (NULL == fp_r)
	{
		ERR_MSG("fopen");
		return -1;
	}

	if (NULL == fp_w)
	{
		ERR_MSG("fopen");
		return -1;
	}

	while (1)
	{
		char a = fgetc(fp_r);
		if (EOF == a)
		{
			printf("复制完成\n");
			break;
		}
		fputc(a, fp_w);
	}
	return 0;
}
