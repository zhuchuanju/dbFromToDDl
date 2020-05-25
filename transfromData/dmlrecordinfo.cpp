#include "dmlrecordinfo.h"
#include "dealdata.h"


DMLRecordInfo::DMLRecordInfo()
{

}

DMLRecordInfo::~DMLRecordInfo()
{
    clear();
}

int DMLRecordInfo::transformStream(const vector<DMLColInfo>& vecDmlColInfo)
{
    if (m_rowVarints.size() != vecDmlColInfo.size())
    {
        cout << "record and tableCol colNum is not same" << endl;
        return -1;
    }

    clearData();

    // 该记录的操作类型
    DealData::putCharToData(m_vecRecData, static_cast<char>(m_recordType));

    for (unsigned int i = 0; i < m_rowVarints.size(); ++i)
    {
        const DMLColInfo& colInfo = vecDmlColInfo[i];
        const Variant& variant = m_rowVarints[i];

        if (EDML_COL_NULL::NOT_BE_NULL == colInfo.getColNULL())
        {
            transformVariantToStream(variant);
        }
        else if (EDML_COL_NULL::CAN_BE_NULL == colInfo.getColNULL())
        {
            // 该列值为NULL
            if (!variant.isValid())
            {
                DealData::putCharToData(m_vecRecData, static_cast<char>(EDML_VARIANT_NULL::IS_NULL));
            }
            else
            {
                DealData::putCharToData(m_vecRecData, static_cast<char>(EDML_VARIANT_NULL::IS_NOT_NULL));
                transformVariantToStream(variant);
            }
        }
    }

#if 0
    // 列值
    for (const Variant& variant : m_rowVarints)
    {
        if (Variant::Char == variant.type())
        {
            DealData::putIntToData(m_vecRecData, 1);
            DealData::putCharToData(m_vecRecData, variant.toChar());
        }
        else if (Variant::Short == variant.type())
        {
            DealData::putIntToData(m_vecRecData, 2);
            DealData::putShortToData(m_vecRecData, variant.toShort());
        }
        else if (Variant::Int == variant.type())
        {
            DealData::putIntToData(m_vecRecData, 4);
            DealData::putIntToData(m_vecRecData, variant.toInt());
        }
        else if (Variant::LongLong == variant.type())
        {
            DealData::putIntToData(m_vecRecData, 8);
            DealData::putLongLongToData(m_vecRecData, variant.toLongLong());
        }
        else if (Variant::Float == variant.type())
        {
            DealData::putIntToData(m_vecRecData, 4);
            DealData::putFloatToData(m_vecRecData, variant.toFloat());
        }
        else if (Variant::Double == variant.type())
        {
            DealData::putIntToData(m_vecRecData, 8);
            DealData::putDoubleToData(m_vecRecData, variant.toDouble());
        }
        else if (Variant::String == variant.type())
        {
            DealData::putIntToData(m_vecRecData, variant.toString().size());
            DealData::putStringToData(m_vecRecData, variant.toString());
        }
        else if (Variant::Bool == variant.type())
        {
            DealData::putIntToData(m_vecRecData, 1);
            DealData::putB2CToData(m_vecRecData, variant.toBool());
        }
        else if (Variant::BigBytes == variant.type())
        {
            vector<char> vecData = variant.toBigVector();

            DealData::putIntToData(m_vecRecData, vecData.size());
            DealData::putBigDataToData(m_vecRecData, vecData);
        }
        else
        {
            cout << "DMLRecordInfo::addRowVariant not find variant type : " << variant.toString() << endl;
        }
    }
#endif

    return 0;
}

void DMLRecordInfo::parseRecordInfo(const vector<DMLColInfo> &dmlColType, const char *ptrBuf, int &totalLen)
{
    parseRecordType(ptrBuf);
    ptrBuf += sizeof(EDMLRECORD_TYPE);
    totalLen += sizeof(EDMLRECORD_TYPE);

    for (const DMLColInfo& colType : dmlColType)
    {
        unsigned int dataLen = 0;

        //  解析数据
        addVariantData(colType, ptrBuf, dataLen);

        ptrBuf += dataLen;
        totalLen += dataLen;
    }
}

EDMLRECORD_TYPE DMLRecordInfo::recordType() const
{
    return m_recordType;
}

void DMLRecordInfo::setRecordType(const EDMLRECORD_TYPE &recordType)
{
    m_recordType = recordType;
}

void DMLRecordInfo::parseRecordType(const char *ptrBuf)
{
    m_recordType = static_cast<EDMLRECORD_TYPE>(DealData::parseBufToChar(ptrBuf));
}

void DMLRecordInfo::addRowVariant(const Variant &variant)
{
//    if (m_colAttrNull.size() == m_rowVarints.size())
//    {
//        cout << "col is full, please check col and variant num" << endl;
//        return ;
//    }

//    const EDML_COL_NULL& colAttrNull = m_colAttrNull.at(m_rowVarints.size());

//    if (colAttrNull)

    m_rowVarints.push_back(variant);
}

const vector<Variant> &DMLRecordInfo::getRowVariants()
{
    return m_rowVarints;
}

const Variant &DMLRecordInfo::getDmlCol(const unsigned int col) const
{
    if (col >= m_rowVarints.size())
    {
        cout << "DMLRecordInfo::getColVariant not find col: " << col << endl;
    }

    return m_rowVarints.at(col);
}

void DMLRecordInfo::clear()
{
    m_recordType = EDMLRECORD_TYPE::UNKNOWN;
    m_rowVarints.clear();

    m_vecRecData.clear();
}

void DMLRecordInfo::clearData()
{
    m_vecRecData.clear();
}

const vector<char> &DMLRecordInfo::getDmlRecordInfo() const
{
    return m_vecRecData;
}

void DMLRecordInfo::addVariantData(const DMLColInfo &colInfo, const char *ptrBuf, unsigned int &len)
{
    if (EDML_COL_NULL::NOT_BE_NULL == colInfo.getColNULL())
    {
        parserVariantInfo(colInfo.getColType(), ptrBuf, len);
    }
    else if (EDML_COL_NULL::CAN_BE_NULL == colInfo.getColNULL())
    {
        EDML_VARIANT_NULL isNull = static_cast<EDML_VARIANT_NULL>(DealData::parseBufToChar(ptrBuf));
        ptrBuf += sizeof(EDML_VARIANT_NULL);
        len += sizeof(EDML_VARIANT_NULL);

        if (EDML_VARIANT_NULL::IS_NULL == isNull)
        {
            m_rowVarints.push_back(Variant());
            return ;
        }
        else if (EDML_VARIANT_NULL::IS_NOT_NULL == isNull)
        {
            parserVariantInfo(colInfo.getColType(), ptrBuf, len);
        }
        else
        {
            cout << "err not find null variant attribute" << endl;
        }
    }
    else
    {
        cout << "err not find null attribute" << endl;
    }
}

void DMLRecordInfo::parserVariantInfo(const EDML_COL_TYPE &colType, const char *ptrBuf, unsigned int &len)
{
    switch (colType)
    {
    case EDML_COL_TYPE::DT_U_CHAR:
        m_rowVarints.push_back(DealData::parseBufToUnChar(ptrBuf));
        len += sizeof(unsigned char);
        break;
    case EDML_COL_TYPE::DT_CHAR:
        m_rowVarints.push_back(DealData::parseBufToChar(ptrBuf));
        len += sizeof(char);
        break;
    case EDML_COL_TYPE::DT_U_SHORT:
        m_rowVarints.push_back(DealData::parseBufToUnShort(ptrBuf));
        len += sizeof(unsigned short);
        break;
    case EDML_COL_TYPE::DT_SHORT:
        m_rowVarints.push_back(DealData::parseBufToShort(ptrBuf));
        len += sizeof(short);
        break;
    case EDML_COL_TYPE::DT_U_INT:
        m_rowVarints.push_back(DealData::parseBufToUnInt(ptrBuf));
        len += sizeof(unsigned int);
        break;
    case EDML_COL_TYPE::DT_INT:
        m_rowVarints.push_back(DealData::parseBufToInt(ptrBuf));
        len += sizeof(int);
        break;
    case EDML_COL_TYPE::DT_U_LONGLONG:
        m_rowVarints.push_back(DealData::parseBufToUnLongLong(ptrBuf));
        len += sizeof(unsigned long long);
        break;
    case EDML_COL_TYPE::DT_LONGLONG:
        m_rowVarints.push_back(DealData::parseBufToLongLong(ptrBuf));
        len += sizeof(long long);
        break;
    case EDML_COL_TYPE::DT_FLOAT:
        m_rowVarints.push_back(DealData::parseBufToFloat(ptrBuf));
        len += sizeof(float);
        break;
    case EDML_COL_TYPE::DT_DOUBLE:
        m_rowVarints.push_back(DealData::parseBufToDouble(ptrBuf));
        len += sizeof(double);
        break;
    case EDML_COL_TYPE::DT_STRING:
        {
            unsigned int lenStr = 0;
            m_rowVarints.push_back(DealData::parseBufToString(ptrBuf, lenStr));
            len += lenStr;
            break;
        }
    case EDML_COL_TYPE::DT_BOOL:
        m_rowVarints.push_back(DealData::parseBuftoBool(ptrBuf));
        len += sizeof(bool);
        break;
    case EDML_COL_TYPE::DT_BYTES:
        {
            unsigned int dataLen = DealData::parseBufToUnInt(ptrBuf);
            ptrBuf += sizeof(unsigned int);
            len += sizeof(unsigned int);

            Variant variant(DealData::parseBufToBigVector(ptrBuf, dataLen));
            m_rowVarints.push_back(variant);

            len += dataLen;
            break;
        }
    default:
        cout << "err DMLRecordInfo::parserVariantInfo() default: not find type" << endl;
        break;
    }
}

void DMLRecordInfo::transformVariantToStream(const Variant &variant)
{
    if (Variant::UChar == variant.type())
    {
        DealData::putUnCharToData(m_vecRecData, variant.toUchar());
    }
    else if (Variant::Char == variant.type())
    {
        DealData::putCharToData(m_vecRecData, variant.toChar());
    }
    else if (Variant::UShort == variant.type())
    {
        DealData::putUnShortToData(m_vecRecData, variant.toUShort());
    }
    else if (Variant::Short == variant.type())
    {
        DealData::putShortToData(m_vecRecData, variant.toShort());
    }
    else if (Variant::UInt == variant.type())
    {
        DealData::putUnIntToData(m_vecRecData, variant.toUInt());
    }
    else if (Variant::Int == variant.type())
    {
        DealData::putIntToData(m_vecRecData, variant.toInt());
    }
    else if (Variant::ULongLong == variant.type())
    {
        DealData::putLongLongToData(m_vecRecData, variant.toULongLong());
    }
    else if (Variant::LongLong == variant.type())
    {
        DealData::putLongLongToData(m_vecRecData, variant.toLongLong());
    }
    else if (Variant::Float == variant.type())
    {
        DealData::putFloatToData(m_vecRecData, variant.toFloat());
    }
    else if (Variant::Double == variant.type())
    {
        DealData::putDoubleToData(m_vecRecData, variant.toDouble());
    }
    else if (Variant::String == variant.type())
    {
        DealData::putStringToData(m_vecRecData, variant.toString());
        DealData::putEndFlag(m_vecRecData);
    }
    else if (Variant::Bool == variant.type())
    {
        DealData::putB2CToData(m_vecRecData, variant.toBool());
    }
    else if (Variant::BigBytes == variant.type())
    {
        vector<char> vecData = variant.toBigVector();

        DealData::putUnIntToData(m_vecRecData, vecData.size());
        DealData::putBigDataToData(m_vecRecData, vecData);
    }
    else
    {
        cout << "DMLRecordInfo::addRowVariant not find variant type : " << variant.toString() << endl;
    }
}

//void DMLRecordInfo::setColAttrNull(const vector<EDML_COL_NULL> &colAttrNull)
//{
//    m_colAttrNull.clear();
//    m_colAttrNull = colAttrNull;
//}

void DMLRecordInfo::printVecVariantInfo() const
{
    for (const Variant var : m_rowVarints)
    {
        if (!var.isValid())
            cout << "null" << endl;

        if (Variant::UChar == var.type())
        {
            cout << "unsigned char: " << var.toUchar() << endl;
        }
        else if (Variant::Char == var.type())
        {
            cout << "char: " << var.toChar() << endl;
        }
        else if (Variant::UShort == var.type())
        {
            cout << "unsigned short: " << var.toUShort() << endl;
        }
        else if (Variant::Short == var.type())
        {
            cout << "short: " << var.toShort() << endl;
        }
        else if (Variant::UInt == var.type())
        {
            cout << "unsigned int: " << var.toUInt() << endl;
        }
        else if (Variant::Int == var.type())
        {
            cout << "int: " << var.toInt() << endl;
        }
        else if (Variant::ULongLong == var.type())
        {
            cout << "unsigned long long: " << var.toULongLong() << endl;
        }
        else if (Variant::LongLong == var.type())
        {
            cout << "longlong: " << var.toLongLong() << endl;
        }
        else if (Variant::Float == var.type())
        {
            cout << "float: " << fixed << var.toFloat() << endl;
        }
        else if (Variant::Double == var.type())
        {
            cout << "double: " << fixed << var.toDouble() << endl;
        }
        else if (Variant::Bool == var.type())
        {
            cout << "bool: " << var.toBool() << endl;
        }
        else if (Variant::String == var.type())
        {
            cout << "string: " << var.toString() << endl;
        }
        else if (Variant::BigBytes == var.type())
        {
            cout << "bigBytes: ok but not print" << endl;
        }
        else
        {
            cout << "not find variant type please check..." << endl;
        }
    }
}

void DMLRecordInfo::showStructInfo() const
{
    cout << "m_recordType: " << static_cast<char>(m_recordType) << endl;

    printVecVariantInfo();
}

