#ifndef H_PUB_STRUCT_HEADER_H
#define H_PUB_STRUCT_HEADER_H

#include <algorithm>
#include "packmsgtypeheader.h"

const string STR_TRIGGER_TRIGGERID_COL          = "TriggerId";
const string STR_TRIGGER_DB_TYPE_COL            = "DbType";
const string STR_TRIGGER_OPERTYPE_COL           = "OperType";

struct SUserInfo
{
    SUserInfo()
    {

    }

    SUserInfo(const string& strUser, const string& strPasswd, const string& strDsn)
    {
        user = strUser;
        passwd = strPasswd;
        dsn = strDsn;

        transform(user.begin(), user.end(), user.begin(), ::toupper);
        transform(dsn.begin(), dsn.end(), dsn.begin(), ::toupper);
    }

    SUserInfo& operator =(const SUserInfo& usrInfo)
    {
        user = usrInfo.user;
        passwd = usrInfo.passwd;
        dsn = usrInfo.dsn;

        transform(user.begin(), user.end(), user.begin(), ::toupper);
        transform(dsn.begin(), dsn.end(), dsn.begin(), ::toupper);

        return *this;
    }

    string user;           // 用户名
    string passwd;         // 密码
    string dsn;            // 数据库别名
};

struct SColDescInfo
{
    string name;
    int dbType;
    int otlDbType;
    int dbSize;
    int scale;
    int prec;
    int nullok;
};

struct STriggerInfo
{
    SUserInfo srcTabUserInfo;           // 原表用户信息
    string srcTabName;                  // 原表名
    vector<string> srcPriKeyNames;       // 原表主键列名 因可能是复合主键所以可能有多个
    string triTabName;                  // 触发器名
    string insertTriName;               // 增加相关的触发器
    string updateTriName;               // 更新相关的触发器
    string deleteTriName;               // 删除相关的触发器
    string insertTriSql;                // 创建插入相关的触发器SQL语句
    string updateTriSql;                // 创建更新相关的触发器SQL语句
    string deleteTriSql;                // 创建删除相关的触发器SQL语句
    string createTriTabSql;             // 创建触发器表的SQL语句
};
#endif // PUBSTRUCTHEADER_H
