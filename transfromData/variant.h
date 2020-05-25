#ifndef H_VARIANT_H
#define H_VARIANT_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "string.h"

using namespace std;

class Variant
{
public:
    using uchar = unsigned char;
    using ushort = unsigned short;
    using uint = unsigned int;
    using ulong = unsigned long;
    using ulonglong = unsigned long long;
    using wchar = wchar_t;
public:
    enum Type {
        // DT_NULL = 0x50
        Invalid, // 无效

        // DT_BYTE1 = 0x10,
        Char,
        UChar,
        WChar,

        // DT_BYTE2 = 0x11,
        Short,
        UShort,

        // DT_BYTE4 = 0x12,
        Int,
        UInt,
        Long,
        ULong,

        // DT_BYTE8 = 0x13,
        LongLong,
        ULongLong,

        // DT_FLOAT = 0x14,
        Float,

        // DT_DOUBLE = 0x15,
        Double,
        LongDouble,

        // DT_STRING = 0x20, DT_BYTES = 0x40,
        String,			// std::string
        WString,		// std::wstring

        // DT_BOOL = 0x30,
        Bool,

        // DT_BYTES 大字段数据
        BigBytes,
    };

    template<typename T>
    static Type typeID();
public:
    Variant();
    ~Variant();

    Variant(bool b);
    Variant(char c);
    Variant(uchar uc);
//    Variant(wchar_t wc);
    Variant(short s);
    Variant(ushort us);
    Variant(int i);
    Variant(uint ui);
//    Variant(long l);
//    Variant(ulong ul);
    Variant(long long ll);
    Variant(ulonglong ull);
    Variant(float f);
    Variant(double d);
//    Variant(long double ld);
    Variant(const char *str);
//    Variant(const wchar_t *wstr, bool bIsBig = false);
    Variant(const std::string &str);
//    Variant(const std::wstring &wstr, bool bIsBig = false);
    Variant(const char *str, int len);
    Variant(const vector<char>& vec);

    Variant(const Variant &other);
    Variant(Variant &&other);
    Variant &operator=(const Variant &other);
    Variant &operator=(Variant &&other);

    Type type() const;
    bool canConvert(Type type) const;
    bool isValid() const; // true : 有效， false : null
    bool lookBigDataBuf(const char* ptrbuf, int& len) const;
//    bool isBigStr() const;

    bool toBool() const;
    char toChar() const;
    uchar toUchar() const;
    wchar toWChar() const;
    short toShort() const;
    ushort toUShort() const;
    int toInt() const;
    uint toUInt() const;
    long toLong() const;
    ulong toULong() const;
    long long toLongLong() const;
    ulonglong toULongLong() const;
    float toFloat() const;
    double toDouble() const;
    long double toLongDouble() const;
    std::string toString() const;
    std::wstring toWString() const;
    vector<char> toBigVector() const;

private:
    void make_invalid();

    template<typename T>
    static T strToNumber(const std::string &str);
    template<typename T>
    static T strToNumber(const std::wstring &wstr);

    template<typename T>
    T numVariantToHelper(const T &val) const;

    template <typename T>
    static inline void safe_delete_void_ptr(void *&target);

private:
    struct Private {
        inline Private() noexcept
            : type(Invalid)
            , is_shared(false)
            , is_null(true)
        {
            data.ptr = nullptr;
        }

        // Internal constructor for initialized variants.
        explicit inline Private(Type variantType) noexcept
            : type(variantType)
            , is_shared(false)
            , is_null(false)
        {}

        inline Private(const Private &other) noexcept
            : data(other.data)
            , type(other.type)
            , is_shared(other.is_shared)
            , is_null(other.is_null)
        {}

        union Data {
            bool b;
            char c;
            uchar uc;
            wchar_t wc;
            short s;
            ushort us;
            int i;
            uint ui;
            long l;
            ulong ul;
            long long ll;
            ulonglong ull;
            float f;
            double d;
            long double ld;
            void *ptr;
        }data;

        Type type;
        bool is_shared;
        bool is_null;
        int  i_big_len;
    };
    Private		_d;
};


#endif // VARIANT_H

