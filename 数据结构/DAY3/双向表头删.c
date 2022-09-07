int head_delete(doublelink *D)
{
	if (D == NULL || D->next == NULL)
	{
		printf("删除失败\n");
		return -1;
	}
	D->next = D->next->next;
	D->next->prio = D;
	D->len--;
	printf("头删成功\n");
	return 0;
}