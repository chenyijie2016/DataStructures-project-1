// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NetWork.h"
#include "HTMLparser.h"
#include "cxxopts.hpp"
#include "StringHashTable.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
StringHashTable initDictionary();
void divideWords(String words, StringHashTable dic);

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
    //        for (int i =3; i < 75; i++)
    //        {
    //            if (i != 7 && i!=32 && i!=74)
    //            {
    //                std::cout << "---------" << i << "-----------" << std::endl;
    //                std::ostringstream sstream;
    //                sstream << i << ".html";
    //                HTMLparser htmlparser(sstream.str());
    //            }
    //        }
    //HTMLparser htmlparser("33.html");
    auto dic = initDictionary();
    String words(L"今年可能看见无所谓");
    divideWords(words, dic);
    getchar();
    return 0;
}

StringHashTable initDictionary()
{
    StringHashTable strhashtable;
    const std::locale empty_locale = std::locale::empty();
    typedef std::codecvt_utf8<wchar_t> converter_type; //std::codecvt_utf16
    const converter_type* converter = new converter_type;
    const std::locale utf8_locale = std::locale(empty_locale, converter);


    std::wifstream fin("dictionary.dic");
    fin.imbue(utf8_locale);


    int total = 0;
    if (fin)
    {
        wstring temp;
        while (getline(fin, temp))
        {
            total++;
            //cout << temp << endl;;
            //wstring wstr;
            if (total % 1000 == 0)
            {
                cout << "\r" << total;
            }
            //wprintf(L"%ls\n", temp.c_str());
            String tmp(temp);
            strhashtable.insert(tmp);
        }
    }
    else
    {
        cout << "error";
        throw Error("fail to load dictionary");
    }
#ifdef DEBUG
#ifndef NDEBUG
    String test(L"一不做二不休");
    cout << endl << strhashtable[test];


    ofstream fout("debug.log");
    for (int i = 0; i < HASH_TABLE_SIZE; i++)

    {
        fout << strhashtable.data[i].size() << endl;
    }
#endif
#endif

    return strhashtable;
}

void divideWords(String words, StringHashTable dic)
{
    //正向最大匹配法
    for (int i = words.size(); i > 0; i--)
    {
        String sub;
        sub = words.substr(0, i);
        if (dic[sub])
        {
            sub.output();
            cout << endl;
            String tobedivide;
            if (i == words.size())
                return;
            else
            {
                tobedivide = words.substr(i, words.size());
                divideWords(tobedivide, dic);
                return;
            }
        }
    }
}
