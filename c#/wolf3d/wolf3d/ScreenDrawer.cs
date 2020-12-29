using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace wolf3d
{
    class ScreenDrawer
    {
        int width, height;

        public ScreenDrawer(int height,int width)
        {
            this.height = height;
            this.width = width;
            Console.SetWindowSize(width,height);
            /*for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    Console.Write('#');
                }
                if (i != height - 1)
                {
                    Console.Write('\n');
                }
            }*/
        }

    }
}
