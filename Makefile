linked_list.o : linked_list.cpp
    g++ -std=c++11 -g linked_list.cpp
list: 
    g++ -std=c++11 -g linked_list.o -o list
cstack.o : cstack.cpp
    g++ -std=c++11 -g cstack.cpp
stack:
    g++ -std=c++11 -g cstack.o -o cstack
clean:
	rm -rf *.o *.gch list