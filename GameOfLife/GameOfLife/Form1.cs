using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameOfLife
{
    public partial class Form1 : Form
    {
        // The universe array
        bool[,] universe = new bool[Properties.Settings.Default.UniverseWidth, Properties.Settings.Default.UniverseHeight];
        bool[,] ScratchPad = new bool[Properties.Settings.Default.UniverseWidth, Properties.Settings.Default.UniverseHeight];
        //Creating a gobal varibale for the seed so I can update it for the bottom of the window
        int Seed;
        bool isToroidal = true;
        //created a variable for the living cells
        int LivingCells = 0;
        // Drawing colors
        Color gridColor = Properties.Settings.Default.GridColor;
        Color cellColor = Properties.Settings.Default.CellColor;
        Color numberColor = Properties.Settings.Default.numberColor;
        Color HUDColor = Properties.Settings.Default.HUDColor;
        // The Timer class
        Timer timer = new Timer();

        // Generation count
        int generations = 0;

        public Form1()
        {
            InitializeComponent();

            // Setup the timer
            timer.Interval = Properties.Settings.Default.TimerMiliseconds; // milliseconds
            timer.Tick += Timer_Tick;
            timer.Enabled = false; // timer does not start running
            //Reading in the settings
            graphicsPanel1.BackColor = Properties.Settings.Default.BackColor;
            toolStripStatusLabelInterval.Text = "Interval = " + timer.Interval.ToString();
        }

        // Calculate the next generation of cells
        private void NextGeneration()
        {
            if (isToroidal)
            {


                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    // Iterate through the universe in the x, left to right
                    for (int y = 0; y < universe.GetLength(1); y++)
                    {
                        if (universe[x, y] == true)
                        {
                            if ((CountNeighborsToroidal(x, y) < 2) || (CountNeighborsToroidal(x, y) > 3))
                            {
                                ScratchPad[x, y] = false;
                            }
                            if ((CountNeighborsToroidal(x, y) == 2) || (CountNeighborsToroidal(x, y) == 3))
                            {
                                ScratchPad[x, y] = true;
                            }
                        }
                        if (universe[x, y] == false)
                        {
                            if (CountNeighborsToroidal(x, y) == 3)
                            {
                                ScratchPad[x, y] = true;
                            }
                        }
                    }
                }
            }
            else
            {
                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    // Iterate through the universe in the x, left to right
                    for (int y = 0; y < universe.GetLength(1); y++)
                    {
                        if (universe[x, y] == true)
                        {
                            if ((CountingNeighborsFinite(x, y) < 2) || (CountingNeighborsFinite(x, y) > 3))
                            {
                                ScratchPad[x, y] = false;
                            }
                            if ((CountingNeighborsFinite(x, y) == 2) || (CountingNeighborsFinite(x, y) == 3))
                            {
                                ScratchPad[x, y] = true;
                            }
                        }
                        if (universe[x, y] == false)
                        {
                            if (CountingNeighborsFinite(x, y) == 3)
                            {
                                ScratchPad[x, y] = true;
                            }
                        }
                    }
                }
            }
            for (int x = 0; x < ScratchPad.GetLength(0); x++)
            {
                for (int y = 0; y < ScratchPad.GetLength(1); y++)
                {
                    universe[x, y] = ScratchPad[x, y];
                }
            }

            // Increment generation count
            generations++;

            //Setting the living cell count
            LivingCells = CountingLivingCells();
            // Update status strip generations
            toolStripStatusLabelGenerations.Text = "Generations = " + generations.ToString();
            toolStripStatusLabelSeed.Text = "Seed = " + Seed.ToString();
            toolStripStatusLabelLivingCells.Text = "Living Cells = " + LivingCells.ToString();
            toolStripStatusLabelInterval.Text = "Interval = " + timer.Interval.ToString();
            graphicsPanel1.Invalidate();
        }
        // The event called by the timer every Interval milliseconds.
        private void Timer_Tick(object sender, EventArgs e)
        {
                NextGeneration();
        }

        private void graphicsPanel1_Paint(object sender, PaintEventArgs e)
        {
            // Calculate the width and height of each cell in pixels
            // CELL WIDTH = WINDOW WIDTH / NUMBER OF CELLS IN X
            int cellWidth = graphicsPanel1.ClientSize.Width / universe.GetLength(0);
            // CELL HEIGHT = WINDOW HEIGHT / NUMBER OF CELLS IN Y
            int cellHeight = graphicsPanel1.ClientSize.Height / universe.GetLength(1);

            // A Pen for drawing the grid lines (color, width)
            Pen gridPen = new Pen(gridColor, 1);

            // A Brush for filling living cells interiors (color)
            Brush cellBrush = new SolidBrush(cellColor);

            //Creating a new solid brush to help change the color of the numbers
            Brush numberBrush = new SolidBrush(numberColor);

            //Creating a new solid brush for the HUD
            Brush HUDBrush = new SolidBrush(HUDColor);

            // Iterate through the universe in the y, top to bottom
            for (int y = 0; y < universe.GetLength(1); y++)
            {
                // Iterate through the universe in the x, left to right
                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    // A rectangle to represent each cell in pixels
                    Rectangle cellRect = Rectangle.Empty;
                    cellRect.X = x * cellWidth;
                    cellRect.Y = y * cellHeight;
                    cellRect.Width = cellWidth;
                    cellRect.Height = cellHeight;
                    //Added this to center the numbers in the rectangle
                    StringFormat stringFormat = new StringFormat();
                    stringFormat.Alignment = StringAlignment.Center;
                    stringFormat.LineAlignment = StringAlignment.Center;

                    //Added this for the HUD format
                    StringFormat stringFormat1 = new StringFormat();
                    stringFormat1.Alignment = StringAlignment.Near;
                    stringFormat1.LineAlignment = StringAlignment.Near;

                    // Fill the cell with a brush if alive
                    if (universe[x, y] == true)
                    {
                        e.Graphics.FillRectangle(cellBrush, cellRect);
                    }

                    // Outline the cell with a pen
                    //added a if statement to get rid of the zeros on each cells
                    if (isToroidal)
                    {
                        if (!(numberColor == Properties.Settings.Default.BackColor))
                        {
                            if (CountNeighborsToroidal(x, y) > 0)
                            {
                                e.Graphics.DrawString(CountNeighborsToroidal(x, y).ToString(), graphicsPanel1.Font, numberBrush, cellRect, stringFormat);
                            }
                        }
                        e.Graphics.DrawRectangle(gridPen, cellRect.X, cellRect.Y, cellRect.Width, cellRect.Height);
                    }
                    else
                    {
                        if (!(numberColor == Properties.Settings.Default.BackColor))
                        {
                            if (CountingNeighborsFinite(x, y) > 0)
                            {
                                e.Graphics.DrawString(CountingNeighborsFinite(x, y).ToString(), graphicsPanel1.Font, numberBrush, cellRect, stringFormat);
                            }
                        }
                        e.Graphics.DrawRectangle(gridPen, cellRect.X, cellRect.Y, cellRect.Width, cellRect.Height);
                    }
                    //Drawing the HUD
                    int width = universe.GetLength(0);
                    int height = universe.GetLength(1);

                    if (isToroidal)
                    {
                        e.Graphics.DrawString("Generation(s) " + generations.ToString() + '\n' +
                        "Cell Count " + LivingCells.ToString() + '\n' +
                       "Universe Size: {Width = " + width.ToString() + " , Height = " + height.ToString() + "}" + '\n' +
                      "Boundary Type: Toroidal", graphicsPanel1.Font, HUDBrush, graphicsPanel1.ClientRectangle, stringFormat1);
                    }
                    else
                    {
                        e.Graphics.DrawString("Generation(s) " + generations.ToString() + '\n' +
                       "Cell Count " + LivingCells.ToString() + '\n' +
                      "Universe Size: {Width = " + width.ToString() + " , Height = " + height.ToString() + "}" + '\n' +
                     "Boundary Type: Finite", graphicsPanel1.Font, HUDBrush, graphicsPanel1.ClientRectangle, stringFormat1);
                    }
                }
            }

            // Cleaning up pens and brushes
            gridPen.Dispose();
            cellBrush.Dispose();
        }

        private void graphicsPanel1_MouseClick(object sender, MouseEventArgs e)
        {
            // If the left mouse button was clicked
            if (e.Button == MouseButtons.Left)
            {
                // Calculate the width and height of each cell in pixels
                int cellWidth = graphicsPanel1.ClientSize.Width / universe.GetLength(0);
                int cellHeight = graphicsPanel1.ClientSize.Height / universe.GetLength(1);

                // Calculate the cell that was clicked in
                // CELL X = MOUSE X / CELL WIDTH
                int x = e.X / cellWidth;
                // CELL Y = MOUSE Y / CELL HEIGHT
                int y = e.Y / cellHeight;

                // Toggle the cell's state
                universe[x, y] = !universe[x, y];

                //Having this update on every click
                LivingCells = CountingLivingCells();
                toolStripStatusLabelLivingCells.Text = "Living Cells = " + LivingCells.ToString();
                toolStripStatusLabelInterval.Text = "Interval = " + timer.Interval.ToString();

                // Tell Windows you need to repaint
                graphicsPanel1.Invalidate();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void newToolStripMenuItem_Click_1(object sender, EventArgs e)//new button function
        {
            // Iterate through the universe in the y, top to bottom
            for (int x = 0; x < universe.GetLength(0); x++)
            {
                // Iterate through the universe in the x, left to right
                for (int y = 0; y < universe.GetLength(1); y++)
                {
                    universe[x, y] = false;
                    ScratchPad[x, y] = false;
                }
            }
            generations = 0;
            Seed = 0;
            LivingCells = 0;
            toolStripStatusLabelGenerations.Text = "Generations = " + generations.ToString();
            toolStripStatusLabelSeed.Text = "Seed = " + Seed.ToString();
            toolStripStatusLabelLivingCells.Text = "Living Cells = " + LivingCells.ToString();
            toolStripStatusLabelInterval.Text = "Interval = " + timer.Interval.ToString();
            graphicsPanel1.Invalidate();
        }

        private void newToolStripButton_Click(object sender, EventArgs e)
        {
            for (int y = 0; y < universe.GetLength(1); y++)
            {
                // Iterate through the universe in the x, left to right
                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    universe[x, y] = false;
                    ScratchPad[x, y] = false;
                }
            }
            generations = 0;
            Seed = 0;
            LivingCells = 0;
            toolStripStatusLabelGenerations.Text = "Generations = " + generations.ToString();
            toolStripStatusLabelSeed.Text = "Seed = " + Seed.ToString();
            toolStripStatusLabelLivingCells.Text = "Living Cells = " + LivingCells.ToString();
            toolStripStatusLabelInterval.Text = "Interval = " + timer.Interval.ToString();
            graphicsPanel1.Invalidate();
        }
        //************************************************//
        private void openToolStripMenuItem_Click(object sender, EventArgs e) //Open button function
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|Cells|*.cells";
            dlg.FilterIndex = 2;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                StreamReader reader = new StreamReader(dlg.FileName);
                int maxHeight = 0;
                int maxWidth = 0;
                int yPos = 0;
                while (!reader.EndOfStream)
                {
                    string row = reader.ReadLine();
                    if (String.IsNullOrEmpty(row))
                    {
                        continue;
                    }
                    if (row.Contains("!"))
                    {
                        continue;
                    }
                    if (!row.Contains("!"))
                    {
                        maxHeight++;
                    }
                    maxWidth = row.Length;
                }
                universe = new bool[maxWidth, maxHeight];
                ScratchPad = new bool[maxWidth, maxHeight];
                reader.BaseStream.Seek(0, SeekOrigin.Begin);
                while (!reader.EndOfStream)
                {
                    string row = reader.ReadLine();
                    if (row.Contains("!"))
                    {
                        continue;
                    }
                    else if (!row.Contains("!"))
                    {
                        if (!String.IsNullOrEmpty(row))
                        {
                            for (int xPos = 0; xPos < row.Length; xPos++)
                            {
                                if (row[xPos].Equals('O'))
                                {
                                    //Ask about how to make them correspond with universe
                                    universe[xPos, yPos] = true;
                                }
                                if (row[xPos].Equals('.'))
                                {
                                    //Ask about how to make them correspond with universe
                                    universe[xPos, yPos] = false;
                                }
                            }
                            yPos++;
                        }
                    }
                }
                reader.Close();
                graphicsPanel1.Invalidate();
            
        }
        }
        private void openToolStripButton_Click(object sender, EventArgs e)//open button function
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "All Files|*.*|Cells|*.cells";
            dlg.FilterIndex = 2;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                StreamReader reader = new StreamReader(dlg.FileName);
                int maxHeight = 0;
                int maxWidth = 0;
                int yPos = 0;
                while (!reader.EndOfStream)
                {
                    string row = reader.ReadLine();
                    if (String.IsNullOrEmpty(row))
                    {
                        continue;
                    }
                    if (row.Contains("!"))
                    {
                        continue;
                    }
                    if (!row.Contains("!"))
                    {
                        maxHeight++;
                    }
                    maxWidth = row.Length;
                }
                universe = new bool[maxWidth, maxHeight];
                ScratchPad = new bool[maxWidth, maxHeight];
                reader.BaseStream.Seek(0, SeekOrigin.Begin);
                while (!reader.EndOfStream)
                {
                    string row = reader.ReadLine();
                    if (row.Contains("!"))
                    {
                        continue;
                    }
                    else if (!row.Contains("!"))
                    {
                        if (!String.IsNullOrEmpty(row))
                        {
                            for (int xPos = 0; xPos < row.Length; xPos++)
                            {
                                if (row[xPos].Equals('O'))
                                {
                                    //Ask about how to make them correspond with universe
                                    universe[xPos, yPos] = true;
                                }
                                if (row[xPos].Equals('.'))
                                {
                                    //Ask about how to make them correspond with universe
                                    universe[xPos, yPos] = false;
                                }
                            }
                            yPos++;
                        }
                    }
                }
                reader.Close();
                graphicsPanel1.Invalidate();
            }
        }
        //************************************************//
        private void saveToolStripMenuItem_Click(object sender, EventArgs e) //Save button function
        {

        }

        private void saveToolStripButton_Click(object sender, EventArgs e)
        {

        }
        //************************************************//

        private int CountNeighborsToroidal(int x, int y)
        {
            int count = 0;
            int xLen = universe.GetLength(0);
            int yLen = universe.GetLength(1);
            for (int xOffset = -1; xOffset <= 1; xOffset++)
            {
                for (int yOffset = -1; yOffset <= 1; yOffset++)
                {
                    int xCheck = x + xOffset;
                    int yCheck = y + yOffset;
                    if (!(xOffset == 0) || !(yOffset == 0))
                    {

                        if (xCheck < 0)
                        {
                            xCheck = xLen - 1;
                        }
                        if (xCheck >= xLen)
                        {
                            xCheck = 0;
                        }
                        if (yCheck < 0)
                        {
                            yCheck = yLen - 1;
                        }
                        if (yCheck >= yLen)
                        {
                            yCheck = 0;
                        }
                        if (universe[xCheck, yCheck] == true)
                        {
                            count++;
                        }
                    }
                }
            }
            return count;
        }
        private int CountingNeighborsFinite(int x, int y)
        {
            int count = 0;
            int xLen = universe.GetLength(0);
            int yLen = universe.GetLength(1);
            for (int xOffset = -1; xOffset <= 1; xOffset++)
            {
                for (int yOffset = -1; yOffset <= 1; yOffset++)
                {
                    int xCheck = x + xOffset;
                    int yCheck = y + yOffset;
                    if (!(xOffset == 0) || !(yOffset == 0))
                    {

                        if (xCheck < 0)
                        {
                            continue;
                        }
                        if (xCheck >= xLen)
                        {
                            continue;
                        }
                        if (yCheck < 0)
                        {
                            continue;
                        }
                        if (yCheck >= yLen)
                        {
                            continue;
                        }
                        if (universe[xCheck, yCheck] == true)
                        {
                            count++;
                        }
                    }
                }
            }
            return count;
        }

        private void toolStripButton1_Click(object sender, EventArgs e) //Start button function
        {
            timer.Enabled = true;
        }

        private void toolStripButton2_Click(object sender, EventArgs e) //Pause button function
        {
            timer.Enabled = false;
        }

        private void toolStripButton3_Click(object sender, EventArgs e)//Next button function
        {
            NextGeneration();
            graphicsPanel1.Invalidate();
        }

        private void GenerateRandomUniverse()
        {
            //intialize a Random variable
            Random rand = new Random();
            //Goes through the rows
            for (int x = 0; x < universe.GetLength(0); x++)
            {
                //Goes trough the colums
                for (int y = 0; y < universe.GetLength(1); y++)
                {
                    //intiate num with the random variable set with a range
                    int num = rand.Next(0, 3);
                    //turning the ceels on and off 
                    if (num == 0)
                    {
                        universe[x, y] = true;
                    }
                    else
                    {
                        universe[x, y] = false;
                    }
                }
            }
        }
        //Method created to use the seed to generate a random grid
        private void GenerateRandomUniverse(int seed)
        {
            //intialize a Random variable
            Random rand = new Random(seed);
            //Goes through the rows
            for (int x = 0; x < universe.GetLength(0); x++)
            {
                //Goes trough the colums
                for (int y = 0; y < universe.GetLength(1); y++)
                {
                    //intiate num with the random variable set with a range
                    int num = rand.Next(0, 3);
                    //turning the ceels on and off 
                    if (num == 0)
                    {
                        universe[x, y] = true;
                    }
                    else
                    {
                        universe[x, y] = false;
                    }
                }
            }
        }

        private void randomizeToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)//SaveAs buttom function
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "All Files|*.*|Cells|*.cells";
            dlg.FilterIndex = 2; dlg.DefaultExt = "cells";
            if (DialogResult.OK == dlg.ShowDialog())
            {
                StreamWriter writer = new StreamWriter(dlg.FileName);
                writer.WriteLine();
                for (int x = 0; x < universe.GetLength(0); x++)
                {
                    String currentRow = string.Empty;
                    for (int y = 0; y < universe.GetLength(1); y++)
                    {
                        if (universe[x, y] == true)
                        {
                            currentRow = currentRow + 'O';
                        }
                        else if (universe[x, y] == false)
                        {
                            currentRow = currentRow + '.';
                        }
                    }
                    writer.WriteLine(currentRow);
                }
                writer.Close();
            }
        }

        private void currentSeedToolStripMenuItem_Click(object sender, EventArgs e)
        {
            GenerateRandomUniverse();
            graphicsPanel1.Invalidate();
        }
        private void fromSeedToolStripMenuItem_Click(object sender, EventArgs e)//From seed buttom function
        {
            SeedDialog seed = new SeedDialog();
            seed.ShowDialog();
            GenerateRandomUniverse((int)seed.Seed);
            Seed = (int)seed.Seed;
            graphicsPanel1.Invalidate();
        }

        private void cellColorToolStripMenuItem_Click(object sender, EventArgs e)//Cell color function
        {
            ColorDialog dlg = new ColorDialog();
            dlg.Color = cellColor;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                cellColor = dlg.Color;
                graphicsPanel1.Invalidate();
            }
            //dlg.ShowDialog();
        }

        private void backColorToolStripMenuItem_Click(object sender, EventArgs e)//Grid color changer function
        {
            ColorDialog dlg = new ColorDialog();
            dlg.Color = gridColor;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                gridColor = dlg.Color;
                graphicsPanel1.Invalidate();
            }
            //dlg.ShowDialog();

        }
        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {

            graphicsPanel1.Invalidate();
        }

        private void toggleGridToolStripMenuItem_Click(object sender, EventArgs e)//Grid line on and off button
        {
            if (!(gridColor == Color.Transparent))
            {
                gridColor = Color.Transparent;
            }
            else
            {
                gridColor = Properties.Settings.Default.GridColor;
            }
            graphicsPanel1.Invalidate();
        }

        private void toggleNeighborCountToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!(numberColor == Color.Transparent))
            {
                numberColor = Color.Transparent;
            }
            else
            {
                numberColor = Properties.Settings.Default.numberColor;
            }
            graphicsPanel1.Invalidate();
        }

        private void backColorToolStripMenuItem1_Click(object sender, EventArgs e)//back color button
        {
            ColorDialog dlg = new ColorDialog();
            if (DialogResult.OK == dlg.ShowDialog())
            {
                graphicsPanel1.BackColor = dlg.Color;
                graphicsPanel1.Invalidate();
            }
        }

        private void settingsToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
        //Creating a method to calculate how many cells are alive at an instance
        private int CountingLivingCells()
        {
            int cells = 0;
            for (int xPos = 0; xPos < universe.GetLength(0); xPos++)
            {
                for (int yPos = 0; yPos < universe.GetLength(1); yPos++)
                {
                    if (universe[xPos, yPos] == true)
                    {
                        cells++;
                    }
                }
            }
            return cells;
        }

        private void colorToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void backColorToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            ColorDialog dlg = new ColorDialog();
            if (DialogResult.OK == dlg.ShowDialog())
            {
                graphicsPanel1.BackColor = dlg.Color;
                graphicsPanel1.Invalidate();
            }
        }

        private void cellColorToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            ColorDialog dlg = new ColorDialog();
            dlg.Color = cellColor;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                cellColor = dlg.Color;
                graphicsPanel1.Invalidate();
            }
        }

        private void gridColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog dlg = new ColorDialog();
            dlg.Color = gridColor;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                gridColor = dlg.Color;
                graphicsPanel1.Invalidate();
            }
        }

        private void optionsToolStripMenuItem1_Click_1(object sender, EventArgs e)//options button
        {
            OptionsModalDialog dlg = new OptionsModalDialog();
            //Still need to figure out how to set the timer interval
            //to set the varibale in the numericUpDown for the milliseconds
            //dlg.Miliseconds = timer.Interval;
            int width = (int)dlg.WidthCells;
            int height = (int)dlg.HeightCells;
            if (DialogResult.OK == dlg.ShowDialog())
            {
                timer.Interval = (int)dlg.Miliseconds;
                toolStripStatusLabelInterval.Text = "Interval = " + timer.Interval.ToString();
                //Added this if statement so that if you do not change the grid them 
                //it will not erase what is on the grid when you change the interval
                if (!(width == (int)dlg.WidthCells) || !(height == (int)dlg.HeightCells))
                {
                    universe = new bool[(int)dlg.WidthCells, (int)dlg.HeightCells];
                    ScratchPad = new bool[(int)dlg.WidthCells, (int)dlg.HeightCells];
                    graphicsPanel1.Invalidate();
                }
            }
            //dlg.ShowDialog();
        }

        private void resetToolStripMenuItem_Click_1(object sender, EventArgs e)//reset button
        {
            ////I am setting the default grid a 10 by 10 with black line color and grey cell color
            //gridColor = Color.Black;
            //cellColor = Color.Gray;
            //graphicsPanel1.BackColor = Color.White;
            //universe = new bool[10, 10];
            //ScratchPad = new bool[10, 10];
            Properties.Settings.Default.Reset();

            timer.Interval = Properties.Settings.Default.TimerMiliseconds;
            graphicsPanel1.BackColor = Properties.Settings.Default.BackColor;
            gridColor = Properties.Settings.Default.GridColor;
            cellColor = Properties.Settings.Default.CellColor;
            numberColor = Properties.Settings.Default.numberColor;
            universe = new bool[Properties.Settings.Default.UniverseWidth, Properties.Settings.Default.UniverseHeight];
            ScratchPad = new bool[Properties.Settings.Default.UniverseWidth, Properties.Settings.Default.UniverseHeight];
            graphicsPanel1.Invalidate();
        }

        private void Form1_FontChanged(object sender, EventArgs e)
        {

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)//form closed button
        {
            Properties.Settings.Default.TimerMiliseconds = timer.Interval;
            Properties.Settings.Default.BackColor = graphicsPanel1.BackColor;
            Properties.Settings.Default.GridColor = gridColor;
            Properties.Settings.Default.CellColor = cellColor;
            Properties.Settings.Default.numberColor = numberColor;
            Properties.Settings.Default.UniverseWidth = universe.GetLength(0);
            Properties.Settings.Default.UniverseHeight = universe.GetLength(1);
            Properties.Settings.Default.Save();
        }

        private void reloadToolStripMenuItem_Click(object sender, EventArgs e)//reload button
        {
            Properties.Settings.Default.Reload();

            graphicsPanel1.BackColor = Properties.Settings.Default.BackColor;
            gridColor = Properties.Settings.Default.GridColor;
            cellColor = Properties.Settings.Default.CellColor;
            numberColor = Properties.Settings.Default.numberColor;
            universe = new bool[Properties.Settings.Default.UniverseWidth, Properties.Settings.Default.UniverseHeight];
            ScratchPad = new bool[Properties.Settings.Default.UniverseWidth, Properties.Settings.Default.UniverseHeight];
            graphicsPanel1.Invalidate();
        }

        private void toggleGridToolStripMenuItem_CheckStateChanged(object sender, EventArgs e)
        {

        }

        private void toggleGridToolStripMenuItem1_Click(object sender, EventArgs e)//Context senstive menuitem toggle
        {
            if (!(gridColor == Color.Transparent))
            {
                gridColor = Color.Transparent;
            }
            else
            {
                gridColor = Properties.Settings.Default.GridColor;
            }
            graphicsPanel1.Invalidate();
        }

        private void hUDToolStripMenuItem_Click(object sender, EventArgs e)//HUD controls
        {
            if (!(HUDColor == Color.Transparent))
            {
                HUDColor = Color.Transparent;
            }
            else
            {
                HUDColor = Properties.Settings.Default.HUDColor;
            }
            graphicsPanel1.Invalidate();
        }

        private void hUDToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (!(HUDColor == Color.Transparent))
            {
                HUDColor = Color.Transparent;
            }
            else
            {
                HUDColor = Properties.Settings.Default.HUDColor;
            }
            graphicsPanel1.Invalidate();
        }

        private void toggleNeighborCountToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (!(gridColor == Color.Transparent))
            {
                gridColor = Color.Transparent;
            }
            else
            {
                gridColor = Properties.Settings.Default.GridColor;
            }
            graphicsPanel1.Invalidate();
        }

        private void tororidalToolStripMenuItem_Click(object sender, EventArgs e)
        {
            isToroidal = !isToroidal;
        }
    }
}
