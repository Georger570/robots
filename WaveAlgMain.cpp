#include "array.h"
#include "wavealgorithm.h"
#include "stdio.h"

int main()
{
    arr arraySize = {10, 10}; //Get this infomation from first robot
    arr* array = InitArray(arraySize.n_rows, arraySize.n_columns);		//Карта; 0 - свободно, 1 - препятсвие
    PrintArray(array);
    arr* iStepMap = InitArray(array->n_rows, array->n_columns);	//Карта шагов; содержит число шагов до ФИНИША в текущей координате;
                                                                                // -1 - не посещали, -2 - препятствие
    int* iResultX = static_cast<int*>(calloc(array->n_rows * array->n_columns, sizeof(int)));	//X-координата пути; [0] - точка НАЧАЛА
    int* iResultY = static_cast<int*>(calloc(array->n_rows * array->n_columns, sizeof(int)));	//Y-координата пути; [0] - точка НАЧАЛАa

    coord start, end;
    start.x = 1, start.y = 0, end.x = 9, end.y = 7; //

    WaveStart(start, end, array, iStepMap->ptr, iResultX, iResultY);
    PrintArray(iStepMap);
    PathResult(start, end, array->n_rows, iStepMap->ptr, iResultX, iResultY);
    //PrintArray(iStepMap);
    /*map_out = fopen("map_out.txt", "w");
    for (int i = 0; i < (array->n_rows * array->n_columns); i++)
    {
        fprintf(map_out, "%d ", iResultX[i]);
    }
    fprintf(map_out, "\n");
    for (int i = 0; i < (array->n_rows * array->n_columns); i++)
    {
        fprintf(map_out, "%d ", iResultY[i]);
    }
    fclose(map_out);
    */
    return 0;
}
