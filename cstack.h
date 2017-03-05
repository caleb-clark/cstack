#pragma once

#include <iostream>
#include <string>
#include <climits>
#include <cstring>
#include "linked_list.h"


template <class T>
class cstack
{

private:

        linked_list * l;
        int size_;
public:
    //constructor
    cstack();
    //destructor
    ~cstack();
    //copy contructor
    cstack(const cstack<T> & cs);
    //copy assignment operator
    cstack &  operator=(const cstack<T> & cs);
    //push element onto stack
    bool push(const T & elem);
    //remove top element from stack
    T pop();
    //returns value of top element
    T top();
    //returns size of stack
    int size();


};
    //constructor
    template <typename T>
    cstack<T>::cstack()
    {
        size_ = 0;
        l = new linked_list();
        l->Init(8*(sizeof(T)+sizeof(node)),sizeof(T)+sizeof(node));
    }

    //destructor
    template <typename T>
    cstack<T>::~cstack()
    {
        delete l;
        l = NULL;
    }

    //copy contructor
    template <typename T>
    cstack<T>::cstack(const cstack<T> & cs)
    {
        l = cs;
    }

    //copy assignment operator
    template <typename T>
    cstack<T> &  cstack<T>::operator=(const cstack<T> & cs)
    {
        l = cs;
    }

    //push element onto stack
    template <typename T>
    bool cstack<T>::push(const T & elem)
    {
        T tmp = elem;
        T * ptr = &tmp;
        l->Insert(size_, (char*)ptr, sizeof(elem));
        size_++;
        return true;
    }

    //remove top element from stack
    template <typename T>
    T cstack<T>::pop()
    {
        if (size_ < 1) {
            std::cout << "No elements to pop" << std::endl;
            return T();
        }
        node * n = l->getFreePointer();
        n++;
        T * tmp = (T*)n;
        if (l->RemoveLast()){
            size_--;
            return *tmp;
        } else {
            return T();
        }
    }

    //returns value of top element
    template <typename T>
    T cstack<T>::top()
    {
        if (size_ < 1) {
            std::cout << "No elements" << std::endl;
            return T();
        }
        node * n = l->getFreePointer();
       // std::cout << sizeof(node) << std::endl;
        n += sizeof(node);
        T * tmp = (T*)n;
        return *tmp;
    }

    template <typename T>
    int cstack<T>::size()
    {
        return size;
    }
