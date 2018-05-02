package edu.niu.cs.z981329.assignment4;

import android.content.Context;
import android.support.v7.widget.AppCompatCheckBox;
import android.util.AttributeSet;

/*
    HomeworkButton

    This is a checkbox button that contains a homeworking item
 */
public class HomeworkButton extends AppCompatCheckBox
{
    private HomeWorkItem homeWorkItem;

    /*
        HomeworkButton

        constructor to connect the item to the button
     */
    public HomeworkButton(Context context,HomeWorkItem item)
    {
        super(context);
        homeWorkItem=item;
    }

    /*
        HomeworkButton

        constructor used by system
     */
    public HomeworkButton(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    /*
            getHomeWorkItem

            used to get the item from the button
         */
    public HomeWorkItem getHomeWorkItem()
    {
        return homeWorkItem;
    }
}
