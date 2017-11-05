#pragma once



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
        msg = new char[200];
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
    abort();
}
