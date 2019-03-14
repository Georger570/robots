#include "stdio.h"
#include "stdlib.h"
#include "array.h"
#include "WaveAlgorithm.h"

int main()
{
	FILE *map_in;
	if ((map_in = fopen("map.txt", "r")) != NULL)
	{
		arr *array = InitArray(map_in);		
		fclose(map_in);
		PrintArray(array);
		//int iSize = array->n_rows;	//Размерность матрицы
		//int iMap[array->n_rows][array->n_columns];	//Карта; 0 - свободно, 1 - препятсвие
		printf("\n");		
		/*int **iMap = (int**) calloc(array-> n_rows, sizeof(int*));
		for ( int i = 0; i<array->n_columns; i++)
		{
			iMap[i] = (int*) calloc(array-> n_columns, sizeof(int));
		}
		for(int i = 0; i<(array->n_rows); i++)
		{
			for(int j = 0; j<(array->n_columns); j++)
			{ 
				iMap[i][j]=array->ptr[i*array->n_columns+j];
				printf("%d", iMap[i][j]);
			}	
			printf("\n");		
		}*/		
		int **iStepMap = (int**) calloc(array-> n_rows, sizeof(int*));
		for ( int i = 0; i<array->n_columns; i++)
		{
			iStepMap[i] = (int*) calloc(array-> n_columns, sizeof(int));
		}	//Карта шагов; содержит число шагов до ФИНИША в текущей координате;
						// -1 - не посещали, -2 - препятствие
		int *iResultX = (int*) calloc(array->n_rows * array->n_columns, sizeof(int));	//X-координата пути; [0] - точка НАЧАЛА
		int *iResultY = (int*) calloc(array->n_rows * array->n_columns, sizeof(int));;	//Y-координата пути; [0] - точка НАЧАЛАa
		int start_x=0, start_y=0, end_x=4, end_y=4;
		WaveStart( start_x, start_y, end_x, end_y,  array, iStepMap, iResultX, iResultY);
		printf("\n");
		for(int i = 0; i<(array->n_rows); i++)
		{
			for(int j = 0; j<(array->n_columns); j++)
			{ 
				printf("%d  ", iStepMap[i][j]);
					
			}
			printf("\n");	
		}
		//PathResult( start_x, start_y, end_x, end_y, iSize, &iMap, &iStepMap, &iResultX, &iResultY);					
	}	
	else printf("Error. File is missing!\n");
	
	return 0;
}
