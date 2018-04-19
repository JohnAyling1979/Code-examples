/*
 * Program: Assignment 5
 * Author:  John Ayling
 * Due:     4/16/18
 * Notes:   This program is a password manager. Passwords are encrypted and saved
 *          with an XOR on char '/uABCD'
 */ 
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace assignment_5
{
    /*
     * Main form class
     */
    public partial class Form1 : Form
    {
        //instance variables
        private String mPass;
        private List<LoginInfo> infoList;
        private Boolean changes;
        private int selected;
        private char key;
        Thread hideThread;

        /*
         * Constructor
         */
        public Form1()
        {
            //set start values at the start
            changes = false;
            selected = 0;
            infoList = new List<LoginInfo>();
            key = '\uABCD';

            //setcomponents
            InitializeComponent();
        }//end Form1

        /*
         * Ran when the form first loads. It reads the master password from a file
         */
        private void Form1_Load(object sender, EventArgs e)
        {
            //test setup file
            if(File.Exists("setup"))
            {
                //open setup file
                using (StreamReader SR = new StreamReader("setup"))
                {
                    //get the masterpassword from the setup file
                    mPass = SR.ReadLine();
                }//end using
            }else
            {
                //display message and exit
                MessageBox.Show("Master Password file not found","File not Found");
                Application.Exit();
            }//end if/else

            //checks that we read a password
            if(mPass==null)
            {
                //display message and exit
                MessageBox.Show("Setup file doesn't contain a master password","No Password");
                Application.Exit();
            }//end if
        }//end Form1_Load

        /*
         * Used to encrypt and decrypt the passwords
         */
        private String Crypt(String inString)
        {
            StringBuilder outString = new StringBuilder();

            //perform a XOR on each character
            foreach(char letter in inString)
                outString.Append((char)(key ^ letter));

            //return the new string
            return outString.ToString();
        }//end Crypt

        /*
         * Called for the submit button on the master password layout
         */
        private void MasterButton_Click(object sender, EventArgs e)
        {
            //get the user input
            String inPass = mPasswordTB.Text;

            //compare the user input to the decrypted password
            if (inPass == Crypt(mPass))
            {
                //display a message
                MessageBox.Show("Correct password","OK");

                //disable old controls
                DisableMaster();

                //enable new controls
                EnableManager();

                //test the file
                ReadPasswordInfo();
            }else
            { 
                //otherwise displays invalad password message
                MessageBox.Show("Password does not match",":(");
            }//end if/esle
        }//end MasterButton_Click

        /*
         * Called when the exit button is clicked. It will update the loginlist file
         * if any changes were made
         */
        private void Exit_Click(object sender, EventArgs e)
        {
            //ends thread if it was running
            hideThread = null;

            //check for changes
            if(changes)
            {
                WriteChanges();
            }//end if

            //exit the application
            Application.Exit();
        }//end Exit_Click

        /*
         * Called to write the changes to the file
         */
        private void WriteChanges()
        {
            try
            {
                //open the file
                using (StreamWriter SW = new StreamWriter("loginlist"))
                {
                    //go through the list writing the info to the file
                    foreach (LoginInfo info in infoList)
                    {
                        SW.WriteLine(info.Site + " " + info.Login + " " + info.Password);
                    }// end foreach
                }//end using
            }catch (Exception)
            {
                MessageBox.Show("Could not write to file/n" +
                    "Changes were not saved", "Write Error");
            }//end try/catch
        }//end WriteChanges

        /*
         * Called to disable the old controls
         */
        private void DisableMaster()
        {
            //disable and hide all the old controls
            masterButton.Enabled = false;
            masterButton.Visible = false;

            masterLabel.Enabled = false;
            masterLabel.Visible = false;

            mPasswordTB.Enabled = false;
            mPasswordTB.Visible = false;
        }//end DisableMaster

        /*
         * Called to setup the new layout
         */
        private void EnableManager()
        {
            //set the new size and move the exit button
            this.Size = new System.Drawing.Size(592, 362);
            exit.Location = new System.Drawing.Point(403, 280);

            //show and enable all new controls
            outBox.Enabled = true;
            outBox.Visible = true;

            siteLabel.Enabled = true;
            siteLabel.Visible = true;

            loginLabel.Enabled = true;
            loginLabel.Visible = true;

            passLabel.Enabled = true;
            passLabel.Visible = true;

            siteTB.Enabled = true;
            siteTB.Visible = true;

            loginTB.Enabled = true;
            loginTB.Visible = true;

            passTB.Enabled = true;
            passTB.Visible = true;

            options.Enabled = true;
            options.Visible = true;

            submit.Enabled = true;
            submit.Visible = true;

            showButton.Enabled = true;
            showButton.Visible = true;

            outBox.Items.Add("Site".PadRight(20) + "Login".PadRight(20) + "Password");
        }//end EnableManager

        /*
         * Called to read the login info and load it into the program
         */
        private void ReadPasswordInfo()
        {
            //if doesn't exist a new one will be create at exit if info is added
            if (File.Exists("loginlist"))
            {
                //open loginlist file
                using (StreamReader SR = new StreamReader("loginlist"))
                {
                    //read the first line
                    String line = SR.ReadLine();

                    //there is a line
                    while (line != null)
                    {
                        //split the line between the three fields
                        String[] parts = line.Split(' ');

                        try
                        {
                            //create a new loginino and add it to the list and screen
                            LoginInfo info = new LoginInfo(parts[0], parts[1], parts[2]);
                            infoList.Add(info);
                            outBox.Items.Add(info);
                        }
                        catch (IndexOutOfRangeException)
                        {
                            //skip bad line
                        }//end try/catch

                        //read next line
                        line = SR.ReadLine();
                    }//end while
                }//end using
            }//end if
        }//end ReadPasswordInfo

        /*
         * Called when the submit button is clicked. It will perform actions
         * depending on which radio button is selected
         */
        private void Submit_Click(object sender, EventArgs e)
        {
            //perform actions based off of radio button
            if (newRB.Checked)
            {
                Add();
            }else if (modifyRB.Checked && selected != 0)
            {
                Modify();
            }else if (deleteRB.Checked && selected != 0)
            {
                Delete();
            }//end if/else if/else if
        }//end Submit_Click

        /*
         * Used to check for unique login and site info
         */
        private Boolean Unique(LoginInfo info)
        {
            Boolean unique = true;

            //go through the list of logins
            for (int i = 0; i < infoList.Count; i++)
            {
                //if they are == and not the currently select info
                //mark as not unique
                if (info.Equals(infoList[i]) && selected - 1 != i)
                {
                    unique = false;
                    break;
                }//end if
            }//end for

            return unique;
        }//end Unique

        /*
         * Called when an item is selected from the list box
         */
        private void OutBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListBox current = sender as ListBox;
            //get the index
            selected = current.SelectedIndex;

            //check if the selected item is null
            //this happens after a remove or is empty
            if (current.SelectedItem != null && selected!=0)
            {
                //display the info
                siteTB.Text = infoList[selected-1].Site;
                loginTB.Text = infoList[selected-1].Login;
                passTB.Text = Crypt(infoList[selected-1].Password);
            }else
            {
                //reset the selected index
                selected = 0;

                //clear the info
                siteTB.Text = String.Empty;
                loginTB.Text = String.Empty;
                passTB.Text = String.Empty;
            }//end if/else
        }//end OutBox_SelectedIndexChanged

        /*
         * Called when one of the radio buttons is clicked
         */
        private void Options_Enter(object sender, EventArgs e)
        {
            //gets the clicked button and reset listbox
            RadioButton button = (RadioButton)sender;
            outBox.SetSelected(0, false);

            //sets value based off of the clicked radio button
            switch(button.Name)
            {
                case "newRB":
                    submit.Text = "Add";
                    siteTB.Text = String.Empty;
                    loginTB.Text = String.Empty;
                    passTB.Text = String.Empty;
                    siteTB.Enabled = true;
                    loginTB.Enabled = true;
                    passTB.Enabled = true;
                    break;
                case "modifyRB":
                    submit.Text = "Modify";
                    siteTB.Text = String.Empty;
                    loginTB.Text = String.Empty;
                    passTB.Text = String.Empty;
                    siteTB.Enabled = true;
                    loginTB.Enabled = true;
                    passTB.Enabled = true;
                    break;
                case "deleteRB":
                    submit.Text = "Delete";
                    siteTB.Text = String.Empty;
                    loginTB.Text = String.Empty;
                    passTB.Text = String.Empty;
                    siteTB.Enabled = false;
                    loginTB.Enabled = false;
                    passTB.Enabled = false;
                    break;
            }//end switch
        }//end Options_Enter

        /*
         * Ran when show button is clicked
         */
        private void ShowButton_Click(object sender, EventArgs e)
        {
            //create a second thread
            hideThread = new Thread(HidePass);

            //show the password and disable the button
            passTB.PasswordChar = '\0';
            showButton.Enabled = false;

            //start the thread
            hideThread.Start();
        }//end ShowButton_Click

        /*
         * This function is ran in a seperate thread and the main thread.
         * It is used to hide the password after some time has passed
         */
        private void HidePass()
        {
            //check which thread you are in
            if (InvokeRequired)
            {
                //new thread

                //pause the thread
                Thread.Sleep(3000);

                //create the invoker of itself
                MethodInvoker hideMI = new MethodInvoker(HidePass);
                try
                {
                    Invoke(hideMI);
                }catch(InvalidOperationException)
                {
                    hideThread = null;
                }
            }
            else
            {
                //main thread

                //set passchar and enable button
                passTB.PasswordChar = '*';
                showButton.Enabled = true;
            }//end if/else
        }//end HidePass

        /*
         * Call to check if it is a good password
         */
        private Boolean StrongPassword(String inPass)
        {
            //start with everything false
            Boolean longerThan8=false;
            Boolean upperCase=false;
            Boolean lowerCase=false;
            Boolean digit=false;

            if (inPass.Length >= 8)
            {
                //length is ok
                longerThan8 = true;

                //check each char for its type
                foreach (char letter in inPass)
                {
                    if (Char.IsDigit(letter))
                        digit = true;

                    if (Char.IsLower(letter))
                        lowerCase = true;

                    if (Char.IsUpper(letter))
                        upperCase = true;

                    //once all are true break from for loop
                    if (digit && lowerCase && upperCase)
                        break;
                }//end foreach
            }//end if

            //return bool value
            return longerThan8 && upperCase && lowerCase && digit;
        }//end StrongPassword

        /*
         * Checks for good info from the user
         */
         private Boolean GoodData(String site, String login, String password)
        {
            //check for spaces
            if (site.Contains(" ") || login.Contains(" ") || password.Contains(" "))
            {
                MessageBox.Show("Values can not contain spaces", "No Spaces");

                return false;
            }

            //check that all values are filled in
            if (site == String.Empty || login == String.Empty || password == String.Empty)
            {
                MessageBox.Show("Values can not be empty", "Empty Value");

                return false;
            }

            //check for strong password
            if (!StrongPassword(passTB.Text))
            {
                MessageBox.Show("Please enter a strong password\n" +
                    "It must be at least 8 characters long and should " +
                    "contain uppercase and lowercase letters and digits.", "Weak Password");

                return false;
            }

            return true;
        }


        /*
         * Used to add info to the login list
         */
        private void Add()
        {
            //get the user input
            String site = siteTB.Text;
            String login = loginTB.Text;
            String password = Crypt(passTB.Text);


            if (GoodData(site, login, password))
            {
                //create a new logininfo
                LoginInfo info = new LoginInfo(site, login, password);

                //nothing is select on a add
                //needed for unique test
                int temp = selected;
                selected = 0;

                if (Unique(info))
                {
                    //update the changes value
                    changes = true;

                    //add it to the list and output
                    infoList.Add(info);
                    outBox.Items.Add(info);
                }
                else
                {
                    MessageBox.Show("Site and Login info must be unique", "Already Exists");
                }//end if/else

                //reset selected
                selected = temp;
            }
        }//end Add

        /*
         * Call to modify an login info
         */
        private void Modify()
        {
            //get the user input
            String site = siteTB.Text;
            String login = loginTB.Text;
            String password = Crypt(passTB.Text);

            if (GoodData(site, login, password))
            {
                //create a new logininfo
                LoginInfo info = new LoginInfo(site, login, password);

                //checks if unique
                if (Unique(info))
                {
                    //update the changes value
                    changes = true;

                    //update the value in the list
                    infoList[selected - 1].Site = site;
                    infoList[selected - 1].Login = login;
                    infoList[selected - 1].Password = password;

                    //update the display
                    outBox.Items[selected] = infoList[selected - 1].ToString();

                    //display a message saying it has been updated
                    MessageBox.Show("Info has been modified", "Updated");
                }
                else
                {
                    MessageBox.Show("Site and Login info must be unique", "Already Exists");
                }//end if/else
            }
        }//end Modify

        /*
         * Called to delete from the login lost
         */
        private void Delete()
        {
            //display a message to verify
            DialogResult dialogResult = MessageBox.Show("Are you sure?", "Confirm", MessageBoxButtons.YesNo);

            //test the result
            if (dialogResult == DialogResult.Yes)
            {
                //update the changes value
                changes = true;

                //remove the item for both the list and display
                infoList.RemoveAt(selected - 1);
                outBox.Items.RemoveAt(selected);
            }//end if
        }//end Delete
    }//end Form1 class

    /*
     * This class is used to hold the log in information
     * it implement IEquatable
     */
    public class LoginInfo : IEquatable<LoginInfo>
    {
        //instance variables
        private String site;
        private String login;
        private String password;//encrypted password

        /*
         * Constructor
         */
        public LoginInfo(String s, String l, String p)
        {
            site = s;
            login = l;
            password = p;
        }//end LoginInfo

        //properties for the instance variables
        public String Site
        {
            set { site = value; }
            get { return site; }
        }//end Site
        public String Login
        {
            set { login = value; }
            get { return login; }
        }//end Login
        public String Password
        {
            set { password = value; }
            get { return password; }
        }//end Password

        /*
         * required for the IEquatable interface
         */
        public bool Equals(LoginInfo other)
        {
            LoginInfo otherInfo = (LoginInfo)other;

            return (site == otherInfo.Site && login == otherInfo.Login);
        }//end Equals

        /*
         * overrides the ToString function to a formated output
         */
        public override string ToString()
        {
            StringBuilder value = new StringBuilder(site.PadRight(20) + login.PadRight(20));

            //replaces the password with *
            foreach (Char letter in password)
                value.Append('*');
            return value.ToString();
        }//end ToString
    }//end LoginInfo class
}//end namespace