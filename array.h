#ifndef __ARRAY_H__
#define __ARRAY_H__
#include "stdio.h"
#include "stdlib.h"

typedef struct arr {	
	int n_rows;
	int n_columns;
	int **ptr;
} arr;

arr* InitArray_w_File(FILE *map_in)
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
				//array->ptr[i][j] = 0;
				fscanf(map_in, "%d" , &(array->ptr[i][j]));				
				//array->ptr[i][j] = getc(map_in) - '0';
				//if (array->ptr[i][j] < 0)
					//j--;
			}	
		}			
		return array;
}

arr* InitArray(int n_rows,int n_columns)
{
		arr *array = malloc(sizeof(arr));
		array->n_rows = n_rows;
		array->n_columns = n_columns;
		array->ptr = (int**) calloc(array->n_rows, sizeof(int*));			
		for ( int i = 0; i<array->n_rows; i++)
		{
			array-> ptr[i] = (int*) calloc(array-> n_columns, sizeof(int));
		}			
		return array;
}

int PrintArray(arr* array)
{
	printf("\nNumber of rows: %d,\nNumber of columns: %d,\nArray: \n", array->n_rows, array->n_columns);
	for(int i = 0; i<(array->n_rows); i++)
	{
		for(int j = 0; j<(array->n_columns); j++)
		{ 
			printf("%d\t", array->ptr[i][j]);
				
		}
		printf("\n");	
	}
	printf("\n");
}

#endif

