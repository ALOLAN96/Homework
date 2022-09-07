#include <stdio.h>
#include <string.h>
#define ERR_MSG(msg)              \
	{                             \
		printf("%d\n", __LINE__); \
		perror(msg);              \
	}

int main(int argc, const char *argv[])
{
	char str2[20] = "";
	char str3[20] = "";
	char arr[20], brr[20];

	printf("请输入用户名: ");
	gets(arr);
	printf("请输入密码: ");
	gets(brr);

	FILE *fp = fopen("./usr.txt", "r");
	if (NULL == fp)
	{
		ERR_MSG("fopen");
		return -1;
	}

	fscanf(fp, "%s", str2);
	fscanf(fp, "%s", str3);

	fclose(fp);//不要忘记拿到数据后关闭文件

	if (strcmp(str2, arr) == 0)
	{
		if (strcmp(str3, brr) == 0)
		{
			printf("登录成功\n");
			return 0;
		}
		else
		{
			printf("密码错误\n");
			return -2;
		}
	}
	else
	{
		printf("用户不存在\n");
		return -3;
	}
}
