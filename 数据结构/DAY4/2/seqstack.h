#ifndef SEQSTACK_H
#define SEQSTACK_H

#define MAX 20
typedef int datatype;

typedef struct
{
	datatype data[MAX];
	int top;
}seqStack;

seqStack *stack_creat();

int stack_empty(seqStack *S);

int stack_full(seqStack *S);

int push(seqStack *S, datatype e);

int pop(seqStack *S);

void stack_show(seqStack *S);

#endif
