import java.io.Serializable;

/*
    Row

    used to hold data from the the database
 */
public class Row implements Serializable
{
    private String name;
    private String ssn;
    private String address;
    private String zipCode;

    /*
        constructor

        used to create one record
     */
    Row(String name, String ssn, String address, String zipCode)
    {
        this.name = name;
        this.ssn = ssn;
        this.address = address;
        this.zipCode = zipCode;
    }

    /*
        toString

        overrides the toString function to output the data
     */
    @Override
    public String toString()
    {
        return name + " ; " + ssn + " ; " + address + " ; " + zipCode;
    }
}
