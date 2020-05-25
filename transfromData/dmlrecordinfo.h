#ifndef H_DML_RECORD_INFO_H
#define H_DML_RECORD_INFO_H

#include "dmlcolinfo.h"
#include "variant.h"

class DMLRecordInfo
{
public:
    DMLRecordInfo();
//    DMLRecordInfo(const vector<EDML_COL_NULL>& colAttrNull);
    ~DMLRecordInfo();

    // struct -> stream
    int transformStream(const vector<DMLColInfo> &vecDmlColInfo);

    // 设置列的属性 解析字节流数据
    void parseRecordInfo(const vector<DMLColInfo> &dmlColType, const char* ptrBuf, int& totalLen);

    EDMLRECORD_TYPE recordType() const;
    void setRecordType(const EDMLRECORD_TYPE &recordType);
    void parseRecordType(const char* ptrBuf);

    void addRowVariant(const Variant& variant);
    const vector<Variant>& getRowVariants();

    // 从第0列开始
    const Variant& getDmlCol(const unsigned int col) const;

    // 全部清除
    void clear();

    // 清除 m_vecRecData 中的数据内容
    void clearData();

    // 获取该行内容信息
    const vector<char>& getDmlRecordInfo() const;

    // 根据列类型解析stream 组成类的成员变量
    void addVariantData(const DMLColInfo& colInfo, const char* ptrBuf, unsigned int &len);

    // 具体解析 stream-> Variant 中去
    void parserVariantInfo(const EDML_COL_TYPE& colType, const char* ptrBuf, unsigned int &len);

    // 将 m_rowVarints 中所有的 variant 转化为字节流
    void transformVariantToStream(const Variant& variant);

    // 设置各列是否为NULL的属性
//    void setColAttrNull(const vector<EDML_COL_NULL>& colAttrNull);

    //测试打印信息
public:
    void printVecVariantInfo() const;

    // 显示结构体内容信息
    void showStructInfo() const;

private:
    EDMLRECORD_TYPE m_recordType;        // 该记录的操作类型
    vector<Variant> m_rowVarints;        // 一行数据
//    vector<EDML_COL_NULL> m_colAttrNull; // 列中是否可为NULL的属性

    vector<char> m_vecRecData;

};

#endif // DMLRECORDINFO_H
