#include <iostream>
#include "list.h"
#include "coord.h"

using namespace std;

int main()
{
    List Exp;
    List Unexp;
    coord a = {2, 2};
    for (int i = 0; i <5; ++i)
    {
        a = {i, i};
        Exp.addInBeginOfList(a);
    }
    cout<<Exp.isEmptyList()<<" " << endl;
    Exp.showList();
    Exp.popList();
    Exp.showList();
    a = {2, 2};
    List::node* tmp = Exp.findInList(a, 'p');
    Exp.deleteNodeInList(&tmp);
    Exp.showList();
}
