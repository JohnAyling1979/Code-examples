namespace Assignment3
{
    partial class Form1
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.sqlText = new System.Windows.Forms.TextBox();
            this.executeButton = new System.Windows.Forms.Button();
            this.output = new System.Windows.Forms.ListBox();
            this.clearButton = new System.Windows.Forms.Button();
            this.exitButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Rockwell", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(145, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(261, 36);
            this.label1.TabIndex = 7;
            this.label1.Text = "Department Data";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(105, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Enter SQL command";
            // 
            // sqlText
            // 
            this.sqlText.Location = new System.Drawing.Point(117, 46);
            this.sqlText.Name = "sqlText";
            this.sqlText.Size = new System.Drawing.Size(334, 20);
            this.sqlText.TabIndex = 1;
            this.sqlText.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Enter_Pressed);
            // 
            // executeButton
            // 
            this.executeButton.Location = new System.Drawing.Point(457, 44);
            this.executeButton.Name = "executeButton";
            this.executeButton.Size = new System.Drawing.Size(75, 23);
            this.executeButton.TabIndex = 2;
            this.executeButton.Text = "Execute";
            this.executeButton.UseVisualStyleBackColor = true;
            this.executeButton.Click += new System.EventHandler(this.ExecuteButton_Click);
            // 
            // output
            // 
            this.output.BackColor = System.Drawing.Color.Black;
            this.output.Font = new System.Drawing.Font("Arial monospaced for SAP", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.output.ForeColor = System.Drawing.Color.Lime;
            this.output.FormattingEnabled = true;
            this.output.HorizontalScrollbar = true;
            this.output.ItemHeight = 12;
            this.output.Location = new System.Drawing.Point(13, 73);
            this.output.Name = "output";
            this.output.Size = new System.Drawing.Size(519, 184);
            this.output.TabIndex = 5;
            this.output.TabStop = false;
            // 
            // clearButton
            // 
            this.clearButton.Location = new System.Drawing.Point(15, 268);
            this.clearButton.Name = "clearButton";
            this.clearButton.Size = new System.Drawing.Size(520, 23);
            this.clearButton.TabIndex = 3;
            this.clearButton.Text = "Clear";
            this.clearButton.UseVisualStyleBackColor = true;
            this.clearButton.Click += new System.EventHandler(this.ClearButton_Click);
            // 
            // exitButton
            // 
            this.exitButton.Location = new System.Drawing.Point(237, 297);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(75, 23);
            this.exitButton.TabIndex = 4;
            this.exitButton.Text = "Exit";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.ExitButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.CornflowerBlue;
            this.ClientSize = new System.Drawing.Size(544, 332);
            this.ControlBox = false;
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.clearButton);
            this.Controls.Add(this.output);
            this.Controls.Add(this.executeButton);
            this.Controls.Add(this.sqlText);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "Assignment 3";
            this.Load += new System.EventHandler(this.Form1_Load_1);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox sqlText;
        private System.Windows.Forms.Button executeButton;
        private System.Windows.Forms.ListBox output;
        private System.Windows.Forms.Button clearButton;
        private System.Windows.Forms.Button exitButton;
    }
}

