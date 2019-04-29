#include "coord.h"

class MovementIntelligence
{
            
        //Position of Robot
        coord CurrentPosition; //Текущая позиция
        coord direction; //Текущее направление движения робота
        int movement = 0; //Переменная, отвечающая за расстояние, пройденное роботом


        //Files
        //WorkWithFiles Explored;
        //WorkWithFiles Unexplored;
		
		//List
		List* Explored;

/*
==========================================================================================
|	подключите один мотор к клемме: M1+ и M1- а второй к клемме: M2+ и M2-
|   Motor shield использует четыре контакта 4, 5, 6, 7 для управления моторами 
|   4 и 7 — для направления, 5 и 6 — для скорости
==========================================================================================
*/

	#define SENS_R       2 //Рефлектор правого колеса
    #define SENS_L       3 //Рефлектор левого колеса
    
	#define DIR_R        4 //Направление врещения правого двигателя
    #define SPEED_R      5 //Скорость врещения правого двигателя
   
    #define SPEED_L      6 //Скорость врещения левого двигателя
    #define DIR_L        7 //Направление врещения левого двигателя
	
	#define RightSensor 8 //Эхо от прового дальномера
	#define LeftSensor  9 //Эхо от левого дальномера
    #define FrontSensor 10//Эхо от переднего дальномера
	#define trigPin     11//Общий триггер для всех дальномеров

	#define RIGHT 8 
	#define LEFT  9 
    #define BACK 12

	#define SPEED 37

//========================================================================================
	int left_motion=0;
	int right_motion=0;

	int left_status = digitalRead(SENS_L);
	int right_status = digitalRead(SENS_R);

	int dir_left_mov=1;
	int dir_right_mov=1;

	float yaw=0; // Курс
	float global_yaw=0;
	int duration=0, distanceFront=0,distanceLeft=0,distanceRight=0;

 void Init()
 {
	 
	pinMode(trigPin, OUTPUT); 
	pinMode(FrontSensor, INPUT);
	pinMode(LeftSensor, INPUT);
	pinMode(RightSensor, INPUT);
	pinMode(SENS_R, INPUT);
	pinMode(SENS_L, INPUT);

 
    Serial.begin(115200); // открываем последовательный порт
      //Serial.println("Begin init...");
      
      
    for (int i = 4; i < 8; i++)  // настраиваем выводы платы 4, 5, 6, 7 на вывод сигналов 
		pinMode(i, OUTPUT);
	
      delay(2000);
    } 
	
void read_sens() //Обработка рефлекторов колёс
{
	if(left_status!=digitalRead(SENS_L))
	{
		left_status=digitalRead(SENS_L);
		left_motion+=dir_left_mov;
	}
		
	if(right_status!=digitalRead(SENS_R))
	{
		right_status=digitalRead(SENS_R);
		right_motion+=dir_right_mov;
	}
}
	
void correct_course_sens(int speed)
{
	read_sens();
	
	if (left_motion>right_motion)
	{
		analogWrite(SPEED_R, speed);
		analogWrite(SPEED_L, speed-(left_motion-right_motion));
	}
	if (left_motion<right_motion)
	{
		analogWrite(SPEED_R, speed-(right_motion-left_motion));
		analogWrite(SPEED_L, speed);
	}
	if (left_motion==right_motion)
	{
		analogWrite(SPEED_R, speed);
		analogWrite(SPEED_L, speed);
	}
	
}

//Returning true if distance between obstacle and robot is less than variable
bool IsObstacleWithinReach(int echoPin, int distance)
{
	if 	(distance < Rangefinder_perquisition(echoPin))
		return false;
	else 
		return true;
}

int Rangefinder_perquisition(int echoPin)
{
	int distance = 0, duration = 0;	
	digitalWrite(trigPin, LOW); 
	delayMicroseconds(4); 
    // Теперь установим высокий уровень на пине Trig
	digitalWrite(trigPin, HIGH);
	// Подождем 10 μs 
	delayMicroseconds(10); 
	digitalWrite(trigPin, LOW); 
	// Узнаем длительность высокого сигнала на пине Echo
	duration = pulseIn(echoPin, HIGH); 
	// Рассчитаем расстояние
	distance = duration / 58;
	return distance;
}

void get_dist() //Опрос дальномеров
{
	distanceFront = Rangefinder_perquisition(FrontSensor);	
	distanceRight = Rangefinder_perquisition(RightSensor);
	distanceLeft = Rangefinder_perquisition(LeftSensor);
  	Serial.print("Left / Front / Right");
  	Serial.print("\n");
  	Serial.print(distanceLeft);
  	Serial.print(" / ");
  	Serial.print(distanceFront);
  	Serial.print(" / ");
  	Serial.print(distanceRight);
  	Serial.print("\n");
}

void run_fb(int dir, int speed) //Движение вперёд (0) назад (1)
{
	if(dir==0)//forward
	{
		dir_left_mov=1;
		dir_right_mov=1;
		
		digitalWrite(DIR_R, 0);
		digitalWrite(DIR_L, 1);

		analogWrite(SPEED_R, speed);
		analogWrite(SPEED_L, speed);
	}
	else if(dir==1)//back
	{
		dir_left_mov=-1;
		dir_right_mov=-1;
		
		digitalWrite(DIR_R, 1);
		digitalWrite(DIR_L, 0);
	
		analogWrite(SPEED_R, speed);
		analogWrite(SPEED_L, speed);
	}
}

void Turn(int side)
{
	float Angle = 90f;
	switch(side)
	{
		case RIGHT:
			turn_lr(Angle, SPEED, -1);
			break;		
		case LEFT:
			turn_lr(Angle, SPEED, 1);
			break;		
		case BACK:
			turn_lr(Angle, SPEED, -1);
			turn_lr(Angle, SPEED, 1);
		default:	
	if (side == RIGHT)
		turn_lr(Angle, SPEED, -1)
	else if (side == LEFT)
		turn_lr(Angle, SPEED, 1)
	else
	{
		turn_lr(Angle*2, SPEED, 1) 
	}
}

void turn_lr(float angle, int speed=37, int motor) //Поворот влево (<0) вправо (>0) левый мотор -1 правый 1
{
	
	if(angle<0)//left
	{
		dir_left_mov=-1;
		dir_right_mov=1;
		
		digitalWrite(DIR_R, 0);
		digitalWrite(DIR_L, 0);
	}
	
	else if(angle>0)//right
	{
		dir_left_mov=1;
		dir_right_mov=-1;
		
		digitalWrite(DIR_R, 1);
		digitalWrite(DIR_L, 1);
	}
		
	if (motor == 1)
		analogWrite(SPEED_R, speed);
	else
		analogWrite(SPEED_L, speed);

	for (;;)
	{
		read_sens();
		get_yaw();
		Serial.print(yaw);
      if (yaw==angle)
      {
		  if(angle<0)
		  {
			digitalWrite(DIR_R, 1);
			digitalWrite(DIR_L, 1);
		  }
		  else
		  {
			digitalWrite(DIR_R, 0);
			digitalWrite(DIR_L, 0);
		  }
		  if (motor==1)
			analogWrite(SPEED_R, 255);
		  else
			analogWrite(SPEED_L, 255);
		
		delay(10);
		   
        stop();
        break;
      }
	}

	stop();
	up_global_yaw();
}

void stop()
{	
	analogWrite(SPEED_L, 0);
	analogWrite(SPEED_R, 0);
}

        void MovementIntelligence(List* List1)
        {
            Explored = List1;
            direction(1,0);
			CurrentPosition(0,0);            
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

        coord  getFuturePosition() 
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
            coord side_direction;
            if (side == RIGHT)
            {
                side_direction = Direction_if_TurnRight(direction);
                return Explored->IsAlreadyInList(getFuturePosition(side_direction, CurrentPosition));
            }
            else if (side == LEFT)
            {
                side_direction = Direction_if_TurnLeft(direction);
                return Explored->IsAlreadyInList(getFuturePosition(side_direction, CurrentPosition));
            }
            return false;
        }

        bool Emergency()
        {
            return true;
        }

        int TurnFunction()
        {
            coord side_direction;
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

void up_global_yaw()
{
	global_yaw+=yaw;
	right_motion=0;
	left_motion=0;
	while (global_yaw>=360)
		global_yaw=global_yaw-360;
}

int get_yaw()
{
	if (left_motion>right_motion)
	{
		yaw=(left_motion-right_motion)*3.6;//3.6 ok
		return 0;
	}
	if (left_motion<right_motion)
	{
		yaw=(right_motion-left_motion)*-3.6;
		return 0;
	}
	yaw=0;
}

////////////////////////NOT IN USE//////////////////////

void correct_course_RF(int speed)
{
	get_dist();
	if (distanceFront<7&&distanceFront>2)
	{
		Serial.print(distanceFront);
		Serial.print("\n");
		stop();
		delay(1000);
	}
	if (distanceLeft>distanceRight)
	{
		analogWrite(SPEED_R, speed);
		analogWrite(SPEED_L, opspeed-3);
	}
	if (distanceLeft<distanceRight)
	{
		analogWrite(SPEED_R, speed-3);
		analogWrite(SPEED_L, speed);
	}
	
	
		analogWrite(SPEED_R, speed);
		analogWrite(SPEED_L, speed);
}
