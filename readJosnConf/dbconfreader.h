#ifndef H_DBCONF_READER_H
#define H_DBCONF_READER_H

#include "dbconfinfo.h"
#include "basejsonreader.h"

class DbConfReader : public BaseJsonReader
{
public:
    DbConfReader();
    ~DbConfReader();

public:
    virtual void dataClear() override;

public: // test
    void showReadInfo();

private:
    virtual bool readDetails(const Json::Value &value) override;

    bool readSqlInfo(const Json::Value &value);
    bool readUserInfo(const Json::Value &value);
    bool readMapInfo(const Json::Value &value);

private:
    SSqlInfo m_sqlInfo;
};

#endif // DBCONFREADER_H
