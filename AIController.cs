using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;


public class AIController : MonoBehaviour {


	public float sensorLength =  2.0f;
	public float speed = 10f;
	public float directionValue = 1.0f;
	public float turnValue = 0.0f;
	public float turnSpeed = 50.0f;
	Collider myColloder;

	public GameObject robot;

	void Start () 
	{
		myColloder = transform.GetComponent<Collider> ();
	}

	void Update () 
	{
		RaycastHit hit;
		int flag = 0;

		//Правый сенсор
		/*if (Physics.Raycast (transform.position, transform.right, out hit, (sensorLength + transform.localScale.x))) 
		{
			if (hit.collider.tag != "Obstacle" || hit.collider == myColloder) 
			{
				return;
			}
			turnValue -= 1;
			flag++;
		}

		//Левый сенсор
		if (Physics.Raycast (transform.position, -transform.right, out hit, (sensorLength + transform.localScale.x))) 
		{
			if (hit.collider.tag != "Obstacle" || hit.collider == myColloder) 
			{
				return;
			}
			turnValue += 1;
			flag++;
		}*/

		//Передний сенсор
		if (Physics.Raycast (transform.position, transform.forward, out hit, (sensorLength + transform.localScale.z))) 
		{
			if (hit.collider.tag != "Obstacle" || hit.collider == myColloder) 
			{
				return;
			}

			if (directionValue == 1.0f) 
			{
				//directionValue = -1;
				//turnValue -= 107f;
				//Vector3 t = robot.transform.Rotate.y((90,0,0));
				Vector3 t = new Vector3 (90 , 0 , 0);
				transform.Rotate(0 , 90 , 0);
			}
			flag++;
			Debug.Log ("Wall");
			StreamWriter zn;  //Класс для записи в файл
			FileInfo file = new FileInfo("pam.txt");
			zn = file.AppendText(); //Дописываем инфу в файл, если файла не существует он создастся
			zn.WriteLine("Препятствие"); //Записываем в файл текст из текстового поля
			zn.Close(); // Закрываем файл
		}

		//Задний сенсор
		if (Physics.Raycast (transform.position, -transform.forward, out hit, (sensorLength + transform.localScale.z))) 
		{
			if (hit.collider.tag != "Obstacle" || hit.collider == myColloder) 
			{
				return;
			}

			if (directionValue == -1.0f) 
			{
				directionValue = 1;
				turnValue += 112f;
			}
			flag++;
		}

		if (flag == 0) 
		{
			turnValue = 0;
		}

		transform.Rotate (Vector3.up * (turnSpeed * turnValue) * Time.deltaTime);

		transform.position += transform.forward * (speed * directionValue ) * Time.deltaTime;
	}

	void OnDrawGizmos()
	{
		Gizmos.DrawRay (transform.position, transform.forward * (sensorLength + transform.localScale.z));
		Gizmos.DrawRay (transform.position, -transform.forward * (sensorLength + transform.localScale.z));
		Gizmos.DrawRay (transform.position, transform.right * (sensorLength + transform.localScale.x));
		Gizmos.DrawRay (transform.position, -transform.right * (sensorLength + transform.localScale.x));
	}
}
