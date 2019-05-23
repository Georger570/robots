
//==========================================================================================
//|	подключите один мотор к клемме: M1+ и M1- а второй к клемме: M2+ и M2-
//|   Motor shield использует четыре контакта 4, 5, 6, 7 для управления моторами
//|   4 и 7 — для направления, 5 и 6 — для скорости
//==========================================================================================



#include "MovementIntelligence.h"
///////////////////////Only for Qt compiler////////////////////////////////////////

#define INPUT 1
#define OUTPUT 2
#define LOW 0
#define HIGH 1
#define opspeed 5

int digitalRead(int a){}
int digitalWrite(int a, int b){}
void pinMode(int a, int b){}
void delay(int a){}
void analogWrite(int a, int b){}
void delayMicroseconds(int a){}
int pulseIn(int a, int b){}
class Ser{
public:
    static char ad;
    void begin(int a){}
    void print(int a = 1){}
    void print(char* b = &ad){}
};


Ser Serial;
//========================================================================================


//========================================================================================
void MovementIntelligence::Init()
{

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(FRONT_SENSOR, INPUT);
    pinMode(LEFT_SENSOR, INPUT);
    pinMode(RIGHT_SENSOR, INPUT);
    pinMode(SENS_R, INPUT);
    pinMode(SENS_L, INPUT);

    Serial.begin(115200); // открываем последовательный порт
      //Serial.println("Begin init...");


    for (int i = 4; i < 8; i++)  // настраиваем выводы платы 4, 5, 6, 7 на вывод сигналов
        pinMode(i, OUTPUT);

    delay(2000);
}

void MovementIntelligence::read_sens() //Обработка рефлекторов колёс
{
    if (left_status != digitalRead(SENS_L))
    {
        left_status = digitalRead(SENS_L);
        left_motion += dir_left_mov;
    }

    if (right_status != digitalRead(SENS_R))
    {
        right_status = digitalRead(SENS_R);
        right_motion += dir_right_mov;
    }
    setMovement(left_motion);
}

void MovementIntelligence::correct_course_sens(int speed)
{
    read_sens();

    if (left_motion > right_motion)
    {
        analogWrite(SPEED_R, speed);
        analogWrite(SPEED_L, speed - (left_motion - right_motion));
    }
    if (left_motion < right_motion)
    {
        analogWrite(SPEED_R, speed - (right_motion - left_motion));
        analogWrite(SPEED_L, speed);
    }
    if (left_motion == right_motion)
    {
        analogWrite(SPEED_R, speed);
        analogWrite(SPEED_L, speed);
    }

}


int MovementIntelligence::Rangefinder_perquisition(int echoPin)
{
    int distance = 0, duration = 0;
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(4);
    // Теперь установим высокий уровень на пине Trig
    digitalWrite(TRIG_PIN, HIGH);
    // Подождем 10 μs
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    // Узнаем длительность высокого сигнала на пине Echo
    duration = pulseIn(echoPin, HIGH);
    // Рассчитаем расстояние
    distance = duration / 58;
    return distance;
}


//Returning true if distance between obstacle and robot is less than variable
bool MovementIntelligence::IsObstacleWithinReach(int echoPin, int distance)
{
    if (distance < Rangefinder_perquisition(echoPin))
        return false;
    else
        return true;
}

void MovementIntelligence::get_dist() //Опрос дальномеров
{
    distanceFront = Rangefinder_perquisition(FRONT_SENSOR);
    distanceRight = Rangefinder_perquisition(RIGHT_SENSOR);
    distanceLeft = Rangefinder_perquisition(LEFT_SENSOR);
    /*Serial.print("Left / Front / Right");
    Serial.print("\n");
    Serial.print(distanceLeft);
    Serial.print(" / ");
    Serial.print(distanceFront);
    Serial.print(" / ");
    Serial.print(distanceRight);
    Serial.print("\n");*/
}

void MovementIntelligence::run_fb(int dir, int speed) //Движение вперёд (0) назад (1)
{
    if (dir == 0)//forward
    {
        dir_left_mov = 1;
        dir_right_mov = 1;

        digitalWrite(DIR_R, 0);
        digitalWrite(DIR_L, 1);

        analogWrite(SPEED_R, speed);
        analogWrite(SPEED_L, speed);
    }
    else if (dir == 1)//back
    {
        dir_left_mov = -1;
        dir_right_mov = -1;

        digitalWrite(DIR_R, 1);
        digitalWrite(DIR_L, 0);

        analogWrite(SPEED_R, speed);
        analogWrite(SPEED_L, speed);
    }
}

int MovementIntelligence::get_yaw()
{
    if (left_motion > right_motion)
    {
        yaw = (left_motion - right_motion) * 3.60f;//3.6 ok
        return 0;
    }
    if (left_motion < right_motion)
    {
        yaw = (right_motion - left_motion) * -3.60f;
        return 0;
    }
    yaw = 0;
    return 1;
}

void MovementIntelligence::stop()
{
    analogWrite(SPEED_L, 0);
    analogWrite(SPEED_R, 0);
    up_global_yaw();
}

void MovementIntelligence::up_global_yaw()
{
    global_yaw += yaw;
    right_motion = 0;
    left_motion = 0;
    while (global_yaw >= 360)
        global_yaw = global_yaw - 360;
}

//Поворот влево (<0) вправо (>0) левый мотор -1 правый 1
void MovementIntelligence::turn_lr(float angle, int motor, int speed)
{
    if (angle < 0)//left
    {
        dir_left_mov = -1;
        dir_right_mov = 1;

        digitalWrite(DIR_R, 0);
        digitalWrite(DIR_L, 0);
    }

    else if (angle > 0)//right
    {
        dir_left_mov = 1;
        dir_right_mov = -1;

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
        //Serial.print(yaw);
        if (yaw == angle)
        {
            if (angle < 0)
            {
                digitalWrite(DIR_R, 1);
                digitalWrite(DIR_L, 1);
            }
            else
            {
                digitalWrite(DIR_R, 0);
                digitalWrite(DIR_L, 0);
            }
            if (motor == 1)
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

void MovementIntelligence::Turn(int side)
{
    float Angle = 90.0;
    switch (side)
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
        break;
    default:
        if (side == RIGHT)
            turn_lr(Angle, SPEED, -1);
        else if (side == LEFT)
            turn_lr(Angle, SPEED, 1);
        else
        {
            turn_lr(Angle * 2, SPEED, 1);
        }
    }
}

MovementIntelligence::MovementIntelligence(List* List1)
{
    Explored = List1;
}

int MovementIntelligence::getSpeed()
{
    return SPEED;
}

void MovementIntelligence::setMovement(int mov)
{
    movement = mov;
}

int MovementIntelligence::getMovement()
{
    return movement;
}

coord  MovementIntelligence::getFuturePosition(coord direction)
{
    return (direction + CurrentPosition);
}

coord MovementIntelligence::getCurrentPosition() //Получить текущую позицию робота
{
    return CurrentPosition;
}

bool MovementIntelligence::IsObstaclesAround() //Определение, есть ли препятсвие рядом
{
    if (IsObstacleWithinReach(FRONT_SENSOR, DISTANCE) && IsObstacleWithinReach(RIGHT_SENSOR, DISTANCE) && IsObstacleWithinReach(LEFT_SENSOR, DISTANCE))
        return true;
    else return false;
}

bool MovementIntelligence::TryToRegisterMotion(int robot_size) //Определение, прошёл ли робот расстояние, равное длине его корпуса
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

bool MovementIntelligence::CheckSide(int side)
{
    coord side_direction = coord(0,0);
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

bool MovementIntelligence::Emergency()
{
    return true;
}

int MovementIntelligence::TurnFunction()
{
    coord side_direction(0,0);
    if (!IsObstacleWithinReach(RIGHT_SENSOR, DISTANCE)
        && (!CheckSide(RIGHT)))
    {
        direction = Direction_if_TurnRight(direction);
        Turn(RIGHT);
    }
    else if (!IsObstacleWithinReach(LEFT_SENSOR, DISTANCE)
        && (!CheckSide(LEFT)))
    {
        direction = Direction_if_TurnLeft(direction);
        Turn(LEFT);
    }
    return 1;
}
coord MovementIntelligence::Direction_if_TurnRight(coord direction)
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
coord MovementIntelligence::Direction_if_TurnLeft(coord direction)
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
coord MovementIntelligence::Direction_if_TurnAround(coord direction)
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

/////////////////////BackPathing////////////////////////

List* MovementIntelligence::getBackPath(List* Unexplored)
{
    List* Result;

    coord destination = Unexplored -> popTail();
    //WaveStart(getCurrentPosition(), destination, &Map, &&StepMap, Result);
    //PathResult(getCurrentPosition(), destination, Size, &&StepMap, Result)
    return Result;
}

int MovementIntelligence::popGoTo(List* Result, bool* Flag)
{
    int count = 0;
    coord destination = Result->popList();
    while( getFuturePosition(direction) != destination )
        Turn(RIGHT);
    coord position = destination;
    do
    {
        destination = Result->popList();
        count++;
        position = getFuturePosition(position);
    }
    while ( position  == destination || Result->head == NULL );
    if ( Result->head == NULL)
        *Flag = false;
    return count;
}


////////////////////////NOT IN USE//////////////////////

void MovementIntelligence::correct_course_RF(int speed)
{
    get_dist();
    if (distanceFront < 7 && distanceFront>2)
    {
        //Serial.print(distanceFront);
        //Serial.print("\n");
        stop();
        delay(1000);
    }
    if (distanceLeft > distanceRight)
    {
        analogWrite(SPEED_R, speed);
        analogWrite(SPEED_L, speed - 3);
    }
    if (distanceLeft < distanceRight)
    {
        analogWrite(SPEED_R, speed - 3);
        analogWrite(SPEED_L, speed);
    }


    analogWrite(SPEED_R, speed);
    analogWrite(SPEED_L, speed);
}
