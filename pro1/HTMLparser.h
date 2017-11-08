#pragma once

#include "String.h"
#include "Stack.h"
#include "LinkList.h"


class HTMLparser
{
private:
    String html;
    Stack doms;
    HTMLElement *root;
    String token[40];
    LinkList<HTMLElement*> result;
    std::string _filename;
    int token_number, end_token_number;
public:
    HTMLparser(std::string filename);

    void load(std::string filename);

    void toknize();

    void standardized();

    static bool is_not_paired(HTMLElement *e);

    HTMLElement *parse_token(String s);

    static void parse_content(HTMLElement* e, String s);

    PageInfo parse();

    PageInfo parse_tree();

    void destory();
};

