using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace wolf3d
{
    class Program
    {
        static void Main(string[] args)
        {
            //ScreenDrawer game = new ScreenDrawer(50, 100);
            MapLoader tmp = new MapLoader("1.txt");
            Console.ReadKey();
        }
    }
}
