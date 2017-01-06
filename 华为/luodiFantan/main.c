#include <stdio.h>
#include <stdlib.h>

#define START_HEIGHT 100
#define TIMES 1

int main()
{
    int nextAddNum, sumHgt;
    int i;

    nextAddNum = START_HEIGHT;
    sumHgt = START_HEIGHT;
    if(TIMES >= 2)
    {
        for(i = 2; i <= TIMES; i++)
        {
            sumHgt += nextAddNum;
            nextAddNum = nextAddNum/2;
        }
    }
    printf("times=%d    sum=%d\n", TIMES, sumHgt);

    return 0;
}
