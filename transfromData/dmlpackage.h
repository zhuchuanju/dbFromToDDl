#ifndef H_DML_PACKAGE_H
#define H_DML_PACKAGE_H

#include "dmlcolinfo.h"
#include "dmlrecordinfo.h"

class DMLPackage
{
public:
    DMLPackage();
    DMLPackage(const EPKG_VERTYPE& msgVer);
    ~DMLPackage();

public:
    //解析流并填充数据包
    //返回值：0，解析成功  负值定义解析错误
    //参数:数据流指针，数据流长度，解析填充到结构体，解析的数据长度
    int parseStream(const char *pbuff, const int buffLen);

    //打包数据:返回值0：表示成功 负值定义错误
    //参数：结构体，缓冲区指针，缓冲区长度，填充数据长度
    int package(char *const pbuff, int &dataLen);

    // 计算包的打包后数据总长度
    int getStreamBuffLen();

    //清空包内数据
    void clear();

    // 清除所有表记录信息 表结构不变 用于继续乡里面添加Record信息
    void clearRecords();

    // struct -> stream 表头结构打包成 流
    void transformStreamHeader();

    // 消息的版本类型
    inline EPKG_VERTYPE getMsgVersion() const {return this->m_msgVer;}
    inline void setMsgVersion(const EPKG_VERTYPE& msgVer) {m_msgVer = msgVer;}
    void parseVersion(const char* pbuff);

    //消息的操作类型
    inline EPKG_MSGTYPE getMsgType() const {return this->m_msgType;}
    inline void setMsgType(const EPKG_MSGTYPE& msgType) {m_msgType = msgType;}
    bool parseMsgType(const char* pbuff);

//    string getVersion() const;
//    void setVersion(const string &version);
//    void parseVersion(const char* pbuff, int &len);

    unsigned short getSrcId() const;
    void setSrcId(const unsigned short srcId);
    void parseSrcId(const char* pbuff);

    EDB_TYPE getDbType() const;
    void setDbType(const EDB_TYPE &dbType);
    void parseDbType(const char* pbuff);

    EDML_OPTYPE getOpType() const;
    void setOpType(const EDML_OPTYPE &opType);
    void parseOpType(const char* pbuff);

    string getDstTableName() const;
    void setDstTableName(const string &dstTableName);
    void parseDstTableName(const char* pbuff, int &len);

    string getTimeZone() const;
    void setTimeZone(const string &timeZone);
    void parseTimeZone(const char* pbuff, int &len);

    EDML_CODETYPE getCodeType() const;
    void setCodeType(const EDML_CODETYPE &codeType);
    void parseCodeType(const char* pbuff);

    unsigned int getBeginTime() const;
    void setBeginTime(const unsigned int beginTime);
    void parseBeginTime(const char* pbuff);

    // 获取列的数目
    int getMsgColNum() const;
//    void setMsgColNum(const short colNum);
    void parseMsgColNum(const char* pbuff);

    // 增加列的信息
    void addColInfo(DMLColInfo &dmlCol);

    // 获取各列是否可为NULL的属性
//    const vector<EDML_COL_NULL>& getAllColAttrNULL() const;

    // 获取行的数目
    int getMsgRowNum() const;
    void parseMsgRowNum(const char* pbuff);

    // 添加一行数据内容 在使用该函数之前先调用一下 transformStreamHeader
    int addOneRecord(DMLRecordInfo& dmlRecord);

    // 获取数据包总大小
//    int getMsgPackTotalSize() const;

    // 设置最大记录条数
    void setRecordMaxNum(int recordNum);

    // 设置最大组包字节大小 单位是M
    void setUnitMaxNum(int size);

    // 获取列的属性信息
//    vector<EDMLDataType> getDmlColDataTypes()

     // 获取所有行的数据内容
     const vector<DMLRecordInfo>& getDmlAllRows();

     // 获取某行的数据 从第 0 行开始
     const DMLRecordInfo& getDmlRow(const unsigned int row);

     // 获取某一列的属性 从第 0 列开始
     const DMLColInfo& getDmlColAttr(const unsigned int col);

    // 打印调试信息
public:
    void testRecordInfos();

    // 显示存储于struct 中的信息
    void showStructInfo();

private:
    EPKG_VERTYPE m_msgVer;
    EPKG_MSGTYPE m_msgType;
    int m_recordMaxNum;                             // 最大记录条数
    int m_unitMaxValue;                             // 最大字节大小
    unsigned short m_srcId;
    EDB_TYPE m_dbType;
    EDML_OPTYPE m_opType;
    string m_dstTableName;
    string m_timeZone;
    EDML_CODETYPE m_codeType;
    unsigned int m_beginTime;                        // 采集服务开始采集的时间
    unsigned short m_msgColNum;                      // 消息的列数
    vector<DMLColInfo> m_columns;                    // 列的数目，列的名称，列的类型
//    vector<EDML_COL_NULL> m_colAttrNull;             // 列所对应是否可为NULL的属性
    int m_msgRowNum;                                 // 消息的行数 parseBuf的时候使用

    vector<char> m_vecPackHeadr;                     // 表结构信息dui

    vector<DMLRecordInfo> m_records;                 // 行信息
    vector<char> m_vecRows;                          // 表内容信息
};

#endif // DMLPACKAGE_H
