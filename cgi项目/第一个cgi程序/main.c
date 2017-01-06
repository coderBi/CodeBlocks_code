#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"

int main(){
    printf("Content-Type:text/html;charset=gbk\r\n\r\n");
    char* qs = getenv("query_string");
    printf("<html><head></head><body><p><span style = 'color:red'>À≠ «Œ“£ø£ø</span><br/>%s</p></body><html>", qs);
    return 0;
}
