#include <fstream>
#include "basejsonreader.h"

BaseJsonReader::BaseJsonReader()
{

}

BaseJsonReader::~BaseJsonReader()
{

}

bool BaseJsonReader::read(const string &fileName)
{
    Json::Value value;
    Json::Reader jsonReader;

    ifstream ifile;
    ifile.open(fileName);

    if (!ifile.is_open())
    {
        return false;
    }

    if(!jsonReader.parse(ifile, value))
    {
        return false;
    }

    dataClear();

    readDetails(value);

    ifile.close();

    return true;
}
