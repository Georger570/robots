//Robot
MovementIntelligence MovementAI;
bool changeFlag = false;
float sensorLength = 2.0f;
int robot_size = 21;
int turnAngle = 90;
//Coordinates
bool WriteFlag = false;
bool BackFlag = true;
int AnotherFlag = 0;

    //RaycastHit hit;
     
    //Map
    Map map;

	//Lists
	List Explored;
	List Unexplored;

    void Start()
    {
        MovementAI = new MovementIntelligence(Explored);
        map = new Map(MovementAI, MovementAI.hit, transform);
    }

    void loop()
    {
		correct_course_sens(MovementAI.speed);
		read_sens();     
		if(MovementAI.movement == StepReach)
		{
			Sensors(MovementAI.getCurrentPosition());
        map.arrformap(MovementAI.getCurrentPosition(), MovementAI.direction, MovementAI.speed);
        if (MovementAI.IsObstaclesAround())
        {
            stop();
            MovementAI.TurnFunction(turnAngle);
        }
        else if (Explored.isAlreadyInList(MovementAI.getFuturePosition()) == true)
        {
            stop();
            MovementAI.TurnFunction(turnAngle);
        }
        if (MovementAI.TryToRegisterMotion(robot_size))
        {
			Explored.AppendLine(MovementAI.getCurrentPosition());           
        }
		}
		
    }

    int Sensors(coord position)
    {
        coord side_direction;
        if (!IsObstacleWithinReach(RightSensor, distance) && !MovementAI.CheckSide(transform.right))
        {
            side_direction = MovementAI.Direction_if_TurnRight(MovementAI.direction);
            if (!Unexplored.isAlreadyinList(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition())) && !Explored.isAlreadyInList(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition())))
            {
                Unexplored.AppendLine(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition()));
            }
        }
        if (!IsObstacleWithinReach(RightSensor, distance) && !MovementAI.CheckSide(-transform.right))
        {
            side_direction = MovementAI.Direction_if_TurnLeft(MovementAI.direction);
            if (!Unexplored.isAlreadyInList(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition())) && !Explored.isAlreadyInList(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition())))
            {
                Unexplored.AppendLine(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition()));
            }
        }
        return 1;
    }
}
