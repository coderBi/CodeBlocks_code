/*
此题是黑马群中讨论的问题，求阶层结果中的0个数，理论上是找出所有的2跟5的个数，取得较小值。
实际中2肯定会比5多，所以问题即是求出阶层中5的个数
ps:论坛上给出的找出5的个数可能是有问题的，这里测试20！中的确有7个0 但是中间有3个0，也就是可能出现0在中间不能参与计数的情况
        这里只能求出有多少个0；
ps:经过再次验证，这2*5模型，连有几个0都检查不出来。55555555555555~    7*8*9 = 504   *5=2520

ps:经过分析，其实这里统计5的个数来看后面连续的0是可靠地，因为其他进位的0是不可能进入尾部连续的0中的。
    但是目前统计5的个数方法有问题，下面将进行重写
*/
#include <stdio.h>
#include <stdlib.h>

int _GetCountOf5(int n)   //这里统计方法有问题，存在前后重复统计的情况
{
    int i, sum = 0;
    for(i = n; i > n/2; i--)
    {
        if(i%5 == 0)
        {
            sum += i/5;
            sum += _GetCountOf5(i/5);
        }
    }
    return sum;
}

int GetCountOf5(int n)
{
    int i, res = 0;
    for(i = 5; i <= n; i += 5)
    {
        int temp = i;
        while(temp%5 == 0)
        {
            res++;
            temp /= 5;
        }
    }
    return res;
}

int GetCountOfFive(int n)
{
    int i, res = 0, maxNum = 0;
    if(n < 5)
        return 0;
    for(i = n; i > n-5; i--)
    {
        if(i%5 == 0)
        {
            maxNum = i;
            break;
        }
    }
    res += maxNum/5;
    res += GetCountOfFive(maxNum/5);
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", GetCountOf5(n));
    printf("%d\n", GetCountOfFive(n));
    return 0;
}
