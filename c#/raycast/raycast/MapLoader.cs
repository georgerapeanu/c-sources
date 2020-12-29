using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace raycast
{
    class MapLoader
    {
        static string DEBUG_PATH = Directory.GetCurrentDirectory();
        static string BIN_PATH = Directory.GetParent(DEBUG_PATH).ToString();
        static string WOLF3D_PATH = Directory.GetParent(BIN_PATH).ToString();
        static string MAPS_PATH = WOLF3D_PATH + "\\maps\\";

        double eps = 1e-6;
        double angle_eps = 5e-2;
        double move_eps = 1e-1;

        int height;
        int width;
        double p_x, p_y;
        double ang;
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

            move_eps *= height / 5;

            a = new string[height];
            ang = 0;

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
                        p_x = i + 0.5;
                        p_y = j + 0.5;
                    }
                }
            }
            ang = 0;
        }
        public void cast(double alfa, double beta,ref double x,ref double y,ref double z)
        {
            beta += ang;
            double dx, dy, dz;
            dz = Math.Sin(alfa);
            dy = Math.Cos(alfa) * Math.Sin(beta);
            dx = -Math.Cos(alfa) * Math.Cos(beta);

            x = p_x;
            y = p_y;
            z = 1;
          //  Debug.Write("angles " + Convert.ToString(alfa) + " " + Convert.ToString(beta) + "\n");
          //  Debug.Write("here we are " + Convert.ToString(x) + " " + Convert.ToString(y) + " " + Convert.ToString(z) + "\n");
          //  Debug.Write("here we are2 " + Convert.ToString(dx) + " " + Convert.ToString(dy) + " " + Convert.ToString(dz) + "\n");

            while (true)
            {
                int xx = Convert.ToInt32(Math.Floor(x));
                int yy = Convert.ToInt32(Math.Floor(y));
                if (z > 2 || z < 0 || xx < 0 || xx >= height || yy < 0 || yy >= width || a[xx][yy] == '#')
                {
                    break;
                }

                double k = 1e9;

                if (dx < 0)
                {
                    k = Math.Min(k, (xx - x) / dx);
                }
                else if (dx > 0)
                {
                    k = Math.Min(k, (xx + 1 - x) / dx);
                }

                if (dy < 0)
                {
                    k = Math.Min(k, (yy - y) / dy);
                }
                else if (dy > 0)
                {
                    k = Math.Min(k, (yy + 1 - y) / dy);
                }
                k += eps;
                x += k * dx;
                y += k * dy;
                z += k * dz;
            }
        }

        public void move(char key)
        {
            if (key == 'a')
            {
                ang -= angle_eps;
            }
            else if (key == 'd')
            {
                ang += angle_eps;
            }
            else if (key == 'w')
            {
                double xx = 0, yy = 0, zz = 0;
                cast(0, 0, ref xx, ref yy, ref zz);
                if (Math.Pow(xx - p_x, 2) + Math.Pow(yy - p_y, 2) > move_eps + eps)
                {
                    p_x -= move_eps * Math.Cos(ang);
                    p_y += move_eps * Math.Sin(ang);
                }
            }
            else
            {
                double xx = 0, yy = 0, zz = 0;
                cast(0, Math.Acos(-1), ref xx, ref yy, ref zz);
                if (Math.Pow(xx - p_x, 2) + Math.Pow(yy - p_y, 2) > move_eps + eps)
                {
                    p_x += move_eps * Math.Cos(ang);
                    p_y -= move_eps * Math.Sin(ang);
                }
            }
        }
    }
}
