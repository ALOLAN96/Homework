#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_MSG(msg)                            \
    {                                           \
        fprintf(stderr, "Line: %d ", __LINE__); \
        perror(msg);                            \
    }
#define PORT 8888
#define IP "192.168.31.248"

typedef struct //通信协议基本构成
{
    char opcode;
    char username[20];
    char txt[128];
} msg;

int init_TCP_cli(int *sfd);

int do_Register(int sfd);
int do_Login(int sfd, char *username);
int do_interface(int sfd, char *username);
int do_Inquire(int sfd, char *username);
int do_Quit_user(int sfd, char *username);
int do_History(int sfd, char *username);

int main(int argc, const char *argv[])
{
    int sfd;

    char username[20] = ""; //获取成功登录后用户名

    if (-1 == init_TCP_cli(&sfd)) // bind, connect//客户端初始化
    {
        return -1;
    }

    while (1)
    {
        char order;
        system("clear");
        printf("**********************************\n");
        printf("**********************************\n");
        printf("**************1.注册**************\n");
        printf("**************2.登录**************\n");
        printf("**************3.退出**************\n");
        printf("**********************************\n");
        printf("**********************************\n");
        printf("请输入命令(1/2/3): ");

        order = getchar();
        while (getchar() != '\n')
            ;

        switch (order)
        {
        case '1':
            do_Register(sfd); //注册
            break;
        case '2':
            do_Login(sfd, username); //登录
            break;
        case '3':
            goto END; //客户端退出
            break;
        default:
            printf("输入有误,请重新输入!!!\n");
        }
        printf("输入任意按键清屏>>>>");
        while (getchar() != '\n')
            ;
    }
END:
    close(sfd);
    return 0;
}

int do_Login(int sfd, char *username) //登录
{
    msg sendmsg, recvmsg;
    sendmsg.opcode = 'L'; //填写登录操作码

    printf("请输入登录用户名：");
    fgets(sendmsg.username, sizeof(sendmsg.username), stdin);
    sendmsg.username[strlen(sendmsg.username) - 1] = 0;

    printf("请输入登录密码: ");
    fgets(sendmsg.txt, sizeof(sendmsg.txt), stdin);
    sendmsg.txt[strlen(sendmsg.txt) - 1] = 0;

    ssize_t res_send = send(sfd, &sendmsg, sizeof(sendmsg), 0);
    // printf("send = %ld\n", res_send);
    if (-1 == res_send)
    {
        ERR_MSG("send");
        return -1;
    }

    ssize_t res_recv = recv(sfd, &recvmsg, sizeof(recvmsg), 0);
    // printf("recv = %ld\n", res_recv);
    if (-1 == res_recv)
    {
        ERR_MSG("recv");
        return -1;
    }

    if ('S' == recvmsg.opcode)
    {
        printf("登录成功\n");
        strcpy(username, sendmsg.username); //存储成功登录的用户名
        do_interface(sfd, username);
    }
    else if ('E' == recvmsg.opcode)
    {
        printf("登录失败\n");
    }

    return 0;
}

int do_interface(int sfd, char *username) //二级界面显示
{
    while (1)
    {
        char order;
        system("clear");
        printf("**********************************\n");
        printf("**********************************\n");
        printf("*************1.查单词*************\n");
        printf("*************2.查历史*************\n");
        printf("*************3.返回上级***********\n");
        printf("**********************************\n");
        printf("**********************************\n");
        printf("请输入命令(1/2/3): ");

        order = getchar();
        while (getchar() != '\n')
            ;

        switch (order)
        {
        case '1':
            do_Inquire(sfd, username); //查单词
            break;
        case '2':
            do_History(sfd, username); //查历史
            break;
        case '3':
            do_Quit_user(sfd, username); //退出登录
            return 0;
        default:
            printf("输入有误,请重新输入!!!\n");
        }
        printf("输入任意按键清屏>>>>");
        while (getchar() != '\n')
            ;
    }
    return 0;
}

int do_History(int sfd, char *username) //查询历史记录
{
    msg sendmsg;

    sendmsg.opcode = 'H';               //填充操作码
    strcpy(sendmsg.username, username); //填充username

    ssize_t res_send = send(sfd, &sendmsg, sizeof(sendmsg), 0);
    if (-1 == res_send)
    {
        ERR_MSG("send");
        return -1;
    }

    while (1)
    {
        msg recvmsg;
        char count;
        ssize_t res_recv = recv(sfd, &recvmsg, sizeof(recvmsg), 0);
        if (-1 == res_recv)
        {
            ERR_MSG("recv");
            return -1;
        }

        if ('S' == recvmsg.opcode)
        {
            count = recvmsg.txt[0];
            if (count >= '1')
            {
                printf("%s\n", recvmsg.txt + 1);
                bzero(recvmsg.txt, sizeof(recvmsg.txt));
                count--;
                if ('0' == count)
                {
                    break;
                }
            }
        }
        else if ('E' == recvmsg.opcode)
        {
            printf("抱歉，未查询到该用户历史\n");
            break;
        }
    }
}

int do_Quit_user(int sfd, char *username) //用户命令退出
{
    msg sendmsg;

    sendmsg.opcode = 'Q';               //填充操作码
    strcpy(sendmsg.username, username); //填充username

    ssize_t res_send = send(sfd, &sendmsg, sizeof(sendmsg), 0);
    if (-1 == res_send)
    {
        ERR_MSG("send");
        return -1;
    }
    printf("账号退出成功\n");
}

int do_Inquire(int sfd, char *username) //查询单词
{
    msg sendmsg;

    sendmsg.opcode = 'I';               //填充操作码
    strcpy(sendmsg.username, username); //填充username

    printf("请输入想要查找的单词：");
    fgets(sendmsg.txt, sizeof(sendmsg.txt), stdin);
    sendmsg.txt[strlen(sendmsg.txt) - 1] = 0;

    ssize_t res_send = send(sfd, &sendmsg, sizeof(sendmsg), 0);
    if (-1 == res_send)
    {
        ERR_MSG("send");
        return -1;
    }

    while (1)
    {
        msg recvmsg;
        char count;
        ssize_t res_recv = recv(sfd, &recvmsg, sizeof(recvmsg), 0);
        if (-1 == res_recv)
        {
            ERR_MSG("recv");
            return -1;
        }

        if ('S' == recvmsg.opcode)
        {
            count = recvmsg.txt[0];
            if (count >= '1')
            {
                printf("%s\t%s\n", sendmsg.txt, (recvmsg.txt + 1));
                bzero(recvmsg.txt, sizeof(recvmsg.txt));
                count--;
                if ('0' == count)
                {
                    break;
                }
            }
        }
        else if ('E' == recvmsg.opcode)
        {
            printf("抱歉，未查询到该单词\n");
            break;
        }
    }
    return 0;
}

int do_Register(int sfd) //注册
{
    msg sendmsg, recvmsg;
    sendmsg.opcode = 'R'; //填写注册操作码

    printf("请输入注册用户名：");
    fgets(sendmsg.username, sizeof(sendmsg.username), stdin);
    sendmsg.username[strlen(sendmsg.username) - 1] = 0;

    printf("请输入注册密码: ");
    fgets(sendmsg.txt, sizeof(sendmsg.txt), stdin);
    sendmsg.txt[strlen(sendmsg.txt) - 1] = 0;

    ssize_t res_send = send(sfd, &sendmsg, sizeof(sendmsg), 0);
    // printf("send = %ld\n", res_send);
    if (-1 == res_send)
    {
        ERR_MSG("send");
        return -1;
    }

    ssize_t res_recv = recv(sfd, &recvmsg, sizeof(recvmsg), 0);
    // printf("recv = %ld\n", res_recv);
    if (-1 == res_recv)
    {
        ERR_MSG("recv");
        return -1;
    }

    if ('S' == recvmsg.opcode)
    {
        printf("注册成功\n");
    }
    else if ('E' == recvmsg.opcode)
    {
        printf("注册失败");
        printf("\t错误原因: %s\n", recvmsg.txt);
    }

    return 0;
}

int init_TCP_cli(int *sfd)
{
    *sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == *sfd)
    {
        ERR_MSG("socket");
        return -1;
    }

    //无需bind

    struct sockaddr_in ser; //服务器地址信息结构体
    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr(IP);
    socklen_t serlen = sizeof(ser);

    int res_connect = connect(*sfd, (struct sockaddr *)&ser, serlen);
    if (-1 == res_connect)
    {
        ERR_MSG("connect");
        return -1;
    }

    return 0;
}
