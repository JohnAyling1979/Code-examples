package edu.niu.cs.z981329.hawaii;
/*
    Program:    Sounds
    Author:     John Ayling
    Due:        3/23/18
    Notes:      to play sounds with button click
 */
import android.app.Activity;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;


/*
    MainActivity class loads after splash screen
*/
public class MainActivity extends Activity
{
    private Button ukuButton, drumButton;
    private MediaPlayer ukuMP, drumMP;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //set connection
        ukuButton=findViewById(R.id.ukuleleButton);
        drumButton=findViewById(R.id.drumButton);

        //create the media player for the ukulele mp3
        ukuMP = new MediaPlayer();
        ukuMP = MediaPlayer.create(this,R.raw.ukulele);

        //create the media player for the drum mp3
        drumMP = new MediaPlayer();
        drumMP = MediaPlayer.create(this,R.raw.drums);
    }//end on create

    public void playUku(View view)
    {
        //if playing
        if (ukuMP.isPlaying())
        {
            //pause the sound and update the button
            ukuMP.pause();
            ukuButton.setText(R.string.playuku);
        } else
        {
            if (drumMP.isPlaying())
            {
                //pause the sound and update the button
                drumMP.pause();
                drumButton.setText(R.string.playdrum);
            }//end if

            //start the sound and update the button
            ukuMP.start();
            ukuButton.setText(R.string.stopuku);
        }//end if/else
    }//end playUku

    public void playDrum(View view)
    {
        //if playing
        if(drumMP.isPlaying())
        {
            //pause the sound and update the button
            drumMP.pause();
            drumButton.setText(R.string.playdrum);
        }else
        {
            if(ukuMP.isPlaying())
            {
                //pause the sound and update the button
                ukuMP.pause();
                ukuButton.setText(R.string.playuku);
            }//end if

            //start the sound and update the button
            drumMP.start();
            drumButton.setText(R.string.stopdrum);
        }//end if/else

    }//end playUku

}//end mainActivity
