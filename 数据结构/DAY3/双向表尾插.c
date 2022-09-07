int instr_tail(doublelink *D, datatype e)
{
	if (D == NULL)
	{
		printf("输入链表无效\n");
		return -1;
	}

	doublelink *p = D;
	while (p->next != NULL)
	{
		p = p->next;
	}

	doublelink *q = (doublelink *)malloc(sizeof(doublelink));
	if (q == NULL)
	{
		printf("节点申请失败\n");
		return -2;
	}
	q->data = e;
	q->next = NULL;
	q->prio = NULL;

	p->next = q;
	q->prio = p;
	D->len++;
	return 0;
}