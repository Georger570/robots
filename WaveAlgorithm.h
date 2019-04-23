#include "stdio.h"
#include <stdbool.h>
#include "array.h"
#include "coord.h"
/*
const int iSize = 10;	//Matrix size;
int iMap[10][10];	//Map; 0 - is free, 1 - wall;
int iStepMap[10][10];	//Step map; countains nimber of steps to finish in the current coordinate;
						// -1 - did't visit, -2 - wall
int iResultX[100];	//X- way coordinate; [0] - Start point
int iResultY[100];	//Y- way coordinate; [0] - Start point
*/
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//x0, y0 - Begin coordinate; x1, y1 - Finish coordinate
//Start wave from Finish

bool WaveStart(coord start, coord end, arr* iMap, int **iStepMap, int *iResultX, int *iResultY)
{
	//Initialization
	int iStep = 0;
	//Step;
	//int iI;
	bool bResult = false,	//path found
		bAdded = true;	//Made changes. To control the cycle;
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
	//Free check
	if ((iMap -> ptr[start.x][start.y]) == 1 || (iMap -> ptr[end.x][end.y]) == 1)
	{
		bResult = false;

		return bResult;
	}
	//Wave BEGIN.
	while (bAdded && iStepMap[start.x][start.y] == -1)
	{
		bAdded = false;	
		iStep++;

		for (int i = 0; i < iMap -> n_rows; i++)	// Check the whole map;
			for (int j = 0; j < iMap -> n_columns; j++)
				//If point with coordinates (i;j) has been verifief
				//in the previous step we do not check the adjacent cells;
				if (iStepMap[i][j] == iStep - 1)
				{
					int _i, _j;
					_i = i;
					_j = j;

					for (int k = 0; k < iMap -> n_rows; k++)
					{
						//Check all points around
						switch (k)
						{
						case 0: _i = i + 1; _j = j; break;
						case 1: _i = i - 1; _j = j; break;
						case 2: _i = i; _j = j + 1; break;
						case 3: _i = i; _j = j - 1; break;
						}
						//we check the cells for belonging to the matrix and whether it was processed
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
	int x = start.x, y = start.y;	//coordinates of the previous waypoint
	bool bAdded = true;
	iResultX[iI] = start.x;
	iResultY[iI] = start.y;

	if (start.x == end.x && start.y == end.y)
	{
		iResultX[iI] = end.x;
		iResultY[iI] = end.y;
		return;
	}
	//Begin SAVE PATH. Wave Start
	while (bAdded && iStep >= 0)
	{
		bAdded = false;
		iI++;		//the number of the next point of the found route
		iStep--;	//MORE steps
		for (int i = 0; i < iSize; i++)
			for (int j = 0; j < iSize; j++)
				//If the point with coordinates (i; j) was processed at the previous step, then we process the neighboring cells
				if (iStepMap[i][j] == iStep)
				{
					int _i, _j;
					_i = i;
					_j = j;
					
					for (int k = 0; k < 4; k++)
					{	
						switch (k)
						{
						case 0: _i = i; _j = j - 1; break;
						case 1: _i = i + 1; _j = j; break;
						case 2: _i = i; _j = j + 1; break;
						case 3: _i = i - 1; _j = j; break;
						}
						//Check the cells for belonging to the matrix
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
