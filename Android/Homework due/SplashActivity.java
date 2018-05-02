package edu.niu.cs.z981329.assignment4;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import java.util.Timer;
import java.util.TimerTask;

/*
    SplashActivity

    First screen
 */
public class SplashActivity extends AppCompatActivity
{
    /*
        onCreate

        called at the start
     */
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash);

        //create the TimerTask
        TimerTask task = new TimerTask()
        {
            @Override
            public void run()
            {
                finish();
                startActivity(new Intent(SplashActivity.this,MainActivity.class));
            }
        };

        //create the timer to run the task
        Timer timer = new Timer();
        timer.schedule(task,2000);
    }
}
