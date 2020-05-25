#include "fileoperate.h"

std::vector<char> FileOperate::m_vec; //读取文件中数据存放
std::mutex FileOperate::m_mutex;

FileOperate::FileOperate()
{

}

FileOperate::~FileOperate()
{

}


int FileOperate::readFile(const std::string &strFilePath, const string &strFileName)
{
    /*!
        00——只检查文件是否存在 当strFilePath为目录时，_access只判断指定目录是否存在
        02——写权限
        04——读权限
        06——读写权限
    */
    if (-1 == access(strFilePath.c_str(), 0))
    {
        cout << "no exist dir: " << strFilePath << endl;
        return -1;
    }

    const string strFile = strFilePath+"/"+strFileName;
    cout << "read strFileName: " << strFile << endl;

    if (-1 == access(strFile.c_str(),4)
            && -1 == access(strFile.c_str(),6))
    {
        cout << "file no read power: " << strFileName << endl;
        return -2;
    }

    ifstream fin(strFile.c_str(), std::ios::binary);
    vector<char> buf(static_cast<unsigned int>(fin.seekg(0, std::ios::end).tellg()));
    fin.seekg(0, std::ios::beg).read(&buf[0], static_cast<std::streamsize>(buf.size()));
    fin.close();

//    std::lock_guard<std::mutex> lck(mutex);
    m_mutex.lock();
    m_vec.clear();
    m_vec = buf;
    m_mutex.unlock();

    cout << strFileName << " buf size: " << m_vec.size() << endl;
    return 0;
}

int FileOperate::writeFile(const string &strFilePath, const string &strFileName, const vector<char> &varContent)
{
    if (-1 == access(strFilePath.c_str(), 0))
    {
        cout << "no exist dir: " << strFilePath << endl;
        return -1;
    }

    const string strFile = strFilePath + "/" + strFileName;
    cout << "sava file name : " << strFile << endl;

#if 0
    // 没有此文件则创建
    cout << "2: " << (-1 == access(strFile.c_str(), 2)) << endl;
    cout << "6: " << (-1 == access(strFile.c_str(), 6)) << endl;
    if (-1 == access(strFile.c_str(), 2)
            && -1 == access(strFile.c_str(), 6))
    {
        cout << "file no write power: " << strFileName << endl;
        return -2;
    }
#endif

    ofstream fout;
    fout.open(strFile.c_str(), std::ios::binary);

    if (fout.is_open())
    {
        for (auto it = varContent.begin(); it != varContent.end(); ++it)
        {
            fout << (*it);
        }
    }
    else
    {
        cout << "open file err: " << strFile << endl;
    }

    fout.close();

    return 0;
}

