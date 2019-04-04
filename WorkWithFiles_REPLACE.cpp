class WorkWithFiles // But without files :^(
{
    public string FileName = "";
    FileInfo file;
    StreamWriter Writer;
    StreamReader Reader;
	
    public WorkWithFiles(string Name)
    {
        FileName = Name;
        File.Delete(FileName);
        file = new FileInfo(FileName);
        Writer = file.AppendText();
        Writer.Close();
    }

    public void AppendLine(coordinates position)
    {
        Writer = file.AppendText();
        Writer.WriteLine(position.x + ";" + position.z);
        Writer.Close();
    }

    public string ReadLine()
    {
        Reader = file.OpenText();
        string Str = Reader.ReadLine();
        Reader.Close();
        return Str;
    }

    public bool isAlreadyinFile(coordinates position)
    {
        string NextCoord = position.x + ";" + position.z;
        Reader = file.OpenText();
        string CoordFromFile = Reader.ReadLine();
        while (CoordFromFile != null)
        {
            //string[] splitedStr = Coord.Split(';');
            //int x_fromFile = int.Parse(splitedStr[0]);
            //int z_fromFile = int.Parse(splitedStr[1]);
            //if (((x + direction.x) == x_fromFile) && ((z + direction.z) == z_fromFile))
            if (NextCoord == CoordFromFile)
            {
                Reader.Close();
                return true;
            }
            CoordFromFile = Reader.ReadLine();
        }
        Reader.Close();
        return false;
    }

        /*public bool WriteInFile(ref Vector3 movement, coord_direction direction, ref int x, ref int z, float robot_size) //transform.localScale.z
        {
            if (Math.Abs(movement.x) >= robot_size)
            {
                if (movement.x < 0)
                    movement.x = movement.x + robot_size;
                else if (movement.x > 0)
                    movement.x = movement.x - robot_size;
                x = x + direction.x;
                z = z + direction.z;
                //print(x + " " + z);
                AppendLine(x, z);
                //WriteFlag = true;

            }
            else if (Math.Abs(movement.z) >= robot_size)
            {
                if (movement.z < 0)
                    movement.z = movement.z + robot_size;
                else if (movement.z > 0)
                    movement.z = movement.z - robot_size;
                x = x + direction.x;
                z = z + direction.z;
                //print(x + " " + z);
                AppendLine(x, z);
                //WriteFlag = true;
            }
            return true;
        }*/
    public void ExcludeMatchingFromFile(coordinates position)
    {
        FileInfo AnotherOne = new FileInfo("tif1.txt");
        Reader = file.OpenText();
        Writer = AnotherOne.AppendText();
        string Coord = Reader.ReadLine();
        while (Coord != null)
        {
        string[] splitedStr = Coord.Split(';');
            int x_fromFile = int.Parse(splitedStr[0]);
            int z_fromFile = int.Parse(splitedStr[1]);
            if ((position.x == x_fromFile) && (position.z == z_fromFile))
            {
                //zr.Close();
                Coord = Reader.ReadLine();
                continue;
                //var lines = System.IO.File.ReadAllLines("tif.txt");
                //System.IO.File.WriteAllLines("tif.txt", lines.Skip(count).ToArray());
            }
            Writer.WriteLine(Coord);
            Coord = Reader.ReadLine();
        }
        Reader.Close();
        Writer.Close();
        AnotherOne.Replace("tif.txt", "tif_backup.txt");
        File.Delete("tif1.txt");
    }

}
