#include "ddlcolumn.h"

DDLColumn::DDLColumn()
{

}

DDLColumn::~DDLColumn()
{
}

void DDLColumn::parseColumnInfo(const EDDL_OPTYPE &operType, const char *ptrBuf, int &totalLen)
{
    int len = 0;

    // 表操作类型
//    m_ddlOperType = operType;

    // 解析 字段名
    parseColumnName(ptrBuf, len);
    ptrBuf += len;
    totalLen += len;

    if (EDDL_OPTYPE::UPD == operType)
    {
        // 解析 字段变更类型
        parseChangeType(ptrBuf);
        ptrBuf += sizeof(EDDLCOLUMN_CHGTYPE);
        totalLen += sizeof(EDDLCOLUMN_CHGTYPE);

        if (EDDLCOLUMN_CHGTYPE::RNA == m_changeType)
        {
            // 解析 目的字段名
            parseDstFieldName(ptrBuf, len);
            ptrBuf += len;
            totalLen += len;
        }
    }

    if (EDDL_OPTYPE::UPD == operType
            && EDDLCOLUMN_CHGTYPE::DEL == m_changeType)
    {

    }
    else
    {
        // 字段类型
        parseColumnType(ptrBuf, len);
        ptrBuf += len;
        totalLen += len;

        // 空属性
        parseIsNull(ptrBuf);
        ptrBuf += sizeof(EDDL_IS_NULL);
        totalLen += sizeof(EDDL_IS_NULL);

        // 主键属性
        parseIsPrimary(ptrBuf);
        ptrBuf += sizeof(EDDL_IS_PRIMARY);
        totalLen += sizeof(EDDL_IS_PRIMARY);

        // 排序规则
        parseCollation(ptrBuf, len);
        ptrBuf += len;
        totalLen += len;

        // 字段描述
        parseDesc(ptrBuf, len);
        ptrBuf += len;
        totalLen += len;
    }
}

//void DDLColumn::setDDLOperType(const EDDL_OPTYPE &operType)
//{
//    m_ddlOperType = operType;
//}

void DDLColumn::transformStream(const EDDL_OPTYPE &operType)
{
    clearData();

    // 字段名
    DealData::putStringToData(m_data, m_columnName);
    DealData::putEndFlag(m_data);

    // 只有operType = 'U' 添加 字段变更类型
    if (EDDL_OPTYPE::UPD == operType)
    {
        DealData::putCharToData(m_data, static_cast<char>(m_changeType));

        // 目的字段名
        if (EDDLCOLUMN_CHGTYPE::RNA == m_changeType)
        {
            DealData::putStringToData(m_data, m_dstFieldName);
            DealData::putEndFlag(m_data);
        }
    }

    // 字段类型
    if (EDDL_OPTYPE::UPD == operType
            && EDDLCOLUMN_CHGTYPE::DEL == m_changeType)
    {

    }
    else
    {
        // 字段类型
        DealData::putStringToData(m_data, m_columnType);
        DealData::putEndFlag(m_data);

        // 空属性
        DealData::putCharToData(m_data, static_cast<char>(m_isNull));

        // 主键属性
        DealData::putCharToData(m_data, static_cast<char>(m_isPrimary));

        // 排序规则
        DealData::putStringToData(m_data, m_collation);
        DealData::putEndFlag(m_data);

        // 字段描述
        DealData::putStringToData(m_data, m_desc);
        DealData::putEndFlag(m_data);
    }
}

string DDLColumn::columnName() const
{
    return m_columnName;
}

void DDLColumn::setColumnName(const string &columnName)
{
    m_columnName = columnName;
}

void DDLColumn::parseColumnName(const char *ptrBuf, int &len)
{
    m_columnName = DealData::parseBufToString(ptrBuf, len);
}

EDDLCOLUMN_CHGTYPE DDLColumn::changeType() const
{
    return m_changeType;
}

void DDLColumn::setChangeType(const EDDLCOLUMN_CHGTYPE &changeType)
{
    m_changeType = changeType;
}

void DDLColumn::parseChangeType(const char *ptrBuf)
{
    m_changeType = static_cast<EDDLCOLUMN_CHGTYPE>(DealData::parseBufToChar(ptrBuf));
}

string DDLColumn::columnType() const
{
    return m_columnType;
}

void DDLColumn::setColumnType(const string &columnType)
{
    m_columnType = columnType;
}

void DDLColumn::parseColumnType(const char *ptrBuf, int &len)
{
    m_columnType = DealData::parseBufToString(ptrBuf, len);
}

EDDL_IS_NULL DDLColumn::isNull() const
{
    return m_isNull;
}

void DDLColumn::setIsNull(const EDDL_IS_NULL& isNull)
{
    m_isNull = isNull;
}

void DDLColumn::parseIsNull(const char *ptrBuf)
{
    m_isNull = static_cast<EDDL_IS_NULL>(DealData::parseBufToChar(ptrBuf));
}

EDDL_IS_PRIMARY DDLColumn::isPrimary() const
{
    return m_isPrimary;
}

void DDLColumn::setIsPrimary(const EDDL_IS_PRIMARY& isPrimary)
{
    m_isPrimary = isPrimary;
}

void DDLColumn::parseIsPrimary(const char *ptrBuf)
{
    m_isPrimary = static_cast<EDDL_IS_PRIMARY>(DealData::parseBufToChar(ptrBuf));
}

string DDLColumn::collation() const
{
    return m_collation;
}

void DDLColumn::setCollation(const string &collation)
{
    m_collation = collation;
}

void DDLColumn::parseCollation(const char *ptrBuf, int &len)
{
    m_collation = DealData::parseBufToString(ptrBuf, len);
}

string DDLColumn::desc() const
{
    return m_desc;
}

void DDLColumn::setDesc(const string &desc)
{
    m_desc = desc;
}

void DDLColumn::parseDesc(const char *ptrBuf, int &len)
{
    m_desc = DealData::parseBufToString(ptrBuf, len);
}

void DDLColumn::clear()
{
    clearStruct();

    clearData();
}

void DDLColumn::clearData()
{
    m_data.clear();
}

void DDLColumn::clearStruct()
{
    m_columnName.clear();
    m_changeType = EDDLCOLUMN_CHGTYPE::UNKNOWN;
    m_columnType.clear();
    m_isNull = EDDL_IS_NULL::UNKNOWN;
    m_isPrimary = EDDL_IS_PRIMARY::UNKNOWN;
    m_collation.clear();
    m_desc.clear();
}

void DDLColumn::showStructInfo() const
{
    cout << "m_columnName: " << m_columnName << endl;
    cout << "m_changeType: " << static_cast<int>(m_changeType) << endl;
    cout << "m_dstFieldName: " << m_dstFieldName << endl;
    cout << "m_columnType: " << m_columnType << endl;
    cout << "m_isNull: " << static_cast<char>(m_isNull) << endl;
    cout << "m_isPrimary: " << static_cast<char>(m_isPrimary) << endl;
    cout << "m_collation: " << m_collation << endl;
    cout << "m_desc: " << m_desc << endl;
}

string DDLColumn::getDstFieldName() const
{
    return m_dstFieldName;
}

void DDLColumn::setDstFieldName(const string &dstFieldName)
{
    m_dstFieldName = dstFieldName;
}

void DDLColumn::parseDstFieldName(const char *ptrBuf, int &len)
{
    m_dstFieldName = DealData::parseBufToString(ptrBuf, len);
}

