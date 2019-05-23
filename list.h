#ifndef LIST_H
#define LIST_H
#include "coord.h"
#include <stdlib.h>

class List
{
public:
	struct node
	{
		coord coords;
		node* next;
	};

	node* head;
	node* tail;

	List() : head(NULL), tail(NULL) {};
	~List();
	void addInBeginOfList(coord position); //
	void addInEndOfList(coord position);
	bool isEmptyList();
	void showList();
	node* findInList(coord position, char flag);
	bool isAlreadyInList(coord position);
	coord popList();
	coord popTail();
	void deleteNodeInList(node** nodeAdress);
};

#endif