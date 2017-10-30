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

    Error(int errorcode) : E_C(errorcode)
    {
    }

    Error() = default;

    void detail()
    {
        std::cout << "Error Code: " << E_C << std::endl;
        std::cout
            << "[0] NO_ERROR\n[1]STACK_MEMORY_OVERFLOW\n[2]STACK_EMPTY\n[3]STRING_OVERFLOW\n[4]SUBSTRING_ERROR\n[5]SUBSTRING_OVER_LENGTH";
        exit(E_C);
    }
};
