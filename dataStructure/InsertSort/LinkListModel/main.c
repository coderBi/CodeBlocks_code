#include <stdio.h>
#include <stdlib.h>

struct DataType
{
    int number;
    struct DataType* next;
};

struct DataType* CreateLinkList();
struct DataType* InsertSortForLinkListModel(struct DataType* head);
struct DataType* InsertOneNumber(struct DataType** head, struct DataType* node);
void PrintLinkList(struct DataType* head);
void FreeLinkList(struct DataType* head);

int main()
{
    struct DataType* head;

    head = CreateLinkList();
    head = InsertSortForLinkListModel(head);
    PrintLinkList(head);
    FreeLinkList(head);
    return 0;
}

struct DataType* CreateLinkList()
{
    struct DataType* head = NULL;
    struct DataType* ptr = NULL;
    char ch;

    ptr = (struct DataType*)malloc(sizeof(struct DataType));
    scanf("%d%c", &ptr->number, &ch);
    ptr->next = NULL;
    head = ptr;
    while(ch != '\n')
    {
        struct DataType* node = NULL;
        node = (struct DataType*)malloc(sizeof(struct DataType));
        scanf("%d%c", &node->number, &ch);
        node->next = NULL;
        ptr->next = node;
        ptr = node;
    }
    return head;
}

struct DataType* InsertSortForLinkListModel(struct DataType* head)
{
    struct DataType* ptr = NULL;
    struct DataType* nextNode = NULL;

    for(ptr = head; ptr != NULL; ptr = nextNode)
    {
        nextNode = InsertOneNumber(&head, ptr);
    }
    return head;
}

struct DataType* InsertOneNumber(struct DataType** head, struct DataType* node)
{
    struct DataType* ptr = NULL;
    struct DataType* prePtr = NULL;
    struct DataType* nextNode = node->next;
    struct DataType* preNode = NULL;

    if(*head == node)
    {
        return nextNode;
    }
    for(ptr = *head; ptr != node; ptr = ptr->next)
    {
        preNode = ptr;
    }

    for(ptr = *head; ptr != node; ptr = ptr->next)
    {
        if(ptr->number > node->number)
        {
            break;
        }
        prePtr = ptr;
    }

    if(ptr != node)
    {
        preNode->next = nextNode;
        if(*head == ptr)
        {
            node->next = *head;
            *head = node;
        }
        else
        {
            prePtr->next = node;
            node->next = ptr;
        }

    }
     return nextNode;
}

void PrintLinkList(struct DataType* head)
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
    return;
}

void FreeLinkList(struct DataType* head)
{
    if(head == NULL)
    {
        return;
    }

    struct DataType* ptr = NULL;
    struct DataType* nextNode = NULL;

    for(ptr = head; ptr != NULL; ptr = nextNode)
    {
        nextNode = ptr->next;
        free(ptr);
    }
    return;

}
