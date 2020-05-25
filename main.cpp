#include <iostream>

#include "dbconfreader.h"
#include "otl2db2.h"
#include "ddlpackage.h"

using namespace std;

int main()
{
    // 读取配置文件
    DbConfReader dbConfReader;
    dbConfReader.read("dbConf.json");
    dbConfReader.showReadInfo();

    // db2 数据库登录
    SUserInfo srcUser("db2inst1", "zcj123", "demodb2");
    Otl2Db2 otl2Db2(srcUser);


    // db2 数据库创建测试表 table_src
    string strSql1 = "drop table table_src";
    string strSql2 = "create table table_src(id int, name varchar(30), score double)";
    otl2Db2.otlExecSqlCmd(strSql1, false);
    otl2Db2.otlExecSqlCmd(strSql2);

    // db2 获取表结构数据内容
    otl2Db2
#if 0
    // ddl 组包将db2 table_src的表结构打包成2进制stream
    DDLPackage ddlPackage;
    // ddl 组包将2进制stream转化为Oracle的表结构
#endif

    return 0;
}
