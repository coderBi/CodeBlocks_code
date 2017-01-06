#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct myStruct
{
    int pointNumber;
    bool isExist;
    struct myStruct* next;
};

int main()
{
    int L, M;
    int i = 0;
    int j = 0;
    int count = 0;
    struct myStruct* ptr1 = NULL;
    struct myStruct* head = NULL;
    struct myStruct* tail = NULL;

    scanf("%d %d",&L,&M);

    /*建立链表*/
    head = (struct myStruct*)malloc(sizeof(struct myStruct));
    head->pointNumber = 0;
    head->isExist = true;
    head->next = NULL;
    tail = head;
    i++;
    while(i <= L)
    {
        ptr1 = (struct myStruct*)malloc(sizeof(struct myStruct));
        ptr1->pointNumber = i;
        ptr1->isExist = true;
        ptr1->next = NULL;
        tail->next = ptr1;
        tail = ptr1;
        i++;
    }
    ptr1 = NULL;

    /*依次修改链表中在区域中节点标记*/
    while(j < M)
    {
        int startNode, endNode;
        scanf("%d %d", &startNode, &endNode);
        for(ptr1 = head; ptr1 != NULL; ptr1 = ptr1->next)
        {
            if(ptr1->pointNumber >= startNode && ptr1->pointNumber <= endNode)
            {
                ptr1->isExist = false;
            }
        }
        j++;
    }

    /*统计数目*/
    for(ptr1 = head; ptr1 != NULL; ptr1 = ptr1->next)
    {
         if(ptr1->isExist == true)
         {
             count++;
         }
    }
    printf("%d\n",count);
    return 0;
}
