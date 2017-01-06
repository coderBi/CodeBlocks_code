#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch1;
    int count1, count2, count3, count4;

    count1 = count2 =  count3 = count4 = 0;
    printf("Input your string:");
    while((ch1 = getchar()) != '\n')
    {
        if(ch1 >= 'a' && ch1 <= 'z' || ch1 >= 'A' && ch1 <= 'Z')
        {
            count1++;
        }
        else if(ch1 >= '0' && ch1 <= '9')
        {
            count2++;
        }
        else if(ch1 == ' ')
        {
            count3++;
        }
        else
        {
            count4++;
        }
    }
    printf("English characters=%d   Numbers=%d  Space=%d    Others=%d\n", count1, count2, count3, count4);
    return 0;
}
