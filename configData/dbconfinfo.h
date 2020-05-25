#ifndef H_DB_CONF_INFO_H
#define H_DB_CONF_INFO_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct SMapInfo
{
    string srcColType;
    string dstColType;
    string dstDatSize;

    void clear()
    {
        srcColType = "";
        dstColType = "";
        dstDatSize = "";
    }
};

struct SColDescInfo
{
    std::string name;
    int dbType;
    int otlDbType;
    int dbSize;
    int scale;
    int prec;
    int nullok;

    void clear()
    {
        name = "";
        dbType = 0;
        otlDbType = 0;
        dbSize = 0;
        scale = 0;
        prec = 0;
        nullok = 0;
    }

    void showColDescInfo()
    {
        std::cout << "name: " << name << std::endl;
        std::cout << "dbType: " << dbType << std::endl;
        std::cout << "otlDbType: " << otlDbType << std::endl;
        std::cout << "dbSize: " << dbSize << std::endl;
        std::cout << "scale: " << scale << std::endl;
        std::cout << "prec: " << prec << std::endl;
        std::cout << "nullok: " << nullok << std::endl;
    }
};

struct SUserInfo
{
    SUserInfo()
    {
        user = "";
        passwd = "";
        dsn = "";
        sqlDbName = "";
    }

    SUserInfo(const string& strUser, const string& strPasswd, const string& strDsn)
    {
        user = strUser;
        passwd = strPasswd;
        dsn = strDsn;
        sqlDbName = "";

        std::transform(user.begin(), user.end(), user.begin(), ::toupper);
        std::transform(dsn.begin(), dsn.end(), dsn.begin(), ::toupper);
    }

    SUserInfo(const string& strUser, const string& strPasswd, const string& strDsn, const string& dbName)
    {
        user = strUser;
        passwd = strPasswd;
        dsn = strDsn;
        sqlDbName = dbName;
    }

    SUserInfo& operator =(const SUserInfo& usrInfo)
    {
        user = usrInfo.user;
        passwd = usrInfo.passwd;
        dsn = usrInfo.dsn;
        sqlDbName = usrInfo.sqlDbName;

        return *this;
    }

    void clear()
    {
        user = "";
        passwd = "";
        dsn = "";
        sqlDbName = "";
    }

    std::string user;           // 用户名
    std::string passwd;         // 密码
    std::string dsn;            // 数据库别名
    std::string sqlDbName;      // 使用的db的名称
};


struct SSqlInfo
{
    string sqlInfo;
    SUserInfo userInfo;
    vector<SMapInfo> mapInfo;

    void clear()
    {
        sqlInfo = "";
        userInfo.clear();
        mapInfo.clear();
    }

    void showInfo()
    {
        cout << "sqlInfo : " << sqlInfo << endl;
        cout << "----------userInfo----------" << endl;
        cout << "user : " << userInfo.user << endl;
        cout << "passwd : " << userInfo.passwd << endl;
        cout << "dsn : " << userInfo.dsn << endl;
        cout << "dbName : " << userInfo.sqlDbName << endl;

        cout << "----------mapInfos----------" << endl;
        for (unsigned int i = 0; i < mapInfo.size(); ++i)
        {
            const SMapInfo& info = mapInfo.at(i);
            cout << "--num--" << i+1 << endl;
            cout << "srcColType : " << info.srcColType << endl;
            cout << "dstColType : " << info.dstColType << endl;
            cout << "dstDatSize : " << info.dstDatSize << endl;
        }
    }
};

#endif // DBCONFINFO_H
