void list_selection_sort(Seqlist *L)
{
    if (NULL == L)
    {
        printf("排序失败\n");
        return;
    }

    for (int i = 0; i < (L->len - 1); i++)
    {
        datatype index = i;
        for (int j = i + 1; j < L->len; j++)
        {
            if (L->data[index] < L->data[j])
            {
                index = j;
            }
        }

        if (index != i)
        {
            datatype temp = L->data[i];
            L->data[i] = L->data[index];
            L->data[index] = temp;
        }
    }
    printf("排序完成\n");
    return;
}