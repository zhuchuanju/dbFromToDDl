#ifndef H_DDL_PACKAGE_H
#define H_DDL_PACKAGE_H

#include "packmsgtypeheader.h"
#include "ddlcolumn.h"

class DDLPackage
{
public:
     DDLPackage();
     DDLPackage(const EPKG_VERTYPE& msgVer);
     ~DDLPackage();

public:
     //解析流并填充数据包
     //返回值：0，解析成功  负值定义解析错误
     //参数:数据流指针，数据流长度，解析填充到结构体，解析的数据长度
     int parseStream(const char *pbuff, const int buffLen);

     //打包数据:返回值0：表示成功 负值定义错误
     //参数：结构体，缓冲区指针，缓冲区长度，填充数据长度
     int package(char *const pbuff, int &dataLen);

     //计算包的打包后数据长度
     int getStreamBuffLen();

     //清空包内数据
     void clear();

     // 清空DDL结构保存的信息
     void clearStruct();

     // 将该结构信息 转化为stream 填充完毕信息后需要 主动调用
     void transformStream();

     // 消息的版本类型
     inline EPKG_VERTYPE getMsgVersion() const {return this->m_msgVer;}
     inline void setMsgVersion(const EPKG_VERTYPE& msgVer) {m_msgVer = msgVer;}
     void parseVersion(const char* pbuff);

     //消息的操作类型
     inline EPKG_MSGTYPE getMsgType() const {return this->m_msgType;}
     inline void setMsgType(const EPKG_MSGTYPE& msgType) {m_msgType = msgType;}
     bool parseMsgType(const char* pbuff);

//     string getVersion() const;
//     void setVersion(const string &version);


     unsigned short getSrcId() const;
     void setSrcId(const unsigned short &srcId);
     void parseSrcId(const char* pbuff);

     EDB_TYPE getDbType() const;
     void setDbType(const EDB_TYPE &dbType);
     void parseDbType(const char* pbuff);

     EDDL_OPTYPE getOpType() const;
     void setOpType(const EDDL_OPTYPE &opType);
     void parseOpType(const char* pbuff);

     string getSrcTableName() const;
     void setSrcTableName(const string &srcTableName);
     void parseSrcTableName(const char* pbuff, int &len);

     string getDstTableName() const;
     void setDstTableName(const string &dstTableName);
     void parseDstTableName(const char* pbuff, int &len);

     int getColumnNum() const;
     void setColumnNum(int columnNum);
     void parseColumnNum(const char* pbuff);

     string getTimeZone() const;
     void setTimeZone(const string &timeZone);
     void parseTimeZone(const char* pbuff, int &len);

     const vector<DDLColumn>& getColumns();
     void addColumns(DDLColumn &column);

     // DDL 获取某行列属性 从第 0 列开始
     const DDLColumn& getDDLColAttr(unsigned int col);

     // 打印 m_data中的信息
     void printData();

//     void testMapInfo();
public:
     // 显示 该 结构体信息
     void showStructInfo() const;

private:
     EPKG_VERTYPE m_msgVer;
     EPKG_MSGTYPE m_msgType;
     unsigned short m_srcId;
     EDB_TYPE m_dbType;
     EDDL_OPTYPE m_opType;
     string m_srcTableName;
     string m_dstTableName;
     int m_columnNum;
     string m_timeZone;
     vector<DDLColumn> m_columns;           // 列的信息
     vector<char> m_data;                   // 存储的数据
};

#endif // DDLPACKAGE_H
