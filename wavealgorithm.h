#include "array.h"
#include "coord.h"
#include "list.h"
/*
const int iSize = 10;	//����������� �������
int iMap[10][10];	//�����; 0 - ��������, 1 - ����������
int iStepMap[10][10];	//����� �����; �������� ����� ����� �� ������ � ������� ����������;
						// -1 - �� ��������, -2 - �����������
int iResultX[100];	//X-���������� ����; [0] - ����� ������
int iResultY[100];	//Y-���������� ����; [0] - ����� ������
*/
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//x0, y0 - ��������� ����������; x1, y1 - �������� ����������
//����� �������� ��������� � ����� ����������

bool WaveStart(coord start, coord end, arr* iMap, int** iStepMap, List* Result)
{
	//���������� � �������������
	int iStep = 0;
	//���; ���������� ����� 0
	//int iI;
	bool bResult = false,	//���� ������
		bAdded = true;	//������� ���������; ��� �������� �����
	for (int i = 0; i < (iMap->n_rows); i++)
		for (int j = 0; j < (iMap->n_columns); j++)
		{
			if ((iMap->ptr[i][j]) != 0)
				iStepMap[i][j] = -2;	//�����������
			else
				iStepMap[i][j] = -1;	//�� ��������
		}
	for (int i = 0; i < (iMap->n_rows * iMap->n_columns); i++)
	{
		coord coords(-1, -1);
		Result->addInEndOfList( coords );
	}
	iStep = 0;
	//--------
	iStepMap[end.x][end.y] = iStep;
	//--------
	//�������� ��������� �� ��������/������
	if ((iMap->ptr[start.x][start.y]) == 1 || (iMap->ptr[end.x][end.y]) == 1)
	{
		bResult = false;

		return bResult;
	}
	//������ �����. ������� �����
	while (bAdded && iStepMap[start.x][start.y] == -1)
	{
		bAdded = false;	//������ ��� �� ��������
		iStep++;	//����������� ����� �����

		for (int i = 0; i < iMap->n_rows; i++)	// ��������� �� ���� �����
			for (int j = 0; j < iMap->n_columns; j++)
				//���� ����� � ������������ (i;j) �������������� ��
				//���������� ����, �� ������������ �������� ������
				if (iStepMap[i][j] == iStep - 1)
				{
					int _i, _j;
					_i = i;
					_j = j;

					for (int k = 0; k < iMap->n_rows; k++)
					{
						//��������������� ���������� �������� �����
						//� ������������ ��
						switch (k)
						{
						case 0: _i = i + 1; _j = j; break;
						case 1: _i = i - 1; _j = j; break;
						case 2: _i = i; _j = j + 1; break;
						case 3: _i = i; _j = j - 1; break;
						}
						//��������� ������ �� �������������� �������
						//� �� ��, �������������� �� ��� (-1)
						if (_i >= 0 && _j >= 0 && _i < iMap->n_rows && _j < iMap->n_rows)
							if (iStepMap[_i][_j] == -1)
							{
								iStepMap[_i][_j] = iStep;
								bAdded = true;
							}
					}
				}
	}
	//����� �����.
	//��������� ����������� �����
	//���� ��������� ����� (x0,y0) �� ���������� (=-1, =-2), �� ���� �� ������
	// -1 - �� ��������, -2 - �����������
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
void PathResult(coord start, coord end, int iSize, int** iStepMap, List* Result)
{
	int iStep = iStepMap[start.x][start.y];
	int x = start.x, y = start.y;	//���������� ���������� ����� ��������
	bool bAdded = true;	//������� ���������; ��� �������� �����
	Result->head->coords = start;
	if (start.x == end.x && start.y == end.y)
	{
		Result->head->coords = end;
		return;
	}
	//������ ���������� ����. ������� �����
	List::node* Noda = Result->head;
	while (bAdded && iStep >= 0)
	{
		bAdded = false;	//������ ��� �� ��������
		Noda = Noda->next;		//��������� ����� ���������� ��������
		iStep--;	//����������� ����� �����
		for (int i = 0; i < iSize; i++)	// ��������� �� ���� �����
			for (int j = 0; j < iSize; j++)
				//���� ����� � ������������ (i;j) �������������� ��
				//���������� ����, �� ������������ �������� ������
				if (iStepMap[i][j] == iStep)
				{
					int _i, _j;
					_i = i;
					_j = j;

					for (int k = 0; k < 4; k++)
					{
						//��������������� ���������� �������� �����
						//� ������������ ��
						switch (k)
						{
						case 0: _i = i; _j = j - 1; break;
						case 1: _i = i + 1; _j = j; break;
						case 2: _i = i; _j = j + 1; break;
						case 3: _i = i - 1; _j = j; break;
						}
						//��������� ������ �� �������������� �������
						if (_i >= 0 && _j >= 0 && _i < iSize && _j < iSize)
							if (_i == x && _j == y)
							{
								Noda->coords.x = _i;
								Noda->coords.y = _j;
								x = i;
								y = j;

								bAdded = true;
							}
					}
				}
	}
	//����� ���������� ����.
	Noda->coords = end;

	return;
}
