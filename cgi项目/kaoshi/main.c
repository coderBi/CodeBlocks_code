#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include <string.h>

int cgiMain()
{
    cgiHeaderContentType("text/html;charse=gbk");
    char ti1[10], *_ti1 = "a";
    char *ti2[] = {"a", "b", "c"};
    int ti2Res[3] = {0};
    int ti2Invalid;
    char ti3[10] = {0}, *_ti3 = "nannv";
    fprintf(cgiOut, "<html><head></head><body>");
    if(cgiFormSuccess != cgiFormString("ti1", ti1, sizeof(ti1))){
        fprintf(cgiOut, "单选题没做！<br>");
    }
    else if(strcmp(ti1, _ti1) == 0){
        fprintf(cgiOut, "单选题正确！<br>");
    } else {
        fprintf(cgiOut, "单选题错误！<br>");
    }

    if(cgiFormCheckboxMultiple("ti2", ti2, 3, ti2Res, &ti2Invalid) != cgiFormSuccess){
        fprintf(cgiOut, "多选题没做！<br>");
    } else if(ti2Res[0] == 1 && ti2Res[1] == 1 && ti2Res[2] == 1){
        fprintf(cgiOut, "多选题正确！<br>");
    } else {
        fprintf(cgiOut, "多选题错误！<br>");
    }
    if(cgiFormSuccess != cgiFormString("sex", ti3, sizeof(ti3))){
        fprintf(cgiOut, "性别题没做！<br>");
    }
    else if(strcmp(ti3, _ti3) == 0){
        fprintf(cgiOut, "性别题正确！<br>");
    } else {
        fprintf(cgiOut, "性别题错误！<br>");
    }
    fprintf(cgiOut, "</body></html>");
    return 0;
}
