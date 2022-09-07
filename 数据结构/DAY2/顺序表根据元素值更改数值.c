int list_update_pos(Seqlist *L, int pos, datatype e)
{
    if (NULL == L || list_empty(L) || pos < 0 || pos > L->len)
    {
        printf("查找失败\n");
        return -1;
    }
    L->data[pos - 1] = e;
    printf("修改完成\n");
    return 0;
}