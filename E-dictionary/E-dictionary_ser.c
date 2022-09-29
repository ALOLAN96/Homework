#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sqlite3.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

typedef struct //线程函数传参结构体
{
    int newfd;
    struct sockaddr_in addrinfo;
    sqlite3 *userdb;
    sqlite3 *dictdb;
} pth_parameters;

typedef struct //通信协议基本构成
{
    char opcode;
    char username[20];
    char txt[128];
} msg;

int init_TCP_ser(int *sfd);
int init_BANK_word(sqlite3 **Dictionary);
int init_BANK_user(sqlite3 **User);

void *callBack(void *arg);

int do_Register(int newfd, msg info, sqlite3 *User);
int do_Login(int newfd, msg info, sqlite3 *User, char *username);
int do_Inquire(int newfd, msg info, sqlite3 *User, sqlite3 *Dictionary);
int do_History(int newfd, msg info, sqlite3 *User);
int do_Quit_user(int newfd, msg info, sqlite3 *User);
int do_History(int newfd, msg info, sqlite3 *User);

#define ERR_MSG(msg)                            \
    {                                           \
        fprintf(stderr, "Line: %d ", __LINE__); \
        perror(msg);                            \
    }

#define PORT 8888
#define IP "192.168.31.248"

int main(int argc, const char *argv[])
{
    int sfd;             //监听套接字
    sqlite3 *User;       // user库地址
    sqlite3 *Dictionary; // Dictionary库地址

    init_BANK_word(&Dictionary); //单词库、单词表初始化

    init_BANK_user(&User); //用户库，信息表，历史表初始化

    init_TCP_ser(&sfd); //服务器初始化
                        // socket,bind,listen

    struct sockaddr_in cli; //客户端地址信息结构体
    socklen_t cliadrlen = sizeof(cli);

    while (1)
    {
        int newfd = accept(sfd, (struct sockaddr *)&cli, &cliadrlen);
        if (-1 == newfd)
        {
            ERR_MSG("accept");
            return -1;
        }
        printf("[%s | %d]客户端链接成功\n", (char *)inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        pthread_t tid; //线程函数参数构造
        pth_parameters pth_into;
        pth_into.newfd = newfd;
        pth_into.addrinfo = cli;
        pth_into.userdb = User;
        pth_into.dictdb = Dictionary;

        int pt_crt = pthread_create(&tid, NULL, callBack, &pth_into);
        if (0 != pt_crt)
        {
            ERR_MSG("pthread_create");
            return -1;
        }

        pthread_detach(tid);
    }
}

void *callBack(void *arg) //进程函数
{
    int newfd = (*(pth_parameters *)arg).newfd;
    struct sockaddr_in cli = (*(pth_parameters *)arg).addrinfo;
    sqlite3 *Dictionary = (*(pth_parameters *)arg).dictdb;
    sqlite3 *User = (*(pth_parameters *)arg).userdb;

    char username[20] = ""; //存储登录成功的用户名

    while (1)
    {
        msg recvmsg;

        ssize_t res_recv = recv(newfd, &recvmsg, sizeof(recvmsg), 0);
        if (0 == res_recv)
        {
            printf("[%s | %d]客户端断开链接\n", (char *)inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

            char sql[512] = ""; //断链接后修改登录状态值（变0）
            sprintf(sql, "update login set state=0 where username0 =\"%s\";", username);
            printf("%s\n", sql);
            char *errmsg = NULL;
            int sql_exec = sqlite3_exec(User, sql, NULL, NULL, &errmsg);
            if (SQLITE_OK != sql_exec)
            {
                fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(User));
                break;
            }
            close(newfd);
            break;
        }
        else if (-1 == res_recv)
        {
            ERR_MSG("recv");
            break;
        }

        switch (recvmsg.opcode)
        {
        case 'R': //注册
            do_Register(newfd, recvmsg, User);
            break;
        case 'L': //登录
            do_Login(newfd, recvmsg, User, username);
            break;
        case 'I': //查询单词
            do_Inquire(newfd, recvmsg, User, Dictionary);
            break;
        case 'H': //查询历史记录
            do_History(newfd, recvmsg, User);
            break;
        case 'Q': //用户命令退出
            do_Quit_user(newfd, recvmsg, User);
            break;

        default:
            break;
        }
    }
}

int do_History(int newfd, msg info, sqlite3 *User) //查历史
{
    // sql命令语句
    char sql[512] = "";

    sprintf(sql, "select * from history where username0 = \"%s\";", info.username);
    printf("%s\n", sql);

    char **pres;    //返回char*数组的首地址
    int row, colum; //返回结果的行和列
    char *errmsg = NULL;
    int res = sqlite3_get_table(User, sql, &pres, &row, &colum, &errmsg);
    if (SQLITE_OK != res)
    {
        fprintf(stderr, "Line: %d sqlite3_get_table: %s\n", __LINE__, sqlite3_errmsg(User));
        return -1;
    }

    msg sendmsg; //构造待发送结构体

    if (0 != row)
    {
        printf("ROW=%d\n", row);
        printf("COLUM=%d\n", colum);

        sendmsg.opcode = 'S';

        int count = row;

        while (count >= 1)
        {
            bzero(sendmsg.txt, sizeof(sendmsg.txt));
            sprintf(sendmsg.txt, "%d%s %s %s %s", count, pres[(((count + 1) * colum) - 4)], pres[(((count + 1) * colum) - 3)], pres[(((count + 1) * colum) - 2)], pres[(((count + 1) * colum) - 1)]);
            printf("%s\n", sendmsg.txt);

            ssize_t res_send = send(newfd, &sendmsg, sizeof(sendmsg), 0);
            if (-1 == res_send)
            {
                ERR_MSG("send");
                return -1;
            }
            count--;
        }
    }
    else
    {
        sendmsg.opcode = 'E';
        ssize_t res_send = send(newfd, &sendmsg, sizeof(sendmsg), 0);
        if (-1 == res_send)
        {
            ERR_MSG("send");
            return -1;
        }
    }

    sqlite3_free_table(pres);
    return 0;
}

int do_Quit_user(int newfd, msg info, sqlite3 *User) //用户退出命令
{
    // sql命令语句
    char sql[512] = "";
    sprintf(sql, "update login set state=0 where username0 =\"%s\";", info.username);
    printf("%s\n", sql);

    char *errmsg = NULL;
    int sql_exec = sqlite3_exec(User, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != sql_exec)
    {
        fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(User));
        return -1;
    }
}

int do_Inquire(int newfd, msg info, sqlite3 *User, sqlite3 *Dictionary) //查单词并添加到历史记录表中
{
    // sql命令语句
    char sql[512] = "";

    time_t Time; //记录查询时间
    Time = time(NULL);
    struct tm *ptr = localtime(&Time);

    bzero(sql, sizeof(sql));
    sprintf(sql, "select * from dictionary where word0 = \"%s\";", info.txt);
    printf("%s\n", sql);

    char **pres;    //返回char*数组的首地址
    int row, colum; //返回结果的行和列
    char *errmsg = NULL;
    int res = sqlite3_get_table(Dictionary, sql, &pres, &row, &colum, &errmsg);
    if (SQLITE_OK != res)
    {
        fprintf(stderr, "Line: %d sqlite3_get_table: %s\n", __LINE__, sqlite3_errmsg(User));
        return -1;
    }

    msg sendmsg; //构造待发送结构体
    if (0 != row)
    {
        printf("ROW=%d\n", row);
        printf("COLUM=%d\n", colum);
        sendmsg.opcode = 'S';
        int count = row;

        while (count >= 1)
        {
            bzero(sendmsg.txt, sizeof(sendmsg.txt));

            sprintf(sendmsg.txt, "%d%s", count, pres[(((count + 1) * colum) - 1)]);
            printf("%s\n", sendmsg.txt);

            bzero(sql, sizeof(sql));
            sprintf(sql, "insert into history values (\"%s\", \"%s\", \"%s\",\"%4d-%02d-%02d %02d:%02d:%02d\");", info.username, info.txt, pres[(((count + 1) * colum) - 1)], ptr->tm_year + 1900, ptr->tm_mon + 1, ptr->tm_mday, ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
            printf("%s\n", sql);

            char *errmsg;
            int sql_exec = sqlite3_exec(User, sql, NULL, NULL, &errmsg);
            if (SQLITE_OK != sql_exec)
            {
                fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(User));
                return -1;
            }

            ssize_t res_send = send(newfd, &sendmsg, sizeof(sendmsg), 0);
            if (-1 == res_send)
            {
                ERR_MSG("send");
                return -1;
            }
            count--;
        }
    }
    else
    {
        sendmsg.opcode = 'E';
        ssize_t res_send = send(newfd, &sendmsg, sizeof(sendmsg), 0);
        if (-1 == res_send)
        {
            ERR_MSG("send");
            return -1;
        }

        //添加未查询到单词记录至历史表
        bzero(sql, sizeof(sql));
        sprintf(sql, "insert into history values (\"%s\", \"%s\", \"\",\"%4d-%02d-%02d %02d:%02d:%02d\");", info.username, info.txt, ptr->tm_year + 1900, ptr->tm_mon + 1, ptr->tm_mday, ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
        printf("%s\n", sql);

        char *errmsg;
        int sql_exec = sqlite3_exec(User, sql, NULL, NULL, &errmsg);
        if (SQLITE_OK != sql_exec)
        {
            fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(User));
            return -1;
        }
    }

    sqlite3_free_table(pres);
    return 0;
}

int do_Login(int newfd, msg info, sqlite3 *User, char *username) //登录
{
    // sql命令语句
    char sql[512] = "";
    sprintf(sql, "select * from login where username0 = \"%s\" and password1 = \"%s\" and state = 0;", info.username, info.txt);

    char **pres;    //返回char*数组的首地址
    int row, colum; //返回结果的行和列
    char *errmsg;
    int res = sqlite3_get_table(User, sql, &pres, &row, &colum, &errmsg);
    if (SQLITE_OK != res)
    {
        fprintf(stderr, "Line: %d sqlite3_get_table: %s\n", __LINE__, sqlite3_errmsg(User));
        return -1;
    }

    msg sendmsg; //构造待发送结构体
    if (1 == row)
    {
        sendmsg.opcode = 'S';
        strcpy(username, info.username);

        bzero(sql, sizeof(sql)); //修改登录状态值（变1）
        sprintf(sql, "update login set state=1 where username0 =\"%s\";", info.username);
        printf("%s\n", sql);
        errmsg = NULL;
        int sql_exec = sqlite3_exec(User, sql, NULL, NULL, &errmsg);
        if (SQLITE_OK != sql_exec)
        {
            fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(User));
            return -1;
        }
    }
    else
    {
        sendmsg.opcode = 'E';
    }

    ssize_t res_send = send(newfd, &sendmsg, sizeof(sendmsg), 0);
    if (-1 == res_send)
    {
        ERR_MSG("send");
        return -1;
    }

    sqlite3_free_table(pres);
    return 0;
}

int do_Register(int newfd, msg info, sqlite3 *User) //注册
{
    //作为记录插入到用户注册表中
    // sql命令语句
    char sql[512] = "";
    msg sendmsg; //构造待发送结构体

    sprintf(sql, "insert into login values (\"%s\", \"%s\", 0);", info.username, info.txt); //用户名，密码，登录（0：下线 1：上线）

    char *errmsg = NULL;
    int sql_exec = sqlite3_exec(User, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != sql_exec)
    {
        fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(User));
        sendmsg.opcode = 'E'; //注册失败操作码E
        strcpy(sendmsg.txt, sqlite3_errmsg(User));
    }
    else
    {
        sendmsg.opcode = 'S'; //注册成功操作码S
    }

    ssize_t res = send(newfd, &sendmsg, sizeof(sendmsg), 0);
    if (-1 == res)
    {
        ERR_MSG("send");
        return -1;
    }
    return 0;
}

int init_TCP_ser(int *sfd) // TCP服务器初始化
{
    *sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == *sfd)
    {
        ERR_MSG("socket");
        return -1;
    }

    //允许重用本地地址和端口
    int set = 1;
    socklen_t optlen = sizeof(set);
    int res_setopt = setsockopt(*sfd, SOL_SOCKET, SO_REUSEADDR, &set, optlen);
    if (-1 == res_setopt)
    {
        ERR_MSG("setsockopt");
        return -1;
    }

    //构造绑定服务器地址信息结构体
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr(IP);
    socklen_t serlen = sizeof(ser);

    int res_bind = bind(*sfd, (struct sockaddr *)&ser, serlen);
    if (-1 == res_bind)
    {
        ERR_MSG("bind");
        return -1;
    }

    int res_lisn = listen(*sfd, 128);
    if (-1 == res_lisn)
    {
        ERR_MSG("listen");
        return -1;
    }
    printf("等待accept....\n");
    return 0;
}

int init_BANK_word(sqlite3 **Dictionary) //单词库表初始化:dictionary
{
    char sql[512] = ""; //存储sql语句

    //创建词典库Dictionary
    int sqlop_D = sqlite3_open("./Dictionary", Dictionary);
    if (SQLITE_OK != sqlop_D)
    {
        fprintf(stderr, "Line: %d sqlite3_open: %s\n", __LINE__, sqlite3_errmsg(*Dictionary));
        return -1;
    }
    printf("词典库创建成功\n");

    //防止先前存在错误的词典表，先使用if not exits
    //再删除词典表
    //创建单词表dictionary，导入单词word，翻译translate
    bzero(sql, sizeof(sql));
    strcpy(sql, "create table if not exists dictionary (word0 char, translate1 char);");

    char *errmsg = NULL;
    int sql_exec = sqlite3_exec(*Dictionary, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != sql_exec)
    {
        fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(*Dictionary));
        return -1;
    }

    //删除词典表
    bzero(sql, sizeof(sql));
    strcpy(sql, "drop table dictionary;");
    errmsg = NULL;
    sql_exec = sqlite3_exec(*Dictionary, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != sql_exec)
    {
        fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(*Dictionary));
        return -1;
    }

    //再创建词典表
    bzero(sql, sizeof(sql));
    strcpy(sql, "create table if not exists dictionary (word0 char, translate1 char);");
    errmsg = NULL;
    sql_exec = sqlite3_exec(*Dictionary, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != sql_exec)
    {
        fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(*Dictionary));
        return -1;
    }
    printf("单词表创建成功\n");

    //导入单词
    FILE *fp = fopen("./dict.txt", "r");
    if (NULL == fp)
    {
        ERR_MSG("fopen");
        return -1;
    }
    printf("导入txt打开成功\n");

    char word[50] = "";       //存储txt单词
    char translate[550] = ""; //存储单词翻译
    char temp[600] = "";      // fgets临时存储

    while (1)
    {
        bzero(temp, sizeof(temp));

        char *res = fgets(temp, sizeof(temp), fp);
        if (NULL == res)
        {
            if (2 == errno)
            {
                fclose(fp);
                printf("单词表导入完成\n");
            }
            else
            {
                ERR_MSG("fgets");
                return -1;
            }
            break;
        }

        temp[strlen(temp) - 1] = 0;

        char *middle = temp; //创建寻单词指针
        while (1)
        {
            if ((' ' == *middle) && (' ' == *(middle + 1)))
            {
                break;
            }
            middle++;
        }
        *middle = 0; //单词后第一个空格修改为\0

        strcpy(word, temp);
        strcpy(translate, middle + 3);

        bzero(sql, sizeof(sql));
        sprintf(sql, "insert into dictionary values (\"%s\", \"%s\");", word, translate);

        bzero(word, sizeof(word));
        bzero(translate, sizeof(translate));

        errmsg = NULL;
        sql_exec = sqlite3_exec(*Dictionary, sql, NULL, NULL, &errmsg);
        if (SQLITE_OK != sql_exec)
        {
            fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(*Dictionary));
            return -1;
        }
    }
    printf("单词表数据添加完成\n");
    return 0;
}

int init_BANK_user(sqlite3 **User) //用户库表初始化:login, history
{
    char sql[512] = ""; //存储sql语句

    //创建用户库User
    int sqlop_D = sqlite3_open("./User", User);
    if (SQLITE_OK != sqlop_D)
    {
        fprintf(stderr, "Line: %d sqlite3_open: %s\n", __LINE__, sqlite3_errmsg(*User));
        return -1;
    }
    printf("用户库创建成功\n");

    //用户名(主键)，密码，登录状态表login初始化
    bzero(sql, sizeof(sql));
    strcpy(sql, "create table if not exists login (username0 char primary key, password1 char, state int);"); //用户名，密码，登录（0：下线 1：上线）

    char *errmsg = NULL;
    int sql_exec = sqlite3_exec(*User, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != sql_exec)
    {
        fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(*User));
        return -1;
    }
    printf("用户信息表创建完成\n");

    //历史记录表history初始化
    bzero(sql, sizeof(sql));
    strcpy(sql, "create table if not exists history (username0 char, word1 char, translate2 char, time3 char);"); //用户名，单词， 翻译， 时间

    errmsg = NULL;
    sql_exec = sqlite3_exec(*User, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != sql_exec)
    {
        fprintf(stderr, "Line: %d sqlite3_exec: %s\n", __LINE__, sqlite3_errmsg(*User));
        return -1;
    }
    printf("历史记录表创建完成\n");
    return 0;
}
