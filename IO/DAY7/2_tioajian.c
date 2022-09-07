#include <stdio.h>
#include <pthread.h>
//互斥锁初始化
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//条件变量初始化
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
int flag = 1;//1 : A  2 : B  3 : C 
int count1, count2, count3;
void *callBack_A(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if (1 != flag)
		{
			pthread_cond_wait(&cond3, &mutex);
		}
		printf("A");
		fflush(stdout);
		count1++;
		flag = 2;
		if (10 == count1)
		{
			pthread_cond_signal(&cond1);
			pthread_mutex_unlock(&mutex);

			break;
		}

		pthread_cond_signal(&cond1);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void *callBack_B(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if (2 != flag)
		{
			pthread_cond_wait(&cond1, &mutex);
		}
		printf("B");
		fflush(stdout);
		count2++;
		flag = 3;
		if (10 == count2)
		{
			pthread_cond_signal(&cond2);
			pthread_mutex_unlock(&mutex);
			break;

		}

		pthread_cond_signal(&cond2);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void *callBack_C(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if (3 != flag)
		{
			pthread_cond_wait(&cond2, &mutex);
		}
		printf("C");
		fflush(stdout);
		count3++;
		flag = 1;
		if (10 == count3)
		{
			pthread_cond_signal(&cond3);
			pthread_mutex_unlock(&mutex);
			break;

		}

		pthread_cond_signal(&cond3);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}
int main(int argc, const char *argv[])
{
	count1 = count2 = count3 = 0;
	pthread_t tid1, tid2, tid3;
	//创建3个进程
	int res1 = pthread_create(&tid1, NULL, callBack_A, NULL);
	if (0 != res1)
	{
		perror("pthread_create");
		return -1;
	}
	int res2 = pthread_create(&tid2, NULL, callBack_B, NULL);
	if (0 != res2)
	{
		perror("pthread_create");
		return -1;
	}
	int res3 = pthread_create(&tid3, NULL, callBack_C, NULL);
	if (0 != res3)
	{
		perror("pthread_create");
		return -1;
	}

	//等待关闭线程
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	printf("\n打印结束\n");
	//关闭条件

	return 0;
}
