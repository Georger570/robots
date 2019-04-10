#include "coord.h"

class MovementIntelligence
{
        //Robot
        public float speed = 1f;
        public float speedValue = 10f;
        public float directionValue = 1.0f;
            
        //Position of Robot
        coordinates CurrentPosition; //Текущая позиция
        public coord_direction direction; //Текущее направление движения робота
        public Vector3 movement = new Vector3(0, 0, 0); //Переменная, отвечающая за расстояние, пройденное роботом

        //"Covering all holes"
        public bool BackFlag = true;
        public int XX = 0;
        public int ZZ = 0;

        //Files
        WorkWithFiles Explored;
        WorkWithFiles Unexplored;

        public MovementIntelligence(WorkWithFiles File, WorkWithFiles File2)
        {
            Explored = File;
            Unexplored = File2;
            direction.x = 1;
            direction.z = 0;
            CurrentPosition.x = 0;
            CurrentPosition.z = 0;
        }
		
        public void Moition() //Функция движения
        {
            transform.position += transform.forward * (speed * directionValue) * Time.deltaTime; //Передвижение робота
            movement += transform.forward * (speed * directionValue) * Time.deltaTime; //Текущее растояние, пройденное роботом
        }

        public coordinates  getFuturePosition() 
        {
            coordinates FuturePosition;
            FuturePosition.x = direction.x + CurrentPosition.x;
            FuturePosition.z = direction.z + CurrentPosition.z;
            return FuturePosition;
        }

        public coordinates getCurrentPosition() //Получить текущую позицию робота
        {
            return CurrentPosition;
        }

        public bool AheadIsObstacle() //Определение, есть ли препятсвие спереди
        {
            if (Physics.Raycast(transform.position, transform.forward, out hit, (transform.localScale.x)))
                return true;
            else return false;
        }

        public bool RightIsObstacle() //Определение, есть ли препятсвие справа
        {
            if (Physics.Raycast(transform.position, transform.right, out hit, (transform.localScale.z)))
                return true;
            else return false;
        }

        public bool LeftIsObstacle() //Определение, есть ли препятсвие слева
        {
            if (Physics.Raycast(transform.position, -transform.right, out hit, (transform.localScale.z)))
                return true;
            else return false;
        }

        public bool IsObstaclesAround() //Определение, есть ли препятсвие рядом
        {
            if (AheadIsObstacle() || RightIsObstacle() || LeftIsObstacle())
                return true;
            else return false;
        }

        public bool TryToRegisterMotion(float robot_size) //Определение, прошёл ли робот расстояние, равное длине его корпуса
        {
            if (Math.Abs(movement.x) >= robot_size)
            {
                if (movement.x < 0)
                    movement.x = movement.x + robot_size;
                else if (movement.x > 0)
                    movement.x = movement.x - robot_size;
                CurrentPosition.x = CurrentPosition.x + direction.x;
                CurrentPosition.z = CurrentPosition.z + direction.z;
                //print(x + " " + z);
                return true;
                //WriteFlag = true;

            }
            else if (Math.Abs(movement.z) >= robot_size)
            {
                if (movement.z < 0)
                    movement.z = movement.z + robot_size;
                else if (movement.z > 0)
                    movement.z = movement.z - robot_size;
                CurrentPosition.x = CurrentPosition.x + direction.x;
                CurrentPosition.z = CurrentPosition.z + direction.z;
                //print(x + " " + z);
                return true;
                //WriteFlag = true;
            }
            return false;
        }

        public bool CheckSide(Vector3 side)
        {
            coord_direction side_direction;
            if (side == transform.right)
            {
                side_direction = Direction_if_TurnRight(direction);
                return Explored.isAlreadyinFile(getPosition(side_direction, CurrentPosition));
            }
            else if (side == -transform.right)
            {
                side_direction = Direction_if_TurnLeft(direction);
                return Explored.isAlreadyinFile(getPosition(side_direction, CurrentPosition));
            }
            else if (side == -transform.forward)
            {
                side_direction = Direction_if_TurnAround(direction);
                return Explored.isAlreadyinFile(getPosition(side_direction, CurrentPosition));
            }
            return false;
        }

        public coordinates getPosition(coord_direction direction, coordinates CurrentPosition)
        {
            coordinates FuturePosition;
            FuturePosition.x = CurrentPosition.x + direction.x;
            FuturePosition.z = CurrentPosition.z + direction.z;
            return FuturePosition;
        }

        public bool Emergency()
        {

            return true;
        }

        public int TurnFunction(int turnAngle, ref bool BackFlag)
        {
            /*if (hit.collider.tag != "Obstacle" || hit.collider == myColloder)
            {
                return 0;
            }*/
            coord_direction side_direction;
            if (!(Physics.Raycast(transform.position, transform.right, out hit, (transform.localScale.x * 2)))
                && (!CheckSide(transform.right) && BackFlag ))
                                                        /*(((side_direction.x = Direction_if_TurnRight(direction).x + x) < (side_direction.x = Direction_if_TurnLeft(direction).x + x))
                                                        || ((side_direction.z = Direction_if_TurnRight(direction).z + z) < (side_direction.z = Direction_if_TurnLeft(direction).z + z))))))*/
            {
                direction = Direction_if_TurnRight(direction);
                transform.Rotate(0, turnAngle, 0);
            }
            else if (!(Physics.Raycast(transform.position, -transform.right, out hit, (transform.localScale.x * 2)))
                && (!CheckSide(-transform.right) && BackFlag) )
            {
                direction = Direction_if_TurnLeft(direction);
                transform.Rotate(0, -turnAngle, 0);
            }
            else if (!(Physics.Raycast(transform.position, -transform.forward, out hit, (transform.localScale.z)))
                && (!CheckSide(-transform.forward) && BackFlag))
            {
                direction = Direction_if_TurnAround( direction );
                transform.Rotate(0, 2*turnAngle, 0);
            }
            else if (BackFlag == true)
            {
                //if (BackFlag == true)
                BackFlag = false;
                //AnotherFlag = 0;
                return 0;
            }
            return 1;
        }

        public bool IllBeBack(int turnAngle, ref bool BackFlag, ref int XX, ref int ZZ)
        {
            if (speed == 0)
            {
                string[] SplitedStr = Unexplored.ReadLine().Split(';');
                XX = int.Parse(SplitedStr[0]);
                ZZ = int.Parse(SplitedStr[0]);
                speed = 10;
            }
                //var lines = System.IO.File.ReadAllLines("tif.txt");
            //System.IO.File.WriteAllLines("tif.txt", lines.Skip(1).ToArray());
            if (XX < CurrentPosition.x)
            {
                while (direction.x != -1)
                {
                    if (!Physics.Raycast(transform.position, transform.right, out hit, ((transform.localScale.x))))
                    {
                        direction = Direction_if_TurnRight(direction);
                        transform.Rotate(0, turnAngle, 0);
                    }
                    else break;
                }
            }
            else if (XX > CurrentPosition.x)
            {
                while (direction.x != 1)
                {
                    if (!Physics.Raycast(transform.position, transform.right, out hit, ((transform.localScale.x))))
                    {
                        direction = Direction_if_TurnRight(direction);
                        transform.Rotate(0, turnAngle, 0);
                    }
                    else break;
                }
            }
            else if (ZZ < CurrentPosition.z)
            {
                while (direction.z != -1)
                {
                    if (!Physics.Raycast(transform.position, transform.right, out hit, ((transform.localScale.x))))
                    {
                        direction = Direction_if_TurnRight(direction);
                        transform.Rotate(0, turnAngle, 0);
                    }
                    else break;
                }
            }
            else if (ZZ > CurrentPosition.z)
            {
                while (direction.z != 1)
                {
                    if (!Physics.Raycast(transform.position, transform.right, out hit, ((transform.localScale.x))))
                    {
                        direction = Direction_if_TurnRight(direction);
                        transform.Rotate(0, turnAngle, 0);
                    }
                    else break;
                }
            }
            if (CurrentPosition.x == XX && CurrentPosition.z == ZZ)
                BackFlag = true;
            return true;
        }

        public coord_direction Direction_if_TurnRight(coord_direction direction)
        {
            if (direction.x == 1)
            {
                direction.x = 0;
                direction.z = 1;
            }
            else if (direction.z == 1)
            {
                direction.z = 0;
                direction.x = -1;
            }
            else if (direction.x == -1)
            {
                direction.x = 0;
                direction.z = -1;
            }
            else if (direction.z == -1)
            {
                direction.z = 0;
                direction.x = 1;
            }
            return direction;
        }
        public coord_direction Direction_if_TurnLeft(coord_direction direction)
        {
            if (direction.x == 1)
            {
                direction.x = 0;
                direction.z = -1;
            }
            else if (direction.z == -1)
            {
                direction.z = 0;
                direction.x = -1;
            }
            else if (direction.x == -1)
            {
                direction.x = 0;
                direction.z = 1;
            }
            else
            {
                direction.z = 0;
                direction.x = 1;
            }
            return direction;
        }
        public coord_direction Direction_if_TurnAround(coord_direction direction)
        {
            if (direction.x == 1)
            {
                direction.x = -1;
            }
            else if (direction.z == -1)
            {
                direction.z = 1;
            }
            else if (direction.x == -1)
            {
                direction.x = 1;
            }
            else
            {
                direction.z = -1;
            }
            return direction;
        }
    }
