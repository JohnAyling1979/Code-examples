namespace assignment_5
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
            this.masterLabel = new System.Windows.Forms.Label();
            this.mPasswordTB = new System.Windows.Forms.TextBox();
            this.masterButton = new System.Windows.Forms.Button();
            this.outBox = new System.Windows.Forms.ListBox();
            this.siteLabel = new System.Windows.Forms.Label();
            this.loginLabel = new System.Windows.Forms.Label();
            this.passLabel = new System.Windows.Forms.Label();
            this.siteTB = new System.Windows.Forms.TextBox();
            this.loginTB = new System.Windows.Forms.TextBox();
            this.passTB = new System.Windows.Forms.TextBox();
            this.options = new System.Windows.Forms.GroupBox();
            this.deleteRB = new System.Windows.Forms.RadioButton();
            this.modifyRB = new System.Windows.Forms.RadioButton();
            this.newRB = new System.Windows.Forms.RadioButton();
            this.submit = new System.Windows.Forms.Button();
            this.exit = new System.Windows.Forms.Button();
            this.showButton = new System.Windows.Forms.Button();
            this.options.SuspendLayout();
            this.SuspendLayout();
            // 
            // masterLabel
            // 
            this.masterLabel.AutoSize = true;
            this.masterLabel.Location = new System.Drawing.Point(225, 9);
            this.masterLabel.Name = "masterLabel";
            this.masterLabel.Size = new System.Drawing.Size(116, 13);
            this.masterLabel.TabIndex = 0;
            this.masterLabel.Text = "Enter Master Password";
            // 
            // mPasswordTB
            // 
            this.mPasswordTB.Location = new System.Drawing.Point(228, 26);
            this.mPasswordTB.Name = "mPasswordTB";
            this.mPasswordTB.PasswordChar = '*';
            this.mPasswordTB.Size = new System.Drawing.Size(113, 20);
            this.mPasswordTB.TabIndex = 1;
            // 
            // masterButton
            // 
            this.masterButton.BackColor = System.Drawing.SystemColors.ControlText;
            this.masterButton.Location = new System.Drawing.Point(228, 53);
            this.masterButton.Name = "masterButton";
            this.masterButton.Size = new System.Drawing.Size(113, 23);
            this.masterButton.TabIndex = 2;
            this.masterButton.Text = "Enter";
            this.masterButton.UseVisualStyleBackColor = false;
            this.masterButton.Click += new System.EventHandler(this.MasterButton_Click);
            // 
            // outBox
            // 
            this.outBox.Enabled = false;
            this.outBox.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.outBox.FormattingEnabled = true;
            this.outBox.ItemHeight = 18;
            this.outBox.Location = new System.Drawing.Point(11, 9);
            this.outBox.Name = "outBox";
            this.outBox.Size = new System.Drawing.Size(550, 166);
            this.outBox.TabIndex = 3;
            this.outBox.Visible = false;
            this.outBox.SelectedIndexChanged += new System.EventHandler(this.OutBox_SelectedIndexChanged);
            // 
            // siteLabel
            // 
            this.siteLabel.AutoSize = true;
            this.siteLabel.Enabled = false;
            this.siteLabel.Location = new System.Drawing.Point(148, 207);
            this.siteLabel.Name = "siteLabel";
            this.siteLabel.Size = new System.Drawing.Size(25, 13);
            this.siteLabel.TabIndex = 4;
            this.siteLabel.Text = "Site";
            this.siteLabel.Visible = false;
            // 
            // loginLabel
            // 
            this.loginLabel.AutoSize = true;
            this.loginLabel.Enabled = false;
            this.loginLabel.Location = new System.Drawing.Point(262, 207);
            this.loginLabel.Name = "loginLabel";
            this.loginLabel.Size = new System.Drawing.Size(33, 13);
            this.loginLabel.TabIndex = 5;
            this.loginLabel.Text = "Login";
            this.loginLabel.Visible = false;
            // 
            // passLabel
            // 
            this.passLabel.AutoSize = true;
            this.passLabel.Enabled = false;
            this.passLabel.Location = new System.Drawing.Point(376, 207);
            this.passLabel.Name = "passLabel";
            this.passLabel.Size = new System.Drawing.Size(53, 13);
            this.passLabel.TabIndex = 6;
            this.passLabel.Text = "Password";
            this.passLabel.Visible = false;
            // 
            // siteTB
            // 
            this.siteTB.Enabled = false;
            this.siteTB.Location = new System.Drawing.Point(151, 224);
            this.siteTB.Name = "siteTB";
            this.siteTB.Size = new System.Drawing.Size(100, 20);
            this.siteTB.TabIndex = 7;
            this.siteTB.Visible = false;
            // 
            // loginTB
            // 
            this.loginTB.Enabled = false;
            this.loginTB.Location = new System.Drawing.Point(265, 224);
            this.loginTB.Name = "loginTB";
            this.loginTB.Size = new System.Drawing.Size(100, 20);
            this.loginTB.TabIndex = 8;
            this.loginTB.Visible = false;
            // 
            // passTB
            // 
            this.passTB.Enabled = false;
            this.passTB.Location = new System.Drawing.Point(379, 224);
            this.passTB.Name = "passTB";
            this.passTB.PasswordChar = '*';
            this.passTB.Size = new System.Drawing.Size(100, 20);
            this.passTB.TabIndex = 9;
            this.passTB.Visible = false;
            // 
            // options
            // 
            this.options.Controls.Add(this.deleteRB);
            this.options.Controls.Add(this.modifyRB);
            this.options.Controls.Add(this.newRB);
            this.options.Enabled = false;
            this.options.Location = new System.Drawing.Point(12, 207);
            this.options.Name = "options";
            this.options.Size = new System.Drawing.Size(133, 91);
            this.options.TabIndex = 10;
            this.options.TabStop = false;
            this.options.Text = "Options";
            this.options.Visible = false;
            // 
            // deleteRB
            // 
            this.deleteRB.AutoSize = true;
            this.deleteRB.Location = new System.Drawing.Point(7, 67);
            this.deleteRB.Name = "deleteRB";
            this.deleteRB.Size = new System.Drawing.Size(56, 17);
            this.deleteRB.TabIndex = 2;
            this.deleteRB.Text = "Delete";
            this.deleteRB.UseVisualStyleBackColor = true;
            this.deleteRB.Click += new System.EventHandler(this.Options_Enter);
            // 
            // modifyRB
            // 
            this.modifyRB.AutoSize = true;
            this.modifyRB.Location = new System.Drawing.Point(7, 43);
            this.modifyRB.Name = "modifyRB";
            this.modifyRB.Size = new System.Drawing.Size(56, 17);
            this.modifyRB.TabIndex = 1;
            this.modifyRB.Text = "Modify";
            this.modifyRB.UseVisualStyleBackColor = true;
            this.modifyRB.Click += new System.EventHandler(this.Options_Enter);
            // 
            // newRB
            // 
            this.newRB.AutoSize = true;
            this.newRB.Checked = true;
            this.newRB.Location = new System.Drawing.Point(7, 19);
            this.newRB.Name = "newRB";
            this.newRB.Size = new System.Drawing.Size(47, 17);
            this.newRB.TabIndex = 0;
            this.newRB.TabStop = true;
            this.newRB.Text = "New";
            this.newRB.UseVisualStyleBackColor = true;
            this.newRB.Click += new System.EventHandler(this.Options_Enter);
            // 
            // submit
            // 
            this.submit.BackColor = System.Drawing.SystemColors.ControlText;
            this.submit.Enabled = false;
            this.submit.Location = new System.Drawing.Point(403, 251);
            this.submit.Name = "submit";
            this.submit.Size = new System.Drawing.Size(75, 23);
            this.submit.TabIndex = 11;
            this.submit.Text = "Add";
            this.submit.UseVisualStyleBackColor = false;
            this.submit.Visible = false;
            this.submit.Click += new System.EventHandler(this.Submit_Click);
            // 
            // exit
            // 
            this.exit.BackColor = System.Drawing.SystemColors.ControlText;
            this.exit.Location = new System.Drawing.Point(347, 53);
            this.exit.Name = "exit";
            this.exit.Size = new System.Drawing.Size(75, 23);
            this.exit.TabIndex = 12;
            this.exit.Text = "Exit";
            this.exit.UseVisualStyleBackColor = false;
            this.exit.Click += new System.EventHandler(this.Exit_Click);
            // 
            // showButton
            // 
            this.showButton.BackColor = System.Drawing.SystemColors.ControlText;
            this.showButton.Enabled = false;
            this.showButton.Location = new System.Drawing.Point(486, 224);
            this.showButton.Name = "showButton";
            this.showButton.Size = new System.Drawing.Size(75, 23);
            this.showButton.TabIndex = 13;
            this.showButton.Text = "show";
            this.showButton.UseVisualStyleBackColor = false;
            this.showButton.Visible = false;
            this.showButton.Click += new System.EventHandler(this.ShowButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ClientSize = new System.Drawing.Size(576, 92);
            this.ControlBox = false;
            this.Controls.Add(this.showButton);
            this.Controls.Add(this.exit);
            this.Controls.Add(this.submit);
            this.Controls.Add(this.options);
            this.Controls.Add(this.passTB);
            this.Controls.Add(this.loginTB);
            this.Controls.Add(this.siteTB);
            this.Controls.Add(this.passLabel);
            this.Controls.Add(this.loginLabel);
            this.Controls.Add(this.siteLabel);
            this.Controls.Add(this.outBox);
            this.Controls.Add(this.masterButton);
            this.Controls.Add(this.mPasswordTB);
            this.Controls.Add(this.masterLabel);
            this.ForeColor = System.Drawing.SystemColors.HighlightText;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Password Manager";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.options.ResumeLayout(false);
            this.options.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label masterLabel;
        private System.Windows.Forms.TextBox mPasswordTB;
        private System.Windows.Forms.Button masterButton;
        private System.Windows.Forms.ListBox outBox;
        private System.Windows.Forms.Label siteLabel;
        private System.Windows.Forms.Label loginLabel;
        private System.Windows.Forms.Label passLabel;
        private System.Windows.Forms.TextBox siteTB;
        private System.Windows.Forms.TextBox loginTB;
        private System.Windows.Forms.TextBox passTB;
        private System.Windows.Forms.GroupBox options;
        private System.Windows.Forms.RadioButton deleteRB;
        private System.Windows.Forms.RadioButton modifyRB;
        private System.Windows.Forms.RadioButton newRB;
        private System.Windows.Forms.Button submit;
        private System.Windows.Forms.Button exit;
        private System.Windows.Forms.Button showButton;
    }
}

