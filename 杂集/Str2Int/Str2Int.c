int Str2Int(char* str)  //这里不考虑负数情况
{
    int res = 0;
    if(str == NULL || *str < '0' || *str > '9')
        return -1;
    while(str != NULL && *str >= '0' && *str <= '9')
    {
        res = res*10 + *str - '0';
        str++;
    }
    return res;
}