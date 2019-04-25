#include "stdio.h"
#include <stdbool.h>
#include "array.h"
#include "coord.h"
/*
const int iSize = 10;	//Matrix size
int iMap[10][10];	//Map; 0 - is free, 1 - wall
int iStepMap[10][10];	//Step map; Countains number of steps to finish in the current coordinate
						// -1 - did not visit, -2 - wall
int iResultX[100];	//X - Path coordinate; [0] - Start point
int iResultY[100];	//Y - Path coordinate; [0] - Start point
*/
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//x0, y0 - Begin coordinateа; x1, y1 - Finish coordinate
//wave start to start at the destination

bool WaveStart(coord start, coord end, arr* iMap, int **iStepMap, int *iResultX, int *iResultY)
{
	//Initialization
	int iStep = 0;
	bool bResult = false,	//Path find
		bAdded = true;	//Amended; to control the cycle
	for (int i = 0; i < (iMap -> n_rows); i++)
		for (int j = 0; j < (iMap -> n_columns); j++)
		{
			if ((iMap -> ptr[i][j]) != 0)
				iStepMap[i][j] = -2;	
			else
				iStepMap[i][j] = -1;
		}
	for (int i = 0; i < (iMap -> n_rows * iMap -> n_columns); i++)
	{
		iResultX[i] = -1;
		iResultY[i] = -1;
	}
	iStep = 0;
	//--------
	iStepMap[end.x][end.y] = iStep;
	//--------
	//coordinate check for free / busy
	if ((iMap -> ptr[start.x][start.y]) == 1 || (iMap -> ptr[end.x][end.y]) == 1)
	{
		bResult = false;

		return bResult;
	}
	//WAVE Start.
	while (bAdded && iStepMap[start.x][start.y] == -1)
	{
		bAdded = false;	
		iStep++;	//More Steps

		for (int i = 0; i < iMap -> n_rows; i++)	// Check all map
			for (int j = 0; j < iMap -> n_columns; j++)
				//If the point with coordinates (i; j) was processed at the previous step, then we process the neighboring cells.
				if (iStepMap[i][j] == iStep - 1)
				{
					int _i, _j;
					_i = i;
					_j = j;

					for (int k = 0; k < iMap -> n_rows; k++)
					{
						//iterate over the neighboring points and process them
						switch (k)
						{
						case 0: _i = i + 1; _j = j; break;
						case 1: _i = i - 1; _j = j; break;
						case 2: _i = i; _j = j + 1; break;
						case 3: _i = i; _j = j - 1; break;
						}
						//we check the cells for belonging to the matrix and whether it was processed (-1)
						if (_i >= 0 && _j >= 0 && _i < iMap -> n_rows && _j < iMap -> n_rows)
							if (iStepMap[_i][_j] == -1)
							{
								iStepMap[_i][_j] = iStep;
								bAdded = true;
							}
					}
				}
	}
	//Wave END.

	if (iStepMap[start.x][start.y] == -1 || iStepMap[start.x][start.y] == -2)
		bResult = false;
	else if (iStepMap[start.x][start.y] >= 0)
	{
		bResult = true;
		//WavePath(x0, y0);
	}

	return bResult;
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void PathResult(coord start, coord end, int iSize, int **iStepMap, int *iResultX, int *iResultY)
{
	int iStep = iStepMap[start.x][start.y];
	int iI = 0;
	int x = start.x, y = start.y;	//Coordinates of the previous point
	bool bAdded = true;	
	iResultX[iI] = start.x;
	iResultY[iI] = start.y;

	if (start.x == end.x && start.y == end.y)
	{
		iResultX[iI] = end.x;
		iResultY[iI] = end.y;
		return;
	}
	//Start PATH SAVE. Wave start
	while (bAdded && iStep >= 0)
	{
		bAdded = false;	
		iI++;		//the number of the next point of the found route
		iStep--;
		for (int i = 0; i < iSize; i++)	// Check all map
			for (int j = 0; j < iSize; j++)
				//If the point with coordinates (i; j) was processed at the previous step, then we process the neighboring cells
				if (iStepMap[i][j] == iStep)
				{
					int _i, _j;
					_i = i;
					_j = j;
					
					for (int k = 0; k < 4; k++)
					{
						//Iterate over the neighboring points and process them
						switch (k)
						{
						case 0: _i = i; _j = j - 1; break;
						case 1: _i = i + 1; _j = j; break;
						case 2: _i = i; _j = j + 1; break;
						case 3: _i = i - 1; _j = j; break;
						}
						//check the points on the matrix
						if (_i >= 0 && _j >= 0 && _i < iSize && _j < iSize)
							if (_i == x && _j == y)
							{
								iResultX[iI] = _i;
								iResultY[iI] = _j;
								x = i;
								y = j;

								bAdded = true;
							}
					}
				}
	}
	//End of the PATH SAVE.
	iResultX[iI + 1] = end.x;
	iResultY[iI + 1] = end.y;

	return;
}
