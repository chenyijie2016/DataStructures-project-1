#pragma once

#include <vector>
#include "String.h"

class HTMLElement
{
public:
    String content;
    String type;
    String classes;
    bool is_start_token;
    int _type;
    HTMLElement() { _type = -1; }
    //std::map<String, String> attributes;
    String get_attr(String attr_name);
    std::vector<HTMLElement *> children;
    HTMLElement* parent;

    ~HTMLElement()
    {
        //delete(type);
    }
};

class PageInfo
{
public:
    PageInfo()
    {
    }

    PageInfo(PageInfo const& info)
    {
        url = info.url;
        title = info.title;
        author = info.author;
        category = info.category;
        subcategory = info.subcategory;
        type = info.type;
        content = info.content;
    }

    std::string url;
    String title;//标题
    String author;//作者
    String category;//大类
    String subcategory;//小类
    String type;//发帖类型
    String content;//发帖内容

    bool unicodeencode =false;
public:
    void show();
};

inline void PageInfo::show()
{
    std::cout << "\n--------网页信息---------\n";
    std::cout << "标    题: ";
    title.output();
    std::cout << std::endl;
    std::cout<<"作    者: ";
    author.output();
    std::cout << std::endl;
    std::cout << "发帖大类: ";
    category.output();
    std::cout << std::endl;
    std::cout << "发帖小类: ";
    subcategory.output();
    std::cout << std::endl;
    std::cout << "发帖类型: ";
    type.output();
    std::cout << std::endl;
    if (unicodeencode) {
        //setlocale(LC_ALL, "zh_CN.UTF-8");
        std::cout << "发帖内容: ";
        content.output();
        std::cout << std::endl;
        //setlocale(LC_ALL, "chs.gbk");
    }
    else
    {
        std::cout << "发帖内容: ";
        content.output();
        std::cout << std::endl;
    }
}
