#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, const char *argv[])
{
	// 1.1创建子进程
	pid_t PID = fork();

	// 1.2创建孤儿进程 父进程退出，子进程死循环
	if (0 == PID)
	{
		// 2.改变子进程的会话组
		pid_t sid = setsid();
		if (sid < 0)//回参判断
		{
			perror("setsid");
			return -1;
		}
		printf("sid = %d\n", sid);

		// 3.修改子进程的依赖路径
		chdir("/");

		// 4.重设文件权限掩码
		umask(0);

		//关闭所有文件描述符
		for (int i = 0; i < 1024; i++)
		{
			close(i);
		}

		while (1)
		{
			sleep(1);
		}
	}
	else if (PID > 0)
	{
	}
	else if (PID < 0)
	{
		perror("fork");
		return -1;
	}
	return 0;
}