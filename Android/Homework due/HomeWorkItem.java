package edu.niu.cs.z981329.assignment4;

/*
    HomeWorkItem

    represents the homework item that going into the database
 */
public class HomeWorkItem
{
    private  int id;
    private String className;
    private String homework;
    private String due;
    private Boolean checked;

    /*
        HomeWorkItem

        Constructor to set the instance variables
     */
    HomeWorkItem(int id, String className, String homework, String due,int checked)
    {
        this.id = id;
        this.className = className;
        this.homework = homework;
        this.due = due;
        this.checked = checked != 0;
    }

    /*
        getID

        returns the id
     */
    public int getId()
    {
        return id;
    }

    /*
        getClassName

        returns the name
     */
    public String getClassName()
    {
        return className;
    }

    /*
        getHomework

        returns the assignment
     */
    public String getHomework()
    {
        return homework;
    }

    public String getDue()
    {
        return due;
    }

    /*
        getChecked

        returns if the item is checked
     */
    public Boolean getChecked()
    {
        return checked;
    }

    /*
        setChecked

        sets if the item is checked
     */
    public void setChecked(Boolean checked)
    {
        this.checked = checked;
    }

    /*
        toString

        used to display the items info
     */
    @Override
    public String toString()
    {
        return className +"   |   "+ homework + "   |   " + due;
    }
}
