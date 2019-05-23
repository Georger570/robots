#ifndef MEMLIB_H
#define MEMLIB_H

int** MemoryAllocation(int Size)
{
	int** tmp = new int*[Size];
	for (int i = 0; i < Size; ++i)
		tmp[i] = new int[Size];
	return tmp;
}

#endif
