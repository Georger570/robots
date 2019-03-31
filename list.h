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
    void addInBeginOfList(int x, int y);
    bool isEmptyList();
    void showList();
    node* findInList(int x, int y);
    bool isAlreadyInList(int x, int y);
    coord popList();
    void deleteNodeInList(node** nodeAdress);
};

#endif
