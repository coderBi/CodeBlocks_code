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
        printf("�޷��������ݿ⣡%s\n", mysql_error(mysql));
        goto exit;
    }
    if(mysql_query(mysql,"set names gbk")){
        printf("�����ַ���Ϊgbkʧ�ܣ�%s\n", mysql_error(mysql));
        goto exit;
    }
    if(mysql_query(mysql,"insert into t_users(name,password) values('����','123')")){
        printf("�������ʧ�ܣ�%s\n", mysql_error(mysql));
        goto exit;
    }
    printf("ȫ��ִ����ɣ�\n");
exit:
    mysql_close(mysql);
    return 0;
}
