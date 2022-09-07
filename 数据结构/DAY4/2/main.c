#include <stdio.h>
#include "seqstack.h"
int main(int argc, const char *argv[])
{
	int num, n;
	seqStack *S = stack_creat();
	if (NULL == S)
	{
		return -1;
	}
	printf("请输入需要转换的数值： ");
	scanf("%d", &num);
	printf("请输入想要转换的数制： ");
	scanf("%d", &n);
	int index;
	while (num != 0)
	{
		index = num % n;
		push(S, index);
		num = num / n;
	}
	// push(S, num);  此条件时，不需要补充高位数
	// num > n        此条件时，需要在循环外补充高位
	stack_show(S);

	return 0;
}
