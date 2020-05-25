#include "dmlcolinfo.h"
#include "dealdata.h"

DMLColInfo::DMLColInfo()
{

}

DMLColInfo::~DMLColInfo()
{
    clear();
}

void DMLColInfo::transformStream()
{
    clearData();

    // 列名
    DealData::putStringToData(m_vecDmlCol, m_strColName);
    DealData::putEndFlag(m_vecDmlCol);

    // 列类型
    DealData::putCharToData(m_vecDmlCol, static_cast<char>(m_colType));

    // 该列是否可为NULL
    DealData::putCharToData(m_vecDmlCol, static_cast<char>(m_colNULL));
}

void DMLColInfo::parseColInfo(const char *ptrBuf, int &totalLen)
{
    int len = 0;

    // 列的名称
    parseStrColName(ptrBuf, len);
    ptrBuf += len;
    totalLen += len;

    // 列的类型
    parseColType(ptrBuf);
    ptrBuf += sizeof(EDML_COL_TYPE);
    totalLen += sizeof(EDML_COL_TYPE);

    // 列的空属性
    parseColNULL(ptrBuf);
    ptrBuf += sizeof(EDML_COL_NULL);
    totalLen += sizeof(EDML_COL_NULL);
}

string DMLColInfo::getStrColName() const
{
    return m_strColName;
}

void DMLColInfo::setStrColName(const string &strColName)
{
    m_strColName = strColName;
}

void DMLColInfo::parseStrColName(const char *ptrBuf, int &len)
{
    m_strColName = DealData::parseBufToString(ptrBuf, len);
}

EDML_COL_TYPE DMLColInfo::getColType() const
{
    return m_colType;
}

void DMLColInfo::setColType(const EDML_COL_TYPE &colType)
{
    m_colType = colType;
}

void DMLColInfo::parseColType(const char *ptrBuf)
{
    m_colType = static_cast<EDML_COL_TYPE>(DealData::parseBufToChar(ptrBuf));
}

void DMLColInfo::clear()
{
    m_strColName.clear();
    m_colType = EDML_COL_TYPE::DT_UNKNOWN;

    m_vecDmlCol.clear();
}

void DMLColInfo::clearData()
{
    m_vecDmlCol.clear();
}

const vector<char> &DMLColInfo::getDmlColInfo() const
{
    return m_vecDmlCol;
}

void DMLColInfo::showStructInfo() const
{
    cout << "m_strColName: " << m_strColName << endl;
    cout << "m_colType: " << static_cast<char>(m_colType) << endl;
    cout << "m_colNULL: " << static_cast<char>(m_colNULL) << endl;
}

EDML_COL_NULL DMLColInfo::getColNULL() const
{
    return m_colNULL;
}

void DMLColInfo::setColNULL(const EDML_COL_NULL &colNULL)
{
    m_colNULL = colNULL;
}

void DMLColInfo::parseColNULL(const char *ptrBuf)
{
    m_colNULL = static_cast<EDML_COL_NULL>(DealData::parseBufToChar(ptrBuf));
}
