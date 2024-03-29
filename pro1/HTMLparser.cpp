﻿#include "stdafx.h"
#include "HTMLparser.h"

using namespace std;

#define  TITLE 3
#define DIV 25
#define P 29
#define TD 18
#define EM 27

//#define DEBUG_OUTPUT
HTMLparser::HTMLparser(string filename)
{
    token[0] = String(L"html");
    token[1] = String(L"head");
    token[2] = String(L"meta");//*
    token[3] = String(L"title");
    token[4] = String(L"base");//*
    token[5] = String(L"script");
    token[6] = String(L"body");
    token[7] = String(L"a");
    token[8] = String(L"strong");
    token[9] = String((L"ul"));
    token[10] = String(L"link");//*
    token[11] = String(L"span");
    token[12] = String(L"dl");
    token[13] = String(L"dd");
    token[14] = String(L"input");//*
    token[15] = String(L"dt");//
    token[16] = String(L"table");
    token[17] = String(L"tr");
    token[18] = String(L"td");
    token[19] = String(L"button");
    token[20] = String(L"style");
    token[21] = String(L"li");
    token[22] = String(L"img");//*
    token[23] = String(L"label");
    token[24] = String(L"form");
    token[25] = String(L"div");
    token[26] = String(L"br");//*
    token[27] = String(L"em");
    token[28] = String(L"h1");
    token[29] = String(L"p");
    token[30] = String(L"th");//*
    token[31] = String(L"font");
    token[32] = String(L"h3");
    token[33] = String(L"iframe");
    token[34] = String(L"b");
    token[35] = String(L"h4");
    token[36] = String(L"blockquote");
    token[37] = String(L"ignore_js_op");

    token_number = 38;
    load(filename);
}

/**
 * \brief 从GBK编码的网页文件中读取文本并转换为UTF8
 * \param filename 文件名
 */
void HTMLparser::load(std::string filename)
{
    const char* GBK_LOCALE_NAME = ".936"; //GBK在windows下的locale name
    wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> Conver_GBK(
        new std::codecvt_byname<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
    FILE* fp;
    fp = fopen(("temp/" + filename).c_str(), "r");
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    char* buf = new char[fileSize + 1];
    memset(buf, 0, fileSize + 1);

    fseek(fp, 0, SEEK_SET);
    fread(buf, sizeof(char), fileSize, fp);
    std::wstring wDst = Conver_GBK.from_bytes(buf);
    //wprintf(L"%ls", wDst.c_str());
    delete[] buf;
    buf = nullptr;
    html = *new String(wDst);
}

/**
 * \brief 使用栈将HTML文本划分成dom节点,将出栈后结果保存在result
 */
void HTMLparser::toknize()
{
    cout << html.size() << endl;
    String t;
    try
    {
        int turn = 0;
        t = html.strtok(L'<', true);
        while (!t.empty())
        {
            if (t[1] == L'!')
            {
                t = html.strtok(L'<');
                continue;
            }
            HTMLElement* e = parse_token(t);


#ifdef DEBUG_OUTPUT
            t.output();
            cout << " _type:" << e->_type << "  start?: " << e->is_start_token;
            cout << endl;
#endif

            if (e->is_start_token)
            {
                if (!is_not_paired(e))
                {
                    parse_content(e, t);
                    Push(doms, e);
                }
                else
                {
                    result.push_back(e);
                }
            }
            else
            {
                HTMLElement* top;
                GetTop(doms, top);
                if (top)
                {
                    if (top->_type == e->_type)
                    {
                        Pop(doms, top);
                        result.push_back(top);
                    }
                    else
                    {
                        //html标签错误未闭合
                        //直接放弃最上方节点尝试匹配下一个
                        cout << "Warning: 不匹配的标签" << endl;
                        cout << endl << "栈顶标签: ";
                        top->type.output();
                        cout << endl << "当前标签: ";
                        e->type.output();
                        while (top)
                        {
                            Pop(doms, top);
                            if (top->_type == e->_type)
                            {
                                result.push_back(top);
                                break;
                            }
                        }
                        //throw Error("Unmatched tag");
                    }
                }
            }

            t = html.strtok(L'<');
        }
    }
    catch (Error& e)
    {
        e.detail();
    }
}


/**
 * \brief 预处理html文本，除去换行符及tab
 */
void HTMLparser::standardized()
{
    for (int i = 0; i < html.size(); i++)
    {
        if (html[i] == L'\n')
        {
            html[i] = L' ';
        }
        if (html[i] == L'\t')
        {
            html[i] = L' ';
        }
    }
}

/**
 * \brief 判断该html节点是否是自闭合的
 */
bool HTMLparser::is_not_paired(HTMLElement* e)
{
    auto t = e->_type;
    return t == 2 || t == 4 || t == 10 || t == 14 || t == 22 || t == 26 || t == 30;
}

/**
 * \brief 从字符串解析出单个HTML节点并判断类型
 */
HTMLElement* HTMLparser::parse_token(String s)
{
    //return nullptr;
    auto e = new HTMLElement();
    // 处理结束节点的情况
    if (s[1] == L'/')
    {
        e->is_start_token = false;
        for (int i = 2; i < s.size(); i++)
        {
            if (s[i] == L'>')
            {
                e->type = s.substr(2, i);
                for (int j = 0; j < token_number; j++)
                {
                    if (e->type == token[j])
                    {
                        e->_type = j;

                        break;
                    }
                }
                if (e->_type == -1)
                {
                    cout << "Warning: 不支持的dom标志" << endl;
                    cout << "Tag: ";
                    s.output();
                    cout << endl;
                }
                return e;
            }
        }
    }
    else//处理是开始节点的情况
    {
        e->is_start_token = true;
        for (int i = 1; i < s.size(); i++)
        {
            if (s[i] == L' ' || s[i] == L'>' || s[i] == L'/')
            {
                e->type = s.substr(1, i);
                for (int j = 0; j < token_number; j++)
                {
                    if (e->type == token[j])
                    {
                        e->_type = j;

                        break;
                    }
                }
                if (e->_type == -1)
                {
                    cout << "Warning: 不支持的dom标志" << endl;
                    cout << "Tag: ";
                    s.output();
                    cout << endl;
                }
                return e;
            }
        }
    }
    return nullptr;
}

/**
 * \brief 解析html节点e的内容
 */
void HTMLparser::parse_content(HTMLElement* e, String s)
{
    int start = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == L'>')
        {
            start = i + 1;
            break;
        }
    }
    //提取其内容
    if (s.size() - start > 0)
    {
        e->content = s.substr(start, s.size());
    }
    else
    {
        e->content = String();
    }
    //提取 class 信息
    if (s.indexof(String(L"class")) != s.size())
    {
        int start = s.indexof(String(L"class"));
        int j;
        for (j = start + 7; j < s.size(); j++)
        {
            if (s[j] == L'\"')
                break;
        }
        e->classes = s.substr(start + 7, j);
    }
    //提取 id 信息
    if (s.indexof(String(L"id")) != s.size())
    {
        int start = s.indexof(String(L"id"));
        int j;
        for (j = start + 7; j < s.size(); j++)
        {
            if (s[j] == L'\"')
                break;
        }
        e->id = s.substr(start + 4, j);
    }
}

/**
 * \brief 从 result 中提取网页信息
 */
PageInfo HTMLparser::parse()
{
    PageInfo info;

    //网页信息所在处的class名
    String class_z(L"z");
    String class_authi(L"authi");
    String class_t_f(L"t_f");
    String class_ts(L"ts z h1");
    bool author_found = false;
    bool tf_found = false;
    bool time_found = false;
    try
    {
        for (int i = 0; i < result.size(); i++)
        {
            if (result[i]->_type == DIV && result[i]->classes == class_authi && !author_found)
            {
                info.author = result[i - 1]->content;
                author_found = true;
            }
            if(result[i]->_type==DIV && result[i]->classes == class_authi && result[i-5]->_type == EM && !time_found)
            {
                info.time = result[i - 5]->content;
                time_found = true;
            }

            if (result[i]->_type == TD && result[i]->classes == class_t_f && !tf_found)
            {
                //特殊处理编码问题 如果正常则有三层 否则有四层并且需要转码
                String tmp;

                if (result[i - 1]->_type == P)
                {
                    tmp = result[i - 1]->content;
                }
                else if (result[i - 2]->_type == P)
                {
                    tmp = result[i - 2]->content;
                }
                else if (result[i - 3]->_type == P)
                {
                    tmp = result[i - 3]->content;
                }
                else
                {
                    tmp = result[i]->content;
                }
                int real_content_start;
                for (real_content_start = 0; real_content_start < tmp.size(); real_content_start++)
                {
                    if (tmp[real_content_start] != L' ' && tmp[real_content_start] != L'\n' && tmp[real_content_start]
                        != L'\t')
                        break;
                }
                if (real_content_start < tmp.size())
                {
                    info.content = tmp.substr(real_content_start, tmp.size());
                    info.content = decode(info.content);
                }
                tf_found = true;
            }
            if (result[i]->_type == DIV && result[i]->classes == class_ts)
            {
                info.type = result[i - 5]->content;
            }
            if (result[i]->_type == DIV && result[i]->classes == class_z)
            {
                info.category = result[i - 5]->content;
                info.subcategory = result[i - 3]->content;
                info.title = result[i - 1]->content;
            }
        }
    }
    catch (Error& e)
    {
        e.detail();
    }
    
    return info;
}

/**
 * \brief 遍历dom节点树,提取网页内容
 * \return 
 */
PageInfo HTMLparser::parse_tree()
{
    // TODO: 完成树的生成和遍历
    return PageInfo();
}

/**
 * \brief 清理内存
 */
void HTMLparser::destory()
{
    result.remove_all();
    ClearStack(doms);
    html.destory();
}
