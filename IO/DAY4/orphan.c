#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	pid_t PID = fork();
	if (0 == PID)
	{
		while (1);
	}
	else if (PID > 0)
	{
		printf("父进程已退出\n");
	}
	else if (PID < 0)
	{
		perror("fork");
		return -1;
	}
	return 0;
}
