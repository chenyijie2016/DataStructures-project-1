#include <iostream>
#include <fstream>
#include "Network.h"
#include "CSVparser.hpp"

void DownloadPages();

int main()
{

    //DownloadPages();

    return 0;
}


/**
 * \brief 下载网页文件,使用libcurl库
 */
void DownloadPages()
{
    Network n;
    std::cout << "[Step 1/x] Downloading pages" << std::endl;
    try
    {
        csv::Parser file = csv::Parser("./input/url.csv");
        auto row = file.rowCount();
        for (int i = 0; i < row; i++)
        {
            std::ostringstream stringStream;
            stringStream << "./temp/" << i << ".html";
            //std::cout << file[i][1] << std::endl;
            auto url = file[i][1].substr(1, file[i][1].size() - 2);
            std::cout << '\r' << '[' << i << '/' << row << "]  ";
            //<< file[i][1].substr(1, file[i][1].size() - 2);//<< std::endl;
            n.getUrl(url, stringStream.str());
        }
    }
    catch (...)
    {

    }
}
