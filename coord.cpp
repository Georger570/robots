#include "coord.h"

const coord operator+(const coord& v1, const coord& v2)
{
    return coord(v1.x+v2.x, v1.y+v2.y);
}

const coord operator+=(coord& v1,const coord& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}
	
const bool operator==(const coord& v1, const coord& v2)
{
	return ( (v1.x == v2.x) && (v1.y == v2.y) );
}

const bool operator!=(const coord& v1, const coord& v2)
{
	return !( v1 == v2 );
}

