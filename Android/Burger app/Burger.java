package edu.niu.cs.z981329.burger;

/*
    class Burger

    This class holds calorie information pertaining to the the burger
 */

class Burger
{
    //constants
    static final int BEEF = 90,
                     TURKEY = 170,
                     VEGGIE = 150,
                     CHEDDAR = 113,
                     MOZZ = 78;
    private static final int BACON = 86;

    //instance variables
    private int pattyCalories, cheeseCalories, baconCalories, sauceCalories;

    //constructor
    Burger()
    {
        pattyCalories = BEEF;
        cheeseCalories = 0;
        baconCalories = 0;
        sauceCalories = 0;
    }//end constructor

    //setters
    void setPattyCalories(int pattyCalories)
    {
        this.pattyCalories = pattyCalories;
    }
    void setCheeseCalories(int cheeseCalories)
    {
        this.cheeseCalories = cheeseCalories;
    }
    void setBaconCalories(boolean hasBacon)
    {
        if(hasBacon)
            baconCalories = BACON;
        else
            baconCalories = 0;
    }
    void setSauceCalories(int sauceCalories)
    {
        this.sauceCalories = sauceCalories;
    }

    //getter
    int getTotalCalories()
    {
        return pattyCalories+baconCalories+cheeseCalories+sauceCalories;
    }
}//end Burger class
