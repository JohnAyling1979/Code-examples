using System.Drawing;

namespace Assignment4
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.mainChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.bubbleRB = new System.Windows.Forms.RadioButton();
            this.pieRB = new System.Windows.Forms.RadioButton();
            this.columnRB = new System.Windows.Forms.RadioButton();
            this.barRB = new System.Windows.Forms.RadioButton();
            this.exitButton = new System.Windows.Forms.Button();
            this.clearButton = new System.Windows.Forms.Button();
            this.userButton = new System.Windows.Forms.Button();
            this.randomButton = new System.Windows.Forms.Button();
            this.fileButton = new System.Windows.Forms.Button();
            this.chooseButton = new System.Windows.Forms.Button();
            this.userValue = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.countLabel = new System.Windows.Forms.Label();
            this.fileLabel = new System.Windows.Forms.Label();
            this.chartLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.mainChart)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainChart
            // 
            chartArea1.Name = "ChartArea1";
            this.mainChart.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.mainChart.Legends.Add(legend1);
            this.mainChart.Location = new System.Drawing.Point(12, 70);
            this.mainChart.Name = "mainChart";
            this.mainChart.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.EarthTones;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Bar;
            series1.IsXValueIndexed = true;
            series1.Legend = "Legend1";
            series1.Name = "Series";
            this.mainChart.Series.Add(series1);
            this.mainChart.Size = new System.Drawing.Size(400, 380);
            this.mainChart.TabIndex = 0;
            this.mainChart.Text = "chart";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.bubbleRB);
            this.groupBox1.Controls.Add(this.pieRB);
            this.groupBox1.Controls.Add(this.columnRB);
            this.groupBox1.Controls.Add(this.barRB);
            this.groupBox1.Location = new System.Drawing.Point(559, 70);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(116, 117);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Chart Options";
            // 
            // bubbleRB
            // 
            this.bubbleRB.AutoSize = true;
            this.bubbleRB.Location = new System.Drawing.Point(7, 92);
            this.bubbleRB.Name = "bubbleRB";
            this.bubbleRB.Size = new System.Drawing.Size(86, 17);
            this.bubbleRB.TabIndex = 3;
            this.bubbleRB.TabStop = true;
            this.bubbleRB.Text = "Bubble Chart";
            this.bubbleRB.UseVisualStyleBackColor = true;
            this.bubbleRB.Click += new System.EventHandler(this.ChangeChart);
            // 
            // pieRB
            // 
            this.pieRB.AutoSize = true;
            this.pieRB.Location = new System.Drawing.Point(7, 68);
            this.pieRB.Name = "pieRB";
            this.pieRB.Size = new System.Drawing.Size(68, 17);
            this.pieRB.TabIndex = 2;
            this.pieRB.TabStop = true;
            this.pieRB.Text = "Pie Chart";
            this.pieRB.UseVisualStyleBackColor = true;
            this.pieRB.Click += new System.EventHandler(this.ChangeChart);
            // 
            // columnRB
            // 
            this.columnRB.AutoSize = true;
            this.columnRB.Location = new System.Drawing.Point(7, 44);
            this.columnRB.Name = "columnRB";
            this.columnRB.Size = new System.Drawing.Size(88, 17);
            this.columnRB.TabIndex = 1;
            this.columnRB.TabStop = true;
            this.columnRB.Text = "Column Chart";
            this.columnRB.UseVisualStyleBackColor = true;
            this.columnRB.Click += new System.EventHandler(this.ChangeChart);
            // 
            // barRB
            // 
            this.barRB.AutoSize = true;
            this.barRB.Location = new System.Drawing.Point(7, 20);
            this.barRB.Name = "barRB";
            this.barRB.Size = new System.Drawing.Size(69, 17);
            this.barRB.TabIndex = 0;
            this.barRB.TabStop = true;
            this.barRB.Text = "Bar Chart";
            this.barRB.UseVisualStyleBackColor = true;
            this.barRB.Click += new System.EventHandler(this.ChangeChart);
            // 
            // exitButton
            // 
            this.exitButton.Location = new System.Drawing.Point(559, 429);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(110, 25);
            this.exitButton.TabIndex = 2;
            this.exitButton.Text = "Exit";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.ExitButton_Click);
            // 
            // clearButton
            // 
            this.clearButton.Location = new System.Drawing.Point(559, 400);
            this.clearButton.Name = "clearButton";
            this.clearButton.Size = new System.Drawing.Size(110, 25);
            this.clearButton.TabIndex = 3;
            this.clearButton.Text = "Clear";
            this.clearButton.UseVisualStyleBackColor = true;
            this.clearButton.Click += new System.EventHandler(this.ClearButton_Click);
            // 
            // userButton
            // 
            this.userButton.Location = new System.Drawing.Point(559, 371);
            this.userButton.Name = "userButton";
            this.userButton.Size = new System.Drawing.Size(110, 25);
            this.userButton.TabIndex = 4;
            this.userButton.Text = "Value from User";
            this.userButton.UseVisualStyleBackColor = true;
            this.userButton.Click += new System.EventHandler(this.UserButton_Click);
            // 
            // randomButton
            // 
            this.randomButton.Location = new System.Drawing.Point(559, 342);
            this.randomButton.Name = "randomButton";
            this.randomButton.Size = new System.Drawing.Size(110, 25);
            this.randomButton.TabIndex = 5;
            this.randomButton.Text = "Value at Random";
            this.randomButton.UseVisualStyleBackColor = true;
            this.randomButton.Click += new System.EventHandler(this.RandomButton_Click);
            // 
            // fileButton
            // 
            this.fileButton.Location = new System.Drawing.Point(559, 313);
            this.fileButton.Name = "fileButton";
            this.fileButton.Size = new System.Drawing.Size(110, 25);
            this.fileButton.TabIndex = 6;
            this.fileButton.Text = "Value from File";
            this.fileButton.UseVisualStyleBackColor = true;
            this.fileButton.Click += new System.EventHandler(this.FileButton_Click);
            // 
            // chooseButton
            // 
            this.chooseButton.Location = new System.Drawing.Point(559, 284);
            this.chooseButton.Name = "chooseButton";
            this.chooseButton.Size = new System.Drawing.Size(110, 25);
            this.chooseButton.TabIndex = 7;
            this.chooseButton.Text = "Choose a File";
            this.chooseButton.UseVisualStyleBackColor = true;
            this.chooseButton.Click += new System.EventHandler(this.ChooseButton_Click);
            // 
            // userValue
            // 
            this.userValue.Location = new System.Drawing.Point(456, 374);
            this.userValue.Name = "userValue";
            this.userValue.Size = new System.Drawing.Size(100, 20);
            this.userValue.TabIndex = 8;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(453, 358);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Enter a Value";
            // 
            // countLabel
            // 
            this.countLabel.AutoSize = true;
            this.countLabel.Location = new System.Drawing.Point(559, 265);
            this.countLabel.Name = "countLabel";
            this.countLabel.Size = new System.Drawing.Size(13, 13);
            this.countLabel.TabIndex = 10;
            this.countLabel.Text = "0";
            // 
            // fileLabel
            // 
            this.fileLabel.AutoSize = true;
            this.fileLabel.Location = new System.Drawing.Point(559, 252);
            this.fileLabel.Name = "fileLabel";
            this.fileLabel.Size = new System.Drawing.Size(80, 13);
            this.fileLabel.TabIndex = 11;
            this.fileLabel.Text = "No file selected";
            // 
            // chartLabel
            // 
            this.chartLabel.AutoSize = true;
            this.chartLabel.Font = new System.Drawing.Font("Rockwell", 36F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.chartLabel.Location = new System.Drawing.Point(12, 13);
            this.chartLabel.Name = "chartLabel";
            this.chartLabel.Size = new System.Drawing.Size(96, 54);
            this.chartLabel.TabIndex = 12;
            this.chartLabel.Text = "Bar";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.SteelBlue;
            this.ClientSize = new System.Drawing.Size(680, 469);
            this.ControlBox = false;
            this.Controls.Add(this.chartLabel);
            this.Controls.Add(this.fileLabel);
            this.Controls.Add(this.countLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.userValue);
            this.Controls.Add(this.chooseButton);
            this.Controls.Add(this.fileButton);
            this.Controls.Add(this.randomButton);
            this.Controls.Add(this.userButton);
            this.Controls.Add(this.clearButton);
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.mainChart);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "Assignment 4";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.mainChart)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart mainChart;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton bubbleRB;
        private System.Windows.Forms.RadioButton pieRB;
        private System.Windows.Forms.RadioButton columnRB;
        private System.Windows.Forms.RadioButton barRB;
        private System.Windows.Forms.Button exitButton;
        private System.Windows.Forms.Button clearButton;
        private System.Windows.Forms.Button userButton;
        private System.Windows.Forms.Button randomButton;
        private System.Windows.Forms.Button fileButton;
        private System.Windows.Forms.Button chooseButton;
        private System.Windows.Forms.TextBox userValue;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label countLabel;
        private System.Windows.Forms.Label fileLabel;
        private System.Windows.Forms.Label chartLabel;
    }
}

