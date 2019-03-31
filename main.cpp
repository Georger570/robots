#include <iostream>
#include "list.h"
#include "coord.h"

using namespace std;

int main()
{
    List Exp;
    List Unexp;
    for (int i = 0; i <5; ++i)
    {
        Exp.addInBeginOfList(i,i);
    }
    cout<<Exp.isEmptyList()<<" ";
    Exp.showList();
}
