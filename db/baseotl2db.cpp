#include "baseotl2db.h"

BaseOtl2Db::BaseOtl2Db()
{
    otl_connect::otl_initialize();
}

BaseOtl2Db::~BaseOtl2Db()
{
    otlLogOffDb();
}

bool BaseOtl2Db::otlLogOnDb(const SUserInfo& userInfo)
{
    try{
        m_strUserInfo = userInfo.user + "/" + userInfo.passwd + "@" + userInfo.dsn;
        m_db.rlogon(m_strUserInfo.c_str());

    }catch(otl_exception& p)
    {
        printCatchInfo(p);
        return false;
    }

    return true;
}

bool BaseOtl2Db::otlLogOffDb()
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

bool BaseOtl2Db::otlLogOnDbAgain()
{
    try{

        m_db.rlogon(m_strUserInfo.c_str());

    }catch(otl_exception& p)
    {
        printCatchInfo(p);
        return false;
    }

    return true;
}

long BaseOtl2Db::otlExecSqlCmd(const string &strSql, bool bEnable)
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

void BaseOtl2Db::printCatchInfo(otl_exception &p)
{
    cout << "msg: " << p.msg << endl;
    cout << "stm_text: " << p.stm_text << endl;
    cout << "sqlstate: " << p.sqlstate << endl;
    cout << "var_info: " << p.var_info << endl;
}
