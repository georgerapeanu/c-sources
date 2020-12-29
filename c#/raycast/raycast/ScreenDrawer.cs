using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;
using System.Diagnostics;

namespace raycast
{
    class ScreenDrawer
    {
        public RichTextBox console;
        private MapLoader map;
        private int height = 150;
        private int width = 970;
        private double fov_w = 1;
        private double fov_h = 1.57;
        static double eps = 1e-1;
        public ScreenDrawer(System.Drawing.Size size, MapLoader map)
        {
            this.console = new RichTextBox();
            this.console.Size = size;
            this.console.Top = 0;
            this.console.Left = 0;
            this.console.BackColor = Color.Black;
            this.console.ForeColor = Color.White;
            this.console.WordWrap = false;
            this.console.Font = new Font("Consolas", 1);
            this.console.KeyPress += new System.Windows.Forms.KeyPressEventHandler(key_press);
            this.map = map;
            this.draw();
        }

        protected void draw()
        {
            double hh = Convert.ToDouble(height);
            double ww = Convert.ToDouble(width);
            for (int i = 0; i < height; i++)
            {
                string tmp = "";
                for (int j = 0; j < width; j++)
                {
                    double alfa = ((height - i) / hh - 0.5) * fov_h;
                    double beta = ((j) / ww - 0.5) * fov_w;
                    double xx = 0, yy = 0, zz = 0;
                    map.cast(alfa, beta,ref xx,ref yy,ref zz);
                    //Debug.Write(Convert.ToString(i) + " " + Convert.ToString(j) + " " + Convert.ToString(xx) + " " + Convert.ToString(yy) + " " + Convert.ToString(zz) + "\n");
                    if (zz <= 0)
                    {
                        tmp += ".";
                    }
                    else if (zz > 2)
                    {
                        tmp += " ";
                    }
                    else
                    {
                        int a = Convert.ToInt32(Math.Abs(Math.Round(xx) - xx) < eps);
                        int b = Convert.ToInt32(Math.Abs(Math.Round(yy) - yy) < eps);
                        int c = Convert.ToInt32(Math.Round(zz) != 1.0 && (Math.Abs(Math.Round(zz) - zz) < eps));
                        if (a + b + c >= 2)
                        {
                            tmp += "#";
                        }
                        else
                        {
                            tmp += " ";
                        }
                    }
                }
                tmp += "\n";
                console.AppendText(tmp);
            }
        }

        protected void key_press(object sender, KeyPressEventArgs e)
        {
            map.move(e.KeyChar);
            this.console.Clear();
            this.draw();
        }
    }
}
