package edu.niu.cs.z981329.assignment4;

import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.CalendarView;
import android.widget.EditText;
import android.widget.Toast;
import java.text.SimpleDateFormat;
import java.util.Date;

/*
    AddActivity

    Activity to add items to the SQLite DB
 */
public class AddActivity extends AppCompatActivity
{
    private DataBaseManager manager;
    private int hwYear,hwMonth,hwDay;

    /*
        onCreate

        called at the start of the activity to setup the components
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add);

        //create the database manager
        manager = new DataBaseManager(this);

        //connect the calendar view and set the listener
        CalendarView dateCV = findViewById(R.id.dateCV);
        dateCV.setOnDateChangeListener(new CalendarView.OnDateChangeListener()
        {
            @Override
            public void onSelectedDayChange(@NonNull CalendarView view, int year, int month, int dayOfMonth)
            {
                hwMonth=month+1;
                hwYear=year;
                hwDay=dayOfMonth;
            }
        });
    }

    /*
        goBack

        called when the back button is clicked and used to return to the main activity
     */
    public void goBack(View view)
    {
        finish();
    }

    /*
        addItem

        called when the add button is clicked.
        This method will get the info from the EditText date variables. Then create a homework item\
        and add it to the database
     */
    public void addItem(View view)
    {
        //connect the EditText
        EditText classET = findViewById(R.id.classET),
                homeworkET = findViewById(R.id.homeworkET);

        //save layout values to strings
        String className = classET.getText().toString(),
                homework = homeworkET.getText().toString(),
                date;

        //create the date string
        if(hwMonth!=0)
        {
            //add leading 0 if < 10
            if(hwMonth<10)
                date="0"+hwMonth;
            else
                date=""+ hwMonth;

            //insert /
            date+="/";

            //add leading 0 if < 10
            if(hwDay<10)
                date+="0"+hwDay;
            else
                date+=hwDay;

            //add / and year

            date += "/" + hwYear;
        }
        else
        {
            Date d = new Date();
            SimpleDateFormat df = new SimpleDateFormat("MM/dd/yyyy");
            date = df.format(d);
        }

        //clear strings
        classET.setText("");
        homeworkET.setText("");

        //create a homework item and add it to the database if all fields are full
        if(!className.isEmpty() && !homework.isEmpty())
        {
            HomeWorkItem item = new HomeWorkItem(0, className, homework, date, 0);
            manager.add(item);

            //message to the screen
            Toast.makeText(this,homework + " added",Toast.LENGTH_SHORT).show();
        }else
        {
            //message to the screen
            Toast.makeText(this,"Error: all fields need a value",Toast.LENGTH_SHORT).show();
        }
    }
}
