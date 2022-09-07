int change_value(doublelink *D, datatype old_e, datatype new_e)
{
	if (D == NULL || D->next == NULL)
	{
		printf("更改失败\n");
		return -1;
	}
	doublelink *p = D->next;
	while (p != NULL)
	{
		if (p->data == old_e)
		{
			p->data = new_e;
			return 1;
		}
		p = p->next;
	}
	printf("未找到该值\n");
	return -2;
}