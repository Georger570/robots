#include <stdlib.h>
#ifndef COORD_H
#define COORD_H
#define shit 
struct coord
{
	int x;
	int y;

    coord(int x, int y): x(x), y(y)
    {}

	/*~coord()
	{
		delete this shit;
	}*/
	
	//Operators overloading

	friend const coord operator+(const coord& v1, const coord& v2);

	friend const coord operator+=(coord& v1, const coord& v2);

	friend const bool operator==(const coord& v1, const coord& v2);

	friend const bool operator!=(const coord& v1, const coord& v2);
};

#endif
