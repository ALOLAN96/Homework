#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2, sem3;
int count1, count2, count3;

void *callBack_A(void *arg)
{
	while (1)
	{
		// P sem1
		int res_wait = sem_wait(&sem1);
		if (-1 == res_wait)
		{
			perror("sem_wait");
			return NULL;
		}

		printf("A");
		fflush(stdout);
		count1 ++;
		if (10 == count1)
		{
			int res_post = sem_post(&sem2);
			if (-1 == res_post)
			{
				perror("sem_wait");
				return NULL;
			}
			break;
		}
		// V sem2
		int res_post = sem_post(&sem2);
		if (-1 == res_post)
		{
			perror("sem_wait");
			return NULL;
		}

	}
	pthread_exit(NULL);
}

void *callBack_B(void *arg)
{
	while (1)
	{
		// P sem2
		int res_wait = sem_wait(&sem2);
		if (-1 == res_wait)
		{
			perror("sem_wait");
			return NULL;
		}
		printf("B");
		fflush(stdout);
		count2 ++;
		if (10 == count2)
		{
			int res_post = sem_post(&sem3);
			if (-1 == res_post)
			{
				perror("sem_wait");
				return NULL;
			}

			break;
		}


		// V sem3
		int res_post = sem_post(&sem3);
		if (-1 == res_post)
		{
			perror("sem_wait");
			return NULL;
		}
	}
	pthread_exit(NULL);
}
void *callBack_C(void *arg)
{
	while (1)
	{
		// P sem3
		int res_wait = sem_wait(&sem3);
		if (-1 == res_wait)
		{
			perror("sem_wait");
			return NULL;
		}
		printf("C");
		fflush(stdout);
		count3++;
		if (10 == count3)
		{
			break;
		}

		// V sem1
		int res_post = sem_post(&sem1);
		if (-1 == res_post)
		{
			perror("sem_wait");
			return NULL;
		}
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

	int res_sem1 = sem_init(&sem1, 0, 1);
	if (-1 == res_sem1)
	{
		perror("sem_init");
		return -1;
	}
	int res_sem2 = sem_init(&sem2, 0, 0);
	if (-1 == res_sem2)
	{
		perror("sem_init");
		return -1;
	}
	int res_sem3 = sem_init(&sem3, 0, 0);
	if (-1 == res_sem3)
	{
		perror("sem_init");
		return -1;
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	printf("\n打印结束\n");
}
