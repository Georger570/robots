int* getBackPath(List Explored, List Unexplored)
{
	coord destination = Unexplored.popTail();	
	WaveStart(getCurrentPosition(), destination, &Map, &&StepMap, Result);
	PathResult(getCurrentPosition(), destination, Size, &&StepMap, Result)
	return Result;	 
}

int popGoTo(int* Result)
{
	int count = 0;	
	coord destination = Result.popList();	
	while( getFuturePosition() != destination )
		Turn();
	coord position = destination;
	do
	{		
		destination = Result.popList();
		count++;
		position = getFuturePosition(position);
	}
	while ( position  == destination );
	return count;
}


//////////////////////////////////////////////////
// Get point of destination
// Turn to direction of the point
// Move to the point
// The End
//////////////////////////////////////////////////

