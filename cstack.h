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
        int size;
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
        


};
    //constructor
    template <typename T>
    cstack<T>::cstack()
    {
        size = 0;
        l = new linked_list();
        l->Init(sizeof(T),sizeof(T)+sizeof(node));
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
        T * ptr = tmp;
        l->Insert(0, (char*)ptr, sizeof(elem));
        size++;
        return true;
    }

    //remove top element from stack
    template <typename T>
    T cstack<T>::pop()
    {
        if (l->RemoveLast()){
            size--;
            return true;
        } else {
            return false;
        }
    }

    //returns value of top element
    template <typename T>
    T cstack<T>::top()
    {
        node * n = l->getFreePointer();
        n += sizeof(node);
        T * tmp = (T*)n;
        return *tmp;
    }
