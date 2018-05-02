import javax.sound.sampled.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

/*
    Ball

    contains information about a ball that will be drawn to the screen
 */
class Ball
{
    //instance variables
    private Color color;
    private int radius;
    private int x;
    private int y;
    private int dx;
    private int dy;
    private Clip bounce;

    /*
        constructor
     */
    Ball(Color color, int radius, int x, int y, int dx, int dy)
    {
        //sets the ball info
        this.color = color;
        this.radius = radius;
        this.x = x;
        this.y = y;
        this.dx = dx;
        this.dy = dy;
        //create the sounds used
        try
        {
            //gets a list of mixers available to the system
            Mixer.Info[] mixInfo = AudioSystem.getMixerInfo();

            //use the first one
            Mixer mixer = AudioSystem.getMixer(mixInfo[0]);

            //create the data info
            DataLine.Info dataInfo = new DataLine.Info(Clip.class, null);

            //assigns a line to bounce
            bounce = (Clip) mixer.getLine(dataInfo);

            //creates an audio stream for bounce.wav
            AudioInputStream bounceStream = AudioSystem.getAudioInputStream(new File("bounce.wav"));

            //opens the file
            bounce.open(bounceStream);
        } catch (UnsupportedAudioFileException | IOException | LineUnavailableException e)
        {
            //print any exceptions
            e.printStackTrace();
        }

    }

    /*
        move

        Moves the ball while keeping it withing the boarder
     */
    void move(Dimension d)
    {
        //checks if ball contacts the right or left
        if(x-radius<Math.abs(dx) && dx<0 )
        {
            if(bounce!=null)
                bounce.loop(1);
            dx *= -1;
        }
        else if(x+radius>d.width-Math.abs(dx) && dx>0)
        {
            if(bounce!=null)
                bounce.loop(1);
            dx *= -1;
        }

        //checks if the ball contacts the top or bottom
        if(y-radius<Math.abs(dy) && dy <0 )
        {
            if(bounce!=null)
                bounce.loop(1);
            dy *= -1;
        }
        else if(y+radius>d.height-Math.abs(dy) && dy>0)
        {
            if(bounce!=null)
                bounce.loop(1);
            dy *= -1;
        }

        //move ball
        x+=dx;
        y+=dy;
    }

    /*
        draw

        used to draw the ball to the screen
     */
    void draw(Graphics g)
    {
        g.setColor(color);
        g.fillOval(x-radius,y-radius,radius*2,radius*2);
    }

    /*
        X1

        returns the top X corner
     */
    int X1()
    {
        return x-radius;
    }

    /*
        Y1

        returns the top Y corner
     */
    int Y1()
    {
        return y-radius;
    }

    /*
        getRadius

        return the radius of the circle
     */
    int getRadius()
    {
        return radius;
    }

    /*
        getDx

        returns the dx
     */
    int getDx()
    {
        return dx;
    }

    /*
        getDy

        returns the dy
     */
    int getDy()
    {
        return dy;
    }

    /*
        setDx

        updates the dx
     */
    void setDx(int value)
    {
        dx=value;
    }

    /*
        setDy

        updates the dy
     */
    void setDy(int value)
    {
        dy=value;
    }

    /*
        getVector

        returns the direction the ball is moving using a 4 quadrant system
     */
    int getVector()
    {
        int vector=0;

        if(dx>=0 && dy<=0)
            vector = 1;

        if(dx>0 && dy>=0)
            vector = 2;

        if(dx<=0 && dy>=0)
            vector = 3;

        if(dx<=0 && dy<=0)
            vector = 4;

        return vector;
    }

    /*
        getSpeed

        returns the distance the ball is moving each frame
     */
    double getSpeed()
    {
        return Math.sqrt(dx*dx+dy*dy);
    }

    /*
        playSound

        plays the bounce sound
     */
    void playSound()
    {
        bounce.loop(1);
    }
}
