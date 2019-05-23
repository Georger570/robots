#include "list.h"

List::~List()
{
	tail = NULL;
	while (head != NULL)
	{
		node* tmp = head->next;
		delete head;
		head = tmp;
	}
}

void List::deleteNodeInList(node** nodeAdress)
{
	node* tmp = (*nodeAdress)->next;
	if ((*nodeAdress)->next == tail)
	{
		tail = (*nodeAdress);
		(*nodeAdress)->next = NULL;
	}
	else
		(*nodeAdress)->next = ((*nodeAdress)->next)->next;
	delete(tmp);
}

void List::addInBeginOfList(coord position)
{
	node* tmp = (node*)malloc(sizeof(node));
	tmp->coords = position;
	tmp->next = head;
	head = tmp;
	if (tail == NULL)
		tail = tmp;
}

void List::addInEndOfList(coord position)
{
	node* tmp = (node*)malloc(sizeof(node));
	tmp->coords = position;
	tmp->next = NULL;
	if (tail == NULL)
	{
		tail = tmp;	
		head = tmp;	
	}	
	else
	{
		tail->next = tmp;
		tail = tmp;
	}	
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
	/*node* tmp = head;
	while (tmp != NULL)
	{
		std::cout << tmp->x << "; " << tmp->y << "\t";
		tmp = tmp->next;
	}
	std::cout << std::endl;*/
}

coord List::popList()
{
	node* tmp = head;
	head = head->next;
	coord return_me(tmp->coords);
	delete(tmp);
	return return_me;
}

coord List::popTail()
{

	node* tmp = head;
	while (tmp->next != tail)
		tmp = tmp->next;
	node * tmp_t = tail;
	coord return_me(tmp_t->coords);
	tail = tmp;
	delete (tmp_t);
	return return_me;
}

// Find in List x, y. Return adress when it's find. Return NULL when it's not found.
List::node* List::findInList(coord position, char flag)
{
	if (!isEmptyList())
	{
		node* tmp = head;
		for (;;)
		{
			if (tmp == NULL)
				return NULL;
			else if ((tmp->next->coords == position))
			{
				if (flag == 't')
					return tmp->next;
				else if (flag == 'p')
					return tmp;
			}
			else
				tmp = tmp->next;
		}
	}
	else
	{
		return NULL;
	}
}

// False - x,y is not in List. True - x,y is in List.
bool List::isAlreadyInList(coord position)
{
	if (findInList(position, 't') == NULL)
		return false;
	else
		return true;
}
