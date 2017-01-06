#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"

int cgiMain()
{
    cgiHeaderContentType("text/html;charse=gbk");
    TMPL_varlist * varlist =0;
    if(cgiFormSubmitClicked("submit") == cgiFormSuccess){
        int len;
        cgiFormStringSpaceNeeded("txt1", &len);
        printf("len = %d", len); //通过打印长度发现 浏览器遇到字符串中的 "\r\n" 不会解释为一个换行，也就是显示丢失了
        char *result = (char*)malloc(sizeof(char) *(len +1));
        cgiFormString("txt1", result, len +1);
        varlist = TMPL_add_var(varlist,"textarea",result,"msg",result,0);

    } else{
        varlist = TMPL_add_var(varlist,"textarea","","msg","",0);
    }
    TMPL_write("getTextarea.html", 0, 0, varlist, cgiOut, cgiOut);
    return 0;
}
