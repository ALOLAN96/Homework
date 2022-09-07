#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <pthread.h>

char str[] = "123456";

void *callBack_printf(void *arg)
{
    while (1)
    {
        //申请信号量
        int res_semwait = sem_wait((sem_t *)arg);
        //回值判断
        if (-1 == res_semwait)
        {
            perror("sem_wait");
            return NULL;
        }
        printf("%s\n", str);
        //释放信号量
        int res_sempost = sem_post((sem_t *)arg);
        if (-1 == res_semwait)
        {
            perror("sem_post");
            return NULL;
        }
    }
    pthread_exit(NULL);
}
void *callBack_inversion(void *arg)
{
    while (1)
    {
        //申请信号量
        int res_semwait = sem_wait((sem_t *)arg);
        //回值判断
        if (-1 == res_semwait)
        {
            perror("sem_wait");
            return NULL;
        }
        for (size_t i = 0; i < strlen(str) / 2; i++)
        {
            char temp = str[i];
            str[i] = str[strlen(str) - 1 - i];
            str[strlen(str) - 1 - i] = temp;
        }

        //释放信号量
        int res_sempost = sem_post((sem_t *)arg);
        if (-1 == res_semwait)
        {
            perror("sem_post");
            return NULL;
        }
    }
    pthread_exit(NULL);
}
int main(int argc, const char *argv[])
{
    sem_t sem;
    int res_sem = sem_init(&sem, 0, 1); //初始化信号量，为1
    if (-1 == res_sem)
    {
        perror("sem_init");
        return -1;
    }

    //创建两进程，1.打印 2.逆置
    pthread_t thd_print, thd_inversion;
    if (pthread_create(&thd_print, NULL, callBack_printf, &sem) != 0)
    {
        perror("pthread_create");
        return -1;
    }
    if (pthread_create(&thd_inversion, NULL, callBack_inversion, &sem) != 0)
    {
        perror("pthread_create");
        return -1;
    }
    pthread_join(thd_print, NULL);
    pthread_join(thd_inversion, NULL);

    sem_destroy(&sem);
}
