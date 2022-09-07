#ifndef LOOPLINK_H
#define LOOPLINK_H

typedef int datatype;

typedef struct node
{
    union 
    {
        datatype data;
        int len;
    };
    struct node *next;
}looplink;
int list_insert_head(looplink *L, datatype e);
looplink *looplink_creat();
looplink *kill_head(looplink *L);
looplink *list_pos_delete(looplink *L, int m);

#endif
