<<<<<<< HEAD
﻿using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using System.IO;
using System.Linq;
using Assets;


namespace Assets
{
    class Map : MonoBehaviour
    {
        const int size = 40;
        int[,] Z_negative_X_positive = new int[size, size];
        int[,] Z_positive_X_positive = new int[size, size];
        int[,] Z_positive_X_negative = new int[size, size];
        int[,] Z_negative_X_negative = new int[size, size];
        MovementIntelligence MovementAI;
        Transform transform;
        RaycastHit hit;

        public Map(MovementIntelligence AI, RaycastHit hit, Transform tran)
        {
            MovementAI = AI;
            transform = tran;
=======
#include "Memlib.h" 

class Map
{
        const int size = 40;
        int** Z_negative_X_positive = MemoryAllocation(size);
        int** Z_positive_X_positive = MemoryAllocation(size);
        int** Z_positive_X_negative = MemoryAllocation(size);
        int** Z_negative_X_negative = MemoryAllocation(size);
        MovementIntelligence MovementAI;

        public Map(MovementIntelligence AI)
        {
            MovementAI = AI;
>>>>>>> master
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
<<<<<<< HEAD
                    Z_negative_X_negative[i, j] = 0;
                    Z_negative_X_positive[i, j] = 0;
                    Z_positive_X_negative[i, j] = 0;
                    Z_positive_X_positive[i, j] = 0;
=======
                    Z_negative_X_negative[i][j] = 0;
                    Z_negative_X_positive[i][j] = 0;
                    Z_positive_X_negative[i][j] = 0;
                    Z_positive_X_positive[i][j] = 0;
>>>>>>> master
                }
            }
        }

<<<<<<< HEAD
        int DlyaVlada2( Vector3 side, int side_x, int side_z)
        {

            if (Physics.Raycast(transform.position, side, out hit, (transform.localScale.x)))
            {
                if ((side_z < 0) && (side_x >= 0))
                {
                    Z_negative_X_positive[Math.Abs(side_z), side_x] = 1;
                }
                else if ((side_z >= 0) && (side_x > 0))
                {
                    Z_positive_X_positive[side_z, side_x] = 1;
                }
                else if ((side_z > 0) && (side_x <= 0))
                {
                    Z_positive_X_negative[side_z, Math.Abs(side_x)] = 1;
                }
                else
                {
                    Z_negative_X_negative[Math.Abs(side_z), Math.Abs(side_x)] = 1;
=======
        int WallRegistration( Vector3 side, int side_x, int side_z)
        {

            if (Physics.Raycast(transform.position, side, out hit, (transform.localScale.x)))//Обнаружение препятсвия. Переделать.
            {
                if ((side_z < 0) && (side_x >= 0))
                {
                    Z_negative_X_positive[Math.Abs(side_z)][side_x] = 1; //Добавить библиотеку с модулем
                }
                else if ((side_z >= 0) && (side_x > 0))
                {
                    Z_positive_X_positive[side_z][side_x] = 1;
                }
                else if ((side_z > 0) && (side_x <= 0))
                {
                    Z_positive_X_negative[side_z][Math.Abs(side_x)] = 1;
                }
                else
                {
                    Z_negative_X_negative[Math.Abs(side_z)][Math.Abs(side_x)] = 1;
>>>>>>> master
                }
            }
            return 0;
        }

        // II 0 - +x, I 0 - +z, IV 0 - -x, III - -z;
        public int arrformap(coordinates Coord, coord_direction direction, float speed)
        {
            //File.Delete("map.txt");
<<<<<<< HEAD

            int side_x = Coord.x + direction.x;
            int side_z = Coord.z + direction.z;
            DlyaVlada2(transform.forward, side_x, side_z);
            coord_direction side_direction = MovementAI.Direction_if_TurnRight(direction);
            side_x = Coord.x + side_direction.x;
            side_z = Coord.z + side_direction.z;
            DlyaVlada2(transform.right, side_x, side_z);
            side_direction = MovementAI.Direction_if_TurnLeft(direction);
            side_x = Coord.x + side_direction.x;
            side_z = Coord.z + side_direction.z;
            DlyaVlada2(-transform.right, side_x, side_z);

            if (speed == 0)
=======
			// Заменить transform
            int side_x = Coord.x + direction.x;
            int side_z = Coord.z + direction.z;
            WallRegistration(transform.forward, side_x, side_z);
            coord_direction side_direction = MovementAI.Direction_if_TurnRight(direction);
            side_x = Coord.x + side_direction.x;
            side_z = Coord.z + side_direction.z;
            WallRegistration(transform.right, side_x, side_z);
            side_direction = MovementAI.Direction_if_TurnLeft(direction);
            side_x = Coord.x + side_direction.x;
            side_z = Coord.z + side_direction.z;
            WallRegistration(-transform.right, side_x, side_z);

            /*if (speed == 0)
>>>>>>> master
            {
                FileInfo fileformap = new FileInfo("map.txt");
                File.Delete("map.txt");
                StreamWriter sr = fileformap.AppendText();
                for (int Ox = (size - 1); Ox >= 0; --Ox)
                {
                    string write_X_Negative_hemisphere = "";
                    if (Ox == 0)
                    {
                        for (int Oz = (size - 1); Oz >= 0; --Oz)
                        {
                            write_X_Negative_hemisphere += Z_negative_X_positive[Oz, Ox];
                        }
                        for (int Oz = 1; Oz < size; ++Oz)
                        {
                            write_X_Negative_hemisphere += Z_positive_X_negative[Oz, Ox];
                        }
                        sr.WriteLine(write_X_Negative_hemisphere);
                        continue;
                    }
                    for (int Oz = (size - 1); Oz >= 0; --Oz)
                    {
                        write_X_Negative_hemisphere += Z_negative_X_negative[Oz, Ox];
                    }
                    for (int Oz = 1; Oz < size; ++Oz)
                    {
                        write_X_Negative_hemisphere += Z_positive_X_negative[Oz, Ox];
                    }
                    sr.WriteLine(write_X_Negative_hemisphere);
                }
                for (int Ox = 1; Ox < size; ++Ox)
                {
                    string write_X_Positive_hemisphere = "";
                    for (int Oz = (size - 1); Oz > 0; --Oz)
                    {
                        write_X_Positive_hemisphere += Z_negative_X_positive[Oz, Ox];
                    }
                    for (int Oz = 0; Oz < size; ++Oz)
                    {
                        write_X_Positive_hemisphere += Z_positive_X_positive[Oz, Ox];
                    }
                    sr.WriteLine(write_X_Positive_hemisphere);
                }

                sr.Close();
<<<<<<< HEAD
            }
            return 0;
        }
    }
=======
            }*/
            return 0;
        }
>>>>>>> master
}
