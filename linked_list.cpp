#include "linked_list.h"


/* Constructor */
linked_list::linked_list()
{
	
	head_pointer = NULL;
	front_pointer = NULL;
	free_pointer = NULL;
	free_data_pointer = NULL;
	block_size = 0;
	mem_size = 0;
	max_data_size = 0;
	initialized = false;
	
}

/*Destructor*/
linked_list::~linked_list()
{
	this->Destroy();
}

//copy constructor
linked_list::linked_list(const linked_list & l)
{
		
		this->Init(l.getMemSize(),l.getBlockSize());
		char * iter = this->head_pointer;
		char * iter_cp = l.getHeadPointer();
		while (iter - this->head_pointer < this->mem_size){
			*iter = *iter_cp;
			iter++;
			iter_cp++;
		}
		
		front_pointer = (node*)(((char*)l.getFrontPointer() - l.getHeadPointer()) + this->head_pointer);
		free_pointer = (node*)(((char*)l.getFreePointer() - l.getHeadPointer()) + this->head_pointer);
		free_data_pointer = (node*)(((char*)l.getFreeDataPointer() - l.getHeadPointer()) + this->head_pointer);	
}

//copy assignment operator
linked_list & linked_list::operator=(const linked_list & l)
{

		if (this == &l) return *this;

		this->Destroy();

		this->Init(l.getMemSize(),l.getBlockSize());
		char * iter = this->head_pointer;
		char * iter_cp = l.getHeadPointer();
		while (iter - this->head_pointer < this->mem_size){
			*iter = *iter_cp;
			iter++;
			iter_cp++;
		}
		
		front_pointer = (node*)(((char*)l.getFrontPointer() - l.getHeadPointer()) + this->head_pointer);
		free_pointer = (node*)(((char*)l.getFreePointer() - l.getHeadPointer()) + this->head_pointer);
		free_data_pointer = (node*)(((char*)l.getFreeDataPointer() - l.getHeadPointer()) + this->head_pointer);	

		return *this;
}

void linked_list::Init(int M, int b)
{
	
	if(!initialized){ 
		if(M % b != 0) {
				M = M - (M % b);
		}
		block_size = b;
		mem_size = M;
		head_pointer = (char*) malloc( M );
		if ( b < sizeof( node ) ) {
			std::cout << "Block size cannot accommodate node size. Cancelling" << std::endl;
			this->Destroy();
			return;
		}
		max_data_size = b - sizeof(*((node*)head_pointer));
		//std::cout << "node size: " << sizeof(*((char*)(head_pointer))) << std::endl;
		free_data_pointer = (node*) head_pointer;
		initialized = true;
	}
	else std::cout << "Node already Initialized" << std::endl;
}

void linked_list::Destroy()
{
	if (initialized) 
	{
	node * temp_ptr = front_pointer;
	node * temp_ptr_next = front_pointer;
	while(temp_ptr->next){ //insure all nodes are set to default state
		temp_ptr_next = temp_ptr->next;
		temp_ptr->next = NULL;
		temp_ptr->key = -1;
		temp_ptr->value_len = 0;
		temp_ptr = temp_ptr_next;
	}
	free(head_pointer);
	head_pointer = NULL;
	front_pointer = NULL;
	free_pointer = NULL;
	free_data_pointer = NULL;
	block_size = 0;
	mem_size = 0;
	max_data_size = 0;
	initialized = false;
	}
	else std::cout << "Not initialized" << std::endl;
} 

void linked_list::Insert (int k, char * data_ptr, int data_len)
{
	bool full = true;
	
	
	if(!initialized){ std::cout << "The linked list has not been initialized, call Init()" << std::endl; return;}	
	else if (data_len > max_data_size) //exceeds max data size
	{
		std::cout << "The size of the requested insert exceeds the maximum value. Operation cannot be performed." << std::endl;
		return;
	} else {
		while ( ( (char*) (free_data_pointer) - (head_pointer) ) >= mem_size) //full list
		{
			if (!this->Resize()) {
				std::cout << "Failed to resize" << std::endl;
				return;
			}
			//std::cout << "Last b4 resize: " << *(int*)(free_pointer + 1) << std::endl;
		}
	 
		
		node * newNode = ((node*) free_data_pointer);
		newNode->next = NULL;
		newNode->value_len = data_len;
		newNode->key = k;
		
		if (front_pointer == NULL) //if list is empty set both free pointer and front pointer to newNode
		{
			front_pointer = newNode;
			free_pointer = newNode;
		}
		else // not first in list then make newnode free_pointer and set free_pointer next to newNode
		{ 
		free_pointer->next = newNode;  
		free_pointer = newNode;
		}
		
		char * temp_val = (char*) ( (char*) (newNode) + sizeof(*newNode) ); //char[] ptr to beginning of data block 
		
		memcpy( temp_val, data_ptr, data_len ); //copy value from data_ptr to data block

		free_data_pointer = (node*) ( (char*) (free_data_pointer) + block_size); 
		
		while( ( (node*) (free_data_pointer) )->next) // next free_data_pointer will be the next block whose next ptr is NULL
		{

			free_data_pointer = (node*) ( (char*) (free_data_pointer) + block_size);
 
		}
 
	}
	
}

int linked_list::Delete(int delete_key)
{
	if (initialized) {
		bool found = false;
		node * temp_ptr = front_pointer;
		node * prev_ptr = front_pointer; // so the list does not need to be traversed twice
		while(temp_ptr)
		{

			if( temp_ptr->key == delete_key){ //if found break, set found to true
			 found = true;
			 break;
			}
			
			if(temp_ptr != front_pointer) prev_ptr = prev_ptr->next; //set prev_ptr when temp_ptr not first element in list
			
			temp_ptr = temp_ptr->next; //set temp_ptr to next elem in list
			
		}
		if (found)
		{
			temp_ptr->key = -1;
			temp_ptr->value_len = 0;
			
			
			if (temp_ptr == front_pointer) //if first in list
			{ 
				if(temp_ptr->next == NULL) //if first and only in list
				{
					front_pointer = NULL;
					free_data_pointer = (node*) head_pointer;
					free_pointer = NULL;
					
				}
				else //if first but not only
				{
					front_pointer = temp_ptr->next;
					temp_ptr->next = NULL;
					if (((char*)free_data_pointer - head_pointer) > ((char*)temp_ptr - head_pointer)) //if free_data_pointer is before element being deleted in memory block
						free_data_pointer = temp_ptr;
							
				}	
			}
			// if last in list but not only in list			
			else if (temp_ptr == free_pointer)
			{
				prev_ptr->next = NULL;
				free_pointer = prev_ptr;
			if (((char*)free_data_pointer - head_pointer) > ((char*)temp_ptr - head_pointer)) //if free_data_pointer is before element being deleted in memory block
				free_data_pointer = temp_ptr;
			}
			//in between at least two other nodes			
			else
			{ 

			prev_ptr->next = temp_ptr->next;
			temp_ptr->next = NULL;
			if(((char*)free_data_pointer - head_pointer) > ((char*)temp_ptr - head_pointer)) //if free_data_pointer is before element being deleted in memory block
				free_data_pointer = temp_ptr;
			}
			return delete_key;
		}else return -1; // key not in list
	}
	else //list not initialized
	{
		return -1;
	}
}

/* 
 * function will not check if resize is necessary
 * it will just resize when called. 
 */
bool linked_list::Resize()
{
	if (!initialized) {
		std::cout << "linked_list not initialized" << std::endl;
		return false;
	} else {
		char * temp_head = (char*) malloc(2*mem_size);
		memcpy(temp_head, head_pointer, mem_size);
		
		long long int offset = temp_head - head_pointer;
		node * curr = ( node* ) temp_head;
		for ( int i = 0; i < mem_size; i+=block_size){
			
			if (curr->next) {
				curr->next = (node*)((char*)curr->next + offset);
			}
			curr = (node*)((char*)curr + block_size);
		}
		
		mem_size *= 2;

		
		
		front_pointer = (node*)(((char*)front_pointer - head_pointer) + temp_head);
		free_pointer = (node*)(((char*)free_pointer - head_pointer) + temp_head);
		free_data_pointer = (node*)(((char*)free_data_pointer - head_pointer) + temp_head);
		free(head_pointer);	
		//std::cout << "Last b4 resize: " << *(int*)(free_pointer + 1) << std::endl;	
		head_pointer = temp_head;
		
		return true;
	}
}

bool linked_list::RemoveLast()
{
	if (!initialized) {
		return false;
	}
	else if (!free_pointer) {
		return false;
	}
	else {
		if (this->Delete(free_pointer->key) != -1) { 
			return true;
		} else {
			return false;
		}
	}
}

/* Iterate through the list, if a given key exists, return the pointer to it's node */
/* otherwise, return NULL                                                           */
struct node* linked_list::Lookup(int lookup_key)
{
	std::cout << "searching for " << lookup_key << std::endl;
	node * temp_ptr = front_pointer;
	
	while(temp_ptr){ //traverse list until find key or temp_ptr is NULL
		
		if(temp_ptr->key == lookup_key) return temp_ptr; 
		temp_ptr = temp_ptr->next;
	}
	
	return NULL;
}

/* Prints the list by printing the key and the data of each node */
void linked_list::PrintList()
{
	if (initialized) {
		node * temp_ptr = front_pointer;
		while (temp_ptr) {
			std::cout << "Node:" << std::endl;
			std::cout << " - Key: " << temp_ptr->key << std::endl;
			std::cout << " - Data: ";
			for(int i = 0; i < temp_ptr->value_len; i++)
			{
				std::cout << ((char*)((char*)temp_ptr + sizeof(*temp_ptr)))[i];
			}
			std:: cout << std::endl;
			temp_ptr = temp_ptr->next;
		}
	}
	else std::cout << "List not initialized" << std::endl;

}

/* Getter Functions */
char* linked_list::getHeadPointer() const
{
	return this->head_pointer;
}

node* linked_list::getFrontPointer() const
{
	return this->front_pointer;
}

node* linked_list::getFreePointer() const
{
	return this->free_pointer;
}

node* linked_list::getFreeDataPointer() const
{
	return this->free_data_pointer;
}

int linked_list::getBlockSize() const
{
	return this->block_size;
}

int linked_list::getMemSize() const
{
	return this->mem_size;
}

int linked_list::getMaxDataSize() const
{
	return this->max_data_size;
}

bool linked_list::getInitialized()  const
{
	return this->initialized;
}

/* Setter Functions */
void linked_list::setHeadPointer(char *new_pointer)
{
	this->head_pointer = new_pointer;
}

void linked_list::setFrontPointer(node* new_pointer)
{
	this->front_pointer = new_pointer;
}

void linked_list::setFreePointer(node* new_pointer)
{
	this->free_pointer = new_pointer;
}

void linked_list::setFreeDataPointer(node* new_pointer)
{
	this->free_data_pointer = new_pointer;
}

void linked_list::setBlockSize(int new_block_size)
{
	this->block_size = new_block_size;
}

void linked_list::setMemSize(int new_mem_size)
{
	this->mem_size = new_mem_size;
}

void linked_list::setMaxDataSize(int new_max_data_size)
{
	this->max_data_size = new_max_data_size;
}

void linked_list::setInitialized(bool new_initialized) 
{
	this->initialized = new_initialized;
}
