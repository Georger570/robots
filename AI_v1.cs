using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using System.IO;


public class AI_v1 : MonoBehaviour
{
    //Robot
    public GameObject robot;
    public bool changeFlag = false;
    public float sensorLength = 5.0f;
    //public float sensorLength_LR = 
    public float speed = 10f;
    public float directionValue = 1.0f;
    public float turnValue = 0.0f;
    public float turnSpeed = 50.0f;
    
    //Coordinats
    int x = 0;
    int z = 0;
    int x_direction = 1;
    int z_direction = 0;
    Vector3 movement = new Vector3(0, 0, 0);
    bool WriteFlag = false;

    //Others
    Collider myColloder;
    RaycastHit hit;
    


    void Start()
    {
        File.Delete("pam.txt");
        //File.Create("pam.txt");
        myColloder = transform.GetComponent<Collider>();
    }

    StreamWriter zn;  //Класс для записи в файл
    StreamReader zr;
    FileInfo file = new FileInfo("pam.txt");

    void Update()
    {
        if (Physics.Raycast(transform.position, transform.forward, out hit, (transform.localScale.z)) || !ReadingFromFile(x_direction, z_direction))
        {
            TurnFunction(90);
            //zn.WriteLine("Препятствие");
        }
        //transform.Rotate(Vector3.up * (turnSpeed * turnValue) * Time.deltaTime);
        transform.position += transform.forward * (speed * directionValue) * Time.deltaTime;
        movement += transform.forward * (speed * directionValue) * Time.deltaTime;
        //print(transform.forward * (speed * directionValue) * Time.deltaTime);
        zn = file.AppendText();
        WriteFlag = false;
        if (Math.Abs(movement.x) >= transform.localScale.z)
        {
            if (movement.x < 0)
                movement.x = movement.x + transform.localScale.z;
            else if (movement.x > 0)
                movement.x = movement.x - transform.localScale.z;
            x = x + x_direction;
            z = z + z_direction;
            print(x + " " + z);
            zn.WriteLine(x + ";" + z);
            WriteFlag = true;

        }
        else if (Math.Abs(movement.z) >= transform.localScale.z)
        {
            if (movement.z < 0)
                movement.z = movement.z + transform.localScale.z;
            else if (movement.z > 0)
                movement.z = movement.z - transform.localScale.z;
            x = x + x_direction;
            z = z + z_direction;
            print(x + " " + z);
            zn.WriteLine(x + ";" + z);
            WriteFlag = true;
        }
            
        zn.Close();
    }

    void OnDrawGizmos()
    {
        Gizmos.DrawRay(transform.position, transform.forward * (sensorLength + transform.localScale.z));
        Gizmos.DrawRay(transform.position, -transform.forward * (sensorLength + transform.localScale.z));
        Gizmos.DrawRay(transform.position, transform.right * (sensorLength + transform.localScale.x));
        Gizmos.DrawRay(transform.position, -transform.right * (sensorLength + transform.localScale.x));
    }

    int TurnFunction(int TurnDegrees)
    {
        /*if (hit.collider.tag != "Obstacle" || hit.collider == myColloder)
        {
            return 0;
        }*/
        speed = 0;
        if (!(Physics.Raycast(transform.position, transform.right, out hit, (sensorLength + transform.localScale.x))) && Test())
        {
            transform.Rotate(0, TurnDegrees, 0);
            if (x_direction == 1)
            {
                    x_direction = 0;
                    z_direction = 1;
            }
            else if (z_direction == 1)
            {
                z_direction = 0;
                x_direction = -1;
            }
            else if (x_direction == -1)
            {
                x_direction = 0;
                z_direction = -1;
            }
            else if (z_direction == -1)
            {
                z_direction = 0;
                x_direction = 1;
            }
        }
        else if (!(Physics.Raycast(transform.position, -transform.right, out hit, (sensorLength + transform.localScale.x))) && Test())
        {
            transform.Rotate(0, -TurnDegrees, 0);
            if (x_direction == 1)
            {
                x_direction = 0;
                z_direction = -1;
            }
            else if (z_direction == -1)
            {
                z_direction = 0;
                x_direction = -1;
            }
            else if (x_direction == -1)
            {
                x_direction = 0;
                z_direction = 1;
            }
            else
            {
                z_direction = 0;
                x_direction = 1;
            }
        }
        else if (!(Physics.Raycast(transform.position, -transform.forward, out hit, (sensorLength + transform.localScale.z))) && Test())
        {
            transform.Rotate(0, 2*TurnDegrees, 0);
            if (x_direction == 1)
            {
                x_direction = -1;
            }
            else if (z_direction == -1)
            {
                z_direction = 1;
            }
            else if (x_direction == -1)
            {
                x_direction = 1;
            }
            else
            {
                z_direction = -1;
            }
        }
        else
        {
            speed = 0;
            return 0;
        }
        speed = 10;
        return 1;
    }

    int Sensors()
    {
        if (Physics.Raycast(transform.position, -transform.right, out hit, (transform.localScale.x)))
        {

        }
        if (Physics.Raycast(transform.position, transform.right, out hit, (transform.localScale.x)))
        {
            
        }
        return 1;
    }
    bool ReadingFromFile(int c, int v)
    {
        if (WriteFlag == true)
        {
            zr = file.OpenText();
            string Coord = zr.ReadLine();
            while (Coord != null)
            {
                string[] splitedStr = Coord.Split(';');
                int x_fromFile = int.Parse(splitedStr[0]);
                int z_fromFile = int.Parse(splitedStr[1]);
                if ( ((x + c) == x_fromFile) && ((z+v) == z_fromFile) )
                {
                    zr.Close();
                    return false;
                }
                Coord = zr.ReadLine();
            }
            zr.Close();
        }
        return true;
    }
    bool Test()
    {
        if (x_direction == 1)
        {
            return ReadingFromFile(0, 1);
        }
        else if (z_direction == 1)
        {
            return ReadingFromFile(-1, 0);
        }
        else if (x_direction == -1)
        {
            return ReadingFromFile(0, -1);
        }
        else if (z_direction == -1)
        {
            return ReadingFromFile(1, 0);
        }
        return false;
    }
}
