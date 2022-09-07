#include <stdio.h>
#include <stdlib.h>
#include "seqstack.h"

seqStack *stack_creat()
{
	seqStack *p = (seqStack *)malloc(sizeof(seqStack));
	if (NULL == p)
	{
		printf("创建失败\n");
		return NULL;
	}
	printf("创建成功\n");
	p -> top = -1;
	return p;
}

int stack_empty(seqStack *S)
{
	return S -> top == -1 ? 1 : 0;
}

int stack_full(seqStack *S)
{
	return S -> top == MAX - 1 ? 1 : 0;
}

int push(seqStack *S, datatype e)
{
	if (NULL == S || stack_full(S))
	{
		printf("添加失败\n");
		return -1;
	}
	S -> top ++;
	S -> data[S -> top] = e;
	printf("入栈成功\n");
	return 0;
}

int pop(seqStack *S)
{
	if (NULL == S || stack_empty(S))
	{
		printf("输入无效\n");
		return -1;
	}
	printf("%d出栈成功\n", S->data[S->top]);
	S -> top --;
	return 0;
}

void stack_show(seqStack *S)
{
	if (NULL == S || stack_full(S))
	{
		printf("遍历失败\n");
		return;
	}
	for (int i = S -> top; i > -1; i --)
	{
		printf("%d\t", S -> data[i]);
	}
	printf("\n");
	return;
}

