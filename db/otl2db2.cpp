#include "otl2db2.h"

Otl2Db2::Otl2Db2(const SUserInfo &srcUser)
{
    otlLogOnDb(srcUser);
}

Otl2Db2::~Otl2Db2()
{

}

bool Otl2Db2::getColInfos(const string &strTabName, vector<SColDescInfo> &vecColInfos)
{
    // 获取db2的表结构信息
}

