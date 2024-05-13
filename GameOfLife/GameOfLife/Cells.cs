using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameOfLife
{
    class Cells
    {
        private bool[,] CellsSize = new bool[10,10];
        private int GenerationsAlive = 0;

        Cells()
        {

        }
        
        Cells(int rows, int cols)
        {
            bool[,] CellsSize = new bool[rows, cols];
        }

        public void SetCellsSize(int rows, int cols)
        {
            bool[,] CellsSize = new bool[rows, cols];
        }

        public int GenTimeAlive()
        {
            return GenerationsAlive;
        }

        public void IncermentGen()
        {
            GenerationsAlive++;
        }
    }
}
