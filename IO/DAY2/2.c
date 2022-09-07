#include <stdio.h>

int main(int argc, const char *argv[])
{
    FILE *fp_r = fopen("./1.txt", "r");
    FILE *fp_w = fopen("./2.txt", "w");
    if (NULL == fp_r)
    {
        perror("fopen");
        return -1;
    }
    if (NULL == fp_w)
    {
        perror("fopen");
        return -1;
    }

    char temp;
    size_t val;
    while (1)
    {
        val = fread(&temp, sizeof(temp), 1, fp_r);
        if (val < 1)
        {
            break;
        }
        fwrite(&temp, sizeof(temp), 1, fp_w);
    }

    fclose(fp_r);
    fclose(fp_w);
    return 0;
}