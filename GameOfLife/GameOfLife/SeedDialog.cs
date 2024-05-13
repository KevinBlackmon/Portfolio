using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameOfLife
{
    public partial class SeedDialog : Form
    {
        public SeedDialog()
        {
            InitializeComponent();
        }

        private void SeedDialog_Load(object sender, EventArgs e)
        {

        }

        private void Randomizebutton_Click(object sender, EventArgs e)
        {
            Random rng = new Random();
            int num = rng.Next();
            numericUpDownSeed.Value = num;
        }
        public decimal Seed
        {
            get { return numericUpDownSeed.Value; }
            set { numericUpDownSeed.Value = value; }
        }
    }
}
