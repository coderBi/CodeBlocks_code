#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"

int cgiMain()
{
    cgiHeaderContentType("text/html;charset=gbk");
    //fprintf(cgiOut, "<html><head></head><body><p>ÄãÃÃµÄ£¡</p></body></html>");
    //cgiHeaderLocation("http://www.baidu.com");
    fprintf(cgiOut, "<html><head></head><body>queryString = %s<br>userAgent = %s<br> ip = %s<br>cgiScriptName = %s</body></html>",
             cgiQueryString, cgiUserAgent, cgiRemoteAddr, cgiScriptName);
    return 0;
}
