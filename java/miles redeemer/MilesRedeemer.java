import java.util.*;

/****************************************************************

 Class:             MileageRedeemer

 Instance variable: none

 Class variable:    private options: an Arraylist of possible Destination
                    private miles: an int containing the number of available
                    miles

 Instance method:   none

 class method:      public readDestinations: reads a file and loads the
                    destinations
                    public getCityNames: gets just the names of the
                    destinations
                    public redeemMiles: returns a list of the possible
                    tickets
                    public getRemainingMiles: returns the left over miles

 NOTES:             MilesRedeemer is a static class
****************************************************************/
public class MilesRedeemer
{
    //class variables
    private static ArrayList<Destination> options = new ArrayList<>();
    private static int miles;

    /****************************************************************

     FUNCTION:   readDestinations

     ARGUMENTS:  fileScanner: a scanner that is attached to a file

     RETURNS:    none

     NOTES:      Will read from a file line by line and save the information
                 into the destination array list
    ****************************************************************/
    public static void readDestinations(Scanner fileScanner)
    {
        //local variables
        String line;
        String [] parts, months;

        //while not end of file
        while(fileScanner.hasNext())
        {
            //get the next line
            line = fileScanner.nextLine();

            //split the line by ;
            parts = line.split(";");

            //try for good value in the file
            try
            {
                //split the month by - (possible exception)
                months = parts[4].split("-");

                //add the destination (possible exception)
                options.add(new Destination(parts[0], Integer.parseInt(parts[1]), Integer.parseInt(parts[2]),
                        Integer.parseInt(parts[3]), Integer.parseInt(months[0]), Integer.parseInt(months[1])));
            }
            //any exceptions means the data was bad
            catch (NumberFormatException e)
            {
                System.out.println("Invalid data in input file");
                System.exit(1);
            }
        }//end while

        //sorts the destinations by miles for later use
        options.sort(Comparator.comparing(Destination::getNormalMiles).reversed());

    }//end readDestinations

    /****************************************************************

     FUNCTION:   getCityNames

     ARGUMENTS:  none

     RETURNS:    String[]: a array containing the names of the possible cities

     NOTES:      Will go through the arraylist and grab the city names
    ****************************************************************/
    public static String[] getCityNames()
    {
        //local variable
        String [] cities = new String[options.size()];

        //for each destination copy the name
        for (int i=0;i<options.size();i++)
            cities[i]=options.get(i).getName();

        //sort the cities
        Arrays.sort(cities);

        //returns the sorted array
        return cities;
    }//end getCityNames

    /****************************************************************

     FUNCTION:   redeemMiles

     ARGUMENTS:  newMiles: number of available miles entered by the user
                 month: the month when the trip is to be taken entered by user

     RETURNS:    ArrayList<String>: each string has the city and type of ticket

     NOTES:      Enters the instance variable for miles,  and calculates
                 the available tickets
    ****************************************************************/
    public static ArrayList<String> redeemMiles(int newMiles, int month)
    {
        //local variables
        int currentMiles;
        ArrayList<String> info = new ArrayList<>();
        ArrayList<String> tickets = new ArrayList<>();
        ArrayList<Integer> upgradePrice = new ArrayList<>();

        //updates the instance variable
        miles=newMiles;

        //goes through and assigns the available cities
        for (Destination city: options)
        {
            //checks if supersaver is available
            if(month >= city.getStartMonth() && month<= city.getEndMonth())
                currentMiles = city.getSupersaverMiles();
            else
                currentMiles = city.getNormalMiles();

            //checks if it can afford the ticket
            if(currentMiles <= miles)
            {
                miles -= currentMiles;
                tickets.add("* A trip to " + city.getName() + ", ");
                upgradePrice.add(city.getMilesToUpgrade());
            }//emd if
        }//end for

        //checks for possible upgrade
        for (int i = 0; i < upgradePrice.size(); i++)
        {
            //if possible add first class or do economy
            if(upgradePrice.get(i) <= miles)
            {
                miles -= upgradePrice.get(i);
                info.add(tickets.get(i) + "first class");
            }
            else
                info.add(tickets.get(i) + "economy class");
        }//end for


        //return the complete arrayList
        return info;
    }//end redeemMiles

    /****************************************************************

     FUNCTION:   getRemainingMiles

     ARGUMENTS:  none

     RETURNS:    int: returns the value in the private variable miles

     NOTES:      none
    ****************************************************************/
    public static int getRemainingMiles()
    {
        return miles;
    }//end getRemainingMiles

    /****************************************************************

     FUNCTION:   findDestination

     ARGUMENTS:  String cityName is the name of the city that we are looking for

     RETURNS:    a Destinations or null if no match

     NOTES:      none
     ****************************************************************/
    public static Destination findDestination(String cityName)
    {
        for (Destination city:options)
        {
            if(city.getName().equals(cityName))
                return city;
        }

        return null;
    }
}//end MilesRedeemer