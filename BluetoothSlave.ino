#include <SoftwareSerial.h> 
#define SIZE 2
char a;
char Map[SIZE][SIZE];
int i,j=0;
void setup() {
  Serial.begin(9600);  // подключаем последовательный порт
}

void loop() {
  if (Serial.available()) // проверяем, поступают ли какие-то команды
      {
            Map[i][j] = static_cast<char>(Serial.read()); // переменная val равна полученной команде
            Serial.println(Map[i][j]);
            Serial.println("");
            j = j + ((++i)/SIZE);
            i = (i) % SIZE;
      }
      /*if (j==2)
      {
        Serial.println("//////////////////////////////");
        for (i= 0; i < SIZE; ++i)
        {
          for (j= 0; j < SIZE; ++j)
          {
            Serial.println(Map[i][j]);
          }
        }
        j=0;
      }*/
}
