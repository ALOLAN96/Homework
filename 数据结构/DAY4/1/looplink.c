#include <stdio.h>
#include <stdlib.h>
#include "looplink.h"
/**
 * @brief 链表头节点创建
 * 
 * @return looplink* 
 **/
looplink *looplink_creat()
{   
	looplink *p = (looplink *)malloc(sizeof(looplink));
	if (NULL ==p)
	{
		printf("创建失败\n");
		return NULL;
	}
	p->len = 0;
	p->next = p;
	printf("创建成功\n");
	return p;
}
/**
 * @brief 头插数据
 * 
 * @param L 操作的链表
 * @param e 需要添加到表里的数据
 * @return int 
 **/
int list_insert_head(looplink *L, datatype e)
{
	if (NULL == L)
	{
		printf("所给链表不合法\n");
		return -1;
	}
	looplink *p = malloc(sizeof(looplink));
	if (NULL == p)
	{
		printf("空间申请失败\n");
		return -2;
	}
	p->next = NULL;
	p->data = e;

	p->next = L->next;
	L->next = p;
	L->len++;
	printf("添加成功\n");
	return 0;
}


looplink *kill_head(looplink *L)
{
	if (NULL == L)
	{
		printf("删除失败\n");
		return NULL;
	}
	if (L->next==NULL)
	{
		free(L);
		L = NULL;
		printf("删除成功\n");
		return NULL;
	}
	looplink *q = L;
	while (q->next != L)
	{
		q = q->next;
	}
	q ->next = L->next;
	free(L);
	L = NULL;
	printf("头节点删除成功\n");
	return q -> next;
}
looplink *list_pos_delete(looplink *H, int m)
{
	if (NULL == H)
	{
		printf("输入不合法\n");
		return NULL;
	}
	looplink *temp = NULL;
	looplink *prior = H;
	for (int i = 1; i < m-1; i ++)
	{
		prior = prior -> next;
	}
	temp = prior->next;
	prior->next = temp->next;
	printf("%d\t", temp->data);		
	free(temp);
	temp = NULL;
	return prior->next;
}

