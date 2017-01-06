#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"

int cgiMain()
{
    cgiHeaderContentType("text/html;charset= gbk");
    TMPL_varlist *mainframe = 0;
    TMPL_loop *varloop = 0;
    mainframe = TMPL_add_var(mainframe, "title", "template_loop", 0);
    varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "bww", "age", "18", 0));
    varloop = TMPL_add_varlist(varloop, TMPL_add_var(0, "name", "ww", "age", "20", 0));
    mainframe = TMPL_add_loop(mainframe, "users", varloop);
    TMPL_write("tmplloop.html", 0, 0, mainframe, cgiOut, cgiOut);
    return 0;
}
