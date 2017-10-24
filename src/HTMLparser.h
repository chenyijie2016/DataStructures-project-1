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
    MyDataStructure::String attributes;

    HTMLElement *children;
    HTMLElement *parent;

};


class HTMLparser
{
public:
    HTMLparser(std::string filename);

};


#endif //S_1_HTMLPARSER_H
