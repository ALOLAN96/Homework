#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char temp;

//互斥锁初始化
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//条件变量初始化
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

//条件变量 0 打印 1 读文件
int flag = 1;

struct file
{
	int fd;
};

void *callBack_printf(void *arg) //再打印
{
	while (1)
	{
		//上锁
		pthread_mutex_lock(&mutex);
		if (0 != flag)
		{
			pthread_cond_wait(&cond, &mutex);
		}

		int res_write = write(1, &temp, 1);
		
		if (-1 == res_write)
		{
			perror("write");
			return NULL;
		}
		if (temp == 0)
		{
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
			break;
		}

		flag = 1;
		temp = 0;

		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}
void *callBack_read(void *arg) //先读
{
	struct file *ptr = (struct file *)arg;
	int fd = ptr->fd;

	while (1)
	{
		pthread_mutex_lock(&mutex);

		if (1 != flag)
		{
			pthread_cond_wait(&cond, &mutex);
		}
		int res_read = read(fd, &temp, 1);
		if (0 == res_read)
		{
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
			flag = 0;
			break;
		}
		
		flag = 0;

		//唤醒睡在cond上的线程
		pthread_cond_signal(&cond);

		//解锁
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}
int main(int argc, const char *argv[])
{
	char arr[20] = "";
	printf("请输入想要打印的文件名： ");
	scanf("%s", arr);

	int fd = open(arr, O_RDONLY);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}

	struct file info;
	info.fd = fd;

	//创建两进程，1.打印 2.读文件
	pthread_t thd_print, thd_read;
	if (pthread_create(&thd_print, NULL, callBack_printf, &info) != 0)
	{
		perror("pthread_create");
		return -1;
	}
	if (pthread_create(&thd_read, NULL, callBack_read, &info) != 0)
	{
		perror("pthread_create");
		return -1;
	}
	pthread_join(thd_print, NULL);
	pthread_join(thd_read, NULL);

	int res_close = close(fd);
	if (-1 == res_close)
	{
		perror("close");
		return -1;
	}

	printf("打印结束\n");
	//销毁互斥锁
	int res;
	if ((res = pthread_mutex_destroy(&mutex)) != 0)
	{
		perror("pthread_mutex_destroy");
		printf("%d\n",res);
		return -1;
	}

	//销毁条件变量
	if (pthread_cond_destroy(&cond) != 0)
	{
		perror("pthread_cond_destroy");
		return -1;
	}
}
