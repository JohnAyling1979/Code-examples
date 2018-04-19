import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

/*
    CustomerServer

    Class is the middle man between the client and database
 */
public class CustomerServer extends Thread
{
    private ServerSocket listenSocket;

    public static void main(String args[])
    {
        //create a new server
        new CustomerServer();
    }

    private CustomerServer()
    {
        //set the port
        int port = 9709;
        try
        {
            //create a new ServerSocket on my port
            listenSocket = new ServerSocket(port);
        } catch (IOException e)
        {
            //Print error and exit
            System.err.println("Exception creating server socket: " + e);
            System.exit(1);
        }

        //display message and start thread
        System.out.println("LOG: Server listening on port " + port);
        this.start();
    }

    /**
     * run()
     * The body of the server thread. Loops forever, listening for and
     * accepting connections from clients. For each connection, create a
     * new Conversation object to handle the communication through the
     * new Socket.
     */

    public void run()
    {
        try
        {
            do
            {
                //waits for the client to connect
                Socket clientSocket = listenSocket.accept();

                //print message
                System.out.println("LOG: Client connected");

                // Create a Conversation object to handle this client and pass
                // it the Socket to use.  If needed, we could save the Conversation
                // object reference in an ArrayList. In this way we could later iterate
                // through this list looking for "dead" connections and reclaim
                // any resources.
                new Conversation(clientSocket);
            } while (true);
        } catch(IOException e)
        {
            System.err.println("Exception listening for connections: " + e);
        }
    }
}

/**
 * The Conversation class handles all communication with a client.
 */
class Conversation extends Thread
{
    private Socket clientSocket;
    private ObjectInputStream in;
    private ObjectOutputStream out;

    //Address of the database
    private static final String URL = "jdbc:mysql://courses:3306/JavaCust09";

    private Statement getAllStatement = null;
    private PreparedStatement addStatement = null;
    private PreparedStatement deleteStatement = null;
    private PreparedStatement updateStatement = null;

    /**
     * Constructor
     *
     * Initialize the streams and start the thread.
     */
    Conversation(Socket socket)
    {
        clientSocket = socket;

        try
        {
            //creates input and output streams
            out = new ObjectOutputStream(clientSocket.getOutputStream());
            in = new ObjectInputStream(clientSocket.getInputStream());

            //display message
            System.out.println("LOG: Streams opened");
        } catch(IOException e)
        {
            try
            {
                clientSocket.close();
            } catch(IOException e2)
            {
                System.err.println("Exception closing client socket: " + e2);
            }

            System.err.println("Exception getting socket streams: " + e);
            return;
        }

        try
        {
            //print message
            System.out.println("LOG: Trying to create database connection");

            //connect to the DB
            Connection connection = DriverManager.getConnection(URL);

            // Create your Statements and PreparedStatements here
            getAllStatement = connection.createStatement();
            addStatement = connection.prepareStatement("INSERT INTO customer (name, ssn, address, zipCode) VALUES (?,?,?,?)");
            deleteStatement = connection.prepareStatement("DELETE FROM customer WHERE ssn=?");
            updateStatement = connection.prepareStatement("UPDATE customer SET address=? WHERE ssn=?");

            //print out message
            System.out.println("LOG: Connected to database");
        } catch (Exception e)
        {
            System.err.println("Exception connecting to database manager: " + e);
            return;
        }

        // Start the run loop.
        System.out.println("LOG: Connection achieved, starting run loop");
        this.start();
    }

    /**
     * run()
     *
     * Reads and processes input from the client until the client disconnects.
     */
    public void run() {
        System.out.println("LOG: Thread running");

        try {
            do
            {
                // Read and process input from the client.
                MessageObject inObj = (MessageObject) in.readObject();

                switch (inObj.getMessage())
                {
                    case "get":
                        handleGetAll();
                        break;
                    case "add":
                        handleAdd(inObj);
                        break;
                    case "update":
                        handleUpdate(inObj);
                        break;
                    case "delete":
                        handleDelete(inObj);
                        break;
                }
            } while (true);
        } catch (ClassNotFoundException | IOException e)
        {
            System.err.println("IOException: " + e);
            System.out.println("LOG: Client disconnected");
        } finally
        {
            try
            {
                clientSocket.close();
            } catch (IOException e) {
                System.err.println("Exception closing client socket: " + e);
            }
        }
    }

    /*
        handleGetAll

        called to handle a get all query
     */
    private void handleGetAll()
    {
        //create a new object to pass back
        MessageObject object= new MessageObject();
        try
        {
            //run the query and get the result
            ResultSet resultSet=getAllStatement.executeQuery("select * from customer");

            //create an new arraylist of rows
            ArrayList<Row> table = new ArrayList<>();

            //while we have data in the result
            while (resultSet.next())
            {
                //create a row and add it to the table
                table.add(new Row(resultSet.getString("name"),resultSet.getString("ssn"),resultSet.getString("address"),resultSet.getString("zipCode")));
            }

            //add the table to the message object
            object.setResultSet(table);
        }catch (SQLException e)
        {
            //display message and send empty object back
            e.printStackTrace();
        }

        try
        {
            out.writeObject(object);
        }catch (IOException ex)
        {
            ex.printStackTrace();
        }
    }

    /*
        handleAdd

        called to handle an insert query
     */
    private void handleAdd(MessageObject clientMsg)
    {
        try
        {
            //add the data to the statement
            addStatement.setString(1,clientMsg.getName());
            addStatement.setString(2,clientMsg.getSsn());
            addStatement.setString(3,clientMsg.getAddress());
            addStatement.setString(4,clientMsg.getZipCode());

            //perform the query and save the number of rows effected
            clientMsg.setRowsChanged(addStatement.executeUpdate());
        }catch (SQLException e)
        {
            //display error
            e.printStackTrace();

            //set row changed to zero
            clientMsg.setRowsChanged(0);
        }


        try
        {
            //send the message back
            out.writeObject(clientMsg);
        }catch (IOException ex)
        {
            ex.printStackTrace();
        }
    }

    /*
        handleDelete

        called to handle a delete query
     */
    private void handleDelete(MessageObject clientMsg)
    {
        try
        {
            //set the ssn to the statment
            deleteStatement.setString(1,clientMsg.getSsn());

            //execute the statment and save it to the message
            clientMsg.setRowsChanged(deleteStatement.executeUpdate());
        }catch (SQLException e)
        {
            //print message and set row to 0
            e.printStackTrace();
            clientMsg.setRowsChanged(0);
        }
        try
        {
            //send message back to client
            out.writeObject(clientMsg);
        }catch (IOException ex)
        {
            //print message
            ex.printStackTrace();
        }
    }

    /*
        handleUpdate

        called to handle the update query
     */
    private void handleUpdate(MessageObject clientMsg)
    {
        try
        {
            //set the ssn and address
            updateStatement.setString(1,clientMsg.getAddress());
            updateStatement.setString(2,clientMsg.getSsn());

            //run the update and save the row
            clientMsg.setRowsChanged(updateStatement.executeUpdate());
        }catch (SQLException e)
        {
            //print error and set row to 0
            e.printStackTrace();
            clientMsg.setRowsChanged(0);
        }
        try
        {
            //send object back to client
            out.writeObject(clientMsg);
        }catch (IOException ex)
        {
            ex.printStackTrace();
        }
    }
}
