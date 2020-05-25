#include "dmlpackage.h"
#include "dealdata.h"

const int DML_INT_RECORD_MAX_NUM = 1000;
const int DML_INT_SIZE_MAX_NUM = 10;           // 单位是 M

DMLPackage::DMLPackage()
    : m_msgType(EPKG_MSGTYPE::DML)
    , m_recordMaxNum(DML_INT_RECORD_MAX_NUM)
    , m_unitMaxValue(DML_INT_SIZE_MAX_NUM*1024*1024)
{
    clear();
}

DMLPackage::DMLPackage(const EPKG_VERTYPE &msgVer)
    : m_msgVer(msgVer)
    , m_msgType(EPKG_MSGTYPE::DML)
    , m_recordMaxNum(DML_INT_RECORD_MAX_NUM)
    , m_unitMaxValue(DML_INT_SIZE_MAX_NUM*1024*1024)
{
    clear();
}

DMLPackage::~DMLPackage()
{
    clear();
}

int DMLPackage::parseStream(const char *pbuff, const int buffLen)
{
    // buf[0] = '版本' buf[1] = '操作类型'  bufflen不可能小于2
    if (buffLen < 2)
    {
        cout << "dml pack parseStream err" << endl;
        return -1;
    }

    if (nullptr == pbuff)
    {
        cout << "dml pack parseStream err ptr nullptr " << endl;
        return -2;
    }

    // 清理一下
    clear();

    int posLen = 0; //偏移量
    const char* ptrBuff = pbuff;

    // 消息版本号
    parseVersion(ptrBuff);
    ptrBuff += sizeof(char);

    // 消息类型
    if (!parseMsgType(ptrBuff))
    {
        cout << "err stream type is not dml" << endl;
    }
    ptrBuff += sizeof(char);

    // 源端ID
    parseSrcId(ptrBuff);
    ptrBuff += sizeof(unsigned short);

    // 源数据类型
    parseDbType(ptrBuff);
    ptrBuff += sizeof(EDB_TYPE);

    // 该消息的操作类型
    parseOpType(ptrBuff);
    ptrBuff += sizeof(EDML_OPTYPE);

    // 目的表名
    parseDstTableName(ptrBuff, posLen);
    ptrBuff += posLen;

    // 源表的时区
    parseTimeZone(ptrBuff, posLen);
    ptrBuff += posLen;

    // 字符类型的编码
    parseCodeType(ptrBuff);
    ptrBuff += sizeof(EDML_CODETYPE);

    parseBeginTime(ptrBuff);
    ptrBuff += sizeof(unsigned int);

    parseMsgColNum(ptrBuff);
    ptrBuff += sizeof(unsigned short);

    // 解析列信息 根据列数目 解析列的名称 和类型
    for (unsigned short i = 0; i < m_msgColNum; ++i)
    {
        int len = 0;
        DMLColInfo dmlColInfo;
        dmlColInfo.parseColInfo(ptrBuff, len);
        ptrBuff += len;
        m_columns.push_back(dmlColInfo);
    }

    // 解析记录数目大小
    parseMsgRowNum(ptrBuff);
    ptrBuff += sizeof(int);

    for (int i = 0; i < m_msgRowNum; ++i)
    {
        int len = 0;
        DMLRecordInfo dmlRecordInfo;
        dmlRecordInfo.parseRecordInfo(m_columns, ptrBuff, len);
        ptrBuff += len;
        m_records.push_back(dmlRecordInfo);
    }

    return 0;
}

int DMLPackage::package(char * const pbuff, int &dataLen)
{
    unsigned int headSize = m_vecPackHeadr.size();

    for (unsigned int i = 0; i < headSize; ++i)
    {
        pbuff[i] = m_vecPackHeadr[i];
    }

    for (unsigned int i = 0; i < m_vecRows.size(); ++i)
    {
        pbuff[i+headSize] = m_vecRows[i];
    }

    dataLen = m_vecPackHeadr.size() + m_vecRows.size();

    return 0;
}

int DMLPackage::getStreamBuffLen()
{
    return m_vecPackHeadr.size() + m_vecRows.size();
}

void DMLPackage::clear()
{
    // 清空struct信息
//    m_msgVer = EPKG_VERTYPE::DT_VER_NULL;
    m_srcId = 0;
    m_dbType = EDB_TYPE::DT_NULL;
    m_opType = EDML_OPTYPE::UNKNOWN;
    m_dstTableName.clear();
    m_timeZone.clear();
    m_codeType = EDML_CODETYPE::UNKNOWN;
    m_beginTime = 0;
    m_msgColNum = 0;
    m_msgRowNum = 0;

    m_columns.clear();
    m_records.clear();

    m_vecPackHeadr.clear();
    m_vecRows.clear();

//    DealData::putCharToData(m_vecPackHeadr, static_cast<char>(getMsgVersion()));

    // 类型默认 为 'M'
//    DealData::putCharToData(m_vecPackHeadr, static_cast<char>(getMsgType()));
}

void DMLPackage::clearRecords()
{
    // 清除Record 结构信息
    m_records.clear();

    // 清除Record 字节信息
    m_vecRows.clear();

    // 记录数默认 为 0
    DealData::putIntToData(m_vecRows, 0);
}

void DMLPackage::transformStreamHeader()
{
    m_vecPackHeadr.clear();

    // 消息版本号
    DealData::putCharToData(m_vecPackHeadr, static_cast<char>(m_msgVer));

    // 消息类型
    DealData::putCharToData(m_vecPackHeadr, static_cast<char>(m_msgType));

    // 源端ID
    DealData::putUnShortToData(m_vecPackHeadr, m_srcId);

    // 源数据类型
    DealData::putIntToData(m_vecPackHeadr, static_cast<int>(m_dbType));

    // 该消息的操作类型
    DealData::putCharToData(m_vecPackHeadr, static_cast<char>(m_opType));

    // 目的表名
    DealData::putStringToData(m_vecPackHeadr, m_dstTableName);
    DealData::putEndFlag(m_vecPackHeadr);

    // 源表的时区
    DealData::putStringToData(m_vecPackHeadr, m_timeZone);
    DealData::putEndFlag(m_vecPackHeadr);

    // 字符类型的编码
    DealData::putCharToData(m_vecPackHeadr, static_cast<char>(m_codeType));

    // 采集服务开始采集的时间
    DealData::putUnIntToData(m_vecPackHeadr, m_beginTime);

    // 该消息中列的数目
    DealData::putUnShortToData(m_vecPackHeadr, m_msgColNum);

    // 列的名称 及 类型 1-n
    for (const DMLColInfo& dmlCol : m_columns)
    {
        const vector<char>& colVecData = dmlCol.getDmlColInfo();
        m_vecPackHeadr.insert(m_vecPackHeadr.end(), colVecData.begin(), colVecData.end());
    }

    // 行数信息 默认是 0 用 四个字节表示
    clearRecords();
}

void DMLPackage::parseVersion(const char *pbuff)
{
    m_msgVer = static_cast<EPKG_VERTYPE>(DealData::parseBufToChar(pbuff));
}

bool DMLPackage::parseMsgType(const char *pbuff)
{
    m_msgType = static_cast<EPKG_MSGTYPE>(DealData::parseBufToChar(pbuff));

    if (EPKG_MSGTYPE::DML == m_msgType)
        return true;

    return false;
}

//string DMLPackage::getVersion() const
//{
//    return m_version;
//}

//void DMLPackage::setVersion(const string &version)
//{
//    m_version = version;
//}

//void DMLPackage::parseVersion(const char *pbuff, int &len)
//{
//    m_version = DealData::parseBufToString(pbuff, len);
//}

unsigned short DMLPackage::getSrcId() const
{
    return m_srcId;
}

void DMLPackage::setSrcId(const unsigned short srcId)
{
    m_srcId = srcId;
}

void DMLPackage::parseSrcId(const char *pbuff)
{
    m_srcId = DealData::parseBufToUnShort(pbuff);
}

EDB_TYPE DMLPackage::getDbType() const
{
    return m_dbType;
}

void DMLPackage::setDbType(const EDB_TYPE &dbType)
{
    m_dbType = dbType;
}

void DMLPackage::parseDbType(const char *pbuff)
{
    m_dbType = static_cast<EDB_TYPE>(DealData::parseBufToInt(pbuff));
}

EDML_OPTYPE DMLPackage::getOpType() const
{
    return m_opType;
}

void DMLPackage::setOpType(const EDML_OPTYPE &opType)
{
    m_opType = opType;
}

void DMLPackage::parseOpType(const char *pbuff)
{
    m_opType = static_cast<EDML_OPTYPE>(DealData::parseBufToChar(pbuff));
}

string DMLPackage::getDstTableName() const
{
    return m_dstTableName;
}

void DMLPackage::setDstTableName(const string &dstTableName)
{
    m_dstTableName = dstTableName;
}

void DMLPackage::parseDstTableName(const char *pbuff, int &len)
{
    m_dstTableName = DealData::parseBufToString(pbuff, len);
}

string DMLPackage::getTimeZone() const
{
    return m_timeZone;
}

void DMLPackage::setTimeZone(const string &timeZone)
{
    m_timeZone = timeZone;
}

void DMLPackage::parseTimeZone(const char *pbuff, int &len)
{
    m_timeZone = DealData::parseBufToString(pbuff, len);
}

EDML_CODETYPE DMLPackage::getCodeType() const
{
    return m_codeType;
}

void DMLPackage::setCodeType(const EDML_CODETYPE &codeType)
{
    m_codeType = codeType;
}

void DMLPackage::parseCodeType(const char *pbuff)
{
    m_codeType = static_cast<EDML_CODETYPE>(DealData::parseBufToChar(pbuff));
}

unsigned int DMLPackage::getBeginTime() const
{
    return m_beginTime;
}

void DMLPackage::setBeginTime(const unsigned int beginTime)
{
    m_beginTime = beginTime;
}

void DMLPackage::parseBeginTime(const char *pbuff)
{
    m_beginTime = DealData::parseBufToUnInt(pbuff);
}

//int DMLPackage::getMsgBatch() const
//{
//    return m_msgBatch;
//}

//void DMLPackage::setMsgBatch(const int msgBatch)
//{
//    m_msgBatch = msgBatch;
//}

//void DMLPackage::parseMsgBath(const char *pbuff)
//{
//    m_msgBatch = DealData::parseBufToInt(pbuff);
//}

int DMLPackage::getMsgColNum() const
{
    return m_msgColNum;
}

//void DMLPackage::setMsgColNum(const short colNum)
//{
//    m_msgColNum = colNum;
//}

void DMLPackage::parseMsgColNum(const char *pbuff)
{
    m_msgColNum = DealData::parseBufToUnShort(pbuff);
}

void DMLPackage::addColInfo(DMLColInfo &dmlCol)
{
    dmlCol.transformStream();

    m_columns.push_back(dmlCol);
    m_msgColNum = m_columns.size();

//    m_colAttrNull.push_back(dmlCol.getColNULL());
}

//const vector<EDML_COL_NULL> &DMLPackage::getAllColAttrNULL() const
//{
//    return m_colAttrNull;
//}

int DMLPackage::getMsgRowNum() const
{
    return m_records.size();
}

void DMLPackage::parseMsgRowNum(const char *pbuff)
{
    m_msgRowNum = DealData::parseBufToInt(pbuff);
}

const vector<DMLRecordInfo> &DMLPackage::getDmlAllRows()
{
    return m_records;
}

const DMLRecordInfo& DMLPackage::getDmlRow(const unsigned int row)
{
    if (row >= m_records.size())
    {
        cout << "DMLPackage::getDmlRecord not find row: " << row << endl;
    }

    return m_records.at(row);
}

const DMLColInfo &DMLPackage::getDmlColAttr(const unsigned int col)
{
    if (col >= m_columns.size())
    {
        cout << "DMLPackage::getDmlColAttr not find col: " << col << endl;
    }

    return m_columns.at(col);
}

//void DMLPackage::setMsgRowNum(const int rowNum)
//{
//    m_msgRowNum = rowNum;
//}

//void DMLPackage::addRowInfo(const DMLRecordInfo &rowInfo)
//{
//    m_records.push_back(rowInfo);
//    int rowNums = m_records.size();

//    // 将改行内容
//    const vector<char>& recordVecData = rowInfo.getDmlRecordInfo();
//    m_vecRows.insert(m_vecRows.end(), recordVecData.begin(), recordVecData.end());

//    // 替换前4个字节的内容 为行数信息
//    vector<char> vecTempRow;
//    DealData::putIntToData(vecTempRow, rowNums);

////    for (int i = 0; i < 4; ++i)
////    {
////        m_vecRows[i] =
////    }

//}

int DMLPackage::addOneRecord(DMLRecordInfo &dmlRecord)
{
    dmlRecord.transformStream(m_columns);

    /*
    true:  可以继续添加改行内容已添加进去
    false: 不可以继续添加，且改行也未能添加进去
    */
    if (m_records.size() + 1 > static_cast<unsigned int>(m_recordMaxNum))
    {
        cout << " record num > max_num" << endl;
        return -1;
    }

    // 获取改行内容
    const vector<char>& recordVecData = dmlRecord.getDmlRecordInfo();
    if ((m_vecPackHeadr.size() + m_vecRows.size() + recordVecData.size()) > static_cast<unsigned int>(m_unitMaxValue))
    {
        cout << " size > max_size" << endl;
        return -2;
    }

    m_records.push_back(dmlRecord);
    m_vecRows.insert(m_vecRows.end(), recordVecData.begin(), recordVecData.end());

    // 替换前4个字节的内容 为行数信息
    vector<char> vecTempRow;
    DealData::putIntToData(vecTempRow, m_records.size());

    for (int i = 0; i < 4; ++i)
    {
        m_vecRows[i] = vecTempRow[i];
    }

    return 0;
}

//int DMLPackage::getMsgPackTotalSize() const
//{
//    return m_vecPackHeadr.size() + m_vecRows.size();
//}

void DMLPackage::setRecordMaxNum(int recordNum)
{
    m_recordMaxNum = recordNum;
}

void DMLPackage::setUnitMaxNum(int size)
{
    m_unitMaxValue = size * 1024 * 1024;
}

void DMLPackage::testRecordInfos()
{
    for (const DMLRecordInfo& record : m_records)
    {
        record.printVecVariantInfo();
    }
}

void DMLPackage::showStructInfo()
{
    cout << "m_version: " << static_cast<char>(m_msgVer) << endl;
    cout << "m_srcId: " << m_srcId << endl;
    cout << "m_dbType: " << static_cast<short>(m_dbType) << endl;
    cout << "m_opType: " << static_cast<char>(m_opType) << endl;
    cout << "m_dstTableName: " << m_dstTableName << endl;
    cout << "m_timeZone: " << m_timeZone << endl;
    cout << "m_codeType: " << static_cast<char>(m_codeType) << endl;
    cout << "m_beginTime: " << m_beginTime << endl;
    cout << "m_msgColNum: " << m_msgColNum << endl;
    cout << "m_msgRowNum: " << m_msgRowNum << endl;

    // 列信息
    for (const DMLColInfo& colInfo : m_columns)
    {
        colInfo.showStructInfo();
    }

    // 行信息

    for (const DMLRecordInfo recordInfo : m_records)
    {
        recordInfo.showStructInfo();
    }
}

//vector<EDMLDataType> DMLPackage::getDmlColDataTypes()
//{
//    vector<EDMLDataType> vecColDataType;
//    for (const DMLColInfo& dmlColInfo : m_columns)
//    {
//        vecColDataType.push_back(dmlColInfo.colType());
//    }

//    return vecColDataType;
//}

