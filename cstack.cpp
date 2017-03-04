#include "cstack.h"

    //constructor
    cstack::cstack();
    //destructor
    cstack::~cstack();
    //copy contructor
    cstack::cstack(const cstack & cs);
    //copy assignment operator
    cstack &  cstack::operator=(const cstack & cs);
    //push element onto stack
    bool cstack::push(const T & elem);
    //remove top element from stack
    T cstack::pop();
    //returns value of top element
    T cstack::top();