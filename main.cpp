#include <iostream>
#include "List.h"
#include "coord.h"

using namespace std;

int main()
{
	List Exp;
	List Unexp;
	for (int i = 0; i <5; ++i)
	{
		Exp.addInEndOfList(i,i);
	}
	cout<<isEmptyList();
	showList();
}
