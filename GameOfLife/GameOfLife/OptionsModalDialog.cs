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
    public partial class OptionsModalDialog : Form
    {
        public OptionsModalDialog()
        {
            InitializeComponent();
        }

        private void OptionsModalDialog_Load(object sender, EventArgs e)
        {

        }

        private void OKbutton_Click(object sender, EventArgs e)//ok button function
        {

        }

        private void Cancelbutton_Click(object sender, EventArgs e)//cancel button function
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
        public decimal Miliseconds
        {
            get
            {
                return numericUpDownMiliseconds.Value;
            }
            set
            {
                numericUpDownMiliseconds.Value = value;
            }
        }
        public decimal WidthCells
        {
            get
            {
                return numericUpDownWidthCells.Value;
            }
            set
            {
                numericUpDownWidthCells.Value = value;
            }
        }
        public decimal HeightCells
        {
            get
            {
                return numericUpDownHeightCells.Value;
            }
            set
            {
                numericUpDownHeightCells.Value = value;
            }
        }
    }
}
