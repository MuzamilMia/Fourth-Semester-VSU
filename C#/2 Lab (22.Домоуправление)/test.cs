using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HousingManagementSystem
{
    public partial class test : Form
    {
        public test()
        {
            InitializeComponent();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // Move the icon to the right
            pictureBox1.Left += 5;
            pictureBox2.Left += 5;

            // Stop when it reaches the end of the form
            if (pictureBox1.Left > this.Width && pictureBox2.Left > this.Width)
            {
                timer1.Stop();
                pictureBox1.Visible = false;
                pictureBox2.Visible = false;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            pictureBox1.Visible = true;
            pictureBox1.Left = 0; // start from the left edge
            pictureBox2.Visible = true;
            pictureBox2.Left = 0;
            timer1.Start();
        }
    }
}
