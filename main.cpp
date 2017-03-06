#include "cstack.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
int main()
{
	
    cstack<std::vector<int>> * s = new cstack<std::vector<int>>();
	std::cout << sizeof("") << std::endl;
	std::vector<int> tmp;
	tmp.push_back(100);
	for (int i = 0; i < 100; i++) {
        s->push(tmp);
	}
	std::cout << s->size() << std::endl;
    for (int i = 0; i < 100; i++){
        std::vector<int> t = s->pop();
        std::cout << t.at(0) << std::endl;
    }
    

}