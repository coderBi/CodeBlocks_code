/********************************************
1,快排的关键在于定位部分
2，QuickSort参数（0，length —1）
3，同时给出linkedlist model
    考虑到方向问题，这里采用双向链表
********************************************/

#include <stdio.h>
#include <stdlib.h>

struct DataType
{
    int number;
    struct DataType* previous;
    struct DataType* next;
};

void QuickSort(int arr[], int first, int last);
int Partition(int arr[], int first, int last);
void PrintArray(int arr[], int length);

void QuickSortLinkedListModel(struct DataType* head, struct DataType* tail);
struct DataType* TranslateArrayToLinkedList(int arr[], int length);
void PrintLinkedList(struct DataType* head);
void FreeLinkedList(struct DataType* head);
struct DataType* FindTail(struct DataType* head);

int main()
{
    int arr[10] = {2, 33, 3432, 44, 66, 235, 23, 788, 3, 24};

    QuickSort(arr, 0, 9);
    PrintArray(arr, 10);
    printf("\n\n");

    struct DataType* head = TranslateArrayToLinkedList(arr, 10);
    struct DataType* tail = FindTail(head);
    QuickSortLinkedListModel(head, tail);
    PrintLinkedList(head);
    FreeLinkedList(head);
    return 0;
}

void QuickSort(int arr[], int first, int last)
{
    if(first >= last)
    {
        return;
    }
    int position;

    position = Partition(arr, first, last);
    QuickSort(arr, first, position - 1);
    QuickSort(arr, position + 1, last);
    return;
}

int Partition(int arr[], int first, int last)
{
    int key = arr[first];

    while(first < last)
    {
        while(first < last && arr[last] >= key)
        {
            last--;
        }
        arr[first] = arr[last];

        while(first < last && arr[first] <= key)
        {
            first++;
        }
        arr[last] = arr[first];
    }
    arr[first] = key;
    return first;
}

void PrintArray(int arr[], int length)
{
    int i;
    int count = 0;

    for(i = 0; i < length; i++)
    {
        if(count != 0 && count%10 == 0)
        {
            printf("\n");
        }
        printf("%d  ", arr[i]);
        count++;
    }
    return;
}

void QuickSortLinkedListModel(struct DataType* head, struct DataType* tail)
{
    /*这里要注意一下head->previous != tail情况*/
    if(head == NULL || tail == NULL || head == tail || head->previous != tail)
    {
        return;
    }
    struct DataType* subHead = head;
    struct DataType* subTail = tail;
    int key = subHead->number;

    while(subHead != subTail)
    {
        while(subTail->number >= subHead->number && subHead != subTail)
        {
            subTail = subTail->previous;
        }
        subHead->number = subTail->number;
        while(subHead->number <= subTail->number && subHead != subTail)
        {
            subHead = subHead->next;
        }
        subTail->number = subHead->number;
    }
    subHead->number = key;
    QuickSortLinkedListModel(head, subHead->previous);
    QuickSortLinkedListModel(subHead->next, tail);
    return;
}

struct DataType* TranslateArrayToLinkedList(int arr[], int length)
{
    int i;
    struct DataType* head = NULL;
    struct DataType* ptr = NULL;

    if(length <= 0)
    {
        return NULL;
    }
    ptr = (struct DataType*)malloc(sizeof(struct DataType));
    ptr->previous = NULL;
    ptr->next = NULL;
    ptr->number = arr[0];
    head = ptr;

    for(i = 1; i < length; i++)
    {
        struct DataType* temp = NULL;

        temp = (struct DataType*)malloc(sizeof(struct DataType));
        temp->previous = NULL;
        temp->next = NULL;
        temp->number = arr[i];
        ptr->next = temp;
        temp->previous = ptr;
        ptr = temp;
    }
    return head;
}

void PrintLinkedList(struct DataType* head)
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
    }
    return;
}

void FreeLinkedList(struct DataType* head)
{
    struct DataType* ptr = NULL;
    struct DataType* temp = NULL;

    for(ptr = head; ptr != NULL; ptr = temp)
    {
        temp = ptr->next;
        free(ptr);
    }
    return;
}

struct DataType* FindTail(struct DataType* head)
{
    struct DataType* tail = NULL;

    for(tail = head; tail != NULL && tail->next != NULL; tail = tail->next)
    {
        /*no content here!*/
    }
    return tail;
}
