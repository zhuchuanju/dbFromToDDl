#ifndef H_PACK_MSG_TYPE_HEADER_H
#define H_PACK_MSG_TYPE_HEADER_H

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

using namespace std;

enum class EPKG_VERTYPE : uint8_t
{
    DT_VER_NULL = 0x00,
    DT_VER_1_1  = 0x11,
    DT_VER_1_2  = 0x12
};

// DDL消息类型
enum class EPKG_MSGTYPE : uint8_t
{
    DDL = 'D',
    DML = 'M'
};

//数据库类型
enum class EDB_TYPE : uint32_t
{
    DT_NULL = 0,
    DT_ORACLE = 101,	 // Oracle
    DT_DB2 = 102,		 // DB2
    DT_MYSQL = 103,		 // MySQL
    DT_INFORMIX = 104,   // Informix
    DT_SQL_SERVER = 105, // SQL Server
    DT_KDB = 106,		 //浪潮K-DB
    DT_POSTGRESQL = 107, // PostgreSQL
    DT_SYBASE = 108,	 // SYBASE
    DT_DAMENG = 109,	 //	达梦数据库
    DT_KINGBASE = 110,   // Kingbase
    DT_MARIADB = 111,	// Mariadb
    DT_CACHE = 112,		 //	Cache数据库
    DT_SHENTONG = 113,   //神通数据库
    DT_HANGAO = 114,	 //瀚高数据库
    DT_KUDU = 201,		 // Kudu
    DT_MONGODB = 202,	// MongoDB
    DT_HBASE = 301,		 //	HBase
    DT_CASSANDRA = 302,  // Cassandra
    DT_RIAK = 303,		 // Riak
    DT_GBASE = 304,		 // Gbase
    DT_REDIS = 401,		 // Redis
    DT_ORACLE_BDB = 402, // Oracle BDB
    DT_HADOOP = 501,	 // Hadoop
    DT_GREENPLUM = 502,  // Greenplum
    DT_SPARK = 503,		 // Spark
    DT_HIVE = 504,		 // Hive
    DT_FTP = 601,		 // FTP
    DT_MQ = 602,		 // MQ
    DT_CSV = 701,		 // csv格式文档
    DT_SOLR = 801,		 // Solr
};

//DDL操作类型
enum class EDDL_OPTYPE : uint8_t
{
    UNKNOWN = 0,
    ADD = 'A',
    UPD = 'U',
    DEL = 'D'
};

//列更改类型
enum class EDDLCOLUMN_CHGTYPE : uint8_t
{
    UNKNOWN = 0,
    ADD = 'A',
    UPD = 'U',
    DEL = 'D',
    RNA = 'R'
};

enum class EDDL_IS_NULL : uint8_t
{
    UNKNOWN = 'N',
    NOT_BE_NULL = 0,       // 不可为空
    CAN_BE_NULL = 1,       // 可为空
};

enum class EDDL_IS_PRIMARY : uint8_t
{
    UNKNOWN = 'N',
    NOT_PRIMARY = '0',       // 非主键
    IS_PRIMARY = 1,          // 主键
};

// DML 操作类型 G:全量 I:增量
enum class EDML_OPTYPE : uint8_t
{
    UNKNOWN     = 0,
    G           = 'G',
    I           = 'I',
};

// DML 编码类型 U:utf-8 G: GBK
enum class EDML_CODETYPE : uint8_t
{
    UNKNOWN     = 0,
    UTF8        = 0x10,
    GBK         = 0x21,
    GB2312      = 0x22,
    GB18030     = 0x23,
};

// 没有用该定义类型封装 variant, 但variant类中包含所有变量类型
enum class EDML_COL_TYPE : uint8_t
{
    DT_U_CHAR = 0x00,
    DT_CHAR = 0x01,
    DT_U_SHORT = 0x10,
    DT_SHORT = 0x11,
    DT_U_INT = 0x20,
    DT_INT = 0x21,
    DT_U_LONGLONG = 0x30,
    DT_LONGLONG = 0x31,
    DT_FLOAT = 0x41,
    DT_DOUBLE = 0x51,
    DT_STRING = 0x60,
    DT_BOOL = 0x70,
    DT_BYTES = 0x80,
    DT_UNKNOWN = 0xFF
};

enum class EDML_COL_NULL : uint8_t
{
    UNKNOWN = 'N',
    NOT_BE_NULL = '0',       // 不可为空
    CAN_BE_NULL = '1',       // 可为空
};

enum class EDML_VARIANT_NULL : uint8_t
{
    UNKNOWN = 'N',
    IS_NOT_NULL = '0',         // 不是空值
    IS_NULL = '1',             // 是空值
};

enum class EDML_VARIANT_BOOL : uint8_t
{
    UNKNOWN = 'N',
    BOOL_FALSE = '0',              // true
    BOOL_TRUE = '1',             // false
};

enum class EDMLRECORD_TYPE : uint8_t
{
    UNKNOWN = 0,
    ADD = 'A',
    UPD = 'U',
    DEL = 'D'
};

// 字段 类型
enum class E_DB2_FILELD_TYPE : int
{
    FT_bigint = -5,
    FT_blob = -4,
    FT_clob = -1,
    FT_char = 1,
    FT_decimal = 3,
    FT_int = 4,
    FT_double = 8,
    FT_varchar = 12,
    FT_date = 91,
    FT_time = 92,
    FT_timestamp = 93,
};

enum class E_ORACLE_FILELD_TYPE : int
{
    FT_varchar2 = 1,
    FT_number = 2,
    FT_long = 8,
    FT_date = 12,
    FT_long_raw = 24,
    FT_char = 96,
    FT_clob = 112,
    FT_blob = 113,
};

enum class E_MYSQL_FILELD_TYPE : int
{
    FT_bit  = -7,
    FT_bool = -6,
    FT_bigint = -5,
    FT_blob = -4,
    FT_binary = -2,
    FT_text = -1,
    FT_char = 1,
    FT_decimal = 3,
    FT_int = 4,
    FT_year = 5,
    FT_float = 7,
    FT_double = 8,
    FT_varchar = 12,
    FT_date = 91,
    FT_time = 92,
    FT_timestamp = 93,
};

enum class E_SQLSERVER_FILELD_TYPE : int
{
    FT_UNIQUEIDENTIFIER  = -11,
    FT_XML = -10,
    FT_DATE = -9,
    FT_NCHAR = -8,
    FT_BIT = -7,
    FT_TINYINT = -6,
    FT_BIGINT = -5,
    FT_IMAGE = -4,
    FT_VARBINARY = -3,
    FT_TIMESTAMP = -2,
    FT_TEXT = -1,
    FT_CHAR = 1,
    FT_DECIMAL = 2,
    FT_MONEY = 3,
    FT_INT = 4,
    FT_SMALLINT = 5,
    FT_REAL = 7,
    FT_FLOAT = 8,
    FT_VARCHAR = 12,
    FT_DATETIME = 93,
};

enum class OPERTRI_TYPE : int
{
    UNKNOWN = 0,
    ADD = 1,
    UPD = 2,
    DEL = 3
};

#endif // PACKMSGTYPEHEADER_H
