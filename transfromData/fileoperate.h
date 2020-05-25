#ifndef H_FILE_OPERATE_H
#define H_FILE_OPERATE_H

#include <iostream>
#include <string>
#include <ctime>
#include <ios>
#include <vector>
#include <fstream>
#include <mutex>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class FileOperate
{
public:
    FileOperate();
    ~FileOperate();

    static int readFile(const string& strFilePath, const string& strFileName);
    static int writeFile(const string& strFilePath, const string& strFileName, const vector<char>& varContent);
    static const vector<char>& getReadContent(){return m_vec;}

protected:
    static vector<char> m_vec; //读取文件中数据存放
    static mutex m_mutex;
};

#endif // FILEOPERATE_H


#if 0
using namespace std;

/**
 * 快速读取大文件
 * @return
 */

//int main()
{
    clock_t start = clock();
    ifstream fin("d:\\1.txt", std::ios::binary);

    vector<char> buf(static_cast<unsigned int>(fin.seekg(0, std::ios::end).tellg()));
    fin.seekg(0, std::ios::beg).read(&buf[0], static_cast<std::streamsize>(buf.size()));

    fin.close();
    clock_t end = clock();
    cout << "time : " << ((double) end - start) / CLOCKS_PER_SEC << "s\n";
    vector<char>::iterator it;
    for (it = buf.begin(); it != buf.end(); it++)
    {
        cout << *it << "";
    }
    cout << endl;
}
#endif

#if 0

std::vector<char> varInfo;
while(!lob2.eof()){ // read while not "end-of-file" -- end of CLOB
    ++n;
    lob2>>f2; // reading a chunk of CLOB
    cout<<"   chunk #"<<n;
    cout<<", f3="<<f2[0]<<f2[f2.len()-1]<<", len="<<f2.len()<<endl;

    // begin zcj test
    static int tempIndex = 0;
    {
        if (!tempIndex)
        {
            tempIndex = 1;

            for (int demoIndex = 0; demoIndex < f2.len(); ++demoIndex)
            {
                varInfo.push_back(f2[demoIndex]);
//                        string strDemo = "";
//                        strDemo.assign(static_cast<const char*> (f2.v), 0, f2.len());

//                        cout << "strDemo: " << strDemo << endl;

            }
//                    varInfo.


        }
    }
    // end zcj test

    for (auto it = varInfo.begin(); it != varInfo.end(); ++it)
    {
        cout << (*it);
    }
    cout << endl;

#endif

#if 0
    /*!
    00——只检查文件是否存在 当strFilePath为目录时，_access只判断指定目录是否存在
    02——写权限
    04——读权限
    06——读写权限
    */
//    if (-1 == _access(strFilePath.c_str(), 0))
//    {
//        cout << "no exist: " << strFilePath << endl;
//        return false;
//    }

    const string strFile = strFilePath+"/"+strFileName;
    cout << "strFileName : " << strFile << endl;
//    if (-1 == _access(strFile.c_str(),4)
//            && -1 == _access(strFile.c_str(),6))
//    {
//        cout << "no read power: " << strFileName << endl;
//        return false;
//    }
#endif
