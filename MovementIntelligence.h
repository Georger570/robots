#include "coord.h"
#include "list.h"

#define SENS_R       2 //Рефлектор правого колеса
#define SENS_L       3 //Рефлектор левого колеса

#define DIR_R        4 //Направление врещения правого двигателя
#define SPEED_R      5 //Скорость врещения правого двигателя

#define SPEED_L      6 //Скорость врещения левого двигателя
#define DIR_L        7 //Направление врещения левого двигателя

#define RIGHT_SENSOR 8 //Эхо от прового дальномера
#define LEFT_SENSOR  9 //Эхо от левого дальномера
#define FRONT_SENSOR 10//Эхо от переднего дальномера
#define TRIG_PIN     11//Общий триггер для всех дальномеров

#define RIGHT 8 
#define LEFT  9 
#define BACK 12

#define DISTANCE 21

#define SPEED 37

///////////////////////Only for Qt compiler////////////////////////////////////////
int digitalRead(int a);
//========================================================================================

class MovementIntelligence
{

public:
    void Init();
	int getMovement();
	int getSpeed();
	void read_sens();
	void correct_course_sens(int speed);
	bool IsObstacleWithinReach(int echoPin, int distance);
	int Rangefinder_perquisition(int echoPin);
	void get_dist();
	void correct_course_RF(int speed);
	void run_fb(int dir, int speed);
	void Turn(int side);
	void turn_lr(float angle, int motor, int speed = 37);
	void stop();
	MovementIntelligence(List* List1);
	void setMovement(int mov);
    coord  getFuturePosition(coord direction);
	coord getCurrentPosition();
	bool IsObstaclesAround();
	bool TryToRegisterMotion(int robot_size);
	bool CheckSide(int side);
	bool Emergency();
	int TurnFunction();
	coord Direction_if_TurnRight(coord direction);
	coord Direction_if_TurnLeft(coord direction);
	coord Direction_if_TurnAround(coord direction);

    List* getBackPath(List* Unexplored);
    int popGoTo(List* Result, bool* Flag);

	int get_yaw();
	void up_global_yaw();


    coord CurrentPosition = coord(0,0);
    coord direction = coord(1,0);
    List* Explored;


     float speed = 37.0f;

     //Position of Robot
      //Текущая позиция
     //Текущее направление движения робота
     int movement = 0; //Переменная, отвечающая за расстояние, пройденное роботом


     int left_motion = 0;
     int right_motion = 0;

     int left_status = digitalRead(SENS_L);
     int right_status = digitalRead(SENS_R);

     int dir_left_mov = 1;
     int dir_right_mov = 1;

     float yaw = 0; // Курс
     float global_yaw = 0;
     int duration = 0, distanceFront = 0, distanceLeft = 0, distanceRight = 0;

};
