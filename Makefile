linked_list.o : linked_list.cpp
    g++ -std=c++11 -g linked_list.cpp
list: 
    g++ -std=c++11 -g linked_list.o -o list

clean:
	rm -rf *.o *.gch list