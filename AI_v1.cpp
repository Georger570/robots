public class AI_v1
{
    //Robot
    int TurnCount = 0;
    WorkWithFiles Explored = new WorkWithFiles("pam.txt");
    WorkWithFiles Unexplored = new WorkWithFiles("tif.txt");
    MovementIntelligence MovementAI;
    public bool changeFlag = false;
    public float sensorLength = 2.0f;
    public int robot_size;
    public float speed = 10f;
    public float speedValue = 10f;
    public float directionValue = 1.0f;
    int XX = 0;
    int ZZ = 0;

    //public float sensorLength_LR = 
    public float turnValue = 0.0f;
    public float turnSpeed = 50.0f;
    public int turnAngle = 90;
    //Coordinats

    bool WriteFlag = false;
    bool BackFlag = true;
    int AnotherFlag = 0;
    //Others
    Collider myColloder;
    //RaycastHit hit;
     
    //Map
    Map map;


    void Start()
    {
        MovementAI = new MovementIntelligence(Explored, Unexplored);
        MovementAI.Init(transform);
        myColloder = transform.GetComponent<Collider>();
        robot_size = (int) 1;
        map = new Map(MovementAI, MovementAI.hit, transform);
    }

    void Update()
    {
        Sensors(MovementAI.getCurrentPosition());
        map.arrformap(MovementAI.getCurrentPosition(), MovementAI.direction, MovementAI.speed);
        if (BackFlag == false)
        {
            if (XX == MovementAI.getCurrentPosition().x && ZZ == MovementAI.getCurrentPosition().z)
                BackFlag = true;
            else
                MovementAI.IllBeBack(turnAngle, ref BackFlag,ref XX,ref ZZ);
        }
        if (MovementAI.IsObstaclesAround())
        {
            MovementAI.speed = 0;
            MovementAI.TurnFunction(turnAngle, ref BackFlag);
            TurnCount++;
        }
        else if (Explored.isAlreadyinFile(MovementAI.getFuturePosition()) == true && BackFlag == true)
        {
            TurnCount++;
            MovementAI.speed = 0;
            MovementAI.TurnFunction(turnAngle, ref BackFlag);
        }
        else
        {
            TurnCount = 0;
            MovementAI.speed = speedValue;
            MovementAI.Moition();
        }
        if (MovementAI.TryToRegisterMotion(robot_size))
        {
            Explored.AppendLine(MovementAI.getCurrentPosition());
            Unexplored.ExcludeMatchingFromFile(MovementAI.getCurrentPosition());
        }
    }

    int Sensors(coordinates position)
    {
        coord_direction side_direction;
        if (!Physics.Raycast(transform.position, transform.right, out MovementAI.hit, (transform.localScale.x)) && !MovementAI.CheckSide(transform.right))
        {
            side_direction = MovementAI.Direction_if_TurnRight(MovementAI.direction);
            if (!Unexplored.isAlreadyinFile(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition())) && !Explored.isAlreadyinFile(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition())))
            {
                Unexplored.AppendLine(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition()));
            }
        }
        if (!Physics.Raycast(transform.position, -transform.right, out MovementAI.hit, (transform.localScale.x)) && !MovementAI.CheckSide(-transform.right))
        {
            side_direction = MovementAI.Direction_if_TurnLeft(MovementAI.direction);
            if (!Unexplored.isAlreadyinFile(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition())) && !Explored.isAlreadyinFile(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition())))
            {
                Unexplored.AppendLine(MovementAI.getPosition(side_direction, MovementAI.getCurrentPosition()));
            }
        }
        return 1;
    }
}
