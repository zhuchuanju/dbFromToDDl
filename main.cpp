#include <iostream>
#include "dbconfreader.h"

using namespace std;

int main()
{
    DbConfReader dbConfReader;
    dbConfReader.read("dbConf.json");
    dbConfReader.showReadInfo();
//    cout << "Hello World!" << endl;
    return 0;
}
