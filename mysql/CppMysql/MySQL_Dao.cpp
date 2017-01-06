#include "MySQL_Dao.h"
#include <iostream>
#include <stdlib.h>

MySQL_Dao::MySQL_Dao()
{
    //ctor
    std::cout << "class MySQL_Dao construct in" << std::endl;
    pMysql_Server = mysql_init(0);
    if(!pMysql_Server){
        std::cout << "mysql_init fail..." << std::endl;
        exit(-1);
    }
    if(!mysql_real_connect(pMysql_Server,"localhost","root","123","learn_mysql",0,NULL,0)){
        std::cout <<  mysql_error(pMysql_Server) << std::endl << "connect db fail, check the setting..." << std::endl;
        exit(-1);
    }
    //std::cout << "connect db successfully" << std::endl;
    mysql_query(pMysql_Server,"set names utf8");
}

MySQL_Dao::~MySQL_Dao()
{
    //dtor
    std::cout << "class MySQL_Dao destruct out" << std::endl;
    mysql_close(pMysql_Server);
}

long MySQL_Dao::add(std::string sql){ //mysql_query 无论是有无结果集，都是成功返回 0 ，失败返回其他数字
    if(mysql_query(pMysql_Server,sql.c_str())){ //返回非 0， 执行失败
        std::cout << mysql_error(pMysql_Server) << std::endl;
        //throw(std::string(mysql_error(pMysql_Server)));
        return -1;
    }
    return mysql_affected_rows(pMysql_Server); //执行成功，返回受影响的数目
}

long MySQL_Dao::deleteItem(std::string sql){
    if(mysql_query(pMysql_Server,sql.c_str())){ //返回非 0， 执行失败
        throw(mysql_error(pMysql_Server));
        return -1;
    }
    return mysql_affected_rows(pMysql_Server); //执行成功，返回受影响的数目
}

std::vector<MYSQL_ROW> MySQL_Dao::queryList(std::string sql){
    std::vector<MYSQL_ROW> toReturn;
    if(mysql_query(pMysql_Server,sql.c_str()) == 0){
        MYSQL_RES * pResult = mysql_store_result(pMysql_Server); //存贮返回的结果
        MYSQL_ROW row;
        while( (row = mysql_fetch_row(pResult)) ){
            toReturn.push_back(row);
        }
        mysql_free_result(pResult);
    }
    return toReturn;
}

MYSQL_ROW MySQL_Dao::queryRow(std::string sql) throw(std::string){
    std::vector<MYSQL_ROW> qList = this->queryList(sql);
    if(qList.size() == 0){
        throw std::string("the result contains no content, while there should be one row!");
    }
    return qList[0];
}

std::string MySQL_Dao::queryOne(std::string sql) throw(std::string){
    try{
        MYSQL_ROW mr= this->queryRow(sql); //MYSQL_ROW 其实是 char **
        unsigned int count = mysql_field_count(pMysql_Server);
        if(count == 0){
            throw std::string("there is no content while querying one");
        }
        return mr[0];
    } catch(std::string){
        throw std::string("there is no content while querying one");
    }

}

long MySQL_Dao::updateData(std::string sql){
    if(mysql_query(pMysql_Server,sql.c_str())){ //返回非 0， 执行失败
        std::cout << mysql_error(pMysql_Server) << std::endl;
        //throw(std::string(mysql_error(pMysql_Server)));
        return -1;
    }
    return mysql_affected_rows(pMysql_Server); //执行成功，返回受影响的数目
}
