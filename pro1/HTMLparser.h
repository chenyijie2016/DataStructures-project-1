#pragma once

#include "String.h"
#include <vector>
#include "Stack.h"
#include <map>


class HTMLparser
{
public:


    String *html;
    Stack doms;
    HTMLElement *root;
    //std::map<String, int> DOM_TYPES;
    String *token[40];
    String *end_token[10];
    std::vector<HTMLElement> result;

    int token_number, end_token_number;
public:
    HTMLparser(std::string filename);

    void toknize();

    void standardized();

    bool is_not_paired(HTMLElement *e);

    HTMLElement *parser_token(String *s);

    void parse_content(HTMLElement* e, String* s);
};

