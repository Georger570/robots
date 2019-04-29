#include "coord.h"
#include "List.h"
#include "MovementIntelligence.cpp"

class MovementIntelligence
{
	public:

		float speed = 37.0f;

		//Position of Robot
        coord CurrentPosition; //Текущая позиция
        coord direction; //Текущее направление движения робота
        int movement = 0; //Переменная, отвечающая за расстояние, пройденное роботом

		//List
		List* Explored

		int left_motion=0;
		int right_motion=0;

		int left_status = digitalRead(SENS_L);
		int right_status = digitalRead(SENS_R);

		int dir_left_mov=1;
		int dir_right_mov=1;

		float yaw=0; // Курс
		float global_yaw=0;
		int duration=0, distanceFront=0,distanceLeft=0,distanceRight=0;
		   
		MovementIntelligence(List* List1);
		void Init();


		void read_sens();
		void correct_course_sens(int speed);
		bool IsObstacleWithinReach(int echoPin, int distance);
		int Rangefinder_perquisition(int echoPin);
		void get_dist();
		void correct_course_RF(int speed);
		void run_fb(int dir, int speed);
		void Turn(int side);
		void turn_lr(float angle, int speed=37, int motor);
		void stop();
		void MovementIntelligence(List* List1);
		void setMovement(int mov);
        coord  getFuturePosition();
		coord getCurrentPosition();
		bool IsObstaclesAround();
        bool TryToRegisterMotion(int robot_size);
        bool CheckSide(int side);
        bool Emergency();
        int TurnFunction();
        coord Direction_if_TurnRight(coord direction);
        coord Direction_if_TurnLeft(coord direction);
        coord Direction_if_TurnAround(coord direction);

		int get_yaw();
		void up_global_yaw();
}
