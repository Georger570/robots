#ifndef __ARRAY_H__
#define __ARRAY_H__
#include "stdio.h"
#include "stdlib.h"

typedef struct arr {	
	int n_rows;
	int n_columns;
	int **ptr;
} arr;

arr* InitArray(FILE *map_in)
{
		arr *array = malloc(sizeof(arr));
		fscanf(map_in, "%d", &(array->n_rows));
		fscanf(map_in, "%d", &(array->n_columns));
		array->ptr = (int**) calloc(array->n_rows, sizeof(int*));			
		for ( int i = 0; i<array->n_rows; i++)
		{
			array-> ptr[i] = (int*) calloc(array-> n_columns, sizeof(int));
		}		
		for(int i = 0; i<(array->n_rows); i++)
		{			
			for(int j = 0; j<(array->n_columns); j++)
			{ 
				array->ptr[i][j] = 0;
				char a;				
				array->ptr[i][j] = getc(map_in) - '0';
				if (array->ptr[i][j] < 0)
					j--;
			}	
		}			
		return array;
}

int PrintArray(arr* array)
{
	printf("\nNumber of rows: %d, \nNumber of columns: %d\n Array: \n", array->n_rows, array->n_columns);	
	
	for(int i = 0; i<(array->n_rows); i++)
	{
		for(int j = 0; j<(array->n_columns); j++)
		{ 
			printf("%d  ", array->ptr[i][j]);
				
		}
		printf("\n");	
	}
}

#endif

