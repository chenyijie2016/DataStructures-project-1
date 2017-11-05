#pragma once

template <typename ElemType>
class Node
{
public:
    ElemType _data;
    Node* _next;

    Node(ElemType data) : _data(data)
    {
        _next = nullptr;
    };
};


template <typename ElemType>
class LinkList
{
private:

    unsigned int _size;
public:
    Node<ElemType>* head;

    LinkList()
    {
        head = nullptr;
        _size = 0;
    }

    //ElemType& operator[](unsigned int index);
    void insert(ElemType data);

    unsigned int size();
    bool contains(ElemType data);
    void remove_all();
};

template <typename ElemType>
void LinkList<ElemType>::insert(ElemType data)
{
    Node<ElemType>* ins = new Node<ElemType>(data);
    _size++;
    if (head == nullptr)
    {
        head = ins;
        return;
    }
    auto current = head;
    while (current->_next)
    {
        current = current->_next;
    }
    current->_next = ins;
    return;
}

template <typename ElemType>
unsigned int LinkList<ElemType>::size()
{
    return _size;
}

template <typename ElemType>
void LinkList<ElemType>::remove_all()
{
    auto current = head;

    while (current)
    {
        auto next = current->_next;
        delete current;
        current = next;
    }
    _size = 0;
    head = nullptr;
}

template <typename ElemType>
bool LinkList<ElemType>::contains(ElemType data)
{
    auto current = head;

    while (current)
    {
        if (current->_data == data)
            return true;
        current = current->_next;
    }
    return false;
}
