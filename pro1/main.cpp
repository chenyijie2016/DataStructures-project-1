// pro1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "NetWork.h"
#include "HTMLparser.h"
#include <locale>

int main()
{
    //NetWork::downloadPages();
    setlocale(LC_ALL, "zh_CN.gbk");
    HTMLparser htmlparser("18.html");

    getchar();
    return 0;
}

