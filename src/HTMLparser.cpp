//
// Created by cyj on 2017/10/24.
//

#include "HTMLparser.h"
#include <fstream>
using namespace std;
MyDataStructure::String start_token[] = {
    MyDataStructure::String(string("<html")),
    MyDataStructure::String(string("<head")),
    MyDataStructure::String("<meta"),
    MyDataStructure::String("<link"),
    MyDataStructure::String("<base"),
    MyDataStructure::String("<script"),
    MyDataStructure::String("<body"),
    MyDataStructure::String("<a"),
    MyDataStructure::String("<strong"),
    MyDataStructure::String("<ul"),
    MyDataStructure::String("<li"),
    MyDataStructure::String("<span"),
    //MyDataStructure::String("<img"),//无闭合，特殊处理
    MyDataStructure::String("<dl"),
    MyDataStructure::String("<dd"),
    MyDataStructure::String("<input"),
    MyDataStructure::String("<form"),
    MyDataStructure::String("<table"),
    MyDataStructure::String("<tr"),
    MyDataStructure::String("<td"),
    MyDataStructure::String("<button"),
    MyDataStructure::String("<style"),
    //    MyDataStructure::String("<html"),
    //    MyDataStructure::String("<html"),

};
MyDataStructure::String end_token[] = {
    MyDataStructure::String("</"),
    MyDataStructure::String("/>")
};

HTMLparser::HTMLparser(std::string filename)
{
    std::ifstream tmp("./temp/" + filename);
//    std::string str((std::istreambuf_iterator<char>(tmp)),
//                    std::istreambuf_iterator<char>());
    char buffer[200000];
    //std::cout << str;
    tmp >> buffer;
    html = MyDataStructure::String(buffer);
    std::cout << html;
    //cout << start_token[1];
    //std::cout << sizeof(HTMLElement);
}

void HTMLparser::parse()
{
    std::cout << html.length << std::endl;
    int total = 0;
    for (int i = 0; i < html.length; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            try
            {
                auto sub = html.substring(i + 1, start_token[j].length);

                if (MyDataStructure::strcompare(sub, start_token[j]) == 0)
                {
                    std::cout << sub << "  " << start_token[j] << std::endl;
                    std::cout << "new dom" << total++ << std::endl;
                    auto dom = new HTMLElement;
                    dom->_type = j;

                    if (!doms.is_empty())
                    {
                        dom->parent = doms.gettop();
                    }
                    doms.push(*dom);
                    std::cout << start_token[j] << std::endl;
                }
                free(&sub);
            }
            catch (...)
            {
                std::cout << i << std::endl;
                system("pause");
            }
        }
    }
}
