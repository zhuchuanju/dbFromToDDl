#include "otl2db2.h"

Otl2Db2::Otl2Db2(const SUserInfo &srcUser)
    : m_usrInfo(srcUser)
{
    otlLogOnDb(srcUser.user + "/" + srcUser.passwd + "@" + srcUser.dsn);
}

Otl2Db2::~Otl2Db2()
{
    otlLogOffDb();
}

bool Otl2Db2::otlLogOnDb(const string &strUserInfo)
{
    try{
        m_db.rlogon(strUserInfo.c_str());

    }catch(otl_exception& p)
    {
        printCatchInfo(p);
        return false;
    }

    return true;
}

bool Otl2Db2::otlLogOffDb()
{
    try{

        m_db.logoff();

    }catch(otl_exception& p)
    {
        printCatchInfo(p);
        return false;
    }

    return true;
}

bool Otl2Db2::otlLogOnDbAgain()
{
    return otlLogOnDb(m_usrInfo.user + "/" + m_usrInfo.passwd + "@" + m_usrInfo.dsn);
}

long Otl2Db2::otlExecSqlCmd(const string &strSql, bool bEnable)
{
    long resRes = 0;

    try{
        if (!bEnable)
        {
            resRes = otl_cursor::direct_exec(m_db, strSql.c_str(), otl_exception::disabled);
        }
        else
        {
            resRes = otl_cursor::direct_exec(m_db, strSql.c_str());
        }
    }catch(otl_exception& p)
    {
        printCatchInfo(p);
    }

    return resRes;
}

bool Otl2Db2::getColInfos(const string &strTabName, vector<SColDescInfo> &vecColInfos)
{
    // 获取db2的表结构信息
    if (!existTable(strTabName))
    {
        cout << "not exist table: " << strTabName << endl;
        return false;
    }

    int colNum = 0;
    string strSql = "select * from " + m_usrInfo.user + "." + strTabName;

    try{
        otl_stream streamData(1, strSql.c_str(), m_db);
        otl_column_desc* ptr = streamData.describe_select(colNum);

        if (!ptr)
        {
            cout << "get col info error " << endl;
        }
        else
        {
            for (int i = 0; i < colNum; ++i)
            {
                SColDescInfo colDesInfo({ptr[i].name, ptr[i].dbtype,
                                         ptr[i].otl_var_dbtype,
                                         ptr[i].dbsize, ptr[i].scale,
                                         ptr[i].prec, ptr[i].nullok});

                colDesInfo.showColDescInfo();

                vecColInfos.push_back(colDesInfo);
            }
        }

    }catch(otl_exception& p)
    {
        printCatchInfo(p);
        return false;
    }

    return true;
}

void Otl2Db2::printCatchInfo(otl_exception &p)
{
    cout << "msg: " << p.msg << endl;
    cout << "stm_text: " << p.stm_text << endl;
    cout << "sqlstate: " << p.sqlstate << endl;
    cout << "var_info: " << p.var_info << endl;
}

int Otl2Db2::existTable(const string &strTableName)
{
    int resResult = 0;
    string strSql = "select 1 from syscat.tables where tabname=upper('" + strTableName + "') "
                    "and tabschema=upper('" + m_usrInfo.user + "')";

//    cout << "strSql: " << strSql << endl;
    try{

        otl_stream o(1, strSql.c_str(), m_db );
        o >> resResult;
    }catch(otl_exception& p)
    {
        printCatchInfo(p);
    }

    return resResult;
}

