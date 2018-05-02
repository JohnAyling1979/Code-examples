package edu.niu.cs.z981329.burger;
/*
 Program:             Shipping Calculator

 Programmer:          John Ayling

 Due:                 2/9/18

 Usage:               To calculate the shipping price based on the weight
 */
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.RadioGroup;
import android.widget.SeekBar;
import android.widget.TextView;

/*
  Class:               MainActivity

  Instance variables:  caloriesTV, burger

  Protected methods:   onCreate

  Private methods:     weightTextWatcher, displayCost

  Usage:               Is the Activity that loads at start
 */
public class MainActivity extends Activity
{
    //instance variables
    private TextView caloriesTV;
    private Burger burger;


    @Override
    /*
        Function:       onCreate

        Parameters:     Bundle savedInstanceStates

        Return:         none

        Usage:          Function is called automatically at the start
     */
    protected void onCreate(Bundle savedInstanceState)
    {
        RadioGroup pattyRG, cheeseRG;
        CheckBox baconCB;
        SeekBar sauceSB;

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //create the burger
        burger = new Burger();

        //connect the screen items
        pattyRG = findViewById(R.id.payytChoiceRG);
        cheeseRG = findViewById(R.id.cheeseChoiceRG);
        baconCB = findViewById(R.id.baconCB);
        sauceSB = findViewById(R.id.sauseSB);
        caloriesTV = findViewById(R.id.caloriesTV);

        //updates the total calories
        displayCalories();

        //named listeners for the radio group
        pattyRG.setOnCheckedChangeListener(pattyListener);

        //cheese listen
        cheeseRG.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int checkedID)
            {
                switch (checkedID)
                {
                    case R.id.noCheeseRB:
                        burger.setCheeseCalories(0);
                        break;
                    case R.id.cheedarRB:
                        burger.setCheeseCalories(Burger.CHEDDAR);
                        break;
                    case R.id.motRB:
                        burger.setCheeseCalories(Burger.MOZZ);
                        break;
                }//end switch

                displayCalories();
            }//end on checked
        });//end listener

        //listen for bacon check box
        baconCB.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                if(((CheckBox)view).isChecked())
                    burger.setBaconCalories(true);
                else
                    burger.setBaconCalories(false);

                displayCalories();
            }//end onClick
        });//end listener

        //listen for sauce SeekBar
        sauceSB.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener()
        {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b)
            {
                burger.setSauceCalories(seekBar.getProgress());

                displayCalories();
            }//end onProgressChanged

            @Override
            public void onStartTrackingTouch(SeekBar seekBar)
            {

            }//end onStartTrackingTouch

            @Override
            public void onStopTrackingTouch(SeekBar seekBar)
            {

            }//end onStopTrackingTouch
        });//end listener
    }//end onCreate

    /*
        Function:       pattyListener which contains onCheckedChange

        Parameters:     onCheckedChanged takes a radioGroup and checked ID

        Return:         none

        Usage:          Function listens for a change to the patty group box
     */
    private RadioGroup.OnCheckedChangeListener pattyListener = new RadioGroup.OnCheckedChangeListener()
    {
        @Override
        public void onCheckedChanged(RadioGroup radioGroup, int checkedID)
        {
            switch(checkedID)
            {
                case R.id.beefRB:
                    burger.setPattyCalories(Burger.BEEF);
                    break;
                case  R.id.turkeyRB:
                    burger.setPattyCalories(Burger.TURKEY);
                    break;
                case R.id.veggieRB:
                    burger.setPattyCalories(Burger.VEGGIE);
            }//end switch

            displayCalories();
        }//end onCheckedChanged
    };//end pattyListener

    /*
        Function:       displayColories

        Parameters:     none

        Return:         none

        Usage:          Function updates the calories total to the screen
     */
    private void displayCalories()
    {
        //set string
        String calories = "Calories: " + burger.getTotalCalories();

        //update screen
        caloriesTV.setText(calories);
    }//end displayCalories;
}//end MainActivity
