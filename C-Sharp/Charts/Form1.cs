/*
 * Program:     Assignment 4
 * Author:      John Ayling
 * Due:         3/28/18
 * Usuage:      To display various charts with points for different files
 */
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

namespace Assignment4
{
    /*
     * Main form class
     */
    public partial class Form1 : Form
    {
        private Random number = new Random();
        private Queue<double> points = new Queue<double>();

        /*
         * Constructor
         */
        public Form1()
        {
            InitializeComponent();
        }//end of constructor

        /*
         * Called when the exitButton is clicked
         */
        private void ExitButton_Click(object sender, System.EventArgs e)
        {
            Application.Exit();
        }//end of exitButton_Click

        /*
         * Called when the clearButton is clicked
         */
        private void ClearButton_Click(object sender, System.EventArgs e)
        {
            mainChart.Series[0].Points.Clear();
        }//end of clearButton_Click

        /*
         * Called when any of the radio buttons are clicked 
         */
        private void ChangeChart(object sender, System.EventArgs e)
        {
            //cast it as a radio button
            RadioButton RB = sender as RadioButton;

            //switch based on button
            switch(RB.Name)
            {
                case "barRB":
                    mainChart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Bar;
                    chartLabel.Text = "Bar";
                    break;
                case "columnRB":
                    mainChart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Column;
                    chartLabel.Text = "Column";
                    break;
                case "pieRB":
                    mainChart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Pie;
                    chartLabel.Text = "Pie";
                    break;
                case "bubbleRB":
                    mainChart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Bubble;
                    chartLabel.Text = "Bubble";
                    break;
            }//end switch

            //clear radio button per assignment
            RB.Checked = false;
        }//end changeChart

        /*
         * Called when the chooseButton_Click is clicked
         */
        private void ChooseButton_Click(object sender, System.EventArgs e)
        {
            String fileName,line;
            String[] noPath;
            double point;

            //create an OpenFileDialog
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                //set starting path
                InitialDirectory = Application.StartupPath
            };

            //if a file was selected
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                //clear any old points
                points.Clear();

                //update the file
                fileName = openFileDialog.FileName;

                //split all the folders
                noPath = fileName.Split('\\');

                //display the filename
                fileLabel.Text = noPath[noPath.Length-1];

                //open the file
                using (StreamReader SR = new StreamReader(fileName))
                {
                    //read the first line
                    line = SR.ReadLine();

                    //while there is a line
                    while (line != null)
                    {
                        //test if the line was valid
                        if (Double.TryParse(line, out point))
                        {
                            //and the point to the list
                            points.Enqueue(point);

                            //read for next line
                            line = SR.ReadLine();
                        }
                        else
                        {
                            //bad data in file

                            //clear any read points
                            points.Clear();

                            //set the label to show the message
                            fileLabel.Text = "Error reading file";

                            //break from while
                            break;
                        }
                    }//end while

                    //display the number of points
                    countLabel.Text = points.Count.ToString();
                }//end using
            }//end if
        }//end chooseButton_Click

        /*
         * Called when the add point from file button is pressed
         */
        private void FileButton_Click(object sender, EventArgs e)
        {
            double point;

            //if there are points add one
            if(points.Count>0)
            {
                //get the first point
                point = points.Dequeue();

                //put the point to the chart
                mainChart.Series[0].Points.AddY(point);

                //update the display count
                countLabel.Text = points.Count.ToString();
            }//end if
        }//end FileButton_Click

        /*
         * Called when the add point from random button is pressed
         */
        private void RandomButton_Click(object sender, EventArgs e)
        {
            //add a random point
            mainChart.Series[0].Points.AddY(number.Next(0,30));
        }//end RandomButton_Click

        /*
         * Called when the add point from the user button is pressed
         */
        private void UserButton_Click(object sender, EventArgs e)
        {
            double point;

            //check if there was a valid value
            if (Double.TryParse(userValue.Text, out point))
            {
                //add the point
                mainChart.Series[0].Points.AddY(point);
            }else
            {
                //display error message
                MessageBox.Show("Please enter a valid value(a double)");
            }
            userValue.Text = String.Empty;
        }//end UserButton_Click

        /*
         * Called at the start and sets the three points
         */
        private void Form1_Load(object sender, EventArgs e)
        {
            for(int i=0;i<3;i++)
                mainChart.Series[0].Points.AddY(number.Next(0, 30));
        }
    }//end form class
}//end namespace