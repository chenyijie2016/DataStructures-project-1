#include "stdafx.h"
#include "HTMLparser.h"
using namespace std;
#include <fstream>

HTMLparser::HTMLparser(std::string filename)
{
//    setlocale(LC_CTYPE, "chs");
//    setlocale(LC_ALL, "chs");
    token[0] = new String(std::wstring(L"html"));
    token[1] = new String(std::wstring(L"head"));
    token[2] = new String(std::wstring(L"meta"));//*
    token[3] = new String(std::wstring(L"title"));
    token[4] = new String(std::wstring(L"base"));//*
    token[5] = new String(std::wstring(L"script"));
    token[6] = new String(std::wstring(L"body"));
    token[7] = new String(std::wstring(L"a"));
    token[8] = new String(std::wstring(L"strong"));
    token[9] = new String(std::wstring(L"ul"));
    token[10] = new String(std::wstring(L"link"));//*
    token[11] = new String(std::wstring(L"span"));
    token[12] = new String(std::wstring(L"dl"));
    token[13] = new String(std::wstring(L"dd"));
    token[14] = new String(std::wstring(L"input"));//*
    token[15] = new String(std::wstring(L"dt"));// ???? bug for g++???
    token[16] = new String(std::wstring(L"table"));
    token[17] = new String(std::wstring(L"tr"));
    token[18] = new String(std::wstring(L"td"));
    token[19] = new String(std::wstring(L"button"));
    token[20] = new String(std::wstring(L"style"));
    token[21] = new String(std::wstring(L"li"));
    token[22] = new String(std::wstring(L"img"));//*
    token[23] = new String(std::wstring(L"label"));
    token[24] = new String(std::wstring(L"form"));
    token[25] = new String(std::wstring(L"div"));
    token[26] = new String(std::wstring(L"br"));//*
    token[27] = new String(std::wstring(L"em"));
    token[28] = new String(std::wstring(L"h1"));
    token[29] = new String(std::wstring(L"p"));
    token[30] = new String(std::wstring(L"th"));
    token[31] = new String(std::wstring(L"font"));
    token[32] = new String(std::wstring(L"h3"));
    token[33] = new String(std::wstring(L"iframe"));
    token[34] = new String(std::wstring(L"b"));
    token[35] = new String(std::wstring(L"h4"));
    //    end_token[0] = new String(std::wstring(L"</"));
    //    end_token[1] = new String(std::wstring(L"/>"));
    //    end_token[2] = new String(std::wstring(L" >"));
    //
    //
    token_number = 36;
    //    end_token_number = 2;

    wifstream tmp("temp/" + filename);
    wstring str((istreambuf_iterator<wchar_t>(tmp)),
                istreambuf_iterator<wchar_t>());

    //wprintf(L"%ls", str.c_str()) ;
    html = new String(str);

    standardized();
    parse();
}

void HTMLparser::parse()
{
    try
    {
        int turn = 0;
        auto t = html->firststrtok(L'<');
        while (t)
        {
            if (t->at(1) == L'!')
            {
                delete (t);
                t = html->strtok(L'<');
                continue;
            }
            t->output();

            HTMLElement* e = parser_dom(t);
            cout << " _type:" << e->_type << "  start?: " << e->is_start_token << endl;
            //            if (e->_type == 0)
            //            {
            //                system("pause");
            //            }
            if (e->is_start_token)
            {
                if (!is_not_paired(e))
                {
                    cout << "  [not paired]";
                    if (doms.size() != 0)
                    {
                        cout << "[empty]" << endl;
                        root = e;
                        //doms.push(*e);
                        //e->parent = nullptr;
                    }
                    else
                    {
                        //doms.gettop()->children[doms.gettop()->childnumber++] = *e;
                        //e->parent = doms.gettop();
                        //doms.push(*e);
                    }
                    cout << "---------------------------Stack-size " << doms.size() << endl;
                }
                else
                {
                    //do sth;
                }
            }
            else
            {
                //result.push_back(doms.pop());
                //doms.pop();
                cout << "---------------------------Stack-size " << doms.size() << endl;
            }
            //cout << endl << turn++ << endl;
            //delete (e);
            delete (t);
            t = html->strtok(L'<');
        }
    }
    catch (Error& e)
    {
        e.detail();
    }
}


void HTMLparser::standardized()
{
    for (int i = 0; i < html->length; i++)
    {
        if (html->ch[i] == L'\n')
        {
            html->ch[i] = L' ';
        }
        if (html->ch[i] == L'\t')
        {
            html->ch[i] = L' ';
        }
    }
}

bool HTMLparser::is_not_paired(HTMLElement* e)
{
    auto t = e->_type;
    return t == 2 || t == 4 || t == 10 || t == 14 || t == 22 || t == 26;
}

HTMLElement* HTMLparser::parser_dom(String* s)
{
    auto e = new HTMLElement();
    if (s->at(1) == L'/')
    {
        e->is_start_token = false;
        for (int i = 2; i < s->length; i++)
        {
            if (s->at(i) == L'>')
            {
                e->type = s->substring(3, i - 2);
                for (int j = 0; j < token_number; j++)
                {
                    if (strcompare(e->type, token[j]) == 0)
                    {
                        e->_type = j;
                        delete (e->type);
                        break;
                    }
                }
                return e;
            }
        }
    }
    else
    {
        e->is_start_token = true;
        for (int i = 1; i < s->length; i++)
        {
            if (s->at(i) == L' ' || s->at(i) == L'>' || s->at(i) == L'/')
            {
                e->type = s->substring(2, i - 1);
                for (int j = 0; j < token_number; j++)
                {
                    if (strcompare(e->type, token[j]) == 0)
                    {
                        e->_type = j;
                        delete (e->type);
                        break;
                    }
                }
                return e;
            }
        }
    }
}
