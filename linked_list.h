
#ifndef _linked_list_h_
#define _linked_list_h_

/* --------------------------------------------------------------------------- */
/* Standard Library Includes                                                   */
/* --------------------------------------------------------------------------- */

#include <iostream>
#include <string>
#include <climits>
#include <cstring>


struct node
{
    node* next;
    int key, value_len;
};

class linked_list
{
private:
	/* Always should point to the front of the data block allocated during Init() */
    char *head_pointer;  //why does this point to a character
    
    /* Always points to the front of the initialized list */
    node *front_pointer;
    
    /* Always points to the last initialized node in the list */
    node *free_pointer;
    
    /* Always points to the head of a list of nodes which are not used */ 
    node *free_data_pointer;
    
    int block_size;
    int mem_size; 
    int max_data_size; 
    bool initialized;

    /*  Double the size of the linked list and copy the contents to new space */
    bool Resize();
    

    /* Destroys the linked list and frees all used resources */
    void Destroy(); 

public:
    void Init(int M, int b);
	/* Constructor */
	linked_list();
    /*Destructor*/
    ~linked_list();
    /*Copy Constructor*/
    linked_list(const linked_list& l);
    linked_list & operator=(const linked_list& l);
		 
    
    /* Inserts thea key and copies the value to the payload */
    void Insert(int key,char * value_ptr, int value_len);
    
    bool RemoveLast();
    /* Delete the whole block containing a particular key                 */
    /* When multiple entries have the same key, delete only the first one */
    int Delete(int key);
    
    /* Looks up the first item with a given key, and returns a pointer to the value portion */
    /* The user is able to read or modify the value after obtaining the pointer             */
    node* Lookup (int key);
    
    /* Prints the entire list by following the next pointers.             */
    void PrintList ();
    
    /* Getter Functions */
    char *getHeadPointer() const;
    node *getFrontPointer() const;
    node *getFreePointer() const;
    node *getFreeDataPointer() const;
    
    int getBlockSize() const;
    int getMemSize() const;
    int getMaxDataSize() const;
    bool getInitialized() const;
    
    /* Setter Functions */
    void setHeadPointer(char* new_pointer);
    void setFrontPointer(node* new_pointer);
    void setFreePointer(node* new_pointer);
    void setFreeDataPointer(node* new_pointer);
    
    void setBlockSize(int new_block_size);
    void setMemSize(int new_mem_size);
    void setMaxDataSize(int new_max_data_size);
    void setInitialized(bool new_initialized);
};

#endif
