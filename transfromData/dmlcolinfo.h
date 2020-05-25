#ifndef H_DML_COL_INFO_H
#define H_DML_COL_INFO_H

#include "packmsgtypeheader.h"

class DMLColInfo
{
public:
    DMLColInfo();
    ~DMLColInfo();

    // 打包 struct -> stream
    void transformStream();

    // 解析stream -> struct
    void parseColInfo(const char* ptrBuf, int& totalLen);

    string getStrColName() const;
    void setStrColName(const string &strColName);
    void parseStrColName(const char* ptrBuf, int& len);

    EDML_COL_TYPE getColType() const;
    void setColType(const EDML_COL_TYPE &colType);
    void parseColType(const char* ptrBuf);

    EDML_COL_NULL getColNULL() const;
    void setColNULL(const EDML_COL_NULL &colNULL);
    void parseColNULL(const char* ptrBuf);

    // 全部清除
    void clear();

    // 清除 m_vecDmlCol 中内容
    void clearData();

    // 获取该列的 vector 信息
    const vector<char>& getDmlColInfo()const;

public:
    void showStructInfo() const;



private:
    string m_strColName;                    // 列的名称
    EDML_COL_TYPE m_colType;                // 列的类型
    EDML_COL_NULL m_colNULL;                // 列是否可为NULL

    vector<char> m_vecDmlCol;
};

#endif // DMLCOLINFO_H
