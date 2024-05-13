
namespace GameOfLife
{
    partial class OptionsModalDialog
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.OKbutton = new System.Windows.Forms.Button();
            this.Cancelbutton = new System.Windows.Forms.Button();
            this.numericUpDownWidthCells = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownHeightCells = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.numericUpDownMiliseconds = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWidthCells)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownHeightCells)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMiliseconds)).BeginInit();
            this.SuspendLayout();
            // 
            // OKbutton
            // 
            this.OKbutton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.OKbutton.Location = new System.Drawing.Point(99, 161);
            this.OKbutton.Name = "OKbutton";
            this.OKbutton.Size = new System.Drawing.Size(75, 23);
            this.OKbutton.TabIndex = 0;
            this.OKbutton.Text = "OK";
            this.OKbutton.UseVisualStyleBackColor = true;
            this.OKbutton.Click += new System.EventHandler(this.OKbutton_Click);
            // 
            // Cancelbutton
            // 
            this.Cancelbutton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Cancelbutton.Location = new System.Drawing.Point(191, 161);
            this.Cancelbutton.Name = "Cancelbutton";
            this.Cancelbutton.Size = new System.Drawing.Size(75, 23);
            this.Cancelbutton.TabIndex = 1;
            this.Cancelbutton.Text = "Cancel";
            this.Cancelbutton.UseVisualStyleBackColor = true;
            this.Cancelbutton.Click += new System.EventHandler(this.Cancelbutton_Click);
            // 
            // numericUpDownWidthCells
            // 
            this.numericUpDownWidthCells.Location = new System.Drawing.Point(163, 64);
            this.numericUpDownWidthCells.Name = "numericUpDownWidthCells";
            this.numericUpDownWidthCells.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownWidthCells.TabIndex = 2;
            this.numericUpDownWidthCells.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // numericUpDownHeightCells
            // 
            this.numericUpDownHeightCells.Location = new System.Drawing.Point(163, 90);
            this.numericUpDownHeightCells.Name = "numericUpDownHeightCells";
            this.numericUpDownHeightCells.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownHeightCells.TabIndex = 4;
            this.numericUpDownHeightCells.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(145, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Timer Inverval in Milliseconds";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(146, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Width of the Universe in Cells";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 92);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(131, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Height of Universe in Cells";
            // 
            // numericUpDownMiliseconds
            // 
            this.numericUpDownMiliseconds.Location = new System.Drawing.Point(163, 38);
            this.numericUpDownMiliseconds.Maximum = new decimal(new int[] {
            276447232,
            23283,
            0,
            0});
            this.numericUpDownMiliseconds.Name = "numericUpDownMiliseconds";
            this.numericUpDownMiliseconds.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownMiliseconds.TabIndex = 8;
            this.numericUpDownMiliseconds.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // OptionsModalDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(333, 203);
            this.Controls.Add(this.numericUpDownMiliseconds);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numericUpDownHeightCells);
            this.Controls.Add(this.numericUpDownWidthCells);
            this.Controls.Add(this.Cancelbutton);
            this.Controls.Add(this.OKbutton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "OptionsModalDialog";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "OptionsModalDialog";
            this.Load += new System.EventHandler(this.OptionsModalDialog_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownWidthCells)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownHeightCells)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMiliseconds)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button OKbutton;
        private System.Windows.Forms.Button Cancelbutton;
        private System.Windows.Forms.NumericUpDown numericUpDownWidthCells;
        private System.Windows.Forms.NumericUpDown numericUpDownHeightCells;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown numericUpDownMiliseconds;
    }
}