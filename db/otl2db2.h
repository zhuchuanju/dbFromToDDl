#ifndef H_OTL_2_DB2_H
#define H_OTL_2_DB2_H



#include "baseotl2db.h"

class Otl2Db2 : public BaseOtl2Db
{
public:
    Otl2Db2(const SUserInfo& srcUser);
    ~Otl2Db2();

    // 根据表名 获取表结构列信息
    bool getColInfos(const string& strTabName, vector<SColDescInfo>& vecColInfos);

};

#endif // OTL2DB2_H
