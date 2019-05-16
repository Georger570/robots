#include <iostream>
#include "array.h"
#include "coord.h"
/*
const int iSize = 10;	//Размерность матрицы
int iMap[10][10];	//Карта; 0 - свободно, 1 - препятсвие
int iStepMap[10][10];	//Карта шагов; содержит число шагов до ФИНИША в текущей координате;
						// -1 - не посещали, -2 - препятствие
int iResultX[100];	//X-координата пути; [0] - точка НАЧАЛА
int iResultY[100];	//Y-координата пути; [0] - точка НАЧАЛА
*/
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//x0, y0 - начальная координата; x1, y1 - конечная координата
//волну начинаем запускать с точки назначения

bool WaveStart(coord start, coord end, arr* iMap, int **iStepMap, coord* Result)
{
	//объявление и инициализация
	int iStep = 0;
	//Шаг; изначально равен 0
	//int iI;
	bool bResult = false,	//Путь найден
		bAdded = true;	//Внесены изменения; для контроля цикла
	for (int i = 0; i < (iMap -> n_rows); i++)
		for (int j = 0; j < (iMap -> n_columns); j++)
		{
			if ((iMap -> ptr[i][j]) != 0)
				iStepMap[i][j] = -2;	//препятствие
			else
				iStepMap[i][j] = -1;	//не посещено
		}
	for (int i = 0; i < (iMap -> n_rows * iMap -> n_columns); i++)
	{
		Result[i].x = -1;
		Result[i].y = -1;
	}
	iStep = 0;
	//--------
	iStepMap[end.x][end.y] = iStep;
	//--------
	//проверка координат на свободно/занято
	if ((iMap -> ptr[start.x][start.y]) == 1 || (iMap -> ptr[end.x][end.y]) == 1)
	{
		bResult = false;

		return bResult;
	}
	//Начало ВОЛНЫ. пускаем волну
	while (bAdded && iStepMap[start.x][start.y] == -1)
	{
		bAdded = false;	//ничего еще не добавили
		iStep++;	//Увеличиваем число шагов

		for (int i = 0; i < iMap -> n_rows; i++)	// Пробегаем по всей карте
			for (int j = 0; j < iMap -> n_columns; j++)
				//Если точка с координатами (i;j) обрабатывалась на
				//предыдущем шаге, то обрабатываем соседние клетки
				if (iStepMap[i][j] == iStep - 1)
				{
					int _i, _j;
					_i = i;
					_j = j;

					for (int k = 0; k < iMap -> n_rows; k++)
					{
						//последовательно перебираем соседние точки
						//и обрабатываем их
						switch (k)
						{
						case 0: _i = i + 1; _j = j; break;
						case 1: _i = i - 1; _j = j; break;
						case 2: _i = i; _j = j + 1; break;
						case 3: _i = i; _j = j - 1; break;
						}
						//проверяем клетки на принадлежность матрице
						//и на то, обрабатывалась ли она (-1)
						if (_i >= 0 && _j >= 0 && _i < iMap -> n_rows && _j < iMap -> n_rows)
							if (iStepMap[_i][_j] == -1)
							{
								iStepMap[_i][_j] = iStep;
								bAdded = true;
							}
					}
				}
	}
	//Конец ВОЛНЫ.
	//Обработка результатов ВОЛНЫ
	//Если начальная точка (x0,y0) не обработана (=-1, =-2), то ПУТЬ не найден
	// -1 - не посещали, -2 - препятствие
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
void PathResult(coord start, coord end, int iSize, int **iStepMap, coord* Result)
{
	int iStep = iStepMap[start.x][start.y];
	int iI = 0;
	int x = start.x, y = start.y;	//координаты предыдущей точки маршрута
	bool bAdded = true;	//Внесены изменения; для контроля цикла
	Result[iI] = start;
	if (start.x == end.x && start.y == end.y)
	{
		Result[iI] = end;
		return;
	}
	//Начало СОХРАНЕНИЯ ПУТИ. пускаем волну
	while (bAdded && iStep >= 0)
	{
		bAdded = false;	//ничего еще не добавили
		iI++;		//номер следующей точки найденного маршрута
		iStep--;	//Увеличиваем число шагов
		for (int i = 0; i < iSize; i++)	// Пробегаем по всей карте
			for (int j = 0; j < iSize; j++)
				//Если точка с координатами (i;j) обрабатывалась на
				//предыдущем шаге, то обрабатываем соседние клетки
				if (iStepMap[i][j] == iStep)
				{
					int _i, _j;
					_i = i;
					_j = j;
					
					for (int k = 0; k < 4; k++)
					{
						//последовательно перебираем соседние точки
						//и обрабатываем их
						switch (k)
						{
						case 0: _i = i; _j = j - 1; break;
						case 1: _i = i + 1; _j = j; break;
						case 2: _i = i; _j = j + 1; break;
						case 3: _i = i - 1; _j = j; break;
						}
						//проверяем клетки на принадлежность матрице
						if (_i >= 0 && _j >= 0 && _i < iSize && _j < iSize)
							if (_i == x && _j == y)
							{
								Result[iI].x = _i;
								Result[iI].y = _j;
								x = i;
								y = j;

								bAdded = true;
							}
					}
				}
	}
	//Конец СОХРАНЕНИЯ ПУТИ.
	Result[iI + 1] = end;

	return;
}
