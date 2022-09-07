#include <stdio.h>
#include "looplink.h"
int main(int argc, const char *argv[])
{
    looplink *L = looplink_creat();
    if (NULL == L)
    {
        return -1;
    }

    int n;
    printf("请输入想要创建的人数： ");
    scanf("%d", &n);
    for (int i = n; i > 0; i --)
    {
        list_insert_head(L, i);
    }
    looplink *L_start = kill_head(L);
    int m;
    printf("请输入想要出圈的号码： ");
    scanf("%d", &m);
	while (n > 1)
	{
		L_start = list_pos_delete(L_start, m);
		n--;
	}
	printf("%d\n", L_start->data);
    return 0;
}
