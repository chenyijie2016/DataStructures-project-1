#pragma once

enum ERROR
{
    ABSOULTE_NO_ERROR,
    STACK_MEMORY_OVERFLOW,
    STACK_EMPTY,
    STRING_OVERFLOW,
    SUBSTRING_ERROR,
    SUBSTRING_OVER_LENGTH,
};

class Error
{
public:
    int E_C;
    char* msg;

    Error(int errorcode) : E_C(errorcode)
    {
        msg = new char[100];
    }

    Error(const char* errmsg)
    {
        msg = new char[100];
        E_C = 0;
        strcpy(msg, errmsg);
    }

    Error() = default;

    void detail();
};

inline void Error::detail()
{
    std::cout << std::endl << "Error Code: [" << E_C << "]" << std::endl;
    std::cout << "Error message: [" << msg << "]" << std::endl;;

    system("pause");
    exit(E_C);
}
