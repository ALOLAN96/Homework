#include "fileprint.h"

void get_file_type(struct stat F)
{
    switch (F.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("b");
        break;
    case S_IFCHR:
        printf("c");
        break;
    case S_IFDIR:
        printf("d");
        break;
    case S_IFIFO:
        printf("p");
        break;
    case S_IFLNK:
        printf("l");
        break;
    case S_IFREG:
        printf("-");
        break;
    case S_IFSOCK:
        printf("s");
        break;
    default:
        printf("unknown?\n");
        break;
    }
}

void rwx(struct stat F)
{
    mode_t file_rwx = F.st_mode;
    for (int i = 0; i < 9; i++)
    {
        if ((file_rwx & (0400 >> i)) == 0)
        {
            putchar('-');
            continue;
        }
        switch (i % 3)
        {
        case 0:
            putchar('r');
            break;
        case 1:
            putchar('w');
            break;
        case 2:
            putchar('x');
            break;
        }
    }
    printf(" ");
    return;
}

void hard_link_num(struct stat F)
{
    nlink_t num = F.st_nlink;
    printf("%ld ", num);
    return;
}

int user_id(struct stat F)
{
    uid_t user = F.st_uid;
    struct passwd *UID = getpwuid(user);
    if (NULL == UID)
    {
        perror("getpwuid");
        return -1;
    }

    printf("%s ", UID->pw_name);
    return 0;
}

int group_id(struct stat F)
{
    gid_t g_user = F.st_gid;
    struct group *GID = getgrgid(g_user);
    if (NULL == GID)
    {
        perror("getgrgid");
        return -1;
    }
    printf("%s ", GID->gr_name);
    return 0;
}

void file_size(struct stat F)
{
    off_t file_size = F.st_size;
    printf("%8ld ", file_size);
    return;
}
void time_print(struct stat F)
{
    time_t time = F.st_mtime;
    struct tm *TIME = localtime(&time);
    int month = TIME->tm_mon + 1;
    int day = TIME->tm_mday;
    int hour = TIME->tm_hour;
    int min = TIME->tm_min;
    printf("%d月 %3d %2d:%2d ", month, day, hour, min);
}

void file_name_print(struct dirent *s)
{
    puts(s->d_name);
    return;
}

void file_print(struct stat F)
{
    get_file_type(F);
    rwx(F);
    hard_link_num(F);
    user_id(F);
    group_id(F);
    file_size(F);
    time_print(F);
}
