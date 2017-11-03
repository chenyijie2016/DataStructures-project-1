// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NetWork.h"
#include "HTMLparser.h"
#include <locale>
#include "cxxopts.hpp"


int main(int argc, char* argv[])
{
    cxxopts::Options options("main.exe", "Course Project for DataStructure and Algorithm");
    options.add_options("1")
        ("S,skip", "Skip Download Pages");


    options.parse(argc, argv);
    if (options.count("skip"))
    {
        system("pause");
    }
    std::cout << options.help({"","1"});
    system("pause");
    //NetWork::downloadPages();
    setlocale(LC_ALL, "zh_CN.gbk");
    HTMLparser htmlparser("18.html");

    getchar();
    return 0;
}
