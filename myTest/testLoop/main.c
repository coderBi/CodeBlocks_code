#include <stdio.h>
#include <stdlib.h>

int main()
{



    int i=10;
    loopwwe:
    //���������� goto �ȵ���
    {
        int hah;        //���Ի᲻�����ض���  ����ŵ��������ڲ�
                        //a label can only be part of a statement and a declaration is not a statement
        printf("����poop���棡����\n");

    }

    int hah;   //swith loop ���治Ҫֱ�Ӹ�����  ���Ǹ�һ������ǿ��Ե�
    if(i>0)
    {

        printf("loop%d��Ч�ˣ�����\n",i);
        i--;
        goto loopwwe;

    }
    printf("Hello world!\n");
    return 0;
}
