using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class FoundForRobots : MonoBehaviour {

	public GameObject robot;
	float a = 1;
	float a1 = 1;
	int x = 0;
	int z = 0;
    public bool changeFlag = false;

	void Start () 
	{

		File.Delete ("pam.txt");
	
	}


	void Update () 
	{
		Vector3 offset = new Vector3 (0.0f ,  0.0f ,  0.0f);
		Vector3 offset1 = new Vector3 (5.0f ,  5.0f ,  5.0f);
		Vector3 t = (a*offset) - robot.transform.position;
		/*print (t.z + ">" + offset1.z+a);
		print (t.x + ">QQ" + offset1.x+a);*/
		if( (t.x>a*offset1.x || t.x<-a*offset1.x||t.z>a1*offset1.z || t.z<-a1*offset1.z))
			
		{
		//	System.Threading.Thread.Sleep(500);

			print ("Я ЗАШЕЛ!!!!! !   "+a);
			if ((t.x>a*offset1.x || t.x<-a*offset1.x) )
            {
				x++;
				a++;

			}
			if (t.z>a1*offset1.z || t.z<-a1*offset1.z)
            {
				z++;
				a1++;
			}
            {
                StreamWriter zn;  //Класс для записи в файл
                FileInfo file = new FileInfo("pam.txt");
                zn = file.AppendText(); //Дописываем инфу в файл, если файла не существует он создастся
                zn.WriteLine("(" + x + ";" + z + ")"); //Записываем в файл текст из текстового поля
                zn.Close(); // Закрываем файл
            }
		//	print (t.x + ">" + offset1.x+a);
			/*print (t.z + ">" + offset1.z+a);
			print (t.x + ">" + offset1.x+a);
			print (t.z + ">" + offset1.z+a);
			print(a +"T = " + t);
			print("Теперь начальное положение" +a);
			print("Brobot.transform.position = " + robot.transform.position);
			print("T в цикле" + t);*/


		}
	
	}
}