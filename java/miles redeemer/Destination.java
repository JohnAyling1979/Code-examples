/****************************************************************

 Class:             Destination

 Class variable:    none

 Instance variable: private name: name of the city
                    private normalMiles: miles required for ticker
                    private supersaverMiles: miles required if during special month
                    private milesToUpgrade: miles to upgrade to first class
                    private startMonth: start for saver miles
                    private endMonth: end for saver miles


 Class method:      none

 Instance method:   constructor and getter for all instance variables

 NOTES:             none
****************************************************************/
public class Destination
{
    //instance variables
    private String name;
    private int normalMiles;
    private int supersaverMiles;
    private int milesToUpgrade;
    private int startMonth;
    private int endMonth;

    /****************************************************************

     FUNCTION:   Destination(constructor)

     ARGUMENTS:  name: city name
                 miles: normal miles
                 saverMiles: saver miles
                 upgrade: seat upgrade cost
                 start: saver start month
                 end: saver end month

     RETURNS:    none

     NOTES:      Destination constructor which sets all the instance variables
    ****************************************************************/
    Destination(String name, int miles, int saverMiles, int upgrade, int start, int end)
    {
        this.name = name;
        this.normalMiles = miles;
        this.supersaverMiles = saverMiles;
        this.milesToUpgrade = upgrade;
        this.startMonth = start;
        this.endMonth = end;
    }//end Destination constructor

    //Class getters
    public String getName() {
        return name;
    }
    public int getNormalMiles() {
        return normalMiles;
    }
    public int getMilesToUpgrade() {
        return milesToUpgrade;
    }
    public int getSupersaverMiles() {
        return supersaverMiles;
    }
    public int getStartMonth() {
        return startMonth;
    }
    public int getEndMonth() {
        return endMonth;
    }
}//end Destination
