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

struct SUserInfo
{
    string user;
    string passwd;
    string dsn;
    string dbName;

    void clear()
    {
        user = "";
        passwd = "";
        dsn = "";
        dbName = "";
    }
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
        cout << "dbName : " << userInfo.dbName << endl;

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
