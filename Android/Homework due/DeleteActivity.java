package edu.niu.cs.z981329.assignment4;

import android.graphics.Paint;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

/*
    DeleteActivity

    used to show the delete screen
 */
public class DeleteActivity extends AppCompatActivity
{
    DataBaseManager manager;

    /*
        onCreate

        called at the start to show the screen
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_delete);

        manager=new DataBaseManager(this);

        updateView();
    }

    /*
        inResume

        called to make sure the screen is repopulated
     */
    @Override
    protected void onResume()
    {
        super.onResume();

        updateView();
    }

    /*
        updateView

        called to show the database items on the screen
     */
    public void updateView()
    {
        //get the scroll view and remove any old data
        ScrollView scrollView =findViewById(R.id.delSV);
        scrollView.removeAllViewsInLayout();

        //create a new layout
        LinearLayout layout = new LinearLayout(this);
        layout.setOrientation(LinearLayout.VERTICAL);

        //get all the items from the database
        ArrayList<HomeWorkItem> table = manager.selectAll();

        //sort by date
        Collections.sort(table, new Comparator<HomeWorkItem>()
        {
            @Override
            public int compare(HomeWorkItem o1, HomeWorkItem o2)
            {
                return o1.getDue().compareTo(o2.getDue());
            }
        });

        //add a header
        TextView header=new TextView(this);
        header.setTextSize(24);
        header.setText(R.string.delHeader);
        header.setPaintFlags(header.getPaintFlags() | Paint.UNDERLINE_TEXT_FLAG);
        layout.addView(header);

        //add each item
        for(final HomeWorkItem item : table)
        {
            //create a new TV
            HomeworkButton checkBox= new HomeworkButton(this,item);

            //set the text and size
            checkBox.setText(item.toString());
            checkBox.setTextSize(18);

            //attach a listener
            checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
            {
                @Override
                public void onCheckedChanged(CompoundButton buttonView, boolean isChecked)
                {
                    //cast the button
                    HomeworkButton button=(HomeworkButton)buttonView;

                    //get attached item
                    HomeWorkItem item=button.getHomeWorkItem();

                    //update database and refresh the view
                    manager.deleteItem(item);
                    updateView();
                }
            });

            //add it to the layout
            layout.addView(checkBox);
        }

        //add the back button
        Button backBt = new Button(this);
        backBt.setText(R.string.back);
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
                ViewGroup.LayoutParams.WRAP_CONTENT);
        params.gravity=Gravity.CENTER;
        backBt.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                finish();
            }
        });
        layout.addView(backBt,params);

        //add whole layout to scrollView
        scrollView.addView(layout);
    }
}
