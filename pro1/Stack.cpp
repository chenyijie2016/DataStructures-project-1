#include "stdafx.h"
#include "Stack.h"

void InitStack(Stack& S)
{
    S.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if (!S.base)
        throw Error("Init Stack Fail");
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
}

bool IsEmpty(Stack S)
{
    return S.base == S.top;
}

int StackLength(Stack S)
{
    return S.top - S.base;
}

void GetTop(Stack S, ElemType& e)
{
    if (S.top == S.base)
        throw Error("GetTop when stack is empty");
    e = *(S.top - 1);
}

void Push(Stack& S, ElemType e)
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (ElemType*)realloc(S.base, (S.stacksize + STACK_INCREMENT) * sizeof(ElemType));
        if (!S.base)
            throw Error("Realloc stack fail");
        S.top = S.base + S.stacksize;
        S.stacksize += STACK_INCREMENT;
    }
    *S.top++ = e;
}

void Pop(Stack& S, ElemType& e)
{
    if (S.top == S.base)
        throw Error("Pop when stack is empty");
    e = *--S.top;
}
