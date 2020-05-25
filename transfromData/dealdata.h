#ifndef H_DEAL_DATA_H
#define H_DEAL_DATA_H

#include <iostream>
#include <vector>
#include <string>

#include "packmsgtypeheader.h"

using namespace std;

union U_Trans
{
    char                buf[8];
    short               shortNum;
    unsigned short      uShortNum;
    int                 intNum;
    long long           longNum;
    unsigned long long  unLongLongNum;
    float               floatNum;
    double              doubleNum;
};

class DealData
{
public:
    DealData();
    ~DealData();

    // 添加结束标记
    static void putEndFlag(vector<char>& vecData);

    // 打印 m_data中的信息
    static void printData(const vector<char>& vecData);

    // bool 类型 to m_data 中
    static void putB2CToData(vector<char>& vecData, const bool bFlag);

    // char to m_data 中
    static void putUnCharToData(vector<char>& vecData, const unsigned char c);

    // char to m_data 中
    static void putCharToData(vector<char>& vecData, const char c);

    // short to m_data 中
    static void putShortToData(vector<char>& vecData, const short s, const bool bLittle = true);

    // unsigned short to m_data 中
    static void putUnShortToData(vector<char>& vecData, const unsigned short s, const bool bLittle = true);

    // int to m_data中
    static void putIntToData(vector<char>& vecData, const int data, const bool bLittle = true);

    // unsigned int to m_data 中
    static void putUnIntToData(vector<char>& vecData, const unsigned int data, const bool bLittle = true);

    // long long to m_data 中
    static void putLongLongToData(vector<char>& vecData, const long long data, const bool bLittle = true);

    // float to m_data中
    static void putFloatToData(vector<char>& vecData, const float data);

    // Double to m_data中
    static void putDoubleToData(vector<char>& vecData, const double data);

    // string to m_data中
    static void putStringToData(vector<char>& vecData, const string &strData);

    // bigData to m_data 中
    static void putBigDataToData(vector<char>& vecData, const vector<char>& vecBigData);

    // parse buf stream to Struct.string
    static string parseBufToString(const char* ptrBuf, int &len);
    static string parseBufToString(const char* ptrBuf, unsigned int &len);

    // parse stream to struct.unchar
    static unsigned char parseBufToUnChar(const char* ptrBuf);

    // parse stream to struct.char
    static char parseBufToChar(const char* ptrBuf);

    // parse stream to struct.unshort
    static unsigned short parseBufToUnShort(const char* ptrBuf);

    // parse stream to struct.short
    static short parseBufToShort(const char* ptrBuf);

    // parse stream to struct.unInt
    static unsigned int parseBufToUnInt(const char* ptrBuf);

    // parse stream to struct.int
    static int parseBufToInt(const char* ptrBuf);

    // parse stream to struct.unsigned long long
    static long long parseBufToUnLongLong(const char* ptrBuf);

    // parse stream to struct.long long
    static long long parseBufToLongLong(const char* ptrBuf);

    // parse stream to struct.float
    static float parseBufToFloat(const char* ptrBuf);

    // parse stream to struct.double
    static double parseBufToDouble(const char* ptrBuf);

    // parse stream to struct.string
//    static string parseDataBufToString(const char* ptrBuf, const int len);

    // parse stream to struct.bool
    static bool parseBuftoBool(const char* ptrbuf);

    // parse stream to struct.vector<char> bigData
    static vector<char> parseBufToBigVector(const char* ptrBuf, const int len);

    // parse stream to stuct.charbuf bigData
    static void parseBufToBigBuf(const char* ptrBuf, const int len, char* ptrDstBuf);

    //测试
    static void printPtrBufInfo(const char* ptr, const int len);
};

#endif // DEALDATA_H
