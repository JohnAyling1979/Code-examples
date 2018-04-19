/*
 *
 *  Program:    Assignment 3
 *  Author:     John Ayling
 *  Due:        March 7th
 *  Purpose:    To surply a graphical interface to the database.  At this time it only select and insert
 *  commands are functional as per the assignment
 */
using System;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using System.Data;
using System.IO;
using System.Text;

namespace Assignment3
{
    /*
     * our form class
     */
    public partial class Form1 : Form
    {
        //constant for connection string
        private const String CONN = "server=10.158.56.53;uid=csci473g21;pwd=wordpass21;database=csci473g21;";

        /*
         * Constructor for the form
         */
        public Form1()
        {
            InitializeComponent();
        }//end Form1

        /*
         * Called when the exit button is clicked
         */
        private void ExitButton_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }//end ExitButton_Click

        /*
         * Called when user presses a key from the text field
         * calls Execute code if that key was Enter
         */
        private void Enter_Pressed(object sender,KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
                ExecuteButton_Click(this, new EventArgs());
        }//end Enter_Pressed

        /*
         * Called when the clear button is clicked
         */
        private void ClearButton_Click(object sender, EventArgs e)
        {
            //clear the fields
            output.Items.Clear();
            sqlText.Text = String.Empty;

            //redisplay the tables
            ShowTables();
        }//end ClearButton_Click

        /*
         * Called at the start of the form
         */
        private void Form1_Load_1(object sender, EventArgs e)
        {
            //create the connection
            using (MySqlConnection connection = new MySqlConnection(CONN))
            {
                MySqlCommand command;
                String line;
                String commandStr;
                String[] values;
                char[] splitChar = { ',' };

                try
                {
                    //open connection
                    connection.Open();

                    //drop class table if it exists
                    command = new MySqlCommand("drop table if exists ClassTable", connection);
                    command.ExecuteNonQuery();

                    //create class table
                    command = new MySqlCommand("create table ClassTable(" +
                        "Class varchar(20) not null," +
                        "Teacher varchar(20)," +
                        "Room int(5)," +
                        "Time varchar(5)," +
                        "Days varchar(5)," +
                        "Enrollment int(5)," +
                        "primary key(Class)" +
                        ")", connection);
                    command.ExecuteNonQuery();

                    //fill class table
                    using (StreamReader SR = new StreamReader("Class.txt"))
                    {
                        //get the first line
                        line = SR.ReadLine();

                        while(line !=null)
                        {
                            values = line.Split(splitChar);

                            //create the string
                            commandStr = "Insert into ClassTable values('" + values[0] + "','" +
                                values[1] + "','" +
                                values[2] + "','" +
                                values[3] + "','" +
                                values[4] + "','" +
                                values[5] + 
                                "');";

                            //create and execute the command
                            command = new MySqlCommand(commandStr, connection);
                            command.ExecuteNonQuery();
                            line = SR.ReadLine();
                        }//end while
                    }//end using

                    //drop office table if it exists
                    command = new MySqlCommand("drop table if exists OfficeTable", connection);
                    command.ExecuteNonQuery();

                    //create office table
                    command = new MySqlCommand("create table OfficeTable(" +
                        "Teacher varchar(20) not null," +
                        "Office int(5)," +
                        "primary key(Teacher)" +
                        ")", connection);
                    command.ExecuteNonQuery();

                    //fill office table
                    using (StreamReader SR = new StreamReader("Office.txt"))
                    {
                        //get the first line
                        line = SR.ReadLine();

                        while (line != null)
                        {
                            values = line.Split(splitChar);

                            //create the string
                            commandStr = "Insert into OfficeTable values('" + values[0] + "','" +
                                values[1] + "');";

                            //create and execute the command
                            command = new MySqlCommand(commandStr, connection);
                            command.ExecuteNonQuery();
                            line = SR.ReadLine();
                        }//end while
                    }//end using

                    //drop room table if it exists
                    command = new MySqlCommand("drop table if exists RoomTable", connection);
                    command.ExecuteNonQuery();

                    //create room table
                    command = new MySqlCommand("create table RoomTable(" +
                        "Room int(5) not null," +
                        "Capacity int(5)," +
                        "Smart char(1)," +
                        "primary key(Room))", connection);
                    command.ExecuteNonQuery();

                    //fill room table
                    using (StreamReader SR = new StreamReader("Room.txt"))
                    {
                        //get the first line
                        line = SR.ReadLine();

                        while (line != null)
                        {
                            values = line.Split(splitChar);

                            //create the string
                            commandStr = "Insert into RoomTable values('" + values[0] + "','" +
                                values[1] + "','" +
                                values[2] + "'" +
                                ");";

                            //create and execute the command
                            command = new MySqlCommand(commandStr, connection);
                            command.ExecuteNonQuery();
                            line = SR.ReadLine();
                        }//end while
                    }//end using

                    //show tables
                    ShowTables();
                }//end try
                catch (MySqlException ex)
                {
                    //will print the message connected to the exception
                    output.Items.Add(ex.Message);
                    output.Items.Add(String.Empty);
                }//end catch
                finally
                {
                    //close connection if there
                    if(connection!=null)
                        connection.Close();
                }
            }//end using
        }//end Form1_Load

        /*
         * Called when the execute button is clicked
         */
        private void ExecuteButton_Click(object sender, EventArgs e)
        {
            String query = sqlText.Text;
            StringBuilder line = new StringBuilder();
            char[] space = { ' ','(' };
            String[] values;
            MySqlCommand command;
            MySqlDataReader reader;

            //check is empty
            if (query.Length > 0)
            {
                //make a connection
                using (MySqlConnection connection = new MySqlConnection(CONN))
                {
                    try
                    {
                        //open connection
                        connection.Open();

                        //create the command
                        command = new MySqlCommand(query, connection);

                        //split the sting
                        values = query.Split(space);

                        //select path
                        if (values[0].ToLower().Equals("select"))
                        {
                            //check if count was used
                            if (values[1].ToLower().Equals("count"))
                            {
                                line.Append("Qty is " + command.ExecuteScalar());
                                output.Items.Add("Result of query:");
                                output.Items.Add(line);
                            }//end if
                            else
                            {
                                //execute the command
                                reader = command.ExecuteReader();

                                //clear the line
                                line.Clear();

                                //display column header
                                for (int i = 0; i < reader.FieldCount; i++)
                                {
                                    line.Append(reader.GetName(i).PadRight(20));
                                }//end for

                                //add line to the display
                                output.Items.Add(line);

                                //while there is data
                                while (reader.Read())
                                {
                                    //clear the line
                                    line.Clear();

                                    //build the line
                                    //for (int i=0; i < reader.FieldCount; i++)
                                    //  line.Append(reader.GetString(i).PadRight(20));
                                    IDataRecord record = (IDataRecord)reader;

                                    for(int i = 0; i<record.FieldCount;i++)
                                        line.Append(record[i].ToString().PadRight(20));

                                    //add the line
                                    output.Items.Add(line);
                                }//end while

                                //close reader
                                reader.Close();

                            }//end else
                        }//end if
                        //for insert commands
                        else if (values[0].ToLower().Equals("insert"))
                        {
                            line.Append(command.ExecuteNonQuery() + " lines affected");
                            output.Items.Add("Result of query:");
                            output.Items.Add(line);
                        //for all other commands
                        }//end else if
                        else
                        {
                            output.Items.Add("That command is not currently available");
                        }//end else
                    }//end try
                    //will display ant errors to output
                    catch (MySqlException ex)
                    {
                        //print out any errors
                        output.Items.Add(ex.Message);
                    }//end catch
                    finally
                    {
                        //for spacing
                        output.Items.Add(String.Empty);

                        //focuses on the last line
                        output.SelectedIndex = output.Items.Count - 1;

                        //close connection if exists
                        if (connection!=null)
                            connection.Close();
                    }
                }//end using
            }//end if
        }//end executeButton

        private void ShowTables()
        {
            using (MySqlConnection connection = new MySqlConnection(CONN))
            {
                try
                {
                    connection.Open();

                    //get schema
                    DataTable schema = connection.GetSchema("Tables");

                    //print out tables
                    output.Items.Add("Tables in database");
                    foreach (DataRow row in schema.Rows)
                    {
                        output.Items.Add(row[2].ToString());
                    }//end foreach

                }//end try
                catch (MySqlException ex)
                {
                    //print out any errors
                    output.Items.Add(ex.Message);
                }//end catch
                finally
                {
                    //for spacing
                    output.Items.Add(String.Empty);

                    //focuses on the last line
                    output.SelectedIndex = output.Items.Count - 1;

                    //close connection if exists
                    if (connection!= null)
                        connection.Close();

                }//end finally
            }//end using
        }//show tables
    }//end class Form1
}//end namespace
