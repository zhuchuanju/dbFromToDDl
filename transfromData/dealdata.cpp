#include <string.h>

#include "dealdata.h"

DealData::DealData()
{

}

void DealData::putEndFlag(vector<char> &vecData)
{
    vecData.push_back('\0');
}

void DealData::printData(const vector<char> &vecData)
{
    for (const char c : vecData)
    {
        if ('\0' == c)
        {
            cout << endl;
        }
        cout << c;
    }

    cout << endl;
    cout << "data size: " << vecData.size() << endl;
}

void DealData::putIntToData(vector<char> &vecData, const int data, const bool bLittle)
{
#if 0
    U_Trans unIntToBuf;
    if (bLittle)
    {
        unIntToBuf.buf[3] = data >> 24;
        unIntToBuf.buf[2] = data >> 16;
        unIntToBuf.buf[1] = data >> 8;
        unIntToBuf.buf[0] = data;
    }
    else
    {
        unIntToBuf.buf[0] = data >> 24;
        unIntToBuf.buf[1] = data >> 16;
        unIntToBuf.buf[2] = data >> 8;
        unIntToBuf.buf[3] = data;
    }

    for (int i = 0; i < 4; ++i)
    {
        vecData.push_back(unIntToBuf.buf[i]);
    }
#endif

    char buf[4] = {0};
    memcpy(buf, &data, 4);

    for (int i = 0; i < 4; ++i)
    {
        vecData.push_back(buf[i]);
    }
}

void DealData::putUnIntToData(vector<char> &vecData, const unsigned int data, const bool bLittle)
{
    char buf[4] = {0};
    memcpy(buf, &data, 4);

    for (int i = 0; i < 4; ++i)
    {
        vecData.push_back(buf[i]);
    }
}

void DealData::putLongLongToData(vector<char> &vecData, const long long data, const bool bLittle)
{
    U_Trans unLLongToBuf;
    if (bLittle)
    {
        unLLongToBuf.buf[7] = data >> 56;
        unLLongToBuf.buf[6] = data >> 48;
        unLLongToBuf.buf[5] = data >> 40;
        unLLongToBuf.buf[4] = data >> 32;
        unLLongToBuf.buf[3] = data >> 24;
        unLLongToBuf.buf[2] = data >> 16;
        unLLongToBuf.buf[1] = data >> 8;
        unLLongToBuf.buf[0] = data;
    }
    else
    {
        unLLongToBuf.buf[0] = data >> 56;
        unLLongToBuf.buf[1] = data >> 48;
        unLLongToBuf.buf[2] = data >> 40;
        unLLongToBuf.buf[3] = data >> 32;
        unLLongToBuf.buf[4] = data >> 24;
        unLLongToBuf.buf[5] = data >> 16;
        unLLongToBuf.buf[6] = data >> 8;
        unLLongToBuf.buf[7] = data;
    }

    for (int i = 0; i < 8; ++i)
    {
        vecData.push_back(unLLongToBuf.buf[i]);
    }
}

void DealData::putFloatToData(vector<char> &vecData, const float data)
{
    char buf[4] = {0};

//    strncpy(buf, (char *)&data, 4);
    memcpy(buf, &data, 4);

    for (int i = 0; i < 4; ++i)
    {
        vecData.push_back(buf[i]);
    }
}

void DealData::putDoubleToData(vector<char> &vecData, const double data)
{
    char buf[8] = {0};

//    strncpy(buf, (char *)&data, 8);
    memcpy(buf, &data, 8);

    for (int i = 0; i < 8; ++i)
    {
        vecData.push_back(buf[i]);
    }
}

//void DealData::putFloatToData(vector<char> &vecData, const float data, const bool bLittle)
//{
//    U_Trans unFloatToBuf;
//    if (bLittle)
//    {
//        unFloatToBuf.buf[3] = data >> 24;
//        unFloatToBuf.buf[2] = data >> 16;
//        unFloatToBuf.buf[1] = data >> 8;
//        unFloatToBuf.buf[0] = data;
//    }
//    else
//    {
//        unFloatToBuf.buf[0] = data >> 24;
//        unFloatToBuf.buf[1] = data >> 16;
//        unFloatToBuf.buf[2] = data >> 8;
//        unFloatToBuf.buf[3] = data;
//    }

//    for (int i = 0; i < 4; ++i)
//    {
//        vecData.push_back(unFloatToBuf.buf[i]);
//    }
//}

//void DealData::putDoubleToData(vector<char> &vecData, const double data, const bool bLittle)
//{
//    U_Trans unDoubleToBuf;
//    if (bLittle)
//    {
//        unDoubleToBuf.buf[7] = data >> 56;
//        unDoubleToBuf.buf[6] = data >> 48;
//        unDoubleToBuf.buf[5] = data >> 40;
//        unDoubleToBuf.buf[4] = data >> 32;
//        unDoubleToBuf.buf[3] = data >> 24;
//        unDoubleToBuf.buf[2] = data >> 16;
//        unDoubleToBuf.buf[1] = data >> 8;
//        unDoubleToBuf.buf[0] = data;
//    }
//    else
//    {
//        unDoubleToBuf.buf[0] = data >> 56;
//        unDoubleToBuf.buf[1] = data >> 48;
//        unDoubleToBuf.buf[2] = data >> 40;
//        unDoubleToBuf.buf[3] = data >> 32;
//        unDoubleToBuf.buf[4] = data >> 24;
//        unDoubleToBuf.buf[5] = data >> 16;
//        unDoubleToBuf.buf[6] = data >> 8;
//        unDoubleToBuf.buf[7] = data;
//    }

//    for (int i = 0; i < 8; ++i)
//    {
//        vecData.push_back(unDoubleToBuf.buf[i]);
//    }
//}

void DealData::putStringToData(vector<char> &vecData, const string &strData)
{
    for (char c : strData)
    {
        vecData.push_back(c);
    }
}

void DealData::putBigDataToData(vector<char> &vecData, const vector<char> &vecBigData)
{
    vecData.insert(vecData.end(), vecBigData.begin(), vecBigData.end());
}

void DealData::putB2CToData(vector<char> &vecData, const bool bFlag)
{
    if (bFlag)
    {
        vecData.push_back(static_cast<char>(EDML_VARIANT_BOOL::TRUE));
    }
    else
    {
        vecData.push_back(static_cast<char>(EDML_VARIANT_BOOL::FALSE));
    }
}

void DealData::putUnCharToData(vector<char> &vecData, const unsigned char c)
{
    vecData.push_back(static_cast<char>(c));
}

void DealData::putCharToData(vector<char> &vecData, const char c)
{
    vecData.push_back(c);
}

void DealData::putShortToData(vector<char> &vecData, const short s, const bool bLittle)
{
    U_Trans shortToBuf;
    if (bLittle)
    {
        shortToBuf.buf[1] = s >> 8;
        shortToBuf.buf[0] = s;
    }
    else
    {
        shortToBuf.buf[0] = s >> 24;
        shortToBuf.buf[1] = s >> 16;
    }

    for (int i = 0; i < 2; ++i)
    {
        vecData.push_back(shortToBuf.buf[i]);
    }
}

void DealData::putUnShortToData(vector<char> &vecData, const unsigned short s, const bool bLittle)
{
    U_Trans unShortToBuf;
    if (bLittle)
    {
        unShortToBuf.buf[1] = s >> 8;
        unShortToBuf.buf[0] = s;
    }
    else
    {
        unShortToBuf.buf[0] = s >> 24;
        unShortToBuf.buf[1] = s >> 16;
    }

    for (int i = 0; i < 2; ++i)
    {
        vecData.push_back(unShortToBuf.buf[i]);
    }
}

string DealData::parseBufToString(const char *ptrBuf, int &len)
{
    string strInfo = "";

    while ((*ptrBuf) != '\0') {
        strInfo += *ptrBuf++;
    }

    len = strInfo.size() + 1;

    return strInfo;
}

string DealData::parseBufToString(const char *ptrBuf, unsigned int &len)
{
    string strInfo = "";

    while ((*ptrBuf) != '\0') {
        strInfo += *ptrBuf++;
    }

    len = strInfo.size() + 1;

    return strInfo;
}

int DealData::parseBufToInt(const char *ptrBuf)
{
#if 0
    U_Trans bufToInt;
    bufToInt.buf[0] = *ptrBuf++;
    bufToInt.buf[1] = *ptrBuf++;
    bufToInt.buf[2] = *ptrBuf++;
    bufToInt.buf[3] = *ptrBuf++;

#if 0
    cout << endl;
    cout << "bufto int : " << bufToInt.intNum << endl;
#endif
    return bufToInt.intNum;
#endif

    int iValue = 0;
    memcpy(&iValue, ptrBuf, 4);

    return iValue;
}

long long DealData::parseBufToUnLongLong(const char *ptrBuf)
{
    U_Trans bufToUnLongLong;
    bufToUnLongLong.buf[0] = *ptrBuf++;
    bufToUnLongLong.buf[1] = *ptrBuf++;
    bufToUnLongLong.buf[2] = *ptrBuf++;
    bufToUnLongLong.buf[3] = *ptrBuf++;
    bufToUnLongLong.buf[4] = *ptrBuf++;
    bufToUnLongLong.buf[5] = *ptrBuf++;
    bufToUnLongLong.buf[6] = *ptrBuf++;
    bufToUnLongLong.buf[7] = *ptrBuf++;

    return bufToUnLongLong.unLongLongNum;
}

unsigned int DealData::parseBufToUnInt(const char *ptrBuf)
{
    unsigned int iValue = 0;
    memcpy(&iValue, ptrBuf, 4);

    return iValue;
}

char DealData::parseBufToChar(const char *ptrBuf)
{
    return ptrBuf[0];
}

unsigned char DealData::parseBufToUnChar(const char *ptrBuf)
{
    return static_cast<unsigned char>(ptrBuf[0]);
}

short DealData::parseBufToShort(const char *ptrBuf)
{
    U_Trans bufToShort;
    bufToShort.buf[0] = *ptrBuf++;
    bufToShort.buf[1] = *ptrBuf++;

#if 0
    cout << endl;
    cout << "bufto int : " << bufToInt.intNum << endl;
#endif
    return bufToShort.shortNum;
}

unsigned short DealData::parseBufToUnShort(const char *ptrBuf)
{
    U_Trans bufToUnShort;
    bufToUnShort.buf[0] = *ptrBuf++;
    bufToUnShort.buf[1] = *ptrBuf++;

    return bufToUnShort.uShortNum;
}

bool DealData::parseBuftoBool(const char *ptrbuf)
{
    if (EDML_VARIANT_BOOL::TRUE == static_cast<EDML_VARIANT_BOOL>(ptrbuf[0]))
    {
        return true;
    }
    else if (EDML_VARIANT_BOOL::FALSE == static_cast<EDML_VARIANT_BOOL>(ptrbuf[0]))
    {
        return false;
    }

    cout << "DealData::parseBuftoBool not true and not false " << endl;
    return false;
}

long long DealData::parseBufToLongLong(const char *ptrBuf)
{
    U_Trans bufToLongLong;
    bufToLongLong.buf[0] = *ptrBuf++;
    bufToLongLong.buf[1] = *ptrBuf++;
    bufToLongLong.buf[2] = *ptrBuf++;
    bufToLongLong.buf[3] = *ptrBuf++;
    bufToLongLong.buf[4] = *ptrBuf++;
    bufToLongLong.buf[5] = *ptrBuf++;
    bufToLongLong.buf[6] = *ptrBuf++;
    bufToLongLong.buf[7] = *ptrBuf++;

    return bufToLongLong.longNum;
}

float DealData::parseBufToFloat(const char *ptrBuf)
{
#if 0
    U_Trans bufToFloat;
    bufToFloat.buf[0] = *ptrBuf++;
    bufToFloat.buf[1] = *ptrBuf++;
    bufToFloat.buf[2] = *ptrBuf++;
    bufToFloat.buf[3] = *ptrBuf++;

    return bufToFloat.floatNum;
#endif

//#if 0
    float value = 0;

    strncpy((char *)&value, ptrBuf, 4);

    return value;
//#endif
}

double DealData::parseBufToDouble(const char *ptrBuf)
{
#if 0
    U_Trans bufToDouble;
    bufToDouble.buf[0] = *ptrBuf++;
    bufToDouble.buf[1] = *ptrBuf++;
    bufToDouble.buf[2] = *ptrBuf++;
    bufToDouble.buf[3] = *ptrBuf++;

    return bufToDouble.doubleNum;
#endif

    double value = 0.0;

    strncpy((char *)&value, ptrBuf, 8);

    return value;
}

//string DealData::parseDataBufToString(const char *ptrBuf, const int len)
//{
//    string strInfo = "";

//    for (int i = 0; i < len; ++i)
//    {
//        strInfo += ptrBuf[i];
//    }

//    return strInfo;
//}

vector<char> DealData::parseBufToBigVector(const char *ptrBuf, const int len)
{
    vector<char> vecBigData;

    vecBigData.insert(vecBigData.end(), ptrBuf, ptrBuf+len);

    return vecBigData;
}

void DealData::parseBufToBigBuf(const char *ptrBuf, const int len, char *ptrDstBuf)
{
    memcpy(ptrDstBuf, ptrBuf, len);
}

void DealData::printPtrBufInfo(const char *ptr, const int len)
{
    cout << "print ptrbuf info ... " << " len: " << len  << endl;

    for (int i = 0; i < len; ++i)
    {
        char c = ptr[i];

        if (c == '\0')
            cout << endl;

        cout << c;
    }
    cout << endl;
}
