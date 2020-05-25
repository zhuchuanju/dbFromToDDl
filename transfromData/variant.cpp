#include "variant.h"
#include <sstream>
#include <wchar.h>

Variant::Variant()
    : _d(Invalid)
{
}

Variant::~Variant()
{
    if (String == _d.type)
    {
        if (_d.data.ptr)
            safe_delete_void_ptr<char *>(_d.data.ptr);
    }
    else if (WString == _d.type)
    {
        if (_d.data.ptr)
            safe_delete_void_ptr<wchar_t *>(_d.data.ptr);
    }
    else if (BigBytes == _d.type)
    {
        _d.i_big_len = 0;
        delete [](char*)_d.data.ptr;
        _d.data.ptr = nullptr;
    }
}

Variant::Variant(bool b)
    : _d(Bool)
{
    _d.data.b = b;
}

Variant::Variant(char c)
    : _d(Char)
{
    _d.data.c = c;
}

Variant::Variant(uchar uc)
    : _d(UChar)
{
    _d.data.uc = uc;
}

#if 0
Variant::Variant(wchar_t wc)
    : _d(WChar)
{
    _d.data.wc = wc;
}
#endif
Variant::Variant(short s)
    : _d(Short)
{
    _d.data.s = s;
}

Variant::Variant(ushort us)
    : _d(UShort)
{
    _d.data.us = us;
}

Variant::Variant(int i)
    : _d(Int)
{
    _d.data.i = i;
}

Variant::Variant(uint ui)
    : _d(UInt)
{
    _d.data.ui = ui;
}

#if 0
Variant::Variant(long l)
    : _d(Long)
{
    _d.data.l = l;
}
Variant::Variant(ulong ul)
    : _d(ULong)
{
    _d.data.ul = ul;
}
#endif

Variant::Variant(long long ll)
    : _d(LongLong)
{
    _d.data.ll = ll;
}

Variant::Variant(ulonglong ull)
    : _d(ULongLong)
{
    _d.data.ull = ull;
}

Variant::Variant(float f)
    : _d(Float)
{
    _d.data.f = f;
}
Variant::Variant(double d)
    : _d(Double)
{
    _d.data.d = d;
}

#if 0
Variant::Variant(long double ld)
    : _d(LongDouble)
{
    _d.data.ld = ld;
}
#endif

Variant::Variant(const char *str)
    : _d(String)
{
    if (!str) {
        make_invalid();
    } else {
//        size_t len = strlen(str); // dashen
        _d.data.ptr = new char[strlen(str) + 1];
//        strcpy_s(static_cast<char *>(_d.data.ptr), strlen(str) + 1, str); // dashen
        strncpy(static_cast<char *>(_d.data.ptr), str, strlen(str)+1);
    }
}

#if 0
Variant::Variant(const wchar_t * wstr, bool bIsBig)
    : _d(WString)
{
    if (!wstr) {
        make_invalid();
    } else {
        _d.data.ptr = new char[wcslen(wstr) + 1];
//        wcscpy_s((wchar_t *)_d.data.ptr, wcslen(wstr) + 1, wstr); // dashen
        wcsncpy((wchar_t *)_d.data.ptr, wstr, wcslen(wstr) + 1);
    }
}
#endif

Variant::Variant(const std::string &str)
    : _d(String)
{
    if (str.empty()) {
        make_invalid();
    } else {
        _d.data.ptr = new char[str.size() + 1];
//        strcpy_s((char *)_d.data.ptr, str.size() + 1, str.c_str());
        strncpy((char *)_d.data.ptr, str.c_str(), str.size() + 1);
    }
}

Variant::Variant(const char *str, int len)
    : _d(BigBytes)
{
    if (!str) {
        make_invalid();
    } else {
        _d.i_big_len = len;
        _d.data.ptr = new char[len];
        memcpy(_d.data.ptr, str, len);
    }
}

Variant::Variant(const vector<char> &vec)
    : _d(BigBytes)
{
    if (vec.empty())
    {
        make_invalid();
    }
    else
    {
        _d.i_big_len = vec.size();
        _d.data.ptr = new char[_d.i_big_len];
        memcpy(_d.data.ptr, &vec[0], _d.i_big_len);
    }
}

#if 0
Variant::Variant(const std::wstring &wstr, bool bIsBig)
    : _d(WString)
{
    if (wstr.empty()) {
        make_invalid();
    } else {
        _d.data.ptr = new wchar_t[wstr.size() + 1];
//        wcscpy_s((wchar_t *)_d.data.ptr, wstr.size() + 1, wstr.c_str());
        wcsncpy((wchar_t *)_d.data.ptr, wstr.c_str(), wstr.size() + 1);
    }
}
#endif

Variant::Variant(const Variant &other)
    : _d(other._d)
{
    if (String == _d.type)
    {
        _d.data.ptr = new char[strlen(static_cast<char *>(other._d.data.ptr)) + 1];
//        strcpy_s(static_cast<char *>(_d.data.ptr), strlen(static_cast<char *>(other._d.data.ptr)) + 1,
//            static_cast<char *>(other._d.data.ptr));
        strncpy(static_cast<char *>(_d.data.ptr), static_cast<char *>(other._d.data.ptr),
                strlen(static_cast<char *>(other._d.data.ptr)) + 1);
    }
    else if (WString == _d.type)
    {
        _d.data.ptr = new char[wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1];
//        wcscpy_s(static_cast<wchar_t *>(_d.data.ptr), wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1,
//            static_cast<wchar_t *>(other._d.data.ptr));
        wcsncpy(static_cast<wchar_t *>(_d.data.ptr), static_cast<wchar_t *>(other._d.data.ptr),
                 wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1);
    }
    else if (BigBytes == _d.type)
    {
        _d.i_big_len = other._d.i_big_len;
        _d.data.ptr = new char[other._d.i_big_len];

        memcpy(_d.data.ptr, other._d.data.ptr, _d.i_big_len);
    }
}
Variant::Variant(Variant &&other)
    : _d(other._d)
{
    if (String == other._d.type || WString == other._d.type)
    {
        this->_d.data.ptr = other._d.data.ptr;
        other.make_invalid();
    }
    else if (BigBytes == other._d.type)
    {
        this->_d.i_big_len = other._d.i_big_len;
        this->_d.data.ptr = other._d.data.ptr;
        other.make_invalid();
    }
}

Variant &Variant::operator=(const Variant &other)
{
    if (this == &other)
        return *this;
    if (String == _d.type || WString == _d.type)
    {
        if (_d.data.ptr)
        {
            if (String == _d.type)
                safe_delete_void_ptr<char *>(_d.data.ptr);
            else if (WString == _d.type)
                safe_delete_void_ptr<wchar_t *>(_d.data.ptr);

            _d.data.ptr = nullptr;
        }
    }
    else if (BigBytes == _d.type)
    {
        delete [](char*)_d.data.ptr;
        _d.data.ptr = nullptr;

        _d.i_big_len = 0;
    }


    if (Invalid == other._d.type)
    {
        make_invalid();
        return *this;
    }
    else if (String == other._d.type)
    {
        _d.data.ptr = new char[strlen(static_cast<char *>(other._d.data.ptr)) + 1];
//        strcpy_s(static_cast<char *>(_d.data.ptr), strlen(static_cast<char *>(other._d.data.ptr)) + 1,
//            static_cast<char *>(other._d.data.ptr));

        strncpy(static_cast<char *>(_d.data.ptr), static_cast<char *>(other._d.data.ptr),
                strlen(static_cast<char *>(other._d.data.ptr)) + 1);
    }
    else if (WString == other._d.type)
    {
        _d.data.ptr = new char[wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1];
//        wcscpy_s(static_cast<wchar_t *>(_d.data.ptr), wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1,
//            static_cast<wchar_t *>(other._d.data.ptr));

        wcsncpy(static_cast<wchar_t *>(_d.data.ptr), static_cast<wchar_t *>(other._d.data.ptr),
                 wcslen(static_cast<wchar_t *>(other._d.data.ptr)) + 1);
    }
    else if (BigBytes == other._d.type)
    {
        _d.i_big_len = other._d.i_big_len;
        _d.data.ptr = new char[_d.i_big_len];

        memcpy(_d.data.ptr, other._d.data.ptr, _d.i_big_len);
    }
    else
    {
        _d.data = other._d.data;
    }

    this->_d.type = other._d.type;
    this->_d.is_null = other._d.is_null;
    this->_d.is_shared = other._d.is_shared;
    return *this;
}

Variant &Variant::operator=(Variant &&other)
{
    if (this == &other)
        return *this;
    this->_d = other._d;
    if (String == _d.type || WString == _d.type)
    {
        this->_d.data.ptr = other._d.data.ptr;
        other.make_invalid();
    }
    else if (BigBytes == _d.type)
    {
        this->_d.i_big_len = other._d.i_big_len;
        this->_d.data.ptr = other._d.data.ptr;
        other.make_invalid();
    }
    return *this;
}

Variant::Type Variant::type() const
{
    return _d.type;
}

bool Variant::canConvert(Type type) const
{
    if (Invalid == type)
        return false;
    switch (_d.type)
    {
    case BigBytes:      return false;
    case Invalid:		return false;
    case Char:			return WChar != type && WString != type;
    case UChar:			return WChar != type && WString != type;
    case WChar:			return Char != type && String != type;
    case Short:			return true;
    case UShort:		return true;
    case Int:			return true;
    case UInt:			return true;
    case Long:			return true;
    case ULong:			return true;
    case LongLong:		return true;
    case ULongLong:		return true;
    case Float:			return Char != type && UChar != type && WChar != type;
    case Double:		return Char != type && UChar != type && WChar != type;
    case LongDouble:	return Char != type && UChar != type && WChar != type;
    case String:		return WString != type;
    case WString:		return String != type;
    default: break;
    }
    return false;
}

bool Variant::isValid() const
{
    return _d.type != Invalid;
}

bool Variant::lookBigDataBuf(const char *ptrbuf, int &len) const
{
    if (BigBytes != _d.type)
        return false;

    ptrbuf = static_cast<char*>(_d.data.ptr);
    len = _d.i_big_len;
    return true;
}

std::string Variant::toString() const
{
    if (!isValid() || WString == _d.type || BigBytes == _d.type)
        return "";
    if (String == _d.type)
        return static_cast<char *>(_d.data.ptr);

    std::stringstream ss;
    try {
        switch (_d.type)
        {
        case Bool:
            if (_d.data.b)
                ss << "true";
            else
                ss << "false";                  break;
        case Char:			ss << _d.data.c;	break;
        case UChar:			ss << _d.data.uc;	break;
        case WChar:								break;
        case Short:			ss << _d.data.s;	break;
        case UShort:		ss << _d.data.us;	break;
        case Int:			ss << _d.data.i;	break;
        case UInt:			ss << _d.data.ui;	break;
        case Long:			ss << _d.data.l;	break;
        case ULong:			ss << _d.data.ul;	break;
        case LongLong:		ss << _d.data.ll;	break;
        case ULongLong:		ss << _d.data.ull;	break;
        case Float:			ss << _d.data.f;	break;
        case Double:		ss << _d.data.d;	break;
        case LongDouble:	ss << _d.data.ld;	break;
        default: break;
        }
    } catch (...) {
        return ss.str();
    }

    return ss.str();
}

std::wstring Variant::toWString() const
{
    if (!isValid() || String == _d.type || BigBytes == _d.type)
        return L"";
    if (WString == _d.type)
        return static_cast<wchar_t *>(_d.data.ptr);

    std::wstringstream wss;
    try {
        switch (_d.type)
        {
        case Bool:
            if (_d.data.b) wss << L"true";
            else wss << L"false"; break;
        case Char:			wss << _d.data.c;	break;
        case UChar:			wss << _d.data.uc;	break;
        case WChar:			wss << _d.data.wc;	break;
        case Short:			wss << _d.data.s;	break;
        case UShort:		wss << _d.data.us;	break;
        case Int:			wss << _d.data.i;	break;
        case UInt:			wss << _d.data.ui;	break;
        case Long:			wss << _d.data.l;	break;
        case ULong:			wss << _d.data.ul;	break;
        case LongLong:		wss << _d.data.ll;	break;
        case ULongLong:		wss << _d.data.ull;	break;
        case Float:			wss << _d.data.f;	break;
        case Double:		wss << _d.data.d;	break;
        case LongDouble:	wss << _d.data.ld;	break;
        default: break;
        }
    } catch (...) {
        return wss.str();
    }

    return wss.str();
}

vector<char> Variant::toBigVector() const
{
    vector<char> vecData;

    if (BigBytes == _d.type)
    {
        vecData.insert(vecData.end(), (char*)_d.data.ptr, (char*)_d.data.ptr + _d.i_big_len);
    }

    return vecData;
}

bool Variant::toBool() const
{
    switch (_d.type)
    {
    case BigBytes: return false;
    case Bool:	return _d.data.b;
    case String: return (strcmp((char *)_d.data.ptr, "true") == 0);
    case WString: return (wcscmp((wchar_t *)_d.data.ptr, L"true") == 0);
    default: return numVariantToHelper<bool>(_d.data.b);
    }
}
char Variant::toChar() const
{
    return numVariantToHelper<char>(_d.data.c);
}
Variant::uchar Variant::toUchar() const
{
    return numVariantToHelper<uchar>(_d.data.uc);
}
wchar_t Variant::toWChar() const
{
    return numVariantToHelper<wchar_t>(_d.data.wc);
}
short Variant::toShort() const
{
    return numVariantToHelper<short>(_d.data.s);
}
Variant::ushort Variant::toUShort() const
{
    return numVariantToHelper<ushort>(_d.data.us);
}
int Variant::toInt() const
{
    return numVariantToHelper<int>(_d.data.i);
}
Variant::uint Variant::toUInt() const
{
    return numVariantToHelper<uint>(_d.data.ui);
}
long Variant::toLong() const
{
    return numVariantToHelper<long>(_d.data.l);
}
Variant::ulong Variant::toULong() const
{
    return numVariantToHelper<ulong>(_d.data.ul);
}
long long Variant::toLongLong() const
{
    return numVariantToHelper<long long>(_d.data.ll);
}
Variant::ulonglong Variant::toULongLong() const
{
    return numVariantToHelper<ulonglong>(_d.data.ull);
}
float Variant::toFloat() const
{
    return numVariantToHelper<float>(_d.data.f);
}
double Variant::toDouble() const
{
    return numVariantToHelper<double>(_d.data.d);
}
long double Variant::toLongDouble() const
{
    return numVariantToHelper<long double>(_d.data.ld);
}

void Variant::make_invalid()
{
    _d.type = Invalid;
    _d.is_null = true;
    _d.is_shared = false;
    _d.data.ptr = nullptr;
    _d.i_big_len = 0;
}

template<typename T>
Variant::Type Variant::typeID()
{
//    if (std::is_same_v<T, char>) // windows中写法
    if (std::is_same<T, bool>::value)
        return Bool;
    if (std::is_same<T, char>::value)
        return Char;
    if (std::is_same<T, uchar>::value)
        return UChar;
    if (std::is_same<T, wchar_t>::value)
        return WChar;
    if (std::is_same<T, short>::value)
        return Short;
    if (std::is_same<T, ushort>::value)
        return UShort;
    if (std::is_same<T, int>::value)
        return Int;
    if (std::is_same<T, uint>::value)
        return UInt;
    if (std::is_same<T, long>::value)
        return Long;
    if (std::is_same<T, ulong>::value)
        return ULong;
    if (std::is_same<T, long long>::value)
        return LongLong;
    if (std::is_same<T, ulonglong>::value)
        return ULongLong;
    if (std::is_same<T, float>::value)
        return Float;
    if (std::is_same<T, double>::value)
        return Double;
    if (std::is_same<T, long double>::value)
        return LongDouble;
    if (std::is_same<T, std::string>::value)
        return String;
    if (std::is_same<T, std::wstring>::value)
        return WString;

    return Invalid;
}

template<typename T>
T Variant::strToNumber(const std::string &str)
{
    try {
        switch (typeID<T>())
        {
        case Bool:			return stoi(str);		break;
        case Char:			return stoi(str);		break;
        case UChar:			return stoul(str);		break;
        case WChar:			return stoi(str);		break;
        case Short:			return stoi(str);		break;
        case UShort:		return stoul(str);		break;
        case Int:			return stoi(str);		break;
        case UInt:			return stoul(str);		break;
        case Long:			return stol(str);		break;
        case ULong:			return stoul(str);		break;
        case LongLong:		return stoll(str);		break;
        case ULongLong:		return stoull(str);;	break;
        case Float:			return stof(str);		break;
        case Double:		return stod(str);		break;
        case LongDouble:	return stold(str);		break;
        default: break;
        }
    } catch (...) {
        return T();
    }

    return T();
}

template<typename T>
T Variant::strToNumber(const std::wstring &wstr)
{
    try {
        switch (typeID<T>())
        {
        case Bool:			return stoi(wstr);		break;
        case Char:			return stoi(wstr);		break;
        case UChar:			return stoul(wstr);		break;
        case WChar:			return stoi(wstr);		break;
        case Short:			return stoi(wstr);		break;
        case UShort:		return stoul(wstr);		break;
        case Int:			return stoi(wstr);		break;
        case UInt:			return stoul(wstr);		break;
        case Long:			return stol(wstr);		break;
        case ULong:			return stoul(wstr);		break;
        case LongLong:		return stoll(wstr);		break;
        case ULongLong:		return stoull(wstr);;	break;
        case Float:			return stof(wstr);		break;
        case Double:		return stod(wstr);		break;
        case LongDouble:	return stold(wstr);		break;
        default: break;
        }
    } catch (const std::exception&) {
        return T();
    }

    return T();
}

template<typename T>
T Variant::numVariantToHelper(const T &val) const
{
    if (typeID<T>() == _d.type)
        return val;

    switch (_d.type)
    {
    case Bool:			return T(_d.data.b);	break;
    case Char:			return T(_d.data.c);	break;
    case UChar:			return T(_d.data.uc);	break;
    case WChar:			return T(_d.data.wc);	break;
    case Short:			return T(_d.data.s);	break;
    case UShort:		return T(_d.data.us);	break;
    case Int:			return T(_d.data.i);	break;
    case UInt:			return T(_d.data.ui);	break;
    case Long:			return T(_d.data.l);	break;
    case ULong:			return T(_d.data.ui);	break;
    case LongLong:		return T(_d.data.ll);	break;
    case ULongLong:		return T(_d.data.ull);;	break;
    case Float:			return T(_d.data.f);	break;
    case Double:		return T(_d.data.d);	break;
    case LongDouble:	return T(_d.data.ld);	break;
    case String:		return strToNumber<T>(static_cast<char *>(_d.data.ptr));
    case WString:		return strToNumber<T>(static_cast<wchar_t *>(_d.data.ptr));
    default: break;
    }
    return T();
}

template<typename T>
inline void Variant::safe_delete_void_ptr(void *&target)
{
    if (target)
    {
        T temp = static_cast<T>(target);
        delete []temp;
        temp = nullptr;
        target = nullptr;
    }
}
