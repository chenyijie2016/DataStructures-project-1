#pragma once

#include <vector>
#include "String.h"

class HTMLElement
{
public:
    String *content;
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
