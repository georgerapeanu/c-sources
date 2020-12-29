using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace wolf3d
{
    class MapLoader
    {
        static string DEBUG_PATH = Directory.GetCurrentDirectory();
        static string BIN_PATH = Directory.GetParent(DEBUG_PATH).ToString();
        static string WOLF3D_PATH = Directory.GetParent(BIN_PATH).ToString();
        static string MAPS_PATH = WOLF3D_PATH + "\\maps\\";


        int height;
        int width;
        double p_x, p_y;
        string[] a = new string[1];

        public MapLoader(string name)
        {
            if (!Directory.Exists(MAPS_PATH))
            {
                System.IO.Directory.CreateDirectory(MAPS_PATH);
            }

            if (!File.Exists(MAPS_PATH + name))
            {
                Console.Clear();
                Console.WriteLine("No map found. Reinstall the project.");
                Console.WriteLine("Press any key to continue...");
                Console.ReadKey();
                Environment.Exit(0);
            }
            
            string[] lines = System.IO.File.ReadAllLines(MAPS_PATH + name);
            string[] tmp = lines[0].Split(' ');

            height = Convert.ToInt32(tmp[0]);
            width = Convert.ToInt32(tmp[1]);

            a = new string[height];

            for (int i = 0;i < height ; i++)
            {
                a[i] = lines[i + 1];
            }

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (a[i][j] == 'x')
                    {
                        p_x = i;
                        p_y = j;
                    }
                }
            }
        }
    }
}
