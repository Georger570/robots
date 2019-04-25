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

	#define SPEED 40

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
   
    void read_sens(int,int,int); // 24 отсчёта - один поворот колеса //один отсчёт - 3 градуса //21 шаг примерно корпус робота
	void read_sens_imu(int,int,int);
	
	int speed=37; //Скорость
	
	
 void setup()
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
	
	
	
	 void loop()
	{
	/*
		turn_lr(0,40,0);
		for(;;)
		{
			read_sens();
			Serial.print(left_motion);
			Serial.print("/");
			Serial.print(right_motion);
			Serial.print("\n");
			
			if (right_motion>=10 && left_motion>=10)
			{
				stops();
				break;
			}
		}
		delay(500);
		left_motion=0;
		right_motion=0;
		turn_lr(0,40,0);
		for(;;)
		{
			read_sens();
			Serial.print(left_motion);
			Serial.print("/");
			Serial.print(right_motion);
			Serial.print("\n");
			
			if (right_motion>=10 && left_motion>=10)
				{
				stops();
				break;
			}
		}
		
		*/
		
		//delay(700);
		
		
		
		/*
		
		left_motion=0;
		right_motion=0;
		
		
		run_fb(0,40);
		for(;;)
		{
			correct_course_sens(40);
			if (left_motion>300)
				{
					stops();
					break;
				}
		}

   delay(500);
   
   left_motion=0;
    right_motion=0;
    turn_lr(1,40,0);
    for(;;)
    {
      read_sens();
      Serial.print(left_motion);
      Serial.print("/");
      Serial.print(right_motion);
      Serial.print("\n");
      
      if (right_motion>=11 && left_motion>=11)
        {
        stops();
        break;
      }
	}
	  delay(500);
	  
	  left_motion=0;
    right_motion=0;
    turn_lr(1,40,0);
    for(;;)
    {
      read_sens();
      Serial.print(left_motion);
      Serial.print("/");
      Serial.print(right_motion);
      Serial.print("\n");
      
      if (right_motion>=10 && left_motion>=10)
        {
        stops();
        break;
      }
    }
		delay(5000);
		
		*/
		/*
		read_sens();
      Serial.print(left_motion);
      Serial.print("/");
      Serial.print(right_motion);
	  Serial.print("/");
      Serial.print(yaw);
      Serial.print("\n");
	  get_yaw();
	  */
	  /*
	  for (int i =0;i<10;i++)
	  {
	  turn_lr(1,40,0);
    for(;;)
    {
      read_sens();
      Serial.print(left_motion);
      Serial.print("/");
      Serial.print(right_motion);
  Serial.print("/");
      get_yaw();
	  Serial.print(yaw);
      Serial.print("\n");
      if (yaw==180)
        {
        stops();
        break;
      }
    }
	delay(200);
	  }
	delay(50000);
	  */
	  	  
		  left_motion=0;
		  right_motion=0;
		  
		  run_fb(0,40);
		  for (;;)
		  {
			Serial.print(left_motion);
			Serial.print("/");
			Serial.print(right_motion);
			Serial.print("\n");
			  correct_course_RF(40);
			  if(left_motion>150)
			  {
				  stops();
				  break;
			  }
		  }
		   left_motion=0;
		  right_motion=0;
		  
		   delay(300);
		   turn_lr(90,40,1);
		  delay(300);
		  left_motion=0;
		  right_motion=0;
		  run_fb(0,40);
		  for (;;)
		  {
			Serial.print(left_motion);
			Serial.print("/");
			Serial.print(right_motion);
			Serial.print("\n");
			  correct_course_sens(40);
			  if(left_motion>70)
			  {
				  stops();
				  break;
			  }
		  }
		   left_motion=0;
		  right_motion=0;
	  delay(300);
		   turn_lr(90,40,0);
		   delay(300);
		  
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
	
	void up_global_yaw()
	{
		global_yaw+=yaw;
		right_motion=0;
		left_motion=0;
		while (global_yaw>=360)
			global_yaw=global_yaw-360;
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

//Physics.Raycast(transform.position, transform.right, out MovementAI.hit, (transform.localScale.x))


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

void correct_course_RF(int speed)
{
	get_dist();
	if (distanceFront<7&&distanceFront>2)
	{
		Serial.print(distanceFront);
		Serial.print("\n");
		stops();
		delay(1000);
	}
	if (distanceLeft>distanceRight)
	{
		analogWrite(SPEED_R, speed);
		analogWrite(SPEED_L, speed-3);
	}
	if (distanceLeft<distanceRight)
	{
		analogWrite(SPEED_R, speed-3);
		analogWrite(SPEED_L, speed);
	}
	
	
		analogWrite(SPEED_R, speed);
		analogWrite(SPEED_L, speed);
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

void turn_lr(float angle, int speed=40, int motor) //Поворот влево (<0) вправо (>0) левый мотор -1 правый 1
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
		   
        stops();
        break;
      }
	}

	stops();
	up_global_yaw();
}

void stops()
{	
	analogWrite(SPEED_L, 0);
	analogWrite(SPEED_R, 0);
}
