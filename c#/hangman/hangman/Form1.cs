using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace hangman
{
    public partial class Form1 : Form
    {
        Button[] letters;
        String[] words = { "abecedar", "scoala", "carantina", "informatica", "analiza", "imposibil" };
        String chosenWord;
        int lives;

        private String process_word(String s)
        {
            String ans = "";

            foreach(char c in s){
                if (c == s[0] || c == s[s.Length - 1])
                {
                    ans += c;
                }
                else
                {
                    ans += "_";
                }
            }
            return ans;
        }

        private String reveal(String s,char c)
        {
            String ans = "";
            for (int i = 0; i < chosenWord.Length;i++ )
            {
                if (chosenWord[i] == c)
                {
                    ans += c;
                }
                else
                {
                    ans += s[i];
                }
            }
            return ans;
        }

        private void Lose(){
            this.label3.Text = "you lost";
            this.label1.Text = chosenWord;
            foreach (Button b in letters)
            {
                b.Enabled = false;
            }
        }

        private void Win()
        {
            this.label3.Text = "you won";
            foreach (Button b in letters)
            {
                b.Enabled = false;
            }
        }

        private void click_letter(object sender,EventArgs e)
        {
            char c = ((Button)sender).Text[0];
            ((Button)sender).Enabled = false;
            String s = reveal(this.label1.Text, c);
            if (s == this.label1.Text)
            {
                lives--;
                this.label2.Text = lives.ToString();
                if (lives == 0)
                {
                    Lose();
                }
            }
            else
            {
                this.label1.Text = s;
                if (this.label1.Text.Contains('_') == false)
                {
                    Win();
                }
            }
        }

        public Form1()
        {
            letters = new Button['z' - 'a' + 1];
            lives = 3;
            int i = 0, j = 0;
            int posx = 10;
            int posy = 40;
            int m = 5;
            int h = 40;
            int w = 40;
            int l_cnt = 6;
            for (int x = 0; x <= 'z' - 'a'; x++)
            {
                letters[x] = new Button();
                letters[x].Location = new Point(i * (h + m) + posx, j * (w + m) + posy);
                letters[x].Height = h;
                letters[x].Width = w;
                letters[x].Text = (Convert.ToChar(x + 'a')).ToString();
                letters[x].Click += (sender, e) => { click_letter(sender, e); };  
                this.Controls.Add(letters[x]);
                j = j + (i + 1) / l_cnt;
                i = (i + 1) % l_cnt;
            }
            InitializeComponent();
            chosenWord = words[(new Random()).Next(words.Length)];
            this.label1.Text = process_word(chosenWord);
            this.label2.Text = (lives).ToString();
            letters[chosenWord[0] - 'a'].Enabled = false;
            letters[chosenWord[chosenWord.Length - 1] - 'a'].Enabled = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Application.Restart();
            Environment.Exit(0);
        }
    }
}
