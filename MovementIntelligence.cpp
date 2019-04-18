#include "coord.h"
#include "list.h"

#define RightSensor 1
#define LeftSensor 2
#define FrontSensor 3
#define RIGHT 1
#define LEFT 2
#define distance 21

bool IsObstacleWithinReach(int a, int b)
{
    return true;
}

void Turn(int a)
{
}

class MovementIntelligence
{
        //Robot
        float speed = 1.0f;
        float speedValue = 10.0f;

        //Position of Robot

        //coord* CurrentPosition = new coord(0,0); //Текущая позиция
        //coord* direction = new coord(); //Текущее направление движения робота
        coord CurrentPosition;
        coord direction;
        int movement = 0; //Переменная, отвечающая за расстояние, пройденное роботом


        //Files
        //WorkWithFiles Explored;
        //WorkWithFiles Unexplored;

        //List
        List* Explored;
public:
        MovementIntelligence(List* List1)
        {
            Explored = List1;
            direction.setCoord(1,0);
            CurrentPosition.setCoord(0,0);
        }

        void setMovement(int mov)
        {
            movement = mov;
        }

        /*void Moition() //Функция движения
        {
            run_fb(dir, speed); //Передвижение робота
            movement += transform.forward * (speed * directionValue) * Time.deltaTime; //Текущее растояние, пройденное роботом
        }*/

        coord  getFuturePosition(coord direction)
        {
            return (direction + CurrentPosition);
        }

         coord getCurrentPosition() //Получить текущую позицию робота
        {
            return CurrentPosition;
        }

         bool IsObstaclesAround() //Определение, есть ли препятсвие рядом
        {
            if (IsObstacleWithinReach(FrontSensor, distance) || IsObstacleWithinReach(RightSensor, distance) || IsObstacleWithinReach(LeftSensor, distance))
                return true;
            else return false;
        }

        bool TryToRegisterMotion(int robot_size) //Определение, прошёл ли робот расстояние, равное длине его корпуса
        {
            if (movement >= robot_size)
            {
                movement -= robot_size;
                CurrentPosition += direction;
                //print(x + " " + z);
                return true;
                //WriteFlag = true;

            }
            return false;
        }

        bool CheckSide(int side)
        {
            coord side_direction(0,0);
            if (side == RIGHT)
            {
                side_direction = Direction_if_TurnRight(direction);
                return Explored->isAlreadyInList(getFuturePosition(side_direction));
            }
            else if (side == LEFT)
            {
                side_direction = Direction_if_TurnLeft(direction);
                return Explored->isAlreadyInList(getFuturePosition(side_direction));
            }
            return false;
        }

        bool Emergency()
        {
            return true;
        }

        int TurnFunction()
        {
            coord side_direction(0,0);
            if (!IsObstacleWithinReach(RightSensor, distance)
                && (!CheckSide(RIGHT)) )
            {
                direction = Direction_if_TurnRight(direction);
                Turn(RIGHT);
            }
            else if (!IsObstacleWithinReach(LeftSensor, distance)
                && (!CheckSide(LEFT)) )
            {
                direction = Direction_if_TurnLeft(direction);
                Turn(LEFT);
            }
            return 1;
        }

        coord Direction_if_TurnRight(coord direction)
        {
            if (direction.x == 1)
            {
                direction.x = 0;
                direction.y = 1;
            }
            else if (direction.y == 1)
            {
                direction.y = 0;
                direction.x = -1;
            }
            else if (direction.x == -1)
            {
                direction.x = 0;
                direction.y = -1;
            }
            else if (direction.y == -1)
            {
                direction.y = 0;
                direction.x = 1;
            }
            return direction;
        }
        coord Direction_if_TurnLeft(coord direction)
        {
            if (direction.x == 1)
            {
                direction.x = 0;
                direction.y = -1;
            }
            else if (direction.y == -1)
            {
                direction.y = 0;
                direction.x = -1;
            }
            else if (direction.x == -1)
            {
                direction.x = 0;
                direction.y = 1;
            }
            else
            {
                direction.y = 0;
                direction.x = 1;
            }
            return direction;
        }
        coord Direction_if_TurnAround(coord direction)
        {
            if (direction.x == 1)
            {
                direction.x = -1;
            }
            else if (direction.y == -1)
            {
                direction.y = 1;
            }
            else if (direction.x == -1)
            {
                direction.x = 1;
            }
            else
            {
                direction.y = -1;
            }
            return direction;
        }
    };


