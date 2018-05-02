package edu.niu.cs.z981329.assignment4;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import java.util.ArrayList;

/*
    DataBaseManager

    Used to communicate to the SQLiteDatabase
 */
public class DataBaseManager extends SQLiteOpenHelper
{
    private static final String DATABASE_NAME = "homeworkDB",
            TABLE_NAME = "homework",
            ID = "id",
            CLASSNAME = "className",
            HOMEWORK = "homework",
            DUE = "due",
            DONE = "done";
    private static final int VERSION_NUMBER = 1;

    /*
        DataBaseManager

        constructor call the super constructor
     */
    public DataBaseManager(Context context)
    {
        super(context, DATABASE_NAME, null, VERSION_NUMBER);
    }

    /*
        onCreate

        called when the DB is first created
     */
    @Override
    public void onCreate(SQLiteDatabase db)
    {
        String sqlCreate="create table " + TABLE_NAME +"( "+
                ID + " integer primary key autoincrement, " +
                CLASSNAME + " text, " +
                HOMEWORK + " text, " +
                DUE + " text, " +
                DONE + " integer" +
                " )";

        db.execSQL(sqlCreate);
    }

    /*
        onUpgrade

        called when the version number is changed
     */
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion)
    {
        String dropDB = "drop table if exists " + TABLE_NAME;

        db.execSQL(dropDB);

        onCreate(db);
    }

    /*
        add

        called to add an item to the DB
     */
    public void add(HomeWorkItem item)
    {
        SQLiteDatabase database=getWritableDatabase();

        String insertSql = "insert into " + TABLE_NAME + " values( " +
                "null," +
                " '" + item.getClassName() + "'," +
                " '" + item.getHomework()  + "'," +
                " '" + item.getDue()       + "'," +
                " "  + 0                   + " "  +
                ")";

        database.execSQL(insertSql);
        database.close();
    }

    /*
        update

        called to update when item is checked
     */
    public void update(HomeWorkItem item)
    {
        //Get the DB
        SQLiteDatabase database=getWritableDatabase();
        int checked;

        //change from bool to int for DB
        if(item.getChecked())
            checked=1;
        else
            checked=0;

        String updateSql = "update " + TABLE_NAME + " set " + DONE + " = " + checked +
                " where "+ ID + " = " + item.getId();

        database.execSQL(updateSql);
        database.close();
    }

    /*
        deleteItem

        called to delete an item from the DB
     */
    public void deleteItem(HomeWorkItem item)
    {
        //Get the DB
        SQLiteDatabase database=getWritableDatabase();

        String sql = "delete from " + TABLE_NAME + " where " + ID + " = " + item.getId();

        database.execSQL(sql);
        database.close();
    }

    /*
        reset

        called to remove all items from the DB
     */
    public void reset()
    {
        SQLiteDatabase database=getWritableDatabase();

        database.delete(TABLE_NAME,null,null);
    }

    /*
        selectAll

        called to et all items from the DB
     */
    public ArrayList<HomeWorkItem> selectAll()
    {
        String query = "select * from " + TABLE_NAME;

        SQLiteDatabase db = getReadableDatabase();

        Cursor cursor = db.rawQuery(query,null);

        ArrayList<HomeWorkItem> table = new ArrayList<>();

        //add a new work item for each row in the DB
        while(cursor.moveToNext())
            table.add(new HomeWorkItem(cursor.getInt(0),cursor.getString(1),
                    cursor.getString(2),cursor.getString(3),cursor.getInt(4)));

        db.close();
        cursor.close();

        return table;
    }
}
