#include "fileprint.h"

int main(int argc, const char *argv[])
{
	printf("请输入要打印的目录路径： ");
	char str[20] = ""; //定义存储路径字符数组
	scanf("%s", str);

	DIR *dir = opendir(str); //打开目录
	if (NULL == dir)		 //回参判断
	{
		perror("opendir");
		return -1;
	}

	while (1)
	{
		struct dirent *file_info = readdir(dir);
		if (NULL == file_info)
		{
			if (0 == errno)
			{
				printf("----------------打印结束----------------\n");
				break;
			}
			else
			{
				perror("readdir");
				return -2;
			}
		}
		struct stat file_properties;
		char str2[20] = "";
		strcpy(str2, str);
		//使用sprintf
		// char str2[300] = "";
		// sprintf(str2, "%s%s", str, file_info->d_name)
		if (file_info->d_name[0] != '.')
		{
			strcat(str2, file_info->d_name); //使用注释语句，此处可以注释掉
			int file_res = stat(str2, &file_properties);
			if (-1 == file_res) //回参判断
			{
				perror("stat");
				return -1;
			}
			file_print(file_properties);
			file_name_print(file_info);
		}
	}

	int res_closedir = closedir(dir); //关闭目录
	if (-1 == res_closedir)			  //回参判断
	{
		perror("closedir");
		return -2;
	}
	return 0;
}
