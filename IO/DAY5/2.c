#include <stdio.h>
#include <pthread.h>

void *callBack(void *arg)
{
    while (1)
    {
        printf("这是分支线程\n");
        sleep(1);
    }
}

int main(int argc, const char *argv[])
{
    printf("这是主线程\n");

    pthread_t tid;
    if (pthread_creat(&tid, NULL, callBack, NULL) != 0)
    {
        perror("pthread_creat");
        return -1;
    }
    printf("分支进程创建成功\n");

    while (1)
    {
        printf("这是主线程\n");
        sleep(1);
    }
    return 0;
}