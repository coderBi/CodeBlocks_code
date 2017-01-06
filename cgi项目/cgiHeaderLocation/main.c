#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"

int cgiMain()
{
    printf("location:http://www.baidu.com\r\n\r\n");
    cgiHeaderLocation("http://www.youku.com");
    return 0;
}
