#include "MovementIntelligence.h"
#include "coord.h"
#include "array.h"
#include "list.h"
#include "Memlib.h"
#include "wavealgorithm.h"

//Robot
int robot_size = 21;

bool deadendFlag;
int back_count;

//Coordinates
const int StepReach = 11;

//Map
//Map map;

int Sensors();

//Lists
List Explored;
List Unexplored;
List* Result;

MovementIntelligence MovementAI(&Explored);

void Start()
{
    deadendFlag = false;
    back_count = 0;
    //MovementAI = new MovementIntelligence(Explored);
    //map = new Map(MovementAI, MovementAI.hit, transform);
    MovementAI.run_fb(1, SPEED);

}

void loop()
{
    MovementAI.correct_course_sens(SPEED);
    MovementAI.read_sens();
    if(MovementAI.getMovement() == StepReach)
    {
        MovementAI.stop();
        if (deadendFlag == false)
        {
            Sensors();
            //map.arrformap(MovementAI.getCurrentPosition(), MovementAI.direction, MovementAI.speed);
            if (MovementAI.IsObstaclesAround())
            {
                deadendFlag = true;
                MovementAI.getBackPath(&Unexplored);
                back_count = MovementAI.popGoTo(Result, &deadendFlag);
            }
            if(MovementAI.IsObstacleWithinReach(FRONT_SENSOR, DISTANCE))
            {
                MovementAI.TurnFunction();
            }
            else if (Explored.isAlreadyInList(MovementAI.getFuturePosition(MovementAI.direction)) == true)
            {
                MovementAI.TurnFunction();
            }
        }
        if (MovementAI.TryToRegisterMotion(robot_size))
        {
            Explored.addInBeginOfList(MovementAI.getCurrentPosition());
        }
        else if (back_count > 0)
        {
            back_count--;
        }
        else
        {
            back_count = MovementAI.popGoTo(Result, &deadendFlag);
        }
        MovementAI.run_fb(1, SPEED);
    }
}

int Sensors()
{
    coord side_direction(0,0);
    if (!MovementAI.IsObstacleWithinReach(RIGHT_SENSOR, DISTANCE) && !MovementAI.CheckSide(RIGHT))
    {
        side_direction = MovementAI.Direction_if_TurnRight(MovementAI.direction);
        if (!Unexplored.isAlreadyInList(MovementAI.getFuturePosition(side_direction)) && !Explored.isAlreadyInList(MovementAI.getFuturePosition(side_direction)))
        {
            Unexplored.addInBeginOfList(MovementAI.getFuturePosition(side_direction));
        }
    }
    if (!MovementAI.IsObstacleWithinReach(RIGHT_SENSOR, DISTANCE) && !MovementAI.CheckSide(RIGHT))
    {
        side_direction = MovementAI.Direction_if_TurnLeft(MovementAI.direction);
        if (!Unexplored.isAlreadyInList(MovementAI.getFuturePosition(side_direction)) && !Explored.isAlreadyInList(MovementAI.getFuturePosition(side_direction)))
        {
            Unexplored.addInBeginOfList(MovementAI.getFuturePosition(side_direction));
        }
    }
    return 1;
}
