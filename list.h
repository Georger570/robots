#ifndef List_H
#define List_H
#include "coord.h"
#include <stdlib.h>

class List
{
public:
    struct node
    {
        int x;
        int y;
        node* next;
    };

    node* head;
    node* tail;

    List() : head(NULL), tail(NULL) {};
    ~List();
    void addInBeginOfList(coord position); //
    bool isEmptyList();
    void showList();
    node* findInList(coord position, char flag);
    bool isAlreadyInList(coord position);
    coord popList();
    void deleteNodeInList(node** nodeAdress);
};

#endif
