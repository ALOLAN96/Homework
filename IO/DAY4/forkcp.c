#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, const char *argv[])
{
	int res_r = open("./code.png", O_RDONLY);
	int res_w = open("./haha.png", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (-1 == res_r)
	{
		perror("open_r");
		return -1;
	}
	if (-1 == res_w)
	{
		perror("open_w");
		return -1;
	}
	char temp;//中间搬运变量
	off_t pos_r = lseek(res_r, 0, SEEK_END);//先将原文件偏移到文件尾,计算出大小
	off_t pos_r_new = lseek(res_r, pos_r / 2, SEEK_SET);//从原文件头偏移到一半
	off_t pos_w = lseek(res_w, pos_r_new, SEEK_SET);//待复制文件移动到相同位置
	pid_t PID = fork();//创建子进程
	
	if (PID == 0)
	{
		while(1)
		{
			temp = 0;
			size_t res_read = read(res_r, &temp, 1);
			if (-1 == res_read)
			{
				perror("read35");
				return -1;
			}
			if (0 == res_read)
			{
				break;
			}
			size_t res_write = write(res_w, &temp, 1);
			if (-1 == res_write)
			{
				perror("write45");
				return -1;
			}
		}

	}
	else if (PID > 0)
	{
		sleep(3);
		lseek(res_w, 0, SEEK_SET);
		lseek(res_r, 0, SEEK_SET);
		for (int i = 0; i < pos_r_new; i++)
		{
			temp = 0;
			size_t res_read = read(res_r, &temp, 1);
			if (-1 == res_read)
			{
				perror("read59");
				return -1;
			}
			size_t res_write = write(res_w, &temp, 1);
			if (-1 == res_write)
			{
				perror("write65");
				return -1;
			}
		}	
	}
	else if (PID < 0)
	{
		perror("fork73");
		return -1;
	}

	printf("打印结束\n");
	close(res_r);
	close(res_w);
	return 0;
}
