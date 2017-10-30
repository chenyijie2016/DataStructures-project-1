#include "stdafx.h"
#include "NetWork.h"
#include "CSVparser.hpp"
using namespace std;

void NetWork::getUrl(std::string url, std::string filename)
{
    auto cmd = "curl.exe " + url + " -o " + filename;
    cout << cmd << endl;
    system(cmd.c_str());
}

void NetWork::downloadPages()
{
    std::cout << "[Step 1/x] Downloading pages" << std::endl;
    try
    {
        csv::Parser file = csv::Parser("input/url.csv");
        auto row = file.rowCount();

        for (int i = 0; i < row; i++)
        {
            std::cout << i << std::endl;
            std::ostringstream stringStream;
            stringStream << "temp/" << i << ".html";
            //std::cout << file[i][1] << std::endl;
            auto url = file[i][1].substr(1, file[i][1].size() - 2);
            std::cout << '\r' << '[' << i << '/' << row << "]  ";
            //<< file[i][1].substr(1, file[i][1].size() - 2);//<< std::endl;
            getUrl(url, stringStream.str());
        }
    }
    catch (...)
    {
    }
}
