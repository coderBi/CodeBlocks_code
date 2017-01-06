/***********************************
此程序实现N个人围成圈数数，到M的
倍数就出来求解最后一个人坐标问题
***********************************/
#include <iostream>

using namespace std;

struct Person
{
    int pos;
    struct Person* next;
};

struct Person* DeleteNode(struct Person* head, struct Person* node);

int main()
{
    int m,n;
    int remain_Num;
    int i;
    int sum = 0;
    struct Person* head = NULL;
    struct Person* tail = NULL;
    struct Person* node = NULL;

    cout << "Input n and m:" << endl;
    cin >> n >> m;
    remain_Num = n;

    for(i = 0; i < n; i++)
    {
        node = new struct Person;

        if(head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        node->pos = i + 1;
        node->next = head;
    }

    node = head;
    while(remain_Num > 1)
    {
        struct Person* next_Node = node->next;

        sum++;
        if(sum > 2000)
        {
            sum = 1;
        }
        if(sum%m == 0)
        {
            head = DeleteNode(head, node);
            remain_Num--;
        }
        node = next_Node;
    }
    cout << "pos: " << head->pos;
    return 0;
}

struct Person* DeleteNode(struct Person* head, struct Person* node)
{
    struct Person* returnNode = head;
    struct Person* del = head;
    struct Person* preNode = NULL;

    while(del != node)
    {
        preNode = del;
        del = del->next;
    }
    if(del == head)
    {
        struct Person* tail = head;
        while(1)
        {
            if(tail->next == head)
            {
                break;
            }
            tail = tail->next;
        }
        if(tail == head)
        {
            returnNode = NULL;
        }
        else
        {
            tail->next = head->next;
            returnNode = head->next;
        }
    }
    else
    {
        preNode->next = node->next;
    }
    delete node;
    node = NULL;
    return returnNode;
}
