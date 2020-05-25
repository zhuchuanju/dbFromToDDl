#include "ddlpackage.h"

#if 0
const string STR_DDL_ATTR_MSGTYPE = "MsgType";
const string STR_DDL_ATTR_VERSION = "Version";
const string STR_DDL_ATTR_SRCID = "SrcID";
const string STR_DDL_ATTR_DBTYPE = "DBType";
const string STR_DDL_ATTR_TOPERTYPE = "TOperType";
const string STR_DDL_ATTR_SRCTABLENAME = "SrcTableName";
const string STR_DDL_ATTR_DESCTABLENAME = "DescTableName";
const string STR_DDL_ATTR_COLUMNNUM= "ColumnNum";
const string STR_DDL_ATTR_TIMEZONE = "TimeZone";
#endif

//DDLPackage::DDLPackage()
//    : BasePackage(EPKG_MSGTYPE::DDL)
//{
//    DealData::putCharToData(m_data, static_cast<char>(getMsgType()));

//#if 0
//    m_vecAttr.push_back(STR_DDL_ATTR_MSGTYPE);
//    m_vecAttr.push_back(STR_DDL_ATTR_VERSION);
//    m_vecAttr.push_back(STR_DDL_ATTR_SRCID);
//    m_vecAttr.push_back(STR_DDL_ATTR_DBTYPE);
//    m_vecAttr.push_back(STR_DDL_ATTR_TOPERTYPE);
//    m_vecAttr.push_back(STR_DDL_ATTR_SRCTABLENAME);
//    m_vecAttr.push_back(STR_DDL_ATTR_DESCTABLENAME);
//    m_vecAttr.push_back(STR_DDL_ATTR_COLUMNNUM);
//    m_vecAttr.push_back(STR_DDL_ATTR_TIMEZONE);
//#endif
//}

DDLPackage::DDLPackage()
    : m_msgType(EPKG_MSGTYPE::DDL)
{
    clear();
}

DDLPackage::DDLPackage(const EPKG_VERTYPE &msgVer)
    : m_msgVer(msgVer)
    , m_msgType(EPKG_MSGTYPE::DDL)
{
    clear();
}

DDLPackage::~DDLPackage()
{

}

int DDLPackage::parseStream(const char *pbuff, const int buffLen)
{
    clear();

    // buf[0] = '版本号' buf[1] = '操作类型' bufflen不可能小于2
    if (buffLen < 2)
    {
        cout << "ddl pack parseStream err" << endl;
        return -1;
    }

    // 偏移量
    int posLen = 0;
    const char* ptrBuff = pbuff;

    // 解析消息版本号
    parseVersion(ptrBuff);
    ptrBuff += sizeof(char);

    // 解析消息类型
    if (!parseMsgType(ptrBuff))
    {
        cout << "not dll stream err" << endl;
        return -2;
    }
    ptrBuff += sizeof(char);

    // 解析 源端ID
    parseSrcId(ptrBuff);
    ptrBuff += sizeof(unsigned short);

    // 解析 源数据类型
    parseDbType(ptrBuff);
    ptrBuff += sizeof(EDB_TYPE);

    // 解析 表操作类型
    parseOpType(ptrBuff);
    ptrBuff += sizeof(EDDL_OPTYPE);

    // 解析 数据源表名
    parseSrcTableName(ptrBuff, posLen);
    ptrBuff += posLen;

    // 解析目的表名
    parseDstTableName(ptrBuff, posLen);
    ptrBuff += posLen;

    // 解析表字段数
    parseColumnNum(ptrBuff);
    ptrBuff += sizeof(int);

    // 解析源表的时区
    parseTimeZone(ptrBuff, posLen);
    ptrBuff += posLen;

    // 解析列信息 ==> 协议中的DLL 字段N
    for (int i = 0; i < m_columnNum; ++i)
    {
        int len = 0;
        DDLColumn ddlColumn;
        ddlColumn.parseColumnInfo(m_opType, ptrBuff, len);
        ptrBuff += len;
        m_columns.push_back(ddlColumn);
    }
#if 0
    cout << "ver: " << m_version << endl;
    cout << "srcId: " << m_srcId << endl;
    cout << "dbType: " << static_cast<int>(m_dbType) << endl;
    cout << "opType: " << static_cast<int>(m_opType) << endl;
    cout << "srcTableName: " << m_srcTableName << endl;
    cout << "dstTableName: " << m_dstTableName << endl;
    cout << "colNum: " << m_columnNum << endl;
    cout << "timeZone: " << m_timeZone << endl;

    for (const DDLColumn& ddlCol : m_columns)
    {
        ddlCol.printAllMemInfo();
    }
#endif

    return 0;
}

int DDLPackage::package(char * const pbuff, int &dataLen)
{
    for (unsigned int i = 0; i < m_data.size(); ++i)
    {
        pbuff[i] = m_data[i];
    }

    dataLen = m_data.size();

    return 0;
}

int DDLPackage::getStreamBuffLen()
{
    // 将结构体内容打包成stream
    transformStream();

    return m_data.size();
}

void DDLPackage::clear()
{
    clearStruct();

    m_data.clear();
}

void DDLPackage::clearStruct()
{
//    m_msgVer = EPKG_VERTYPE::DT_VER_NULL;
    m_srcId = 0;
    m_dbType = EDB_TYPE::DT_NULL;
    m_opType = EDDL_OPTYPE::UNKNOWN;
    m_srcTableName.clear();
    m_dstTableName.clear();
    m_columnNum = 0;
    m_timeZone.clear();

    m_columns.clear();
}

void DDLPackage::transformStream()
{
    m_data.clear();

    // 添加版本信息
    DealData::putCharToData(m_data, static_cast<char>(m_msgVer));

    // 添加类型
    DealData::putCharToData(m_data, static_cast<char>(m_msgType));

    // 源端ID
    DealData::putUnShortToData(m_data, m_srcId);

    // 源数据类型
    DealData::putIntToData(m_data, static_cast<int>(m_dbType));

    // 表操作类型
    DealData::putCharToData(m_data, static_cast<char>(m_opType));

    // 数据源表名
    DealData::putStringToData(m_data, m_srcTableName);
    DealData::putEndFlag(m_data);

    // 目的表名
    DealData::putStringToData(m_data, m_dstTableName);
    DealData::putEndFlag(m_data);

    // 当操作类型为删除时 不再添加数据
    if (EDDL_OPTYPE::DEL == m_opType)
    {
        return ;
    }

    // 表字段数
    DealData::putIntToData(m_data, m_columnNum);

    // 源表的时区
    DealData::putStringToData(m_data, m_timeZone);
    DealData::putEndFlag(m_data);

    // 字段信息描述
    for (const DDLColumn& column : m_columns)
    {
        const vector<char>& colVecData = column.getColData();
        m_data.insert(m_data.end(), colVecData.begin(), colVecData.end());
    }
}

//string DDLPackage::getVersion() const
//{
//    return m_version;
//}

//void DDLPackage::setVersion(const string &version)
//{
//    m_version = version;
//}

void DDLPackage::parseVersion(const char *pbuff)
{
    m_msgVer = static_cast<EPKG_VERTYPE>(DealData::parseBufToChar(pbuff));
}

bool DDLPackage::parseMsgType(const char *pbuff)
{
    m_msgType = static_cast<EPKG_MSGTYPE>(DealData::parseBufToChar(pbuff));

    if (EPKG_MSGTYPE::DDL == m_msgType)
        return true;

    return false;
}

unsigned short DDLPackage::getSrcId() const
{
    return m_srcId;
}

void DDLPackage::setSrcId(const unsigned short &srcId)
{
    m_srcId = srcId;
}

void DDLPackage::parseSrcId(const char *pbuff)
{
    m_srcId = DealData::parseBufToUnShort(pbuff);
}

EDB_TYPE DDLPackage::getDbType() const
{
    return m_dbType;
}

void DDLPackage::setDbType(const EDB_TYPE &dbType)
{
    m_dbType = dbType;
}

void DDLPackage::parseDbType(const char *pbuff)
{
    m_dbType = static_cast<EDB_TYPE>(DealData::parseBufToInt(pbuff));

#if 0
    if (m_dbType == EDB_TYPE::DT_DB2)
    {
        cout << "trans ok!" << endl;
    }
#endif
}

EDDL_OPTYPE DDLPackage::getOpType() const
{
    return m_opType;
}

void DDLPackage::setOpType(const EDDL_OPTYPE &opType)
{
    m_opType = opType;
}

void DDLPackage::parseOpType(const char *pbuff)
{
    m_opType = static_cast<EDDL_OPTYPE>(DealData::parseBufToChar(pbuff));

#if 0
    if (m_opType == EDDL_OPTYPE::ADD)
    {
        cout << "m_opType trans ok! " << endl;
    }
#endif
}

string DDLPackage::getSrcTableName() const
{
    return m_srcTableName;
}

void DDLPackage::setSrcTableName(const string &srcTableName)
{
    m_srcTableName = srcTableName;
}

void DDLPackage::parseSrcTableName(const char *pbuff, int &len)
{
    m_srcTableName = DealData::parseBufToString(pbuff, len);
}

string DDLPackage::getDstTableName() const
{
    return m_dstTableName;
}

void DDLPackage::setDstTableName(const string &dstTableName)
{
    m_dstTableName = dstTableName;
}

void DDLPackage::parseDstTableName(const char *pbuff, int &len)
{
    m_dstTableName = DealData::parseBufToString(pbuff, len);
}

int DDLPackage::getColumnNum() const
{
    return m_columnNum;
}

void DDLPackage::setColumnNum(int columnNum)
{
    m_columnNum = columnNum;
}

void DDLPackage::parseColumnNum(const char *pbuff)
{
    m_columnNum = DealData::parseBufToInt(pbuff);
}

string DDLPackage::getTimeZone() const
{
    return m_timeZone;
}

void DDLPackage::setTimeZone(const string &timeZone)
{
    m_timeZone = timeZone;
}

void DDLPackage::parseTimeZone(const char *pbuff, int &len)
{
    m_timeZone = DealData::parseBufToString(pbuff, len);
}

const vector<DDLColumn> &DDLPackage::getColumns()
{
    return m_columns;
}

void DDLPackage::addColumns(DDLColumn &column)
{
    column.transformStream(m_opType);

    m_columns.push_back(column);
}

const DDLColumn &DDLPackage::getDDLColAttr(unsigned int col)
{
    if (col >= m_columns.size())
    {
        cout << "DDLPackage::getDDLColAttr not find col: " << col << endl;
    }

    return m_columns.at(col);
}

void DDLPackage::printData()
{
    DealData::printData(m_data);
}

void DDLPackage::showStructInfo() const
{
    cout << "msgVer: " << static_cast<char>(m_msgVer) << endl;
    cout << "msgType: " << static_cast<char>(m_msgType) << endl;
    cout << "srcId: " << m_srcId << endl;
    cout << "dbType: " << static_cast<int>(m_dbType) << endl;
    cout << "opType: " << static_cast<char>(m_opType) << endl;
    cout << "srcTableName: " << m_srcTableName << endl;
    cout << "dstTableName: " << m_dstTableName << endl;
    cout << "colNum: " << m_columnNum << endl;
    cout << "timeZone: " << m_timeZone << endl;

    for (const DDLColumn& ddlCol : m_columns)
    {
        ddlCol.showStructInfo();
    }
}

//void DDLPackage::testMapInfo()
//{
////    for (auto &it = m_mapInfo.begin(); it != m_mapInfo.end; ++it)
////    {
////        cout << it.first << " - " << it.second << endl;
////    }
//}
