
namespace GameOfLife
{
    partial class SeedDialog
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
            this.Okbutton = new System.Windows.Forms.Button();
            this.Cancelbutton = new System.Windows.Forms.Button();
            this.numericUpDownSeed = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.Randomizebutton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSeed)).BeginInit();
            this.SuspendLayout();
            // 
            // Okbutton
            // 
            this.Okbutton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Okbutton.Location = new System.Drawing.Point(35, 87);
            this.Okbutton.Name = "Okbutton";
            this.Okbutton.Size = new System.Drawing.Size(75, 23);
            this.Okbutton.TabIndex = 0;
            this.Okbutton.Text = "OK";
            this.Okbutton.UseVisualStyleBackColor = true;
            // 
            // Cancelbutton
            // 
            this.Cancelbutton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Cancelbutton.Location = new System.Drawing.Point(136, 87);
            this.Cancelbutton.Name = "Cancelbutton";
            this.Cancelbutton.Size = new System.Drawing.Size(75, 23);
            this.Cancelbutton.TabIndex = 1;
            this.Cancelbutton.Text = "Cancel";
            this.Cancelbutton.UseVisualStyleBackColor = true;
            // 
            // numericUpDownSeed
            // 
            this.numericUpDownSeed.Location = new System.Drawing.Point(70, 27);
            this.numericUpDownSeed.Maximum = new decimal(new int[] {
            -1486618624,
            232830643,
            0,
            0});
            this.numericUpDownSeed.Minimum = new decimal(new int[] {
            -1486618624,
            232830643,
            0,
            -2147483648});
            this.numericUpDownSeed.Name = "numericUpDownSeed";
            this.numericUpDownSeed.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownSeed.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(32, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(32, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Seed";
            // 
            // Randomizebutton
            // 
            this.Randomizebutton.Location = new System.Drawing.Point(196, 27);
            this.Randomizebutton.Name = "Randomizebutton";
            this.Randomizebutton.Size = new System.Drawing.Size(75, 23);
            this.Randomizebutton.TabIndex = 4;
            this.Randomizebutton.Text = "Randomize";
            this.Randomizebutton.UseVisualStyleBackColor = true;
            this.Randomizebutton.Click += new System.EventHandler(this.Randomizebutton_Click);
            // 
            // SeedDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(283, 127);
            this.Controls.Add(this.Randomizebutton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numericUpDownSeed);
            this.Controls.Add(this.Cancelbutton);
            this.Controls.Add(this.Okbutton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SeedDialog";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "SeedDialog";
            this.Load += new System.EventHandler(this.SeedDialog_Load);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownSeed)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Okbutton;
        private System.Windows.Forms.Button Cancelbutton;
        private System.Windows.Forms.NumericUpDown numericUpDownSeed;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Randomizebutton;
    }
}