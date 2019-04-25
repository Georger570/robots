#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // указываем пины rx и tx соответственно
const int size = 2;
char MapOne[size][size];
int MapTwo[size][size];
int MapThree[size][size];
int MapFour[size][size];
String gg = "1111010100101001010100101010101010100101010";
void setup()  {
  pinMode(4,INPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  for(int i=0; i <size; i++)
  {
    for(int j = 0; j <size; j++)
    {
      MapOne[i][j] = '1';
      //MapTwo[i][j] = 0;
      //MapThree[i][j] = 1;
      //MapFour[i][j] = 0;
    }
  }
  for(int i = 0; i<size ; ++i)
  {
     for(int j = 0; j<size ; ++j)
    {
        mySerial.write(static_cast<int>(MapOne[i][j]));
    }
  }
}

void loop() 
{   
   
}
