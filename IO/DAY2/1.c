#include <stdio.h>
#include <string.h>

int count_row(FILE *fp)
{
    char str1[2] = "";
    char str2[2] = "\n";
    int count = 0;
    while (1) //(fgets(str1, sizeof(str1), fp) != NULL) 省略break条件
    {
        char *p = fgets(str1, sizeof(str1), fp);
        if (NULL == p)
        {
            break;
        }
        if (strcmp(str1, str2) == 0)//直接调用指针进行比较  str1[0] =='\n'
        {                           //str1数组长度放长 直接判断str1[strlen(str) - 1] == '\n'
            count++;
        }
    }
    return count;
}
int main(int argc, const char *argv[])
{
    FILE *fp = fopen("./shiyan.txt", "r");
    if (NULL == fp)
    {
        perror("fopen");
        return -1;
    }

    int row = count_row(fp);
    printf("ROW=%d\n", row);
    fclose(fp);
    return 0;
}