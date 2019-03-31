#include "List.h"
#include <iostream>

List::~List()
{
	tail = NULL;
	while (head != NULL)
	{
		node* tmp = head->next;
		delete head;
		head = tmp;
	}
	delete List;
}

void deleteNodeInList(node** nodeAdress)
{
	node * tmp = (*nodeAdress);
	(*nodeAdress) = (*nodeAdress)->next;
	delete(tmp);
}

void List::addInBeginOfList(int x, int y)
{
	node* tmp = (node*) new node;
	tmp -> x = x;
	tmp -> y = y;
	tmp -> next = head;
	head = tmp;
}

bool List::isEmptyList()
{
	if (head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void List::showList()
{
	node* tmp = head;
	while (tmp != NULL)
	{
		std::cout << tmp->x << "\t";
		tmp = tmp->next;
	}
}

coord popList()
{
	node* tmp = head;
	head = head->next;
	coord return_me;
	return_me.x=tmp->x;
	return_me.y=tmp->y;
	delete(tmp);
	return return_me;
}

// Find in List x, y. Return adress when it's find. Return NULL when it's not found.
node* List::findInList(int x, int y)
{
	if (!isEmptyList())
	{
		node* tmp = head;
		for (;;)
		{
			if (tmp == NULL)
				return NULL;
			else if ((tmp->x == x) && (tmp->y == y))
				return tmp;
			else
				tmp = tmp->next;
		}
	}
	else
	{
		return NULL;
	}
}

// False - x,y is not in list. True - x,y is in list.
bool List::isAlreadyInList(int x, int y)
{
	if (findInList == NULL)
		return false;
	else 
		return true;
}