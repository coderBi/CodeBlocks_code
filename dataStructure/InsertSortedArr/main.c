#include <stdio.h>
#include <stdlib.h>

struct DataType
{
  int number;
  struct DataType* next;
};

struct DataType* InsertInSortNum(struct DataType* head, struct DataType* ptr);
void PrintArr(struct DataType* head);
void ReleaseArr(struct DataType* head);

int main()
{
    char ch;
    struct DataType* head = NULL;
    struct DataType* ptr = NULL;
    struct DataType* InsertData = NULL;

    /*输入已经排好的序列，建立相应链表*/
    printf("Input your numbers:\nnote:numbers divided by space and enter key for quit\n");
    ptr = (struct DataType*)malloc(sizeof(struct DataType));
    head = ptr;
    ptr->next = NULL;
    scanf("%d%c", &ptr->number, &ch);
    while(ch != '\n')
    {
        struct DataType* temp = (struct DataType*)malloc(sizeof(struct DataType));
        temp->next = NULL;
        scanf("%d%c", &temp->number,&ch);
        ptr->next = temp;
        ptr = temp;
    }

    /*采集带插入数据*/
    printf("Input your insert data:");
    InsertData = (struct DataType*)malloc(sizeof(struct DataType));
    InsertData->next = NULL;
    scanf("%d", &InsertData->number);

    /*排序与打印结果*/
    head = InsertInSortNum(head, InsertData);
    PrintArr(head);
    ReleaseArr(head);
    return 0;
}

struct DataType* InsertInSortNum(struct DataType* head, struct DataType* ptr)
{
    if(head == NULL)
    {
        printf("Null Arr!\n");
        return NULL;
    }
    else
    {
        if(ptr->number < head->number)
        {
            ptr->next = head;
            head = ptr;
        }
        else
        {
            struct DataType* temp = NULL;
            struct DataType* beforeNode = NULL;

            for(temp = head; temp != NULL; temp = temp->next)
            {
                if(ptr->number < temp->number)
                {
                    break;
                }
                beforeNode = temp;
            }
            beforeNode->next = ptr;
            ptr->next = temp;
        }
    }
    return head;
}

void PrintArr(struct DataType* head)
{
    if(head == NULL)
    {
        printf("Null Array!\n");
        return;
    }
    else
    {
        struct DataType* ptr = NULL;
        int count = 0;

        for(ptr = head; ptr != NULL; ptr = ptr->next)
        {
            if(count != 0 && count%10 == 0)
            {
                printf("\n");
            }
            printf("%d  ", ptr->number);
            count++;
        }
    }
    return;
}

void ReleaseArr(struct DataType* head)
{
    if(head == NULL)
    {
        printf("Null Array!\n");
        return;
    }
    else
    {
        struct DataType* ptr = NULL;
        struct DataType* temp = NULL;

        for(ptr = head; ptr != NULL; ptr =temp)
        {
             temp = ptr->next;
             free(ptr);
        }
    }
    return;
}
