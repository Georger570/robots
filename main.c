#include "stdio.h"
#include "stdlib.h"
#include "array.h"
#include "WaveAlgorithm.h"

int main()
{
	FILE *map_in;
	FILE *map_out;
	if ((map_in = fopen("map.txt", "r")) != NULL)
	{
		arr *array = InitArray(map_in);		
		fclose(map_in);
		PrintArray(array);
		//int iSize = array->n_rows;	//Размерность матрицы
		//int iMap[array->n_rows][array->n_columns];	//Карта; 0 - свободно, 1 - препятсвие
		printf("\n");			
		int **iStepMap = (int**) calloc(array-> n_rows, sizeof(int*));
		for ( int i = 0; i<array->n_columns; i++)
		{
			iStepMap[i] = (int*) calloc(array-> n_columns, sizeof(int));
		}	//Карта шагов; содержит число шагов до ФИНИША в текущей координате;
						// -1 - не посещали, -2 - препятствие
		int *iResultX = (int*) calloc(array->n_rows * array->n_columns, sizeof(int));	//X-координата пути; [0] - точка НАЧАЛА
		int *iResultY = (int*) calloc(array->n_rows * array->n_columns, sizeof(int));;	//Y-координата пути; [0] - точка НАЧАЛАa
		coord start, end;
		start.x = 1, start.y = 0, end.x = 9, end.y = 7;		
		WaveStart(start, end,  array, iStepMap, iResultX, iResultY);
		printf("\n");
		for(int i = 0; i<(array->n_rows); i++)
		{
			for(int j = 0; j<(array->n_columns); j++)
			{ 
				printf("%d  ", iStepMap[i][j]);
					
			}
			printf("\n");	
		}
		PathResult(start, end, array->n_rows, iStepMap, iResultX, iResultY);
		map_out = fopen("map_out.txt", "w");
		for (int i = 0; i<(array->n_rows*array->n_columns); i++)
		{
			fprintf(map_out, "%d " , iResultX[i]);
		}
		fprintf(map_out, "\n");
		for (int i = 0; i<(array->n_rows*array->n_columns); i++)
		{
			fprintf(map_out, "%d " , iResultY[i]);
		}
		fclose(map_out);
	}	
	else printf("Error. File is missing!\n");
	
	return 0;
}
