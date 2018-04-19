import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import javax.swing.*;

/*
    CustomerClient

    Used to connect to the server
 */
public class CustomerClient extends JFrame implements ActionListener
{
    private Socket socket;
    private ObjectInputStream in;
    private ObjectOutputStream out;

    private static final long serialVersionUID = 1L;

    // GUI components
    private JButton connectButton = new JButton("Connect");
    private JButton submit = new JButton("Submit");
    private JRadioButton get = new JRadioButton("Get All",true);
    private JRadioButton add = new JRadioButton("Add");
    private JRadioButton delete = new JRadioButton("Delete");
    private JRadioButton updateAddress = new JRadioButton("Update Address");
    private JTextArea output = new JTextArea();
    private JLabel message = new JLabel("Not connected");
    private JLabel nameLB = new JLabel("Name:");
    private JLabel addressLB = new JLabel("Address:");
    private JLabel ssnLB = new JLabel("SSN:");
    private JLabel zipCodeLB = new JLabel("Zip Code:");
    private JTextField nameTF = new JTextField();
    private JTextField addressTF = new JTextField();
    private JTextField ssnTF = new JTextField();
    private JTextField zipCodeTF = new JTextField();

    /*
        main

        creates an instance of CustomerClient
     */
    public static void main(String[] args)
    {

        EventQueue.invokeLater(CustomerClient::new);
    }

    /*
        constructor

        sets the title and calls create and show
     */
    private CustomerClient()
    {
        super("Customer Database");
        createAndShowGUI();
    }

    /*
        createAndShowGUI

        sets up the GUI
     */
    private void createAndShowGUI()
    {
        // Set up GUI
        setLayout(new BorderLayout());
        JPanel topPanel = new JPanel(new BorderLayout());
        JPanel topPage = new JPanel(new GridLayout(2,4,20,20));
        JPanel topCenter = new JPanel(new FlowLayout());
        JScrollPane mainPanel = new JScrollPane(output);
        ButtonGroup options = new ButtonGroup();

        //sets the frame properties
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        output.setPreferredSize(new Dimension(600,300));

        //add buttons to the group
        options.add(get);
        options.add(add);
        options.add(updateAddress);
        options.add(delete);

        //add to topPage
        topPage.add(nameLB);
        topPage.add(nameTF);
        topPage.add(ssnLB);
        topPage.add(ssnTF);
        topPage.add(addressLB);
        topPage.add(addressTF);
        topPage.add(zipCodeLB);
        topPage.add(zipCodeTF);

        //add to top center
        topCenter.add(connectButton);
        topCenter.add(get);
        topCenter.add(add);
        topCenter.add(updateAddress);
        topCenter.add(delete);
        topCenter.add(submit);

        //add to topPanel
        topPanel.add(topPage,BorderLayout.PAGE_START);
        topPanel.add(topCenter,BorderLayout.CENTER);
        topPanel.add(message,BorderLayout.PAGE_END);

        //add to the frame
        add(topPanel,BorderLayout.PAGE_START);
        add(mainPanel,BorderLayout.CENTER);

        //set starting values
        submit.setEnabled(false);
        nameTF.setEnabled(false);
        addressTF.setEnabled(false);
        ssnTF.setEnabled(false);
        zipCodeTF.setEnabled(false);
        get.setEnabled(false);
        add.setEnabled(false);
        updateAddress.setEnabled(false);
        delete.setEnabled(false);

        //set listeners
        get.addActionListener(this);
        add.addActionListener(this);
        updateAddress.addActionListener(this);
        delete.addActionListener(this);
        connectButton.addActionListener(this);
        submit.addActionListener(this);

        //show the frame
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    /*
        actionPerformed

        called when a button is clicked
     */
    @Override
    public void actionPerformed(ActionEvent e)
    {
        //perform an action based on what is clicked
        switch (e.getActionCommand())
        {
            case "Connect":
                connect();
                break;
            case "Disconnect":
                disconnect();
                break;
            case "Get All":
                nameTF.setEnabled(false);
                addressTF.setEnabled(false);
                ssnTF.setEnabled(false);
                zipCodeTF.setEnabled(false);
                break;
            case "Add":
                nameTF.setEnabled(true);
                addressTF.setEnabled(true);
                ssnTF.setEnabled(true);
                zipCodeTF.setEnabled(true);
                break;
            case "Update Address":
                nameTF.setEnabled(false);
                addressTF.setEnabled(true);
                ssnTF.setEnabled(true);
                zipCodeTF.setEnabled(false);
                break;
            case "Delete":
                nameTF.setEnabled(false);
                addressTF.setEnabled(false);
                ssnTF.setEnabled(true);
                zipCodeTF.setEnabled(false);
                break;
            case "Submit":
                if (get.isSelected())
                    handleGetAll();
                else if (add.isSelected())
                    handleAdd();
                else if (updateAddress.isSelected())
                    handleUpdate();
                else if (delete.isSelected())
                    handleDelete();
                break;
        }

        nameTF.setText("");
        addressTF.setText("");
        ssnTF.setText("");
        zipCodeTF.setText("");
    }

    /*
        connect

        sets up the connection to the server
     */
    private void connect() {
        try
        {
            //disable the button
            connectButton.setEnabled(false);

            //connect to server
            socket = new Socket("hopper.cs.niu.edu", 9709);

            //set up streams
            out = new ObjectOutputStream(socket.getOutputStream());
            in = new ObjectInputStream(socket.getInputStream());

            //change button text and enable
            connectButton.setText("Disconnect");
            connectButton.setEnabled(true);

            //update message
            message.setText("Connected");

            //enable new controls
            get.setEnabled(true);
            get.setSelected(true);
            add.setEnabled(true);
            updateAddress.setEnabled(true);
            delete.setEnabled(true);
            submit.setEnabled(true);

        } catch (UnknownHostException e) {
            message.setText("Exception resolving host name: " + e);
            connectButton.setEnabled(true);
        } catch (IOException e) {
            message.setText("Exception establishing socket connection: " + e);
            connectButton.setEnabled(true);
        }
    }

    /*
        disconnect

        called to disconnect from the server
     */
    private void disconnect() {

        // Disable buttons
        connectButton.setEnabled(false);
        get.setEnabled(false);
        get.setSelected(true);
        add.setEnabled(false);
        updateAddress.setEnabled(false);
        delete.setEnabled(false);
        submit.setEnabled(false);
        nameTF.setEnabled(false);
        nameTF.setText("");
        ssnTF.setEnabled(false);
        ssnTF.setText("");
        addressTF.setEnabled(false);
        addressTF.setText("");
        zipCodeTF.setEnabled(false);
        zipCodeTF.setText("");

        //close connection
        try {
            socket.close();
            message.setText("Disconnected");
        } catch (IOException e) {
            message.setText("Exception closing socket: " + e);
        }

        //enable button
        connectButton.setText("Connect");
        connectButton.setEnabled(true);
    }

    /*
        handleGetAll

        used to send a get all request
     */
    private void handleGetAll()
    {
        try
        {
            //clear window
            output.setText(null);

            //create a new object and send it to the server
            out.writeObject(new MessageObject());

            //get a object back from the server
            MessageObject object = (MessageObject) in.readObject();

            //for each row in the object append the row the the output
            for(Row row : object.getResultSet())
            {
                output.append(row+"\n");
            }

            //update message
            message.setText(object.getResultSet().size() + " records found");
        }catch (IOException | ClassNotFoundException e)
        {
            e.printStackTrace();
        }
    }

    /*
        handleAdd

        called to send new entry to the server
     */
    private void handleAdd()
    {
        //clear the output window and get the info from the GUI
        output.setText(" ");
        String name = nameTF.getText();
        String ssn = ssnTF.getText();
        String address = addressTF.getText();
        String zipCode = zipCodeTF.getText();

        //test if the data is good
        if(goodName(name)&&goodSsn(ssn)&&goodAddress(address)&&goodZip(zipCode))
        {
            try
            {
                //create a new object and send it to the server
                out.writeObject(new MessageObject(name, ssn, address, zipCode));

                //get an object back from the server
                MessageObject result= (MessageObject)in.readObject();

                //update the message with the number of rows added
                message.setText(result.getRowsChanged()+ " added");

            }catch (IOException | ClassNotFoundException e)
            {
                e.printStackTrace();
            }
        }else
        {
            //update message
            message.setText("All fields needs to have correct values");
        }
    }

    /*
        handleDelete

        Used to send a delete command to the server
     */
    private void handleDelete()
    {
        //clear the output window and get the info from the GUI
        output.setText(" ");
        String ssn = ssnTF.getText();

        //test if the data is good
        if(goodSsn(ssn))
        {
            try
            {
                //create a new object and send it to the server
                out.writeObject(new MessageObject(ssn));

                //get an object back from the server
                MessageObject result= (MessageObject)in.readObject();

                //update the message with the number of rows added
                message.setText(result.getRowsChanged()+ " deleted");

            }catch (IOException | ClassNotFoundException e)
            {
                e.printStackTrace();
            }
        }else
        {
            //update message
            message.setText("All fields needs to have correct values");
        }

    }

    /*
        handleUpdate

        used to send an update command to the server
     */
    private void handleUpdate()
    {
        //clear the output window and get the info from the GUI
        output.setText(" ");
        String ssn = ssnTF.getText();
        String address = addressTF.getText();

        //test if the data is good
        if(goodSsn(ssn)&&goodAddress(address))
        {
            try
            {
                //create a new object and send it to the server
                out.writeObject(new MessageObject(ssn, address));

                //get an object back from the server
                MessageObject result= (MessageObject)in.readObject();

                //update the message with the number of rows added
                message.setText(result.getRowsChanged()+ " updated");

            }catch (IOException | ClassNotFoundException e)
            {
                e.printStackTrace();
            }
        }else
        {
            //update message
            message.setText("All fields needs to have correct values");
        }
    }

    /*
        goodName

        checks if the name passes all the requirements
     */
    private Boolean goodName(String name)
    {
        Boolean good =true;

        //checks length and is empty
        if(name.isEmpty() || name.length()>20)
            good=false;

        return good;
    }

    /*
        goodSsn

        checks if the social meets requirements
     */
    private Boolean goodSsn(String ssn)
    {
        Boolean good = true;

        //checks the length
        if (ssn.length() != 11)
            good = false;
            //checks if there are dashes
        else
        {
            if (ssn.charAt(3) != '-' && ssn.charAt(6) != '-')
                good = false;

            //counts the number of non digits
            int notNum = 0;
            for (int i = 0; i < ssn.length(); i++)
            {
                if (!Character.isDigit(ssn.charAt(i)))
                    notNum++;
            }

            //if there where more then 2 it's not good
            if (notNum > 2)
                good = false;
        }
        return good;
    }

    /*
        goodAddress

        checks if the address is good
     */
    private Boolean goodAddress(String address)
    {
        Boolean good =true;

        if(address.isEmpty() || address.length()>40)
            good=false;

        return good;
    }

    /*
        goodZip

        checks if the is good
     */
    private Boolean goodZip(String zipCode)
    {
        Boolean good =true;

        //checks the length
        if(zipCode.length()!=5)
            good=false;

        //checks that all are digits
        for(int i =0;i<zipCode.length();i++)
            if(!Character.isDigit(zipCode.charAt(i)))
                good=false;

        return good;
    }
}
