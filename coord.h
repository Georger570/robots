#ifndef COORD_H
#define COORD_H
struct coord
{
	int x;
	int y;

	coord(int x, int y): x(x), y(y)
    {}

    friend const coord operator+(const coord& v1, const coord& v2)
    {
        return coord(v1.x+v2.x, v1.y+v2.y);
    }

	friend const coord operator+=(coord& v1,const coord& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}
};


#endif
