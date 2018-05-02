package edu.niu.cs.z981329.assignment4;

/*
    Program:    Assignment 4
    Programmer: John Ayling
    Due:        5/3/2018
    Purpose:    To implement a SQLiteDatabase to keep track of homework assignments
 */
import android.content.Intent;
import android.graphics.Paint;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

/*
    MainActivity

    Main screen after the splash screen
 */
public class MainActivity extends AppCompatActivity
{
    //instance variable
    private DataBaseManager manager;

    /*
        onCreate

        called at the start of the activity
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        //create the database
        manager = new DataBaseManager(this);

        //dynamic update
        updateView();
    }

    /*
        onResume

        called when coming back to the activity
     */
    @Override
    protected void onResume()
    {
        super.onResume();
        updateView();
    }

    /*
        updateView

        called to dynamically allocate the screen
     */
    void updateView()
    {
        //get the scroll view and remove any old data
        ScrollView scrollView =findViewById(R.id.scrollview);
        scrollView.removeAllViewsInLayout();

        //create a new layout
        LinearLayout layout = new LinearLayout(this);
        layout.setOrientation(LinearLayout.VERTICAL);

        //get all the items from the database and sort it based on due date
        ArrayList<HomeWorkItem> table = manager.selectAll();
        Collections.sort(table, new Comparator<HomeWorkItem>()
        {
            @Override
            public int compare(HomeWorkItem o1, HomeWorkItem o2)
            {
                return o1.getDue().compareTo(o2.getDue());
            }
        });

        //create the header
        TextView header=new TextView(this);
        header.setTextSize(24);
        header.setText(R.string.header);
        header.setPaintFlags(header.getPaintFlags() | Paint.UNDERLINE_TEXT_FLAG);
        layout.addView(header);

        //for each item in DB
        for(final HomeWorkItem item : table)
        {
            //create a new Homework button
            HomeworkButton checkBox= new HomeworkButton(this,item);

            //set the text
            checkBox.setText(item.toString());

            //set checked if done
            if(item.getChecked())
                checkBox.setChecked(true);

            //set text size
            checkBox.setTextSize(18);

            //set  checkedChange listener
            checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
            {
                @Override
                public void onCheckedChanged(CompoundButton buttonView, boolean isChecked)
                {
                    //cast the button
                    HomeworkButton button=(HomeworkButton)buttonView;

                    //get attached item
                    HomeWorkItem item=button.getHomeWorkItem();

                    //update status
                    if(item.getChecked())
                        item.setChecked(false);
                    else
                        item.setChecked(true);

                    //update database
                    manager.update(item);
                }
            });

            //add it to the layout
            layout.addView(checkBox);
        }

        //and the layout to the scrollview
        scrollView.addView(layout);
    }

    /*
        onCreateOptionsMenu

        called at the start to create the menu
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    /*
        onOptionsItemSelected

        called when an menu item is selected
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        if (id == R.id.action_add)
        {
            startActivity(new Intent(MainActivity.this,AddActivity.class));
            return true;
        }
        if (id == R.id.action_delete)
        {
            startActivity(new Intent(MainActivity.this,DeleteActivity.class));
            return true;
        }
        if (id == R.id.action_reset)
        {
            manager.reset();
            updateView();
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
