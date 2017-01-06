#include <stdio.h>
#include <stdlib.h>
#include "cgic.h"
#include "ctemplate.h"
#include <winsock.h>
#include <mysql.h>

int main()
{
    MYSQL *mysql = mysql_init(0);
    if(!mysql_real_connect(mysql, "localhost", "root", "123", "study1", 0, 0, 0)){
        printf("无法连接数据库！%s\n", mysql_error(mysql));
        goto exit;
    }
    if(mysql_query(mysql,"set names gbk")){
        printf("设置字符集为gbk失败！%s\n", mysql_error(mysql));
        goto exit;
    }
    if(mysql_query(mysql,"insert into t_users(name,password) values('李磊','123')")){
        printf("插入语句失败！%s\n", mysql_error(mysql));
        goto exit;
    }
    printf("全部执行完成！\n");
exit:
    mysql_close(mysql);
    return 0;
}
