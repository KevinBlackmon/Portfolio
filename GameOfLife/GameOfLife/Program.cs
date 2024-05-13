using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameOfLife
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        class GraphicsPanel : Panel
        {
            public GraphicsPanel()
            {
                this.DoubleBuffered = true;

                this.SetStyle(ControlStyles.ResizeRedraw, true);
            }
        }
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}