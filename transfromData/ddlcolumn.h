#ifndef H_DDL_COL_UMN_H
#define H_DDL_COL_UMN_H

#include <iostream>
#include <string>
#include <vector>

#include "dealdata.h"

using namespace std;

class DDLColumn
{
public:
    DDLColumn();
    ~DDLColumn();

    // 解析流的信息入结构体
    void parseColumnInfo(const EDDL_OPTYPE& operType, const char* ptrBuf, int& totalLen);

    // 设置表操作类型
//    void setDDLOperType(const EDDL_OPTYPE& operType);

    // 将填充到结构体中内容打包成字节流, 该函数在所有字段信息填充完毕后主动调用
    void transformStream(const EDDL_OPTYPE& operType);

    string columnName() const;
    void setColumnName(const string &columnName);
    void parseColumnName(const char* ptrBuf, int& len);

    EDDLCOLUMN_CHGTYPE changeType() const;
    void setChangeType(const EDDLCOLUMN_CHGTYPE &changeType);
    void parseChangeType(const char* ptrBuf);

    string getDstFieldName() const;
    void setDstFieldName(const string &dstFieldName);
    void parseDstFieldName(const char* ptrBuf, int& len);

    string columnType() const;
    void setColumnType(const string &columnType);
    void parseColumnType(const char* ptrBuf, int& len);

    EDDL_IS_NULL isNull() const;
    void setIsNull(const EDDL_IS_NULL& isNull);
    void parseIsNull(const char* ptrBuf);

    EDDL_IS_PRIMARY isPrimary() const;
    void setIsPrimary(const EDDL_IS_PRIMARY& isPrimary);
    void parseIsPrimary(const char* ptrBuf);

    string collation() const;
    void setCollation(const string &collation);
    void parseCollation(const char* ptrBuf, int& len);

    string desc() const;
    void setDesc(const string &desc);
    void parseDesc(const char* ptrBuf, int& len);

    // 列中所有信息全部清除
    void clear();

    // 清除数据内容
    void clearData();

    // 清除struct内容
    void clearStruct();

    // 获取该列信息的具体数据
    const vector<char>& getColData()const {return m_data;}

public:
    //test
    void showStructInfo() const;



private:
    string m_columnName;
    EDDLCOLUMN_CHGTYPE m_changeType;
    string m_dstFieldName;                   //目的字段名
    string m_columnType;
    EDDL_IS_NULL m_isNull;
    EDDL_IS_PRIMARY m_isPrimary;
    string m_collation;
    string m_desc;
    vector<char> m_data;

//    EDDL_OPTYPE m_ddlOperType;              // 新增的表操作类型
};

#endif // DDLCOLUMN_H
