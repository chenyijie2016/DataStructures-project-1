// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NetWork.h"
#include "HTMLparser.h"
#include "cxxopts.hpp"
#define _CRT_SECURE_NO_WARNINGS



int main(int argc, char* argv[])
{
    //    cxxopts::Options options("main.exe", "Course Project for DataStructure and Algorithm");
    //    options.add_options("1")
    //        ("S,skip", "Skip Download Pages");
    //
    //
    //    options.parse(argc, argv);
    //    if (options.count("skip"))
    //    {
    //        system("pause");
    //    }
    //    std::cout << options.help({"","1"});
    //    system("pause");
    //NetWork::downloadPages();
   // setlocale(LC_ALL, "zh_CN.UTF-8");
    //setlocale(LC_ALL, "chs.gbk");
    //setlocale(LC_ALL, "zh_CN.gb2312");
    setlocale(LC_ALL, "chs");
    for (int i =3; i < 75; i++)
    {
        if (i != 7 && i!=32 && i!=74)
        {
            std::cout << "---------" << i << "-----------" << std::endl;
            std::ostringstream sstream;
            sstream << i << ".html";
            HTMLparser htmlparser(sstream.str());
        }
    }
    

    getchar();
    return 0;
   
    
}
