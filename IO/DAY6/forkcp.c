#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct msg
{
	int res_r;
	int res_w;
	off_t size;
};

void *callBack_end(void *arg)
{
	struct msg *ptr = (struct msg *)arg;
	int res_r = ptr->res_r;
	int res_w = ptr->res_w;
	off_t size = ptr->size;

	pthread_mutex_lock(&mutex); //上锁

	lseek(res_r, size / 2, SEEK_SET); //先将原文件偏移到中间位置
	lseek(res_w, size / 2, SEEK_SET); //将待复制文件偏移到同样位置
	for (size_t i = size / 2; i < size; i++)
	{
		char temp = 0;
		size_t res_read = read(res_r, &temp, 1);
		if (-1 == res_read)
		{
			perror("read");
			return NULL;
		}
		size_t res_write = write(res_w, &temp, 1);
		if (-1 == res_write)
		{
			perror("write");
			return NULL;
		}
	}
	printf("后半部分打印完毕\n");
	pthread_mutex_unlock(&mutex);//解锁
	pthread_exit(NULL);
}

void *callBack_tail(void *arg)
{
	struct msg *ptr = (struct msg *)arg;
	int res_r = ptr->res_r;
	int res_w = ptr->res_w;
	off_t size = ptr->size;

	pthread_mutex_lock(&mutex);//上锁

	lseek(res_w, 0, SEEK_SET);
	lseek(res_r, 0, SEEK_SET);
	for (size_t i = 0; i < size / 2; i++)
	{
		char temp = 0;
		size_t res_read = read(res_r, &temp, 1);
		if (-1 == res_read)
		{
			perror("read");
			return NULL;
		}
		size_t res_write = write(res_w, &temp, 1);
		if (-1 == res_write)
		{
			perror("write");
			return NULL;
		}
	}
	printf("前半部分复制完成\n");
	pthread_mutex_unlock(&mutex);//解锁
	pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
	int res_r = open("./preview.jpg", O_RDONLY);
	int res_w = open("./112233.jpg", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	off_t size = lseek(res_r, 0, SEEK_END);

	struct msg fileinfo;
	fileinfo.res_r = res_r;
	fileinfo.res_w = res_w;
	fileinfo.size = size;

	pthread_t peda, pedb;
	pthread_create(&peda, NULL, callBack_tail, &fileinfo);
	pthread_create(&pedb, NULL, callBack_end, &fileinfo);

	pthread_join(peda, NULL);
	pthread_join(pedb, NULL);
	close(res_r);
	close(res_w);
	pthread_mutex_destroy(&mutex);

	printf("打印结束\n");
	return 0;
}
