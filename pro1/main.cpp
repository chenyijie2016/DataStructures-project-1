// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "NetWork.h"
#include "HTMLparser.h"
#include "cxxopts.hpp"
#include "StringHashTable.h"
#include "CSVparser.hpp"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
StringHashTable initDictionary();
LinkList<String> divideWords(String words, StringHashTable dic);
void test();
void testdictionary();
void testdecode();
void Init();
void test_output();
void outputResult();
void process();
LinkList<PageInfo> extractInfo(int pagenumbers);


extern const std::locale empty_locale = std::locale::empty();
typedef std::codecvt_utf8<wchar_t> converter_type; //std::codecvt_utf16
extern const converter_type* converter = new converter_type;
extern const std::locale utf8_locale = std::locale(empty_locale, converter);

// 全局属性
bool DOWNLOAD_CLOUD_DIC = false;//是否加载云词典
bool DEBUG_MODE = false;//输出调试信息

int main(int argc, char* argv[])
{
    DEBUG_MODE = true;
    setlocale(LC_ALL, "chs");
    //NetWork::downloadPages();

    Init();
    process();
    //test();
    //testdictionary();
    //testdecode();
    getchar();
    return 0;
}


void Init()
{
    if (DOWNLOAD_CLOUD_DIC)
    {
        //获取云词典
        string cmd = "curl.exe -O http://sync.chenyijie.me/dictionary/cloud_dictionary.dic";
        system(cmd.c_str());
    }
    FILE* fp;
    fp = fopen("output/result.csv", "w");
    char szBOM[4] = {(char)0xEF,(char)0xBB,(char)0xBF,0};
    fprintf(fp, "%s", szBOM);
    fclose(fp);
    // 输出bom头
    // reference : http://oneprog.blog.51cto.com/1043941/1315020
    wofstream result("output/result.csv", ios::app);
    result.imbue(utf8_locale);
    wstring header(L"\"序号\",\"网址\",\"发帖大类\",\"发帖小类\",\"发帖标题\",\"发帖内容\",\"发帖人\",\"发帖日期\",\"发帖类型\",\"分词结果\"");
    result << header << endl;
    result.close();
    //输出结果的表格栏
}


void test_output()
{
    //    wofstream content_fout("content.txt");
    //    content_fout.imbue(utf8_locale);
    //    wofstream title_fout("title.txt");
    //    title_fout.imbue(utf8_locale);

    for (int i = 3; i < 100; i++)
    {
        if (i != 7 && i != 32 && i != 74)
        {
            std::cout << "---------" << i << "-----------" << std::endl;
            std::ostringstream sstream;
            sstream << i << ".html";
            HTMLparser htmlparser(sstream.str());
            htmlparser.toknize();
            auto pageinfo = htmlparser.parse();
            //            content_fout << pageinfo.content.c_str() << endl;
            //            title_fout << pageinfo.title.c_str() << endl;
            pageinfo.show();
            htmlparser.destory();
            //cout << "/r" << i << endl;
        }
    }
    //    content_fout.close();
    //    title_fout.close();
}

void setoption(int argc, char* argv[])
{
    cxxopts::Options options("main.exe", "Course Project for DataStructure and Algorithm");
    options.add_options("1")
        ("S,skip", "Skip Download Cloud Dictionary")
        ("H,help", "Get Help of Options")
        ("D,debug", "Opening debug mode");
    options.parse(argc, argv);
    if (options.count("help"))
        std::cout << options.help({"","1"});
    if (options.count("skip"))
        DOWNLOAD_CLOUD_DIC = false;
    if (options.count("debug"))
        DEBUG_MODE = true;
}

/**
 * \brief 从三个词典文件加载词典，对于本地的两个词典，若不能打开则会 throw 错误
 * \return 存储词典的hashtable
 */
StringHashTable initDictionary()
{
    StringHashTable strhashtable;


    std::wifstream dic_fin("dictionary.dic");
    dic_fin.imbue(utf8_locale);


    int total = 0;
    if (dic_fin)
    {
        wstring temp;
        while (getline(dic_fin, temp))
        {
            total++;
            if (total % 1000 == 0)
            {
                cout << "\r Loading Dictionary... [" << total << "] words";
            }
            String tmp(temp);
            strhashtable.insert(tmp);
        }
    }
    else
    {
        cout << "error";
        throw Error("fail to load dictionary");
    }
    std::wifstream extra_dic_fin("extra_dictionary.dic");
    extra_dic_fin.imbue(utf8_locale);
    if (extra_dic_fin)
    {
        wstring temp;
        while (getline(extra_dic_fin, temp))
        {
            total++;
            if (total % 10 == 0)
            {
                cout << "\r Loading Extra Dictionary... [" << total << "] words";
            }
            String tmp(temp);
            strhashtable.insert(tmp);
        }
    }
    else
    {
        cout << "error";
        throw Error("fail to load extra dictionary");
    }

    if (DOWNLOAD_CLOUD_DIC)
    {
        std::wifstream cloud_dic_fin("cloud_dictionary.dic");
        cloud_dic_fin.imbue(utf8_locale);
        if (cloud_dic_fin)
        {
            wstring temp;
            while (getline(cloud_dic_fin, temp))
            {
                total++;
                if (total % 10 == 0)
                {
                    cout << "\r Loading Cloud Dictionary... [" << total << "] words";
                }
                String tmp(temp);
                strhashtable.insert(tmp);
            }
        }
        else
        {
            cout << "error\n";
            cout << "fail to load cloud dictionary";
        }
    }
    return strhashtable;
}

/**
 * \brief 使用给定的词典及最大正向匹配法进行分词
 * \param words 待分词的字符串
 * \param dic 字典
 * \return 
 */
LinkList<String> divideWords(String words, StringHashTable dic)
{
    LinkList<String> tempresult;
    words = removeChineseSymbol(words);
    String currentstring(words);
    while (!currentstring.empty())
    {
        int i;
        String substr;
        int break_flag = 0;
        for (i = currentstring.size(); i > 0; i--)
        {
            substr = currentstring.substr(0, i);
            if (dic[substr])
            {
                //                cout << " [";
                //                substr.output();
                //                cout << "]";
                tempresult.insert(substr);
                if (i != currentstring.size())
                {
                    currentstring = currentstring.substr(i, currentstring.size());
                    break;
                }
                else
                {
                    break_flag = 1;
                    // return tempresult;
                    break;
                }
            }
        }
        if (break_flag == 1)
        {
            break;
        }
        if (i == 0)
        {
            substr = currentstring.substr(0, 1);
            //            cout << " [";
            //            substr.output();
            //            cout << "]";
            tempresult.insert(substr);
            currentstring = currentstring.substr(1, currentstring.size());
        }
        if (currentstring.size() == 1)
        {
            break;
        }
    }
    LinkList<String> result;
    auto current = tempresult.head;
    String numbers;
    while (current)
    {
        //        cout << current->_data.size()<<"->";
        //        current->_data.output();
        //        cout << " ";
        if (current->_data.size() >= 2)
        {
            if (!numbers.empty())
            {
                result.push_back(numbers);
                numbers = String();
            }
            result.push_back(current->_data);
        }
        else
        {
            if (is_letter_or_number(current->_data[0]))
            {
                numbers = numbers.concat(current->_data);
            }
        }
        current = current->_next;
    }
    if (!numbers.empty())
    {
        result.push_back(numbers);
    }


    return result;
}

void test()
{
    auto dic = initDictionary();
    wifstream fin("content.txt");
    wifstream title_fin("title.txt");
    title_fin.imbue(utf8_locale);
    fin.imbue(utf8_locale);
    LinkList<String> linkliststring;
    if (fin)
    {
        wstring line;
        while (getline(fin, line))
        {
            if (!line.empty())
            {
                String tmp(line);
                linkliststring = divideWords(tmp, dic);
                cout << endl;
                auto current = linkliststring.head;
                while (current)
                {
                    //                    if (current->_data.size() == 1 && is_letter_or_number(current->_data[0]))
                    //                    {
                    //                        current->_data.output();
                    //                    }
                    //                    else
                    {
                        cout << "  ";
                        current->_data.output();
                    }
                    current = current->_next;
                }
            }
        }
    }
    if (title_fin)
    {
        wstring line;
        while (getline(title_fin, line))
        {
            if (!line.empty())
            {
                String tmp(line);
                linkliststring = divideWords(tmp, dic);
                cout << endl;
                auto current = linkliststring.head;
                while (current)
                {
                    //                    if (current->_data.size() == 1 && is_letter_or_number(current->_data[0]))
                    //                    {
                    //                        current->_data.output();
                    //                    }
                    //                    else
                    {
                        cout << "  ";
                        current->_data.output();
                    }
                    current = current->_next;
                }
            }
        }
    }
}


void process()
{
    try
    {
        system("@mkdir temp > error.log");
        csv::Parser parser("input/url.csv");
        int pagenumbers = parser.rowCount();
        vector<string> urls;
        for (int i = 0; i < pagenumbers; i++)
        {
            //            std::ostringstream stringStream;
            //            stringStream << "temp/" << i << ".html";
            string url = parser[i][1].substr(1, parser[i][1].size() - 2);
            urls.push_back(url);
            //           NetWork::getUrl(url, stringStream.str());
        }
        //下载网页并保存

        LinkList<PageInfo> infos = extractInfo(pagenumbers);
        //解析网页

        StringHashTable dic = initDictionary();

        wofstream result("output/result.csv", ios::app);
        result.imbue(utf8_locale);

        //写入文件保存
        auto current = infos.head;
        int num = 0;
        while (current)
        {
            if (DEBUG_MODE)
            {
                num++;
                cout << "当前页面" << num << endl;
                if (num > 2)
                {
                    break;
                }
            }
            //L"\"序号\",\"网址\",\"发帖大类\",\"发帖小类\",\"发帖标题\",\"发帖内容\",\"发帖人\",\"发帖日期\",\"发帖类型\",\"分词结果\"");
            result << num << ',' << urls[num].c_str() << ",\"" << current->_data.category.c_str() << "\","
                << "\"" << current->_data.subcategory.c_str() << L"\","
                << "\"" << current->_data.title.c_str() << L"\","
                << "\"" << current->_data.content.c_str() << L"\","
                << "\"" << current->_data.author.c_str() << L"\","
                << "\"" << current->_data.time.c_str() << L"\","
                << "\"" << current->_data.type.c_str() << L"\",";

            result << "\"";
            LinkList<String> content_wordsresult = divideWords(current->_data.content, dic);
            LinkList<String> title_wordsresult = divideWords(current->_data.title, dic);

            auto c = content_wordsresult.head;
            result << "[发帖内容分词]:";
            while (c)
            {
                result << c->_data.c_str() << " ";
                c = c->_next;
            }
            c = title_wordsresult.head;
            result << "[发帖标题分词]:";
            while (c)
            {
                result << c->_data.c_str() << " ";
                c = c->_next;
            }
            result << "\"";
            result << endl;
            current = current->_next;
        }
    }
    catch (Error& e)
    {
        e.detail();
    }
}

LinkList<PageInfo> extractInfo(int pagenumbers)
{
    LinkList<PageInfo> result;
    for (int i = 0; i < pagenumbers; i++)
    {
        ostringstream sstream;
        sstream << i << ".html";
        HTMLparser htmlparser(sstream.str());
        htmlparser.toknize();
        auto pageinfo = htmlparser.parse();
        result.push_back(pageinfo);
        pageinfo.show();
        htmlparser.destory();
    }
    return result;
}
