import java.io.*;
import java.util.ArrayList;

/*
	class is used to pass info back and forth between client and server
 */
class MessageObject implements Serializable
{
    private String name;
    private String ssn;
    private String address;
    private String zipCode;
    private String message;
    private int rowsChanged;
    private ArrayList<Row> resultSet;

    /*
        Constructor
        used with get all
     */
    MessageObject()
    {
        name=null;
        ssn=null;
        address=null;
        zipCode=null;
        rowsChanged=0;
        resultSet=null;

        message="get";
    }

    /*
        Constructor
        used with add
     */
    MessageObject(String name,String ssn,String address,String zipCode)
    {
        this.name=name;
        this.ssn=ssn;
        this.address=address;
        this.zipCode=zipCode;
        rowsChanged=0;
        resultSet=null;

        message="add";
    }

    /*
        Constructor
        used with update
     */
    MessageObject(String ssn, String address)
    {
        name=null;
        this.ssn=ssn;
        this.address=address;
        zipCode=null;
        rowsChanged=0;
        resultSet=null;

        message="update";
    }

    /*
    Constructor
    used with delete
 */
    MessageObject(String ssn)
    {
        name=null;
        this.ssn=ssn;
        address=null;
        zipCode=null;
        rowsChanged=0;
        resultSet=null;

        message="delete";
    }

    /*
        getName

        used to return the name
     */
    String getName()
    {
        return name;
    }

    /*
        getSsn

        used to return the ssn
     */
    String getSsn()
    {
        return ssn;
    }

    /*
        getAddress

        used to get the address
     */
    String getAddress()
    {
        return address;
    }

    /*
        getZipCode

        used to get the zip code
     */
    String getZipCode()
    {
        return zipCode;
    }

    /*
        getMessage

        used to get the message from the object
     */
    String getMessage()
    {
        return message;
    }

    /*
        getRowChanged

        used to get the number of rows effected
     */
    int getRowsChanged()
    {
        return rowsChanged;
    }

    /*
        getResultSet

        used to get the arraylist of Row data
     */
    ArrayList<Row> getResultSet()
    {
        return resultSet;
    }

    /*
        setResult

        used to add a data arraylist to the object
     */
    void setResultSet(ArrayList<Row> table)
    {
        resultSet=table;
    }

    /*
        setRowsChanged

        used to update the number of rows effect by the command
     */
    void setRowsChanged(int total)
    {
        rowsChanged=total;
    }
}
