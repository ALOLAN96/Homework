#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, const char *argv[])
{
	pid_t PID = fork();

	if (PID == 0)
	{
		printf("子进程已退出\n");
		return 0;
	}
	else if (PID > 0)
	{
		while (1);
	}
	else if (PID < 0)
	{
		perror("fork");
		return 0;
	}
	return 0;
}
