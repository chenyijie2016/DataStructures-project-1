//
// Created by cyj on 2017/10/24.
//

#include "HTMLparser.h"
#include <fstream>
#include <locale.h>
#include <winuser.h>


HTMLparser::HTMLparser(std::string filename)
{
    setlocale(LC_CTYPE, "chs");
    //start_token = new MyDataStructure::String*;
    start_token[0] = new MyDataStructure::String(std::wstring(L"<html"));
    start_token[1] = new MyDataStructure::String(std::wstring(L"<head"));
    start_token[2] = new MyDataStructure::String(std::wstring(L"<meta"));
    start_token[3] = new MyDataStructure::String(std::wstring(L"<link"));
    start_token[4] = new MyDataStructure::String(std::wstring(L"<base"));
    start_token[5] = new MyDataStructure::String(std::wstring(L"<script"));
    start_token[6] = new MyDataStructure::String(std::wstring(L"<body"));
    start_token[7] = new MyDataStructure::String(std::wstring(L"<a"));
    start_token[8] = new MyDataStructure::String(std::wstring(L"<strong"));
    start_token[9] = new MyDataStructure::String(std::wstring(L"<ul"));
    start_token[10] = new MyDataStructure::String(std::wstring(L"<li"));
    start_token[11] = new MyDataStructure::String(std::wstring(L"<span"));
    //MyDataStructure::String("<img"),//无闭合，特殊处理
    start_token[12] = new MyDataStructure::String(std::wstring(L"<dl"));
    start_token[13] = new MyDataStructure::String(std::wstring(L"<dd"));
    start_token[14] = new MyDataStructure::String(std::wstring(L"<input"));
    start_token[15] = new MyDataStructure::String(std::wstring(L"<form"));
    start_token[16] = new MyDataStructure::String(std::wstring(L"<table"));
    start_token[17] = new MyDataStructure::String(std::wstring(L"<tr"));
    start_token[18] = new MyDataStructure::String(std::wstring(L"<td"));
    start_token[19] = new MyDataStructure::String(std::wstring(L"<button"));
    start_token[20] = new MyDataStructure::String(std::wstring(L"<style"));

    end_token[0] = new MyDataStructure::String(std::wstring(L"</"));
    end_token[1] = new MyDataStructure::String(std::wstring(L"/>"));

    std::wifstream tmp("./temp/" + filename);
    std::wstring str((std::istreambuf_iterator<wchar_t>(tmp)),
                     std::istreambuf_iterator<wchar_t>());

    html = new MyDataStructure::String(str);
    parse();
}

void HTMLparser::parse()
{
    std::cout << html->length << std::endl;
    int total = 0;
    for (int i = 0; i < html->length; i++)
    {
        if (html->ch[i] == L'<' || html->ch[i] == L'/')
        {
            try
            {
                for (int j = 0; j < 21; j++)
                {
                    auto sub = html->substring(i + 1, start_token[j]->length);
                    if (MyDataStructure::strcompare(sub, start_token[j]) == 0)
                    {
                        std::cout << i << std::endl;
                        for (int k = 0; k < doms.top - doms.base + 1; k++)
                        {
                            std::cout << "\t";
                        }
                        std::cout << "++dom " << total++ << " ";
                        wprintf(L"type=%ls \n", start_token[j]->ch);
                        auto dom = new HTMLElement;
                        dom->_type = j;

                        if (!doms.is_empty())
                        {
                            dom->parent = doms.gettop();
                        }
                        doms.push(*dom);
                    }

                    delete sub;
                }
                for (int j = 0; j < 2; j++)
                {
                    auto sub = html->substring(i + 1, end_token[j]->length);
                    if (MyDataStructure::strcompare(sub, end_token[j]) == 0)
                    {
                        for (int k = 0; k < doms.top - doms.base; k++)
                        {
                            std::cout << "\t";
                        }

                        std::cout << i << " --end dom " << total++;
                        //std::cout << " type " << doms.gettop()->_type;
                        //start_token[doms.gettop()->_type]->output();
                        std::cout << " Stack size:" << doms.top - doms.base << std::endl;
                        doms.pop();
                    }
                }
            }

            catch (int x)
            {
                std::cout << "ERROR" << x << std::endl;
                system("pause");
            }
            catch (...)
            {
                std::cout << "ERROR" << std::endl;
                system("pause");
            }
        }
    }
}
