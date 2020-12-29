using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace raycast
{
    public partial class Form1 : Form
    {

        MapLoader map;
        ScreenDrawer screen;

        public Form1()
        {
            InitializeComponent();
            map = new MapLoader("2.txt");
            screen = new ScreenDrawer(this.ClientSize,map);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.Controls.Add(screen.console);
           // this.Resize += Form1_Resize;
        }

    }
}
