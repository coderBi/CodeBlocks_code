#ifndef MYSQL_DAO_H
#define MYSQL_DAO_H
#include <winsock2.h>
#include <mysql.h>
#include "Po_Message.h"
#include <vector>
#include <exception>

class MySQL_Dao
{
    public:
        MySQL_Dao();
        virtual ~MySQL_Dao();
        long add(std::string sql);
        long deleteItem(std::string sql);
        long updateData(std::string sql);
        std::vector<MYSQL_ROW> queryList(std::string sql);
        MYSQL_ROW queryRow(std::string sql) throw(std::string);
        std::string queryOne(std::string sql) throw(std::string);

    protected:
    private:
        MYSQL * pMysql_Server;
};

#endif // MYSQL_DAO_H
