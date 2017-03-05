#include "cstack.h"
#include <iostream>

int main()
{
    cstack<int> * s = new cstack<int>();
    for (int i = 0; i < 10; i++) {
        s->push(i*10);
    }
    for (int i = 0; i < 10; i++){
        int t = s->pop();
        std::cout << t << std::endl;
    }
    

}