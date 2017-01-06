#include <stdio.h>
#include <stdlib.h>

int main()
{
    double fenzi1, fenzi2;
    double fenmu1, fenmu2;
    int num = 20;
    double sum = 0;
    int i;

    for(i = 1; i <= num; i++)
    {
        if(i == 1)
        {
            fenzi1 = 2;
            fenmu1 = 1;
            sum = fenzi1/fenmu1;
        }
        else if(i == 2)
        {
            fenzi2 = 3;
            fenmu2 = 2;
            sum += fenzi2/fenmu2;
        }
        else
        {
            double temp1, temp2;
            temp1 = fenzi1 + fenzi2;
            temp2 = fenmu1 + fenmu2;
            sum += temp1/temp2;
            fenzi1 = fenzi2;
            fenzi2 = temp1;
            fenmu1 = fenmu2;
            fenmu2 = temp2;
        }
    }
    printf("num=%d  sum=%lf", num, sum);
    return 0;
}
