#include <iostream>
#include <unistd.h>

#include "dbconfreader.h"
//#include "otl2db2.h"
#include "otl2oracle.h"

using namespace std;

//void db2Operator1()
//{
//    // db2 数据库登录
//    Otl2Db2 otl2Db2(SUserInfo ("db2inst1", "zcj123", "demodb2"));

//    // db2 数据库创建测试表 table_src
//    string strSql1 = "drop table table_src";
//    string strSql2 = "create table table_src(id int, name varchar(30), score double)";
//    otl2Db2.otlExecSqlCmd(strSql1, false);
//    otl2Db2.otlExecSqlCmd(strSql2);

//    // db2 获取表结构数据内容
//    vector<SColDescInfo> vecDb2ColDesc;
//    otl2Db2.getColInfos("table_src", vecDb2ColDesc);
//    otl2Db2.otlLogOffDb();
//}

int main()
{
#if 0
    // 读取配置文件
    DbConfReader dbConfReader;
    dbConfReader.read("dbConf.json");
    dbConfReader.showReadInfo();
#endif
//    db2Operator1();

#if 0
    // ddl 组包将db2 table_src的表结构打包成2进制stream
    DDLPackage ddlPackage;
    // ddl 组包将2进制stream转化为Oracle的表结构
#endif

    Otl2Oracle otl2Oracle(SUserInfo("zcj", "123456", "10.111.24.11:1521/ora11g"));
    cout << 111 << endl;
    string strSql1 = "drop table table_src";
    string strSql2 = "create table table_src(id int, name varchar(30), score double)";
    cout << 222 << endl;
//    otl2Oracle.otlExecSqlCmd(strSql1, false);
//    otl2Oracle.otlExecSqlCmd(strSql2);
//    otl2Oracle.otlLogOffDb();
    return 0;
}


