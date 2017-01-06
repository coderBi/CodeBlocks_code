#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"

int cgiMain()
{
    TMPL_varlist *varlist1 = 0;
    cgiHeaderContentType("text/html;charset=gbk");
    varlist1 = TMPL_add_var(varlist1, "name", "bww", "age", "18", 0);
    TMPL_write("template.html", 0, 0, varlist1, cgiOut, cgiOut);
    return 0;
}
