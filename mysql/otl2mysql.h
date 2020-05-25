#ifndef H_OTL_2_MYSQL_H
#define H_OTL_2_MYSQL_H

#include <iostream>
#include <string>

#include <stdio.h>
#include <string.h>
#include "dbconfinfo.h"

//#define OTL_STL
#define OTL_ODBC_UNIX
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE

#include "otlv4.h"
class Otl2Mysql
{
public:
    Otl2Mysql(const SUserInfo& srcUser);
    ~Otl2Mysql();

public:
    // 登录
    bool otlLogOnDb(const string& strUserInfo);

    // 退出登录
    bool otlLogOffDb();

    // 重新登录
    bool otlLogOnDbAgain();

    // 执行操作数据库的命令 返回值只针对于 insert update delete 有效
    long otlExecSqlCmd(const string& strSql, bool bEnable = true);

    // 根据表名 获取表结构列信息
    bool getColInfos(const string& strTabName, vector<SColDescInfo>& vecColInfos);

private:
    // 打印发生异常的错误信息
    void printCatchInfo(otl_exception& p);

    // 判断该表是否存在
    int existTable(const string& strTableName);


private:
    SUserInfo m_usrInfo;            // 用户登录信息
    otl_connect m_db;               // connect object
};

#endif // OTL2MYSQL_H
