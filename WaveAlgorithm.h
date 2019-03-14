//========================================================================
//            ВОЛНОВОЙ АЛГОРИТМ нахождения кратчайшего пути
//                   от точки A(x0;y0) до B(x1;y1)
//
//А.Даниловский ©26.02.2013
//========================================================================
#include "stdio.h"
#include <stdbool.h>
#include "array.h"
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

bool WaveStart(int x0, int y0, int x1, int y1, arr* iMap, int **iStepMap, int *iResultX, int *iResultY)
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
		printf("1");
	for (int i = 0; i < (iMap -> n_rows * iMap -> n_columns); i++)
	{
		iResultX[i] = -1;
		iResultY[i] = -1;
	}
		printf("2");
	iStep = 0;
	//--------
	iStepMap[x1][y1] = iStep;
	//--------
	//проверка координат на свободно/занято
	if ((iMap -> ptr[x0][y0]) == 1 || (iMap -> ptr[x1][y1]) == 1)
	{
		bResult = false;

		return bResult;
	}
		printf("3");
	//Начало ВОЛНЫ. пускаем волну
	while (bAdded && iStepMap[x0][y0] == -1)
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
		printf("4");
	//Обработка результатов ВОЛНЫ
	//Если начальная точка (x0,y0) не обработана (=-1, =-2), то ПУТЬ не найден
	// -1 - не посещали, -2 - препятствие
	if (iStepMap[x0][y0] == -1 || iStepMap[x0][y0] == -2)
		bResult = false;
	else if (iStepMap[x0][y0] >= 0)
	{
		bResult = true;
		//WavePath(x0, y0);
	}

	return bResult;
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
void PathResult(int x0, int y0, int x1, int y1, const int iSize, int **iStepMap, int* iResultX, int* iResultY)
{
	int iStep = iStepMap[x0][y0];
	int iI = 0;
	int x = x0, y = y0;	//координаты предыдущей точки маршрута
	bool bAdded = true;	//Внесены изменения; для контроля цикла
	printf("0");
	iResultX[iI] = x0;
	iResultY[iI] = y0;

	if (x0 == x1 && y0 == y1)
	{
		iResultX[iI] = x1;
		iResultY[iI] = y1;
		return;
	}
	printf("1");
	//Начало СОХРАНЕНИЯ ПУТИ. пускаем волну
	while (bAdded && iStep >= 0)
	{
		bAdded = false;	//ничего еще не добавили
		iI++;		//номер следующей точки найденного маршрута
		iStep--;	//Увеличиваем число шагов
		printf("2");
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
								iResultX[iI] = _i;
								iResultY[iI] = _j;
								x = i;
								y = j;

								bAdded = true;
							}
					}
				}
	}
	//Конец СОХРАНЕНИЯ ПУТИ.
	iResultX[iI + 1] = x1;
	iResultY[iI + 1] = y1;

	return;
}
