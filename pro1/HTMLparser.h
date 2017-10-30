#pragma once

#include "String.h"
#include "Stack.cpp"
#include <vector>
#include "Stack.h"


class HTMLElement
{
public:
    //String content;
    String *type;
    bool is_start_token;
    int _type;
    //std::map<String, String> attributes;

    std::vector<HTMLElement *> children;
    HTMLElement *parent;

    ~HTMLElement() {
        delete(type);
    }
};


class HTMLparser
{
public:


    String *html;
    Stack<HTMLElement> doms;
    HTMLElement *root;
    //std::map<String, int> DOM_TYPES;
    String *token[40];
    String *end_token[10];
    std::vector<HTMLElement> result;

    int token_number, end_token_number;
public:
    HTMLparser(std::string filename);

    void parse();

    void standardized();

    bool is_not_paired(HTMLElement *e);

    HTMLElement *parser_dom(String *s);
};

