#include "dbconfreader.h"

DbConfReader::DbConfReader()
{
    dataClear();
}

DbConfReader::~DbConfReader()
{

}

void DbConfReader::dataClear()
{
    m_sqlInfo.clear();
}

void DbConfReader::showReadInfo()
{
    m_sqlInfo.showInfo();
}

bool DbConfReader::readDetails(const Json::Value &value)
{
    bool find = false;

    find |= readSqlInfo(value);
    find |= readUserInfo(value);
    find |= readMapInfo(value);

    return find;
}

bool DbConfReader::readSqlInfo(const Json::Value &value)
{
    m_sqlInfo.sqlInfo = value[STR_DB_CONF_SQL_INFO].asString();

    return true;
}

bool DbConfReader::readUserInfo(const Json::Value &value)
{
    m_sqlInfo.userInfo.user = value[STR_DB_CONF_USER_INFO][STR_DB_CONF_USER].asString();
    m_sqlInfo.userInfo.passwd = value[STR_DB_CONF_USER_INFO][STR_DB_CONF_PASSWD].asString();
    m_sqlInfo.userInfo.dsn = value[STR_DB_CONF_USER_INFO][STR_DB_CONF_DSN].asString();
    m_sqlInfo.userInfo.sqlDbName = value[STR_DB_CONF_USER_INFO][STR_DB_CONF_DBNAME].asString();

    return true;
}

bool DbConfReader::readMapInfo(const Json::Value &value)
{
    for (unsigned int i = 0; i < value[STR_DB_CONF_MAPINFO].size(); ++i)
    {
        SMapInfo mapInfo;
        mapInfo.srcColType = value[STR_DB_CONF_MAPINFO][i][STR_DB_CONF_SRCCOLTYPE].asString();
        mapInfo.dstColType = value[STR_DB_CONF_MAPINFO][i][STR_DB_CONF_DSTCOLTYPE].asString();
        mapInfo.dstDatSize = value[STR_DB_CONF_MAPINFO][i][STR_DB_CONF_DSTDATSIZE].asString();

        m_sqlInfo.mapInfo.push_back(mapInfo);
    }

    return true;
}
