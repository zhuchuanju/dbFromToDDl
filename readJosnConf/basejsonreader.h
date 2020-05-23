#ifndef H_BASE_JSON_READER_H
#define H_BASE_JSON_READER_H

#include <iostream>
#include <string>
#include <assert.h>

#ifdef WIN32
#include "../../linuxHeader/json/json.h"
#else
#include "json/json.h"
#endif

using namespace std;

const string STR_DB_CONF_SQL_INFO       = "sqlInfo";
const string STR_DB_CONF_USER_INFO      = "userInfo";
const string STR_DB_CONF_USER           = "user";
const string STR_DB_CONF_PASSWD         = "passwd";
const string STR_DB_CONF_DSN            = "dsn";
const string STR_DB_CONF_DBNAME         = "dbName";
const string STR_DB_CONF_MAPINFO        = "mapInfo";
const string STR_DB_CONF_SRCCOLTYPE     = "srcColType";
const string STR_DB_CONF_DSTCOLTYPE     = "dstColType";
const string STR_DB_CONF_DSTDATSIZE     = "dstDatSize";

class BaseJsonReader
{
public:
    BaseJsonReader();
    virtual ~BaseJsonReader();

public:
    bool read(const string &fileName);
    virtual void dataClear() = 0;

protected:
    virtual bool readDetails(const Json::Value &value) = 0;
};

#endif // BASEJSONREADER_H
