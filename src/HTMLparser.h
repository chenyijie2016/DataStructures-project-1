//
// Created by cyj on 2017/10/24.
//

#ifndef S_1_HTMLPARSER_H
#define S_1_HTMLPARSER_H

#include <iostream>
#include "DataStructure.h"

class HTMLElement
{
public:
    MyDataStructure::String content;
    MyDataStructure::String type;
    int _type;
    MyDataStructure::String attributes;

    HTMLElement* children;
    HTMLElement* parent;
};



class HTMLparser
{
public:

    MyDataStructure::String html;
    MyDataStructure::stack<HTMLElement> doms;
    HTMLElement *root;
public:
    HTMLparser(std::string filename);
    void parse();
};


#endif //S_1_HTMLPARSER_H
