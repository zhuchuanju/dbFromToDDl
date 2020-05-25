#ifndef H_BASE_OTL_2_DB_H
#define H_BASE_OTL_2_DB_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
//#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dbconfinfo.h"

//#if 0 //db2
#define ZCJ_DEFINE_DB2
#define OTL_DB2_CLI
//#endif

#define OTL_STL

#include "otlv4.h"

using namespace std;

class BaseOtl2Db
{
public:
    BaseOtl2Db();
    virtual ~BaseOtl2Db();

public:
    // 登录
    bool otlLogOnDb(const SUserInfo& userInfo);

    // 退出登录
    bool otlLogOffDb();

    // 重新登录
    bool otlLogOnDbAgain();

    // 执行操作数据库的命令 返回值只针对于 insert update delete 有效
    long otlExecSqlCmd(const string& strSql, bool bEnable = true);

protected:
    // 打印发生异常的错误信息
    void printCatchInfo(otl_exception& p);

protected:
    otl_connect m_db;               // connect object
    string m_strUserInfo;           // 用户登录信息

};

#endif // BASEOTL2DB_H
