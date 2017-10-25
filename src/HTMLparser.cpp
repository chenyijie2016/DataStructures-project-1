//
// Created by cyj on 2017/10/24.
//

#include "HTMLparser.h"
#include <fstream>
using namespace std;
MyDataStructure::String start_token[] = {
    MyDataStructure::String(wstring(L"<html")),
    MyDataStructure::String(wstring(L"<head")),
    MyDataStructure::String(wstring(L"<meta")),
    MyDataStructure::String(wstring(L"<link")),
    MyDataStructure::String(wstring(L"<base")),
    MyDataStructure::String(wstring(L"<script")),
    MyDataStructure::String(wstring(L"<body")),
    MyDataStructure::String(wstring(L"<a")),
    MyDataStructure::String(wstring(L"<strong")),
    MyDataStructure::String(wstring(L"<ul")),
    MyDataStructure::String(wstring(L"<li")),
    MyDataStructure::String(wstring(L"<span")),
    //MyDataStructure::String("<img"),//无闭合，特殊处理
    MyDataStructure::String(wstring(L"<dl")),
    MyDataStructure::String(wstring(L"<dd")),
    MyDataStructure::String(wstring(L"<input")),
    MyDataStructure::String(wstring(L"<form")),
    MyDataStructure::String(wstring(L"<table")),
    MyDataStructure::String(wstring(L"<tr")),
    MyDataStructure::String(wstring(L"<td")),
    MyDataStructure::String(wstring(L"<button")),
    MyDataStructure::String(wstring(L"<style")),
    //    MyDataStructure::String("<html"),
    //    MyDataStructure::String("<html"),

};
MyDataStructure::String end_token[] = {
    MyDataStructure::String(wstring(L"</")),
    MyDataStructure::String(wstring(L"/>"))
};

HTMLparser::HTMLparser(std::string filename)
{
    std::wifstream tmp("./temp/" + filename);
    std::wstring str((std::istreambuf_iterator<wchar_t>(tmp)),
                     std::istreambuf_iterator<wchar_t>());

    html = new MyDataStructure::String(str);
    printf("%ls\n", str.c_str());
    printf("%S\n", start_token[1].ch);
    //    cout << start_token[1].length;
}

void HTMLparser::parse()
{
    std::cout << html->length << std::endl;
    int total = 0;
    for (int i = 0; i < html->length; i++)
    {
        try
        {
            for (int j = 0; j < 21; j++)
            {

                auto sub = html->substring(i + 1, start_token[j].length);
                //new  MyDataStructure::String("");

                //auto sub = new  MyDataStructure::String("");
                if (MyDataStructure::strcompare(sub, &start_token[j]) == 0)
                {
                    //std::cout << *sub << "  " << start_token[j] << std::endl;
                    std::cout << "new dom" << total++ << std::endl;
                    auto dom = new HTMLElement;
                    dom->_type = j;

                    if (!doms.is_empty())
                    {
                        dom->parent = *doms.gettop();
                    }
                    doms.push(dom);
                    //std::cout << start_token[j] << std::endl;
                }
                delete sub;


            }
        }
        catch (MyDataStructure::ERROR X)
        {
            std::cout << i << "  ERROE CODE " << X << std::endl;
            break;
            //system("pause");

        }
        catch (...)
        {
            system("pause");
        }
    }
}
