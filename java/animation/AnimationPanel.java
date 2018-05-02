import javax.sound.sampled.*;
import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;

/*
    AnimationPanel

    This panel will produce the animation
 */
public class AnimationPanel extends JPanel implements Runnable
{
    //instance variables
    private ArrayList<Ball> balls;
    private Dimension dimension;
    private Thread thread;
    private Clip background;
    private boolean [] collision;
    private int frames;

    /*
        Constructor
     */
    AnimationPanel(int frames)
    {
        //set the starting values
        this.frames= frames;
        balls = new ArrayList<>();
        dimension = null;
        thread = null;
        collision = new boolean[]{false,false,false};

        //create the sounds used
        try
        {
            //gets a list of mixers available to the system
            Mixer.Info[] mixInfo = AudioSystem.getMixerInfo();

            //use the first one
            Mixer mixer = AudioSystem.getMixer(mixInfo[0]);

            //create the data info
            DataLine.Info dataInfo = new DataLine.Info(Clip.class, null);

            //assigns a line to background
            background = (Clip) mixer.getLine(dataInfo);

            //creates an audio stream for background.wav
            AudioInputStream bgStream = AudioSystem.getAudioInputStream(new File("background.wav"));

            //opens the file
            background.open(bgStream);
        } catch (UnsupportedAudioFileException | IOException | LineUnavailableException e)
        {
            //print any exceptions
            e.printStackTrace();
        }
    }

    /*
        start

        creates and starts the animation thread
     */
    void start()
    {
        //creates a new thread of this class
        thread = new Thread(this);

        //starts the thread which runs runs
        thread.start();
    }

    /*
        stop

        stops the animation thread
     */
    void stop()
    {
        //interrupt the thread and sets it for garbage collection
        thread.interrupt();
        thread=null;
    }

    /*
        paintComponent

        Overrides the paintComponents to animate our balls
     */
    @Override
    protected void paintComponent(Graphics g)
    {
        //calls the original paintComponent
        super.paintComponent(g);

        //if the first time get the dimensions so and create the objects to draw
        if(dimension==null)
        {
            //get the dimension
            dimension = getSize();

            //create a new random number list
            Random random = new Random();

            //create our three ball colors
            Color[] colors = new Color[3];
            colors[0] = Color.RED;
            colors[1] = Color.BLUE;
            colors[2] = Color.GREEN;

            //create the three balls
            for (int i = 0; i < 3; i++)
            {
                //set radius
                int radius = 22;

                //random location
                int x = i * 100 + random.nextInt(100);
                int y = i * 100 + random.nextInt(100);

                //random speed and direction
                int dx = random.nextInt(4) + 3;
                int dy = random.nextInt(4) + 3;
                if (random.nextInt(2) == 0)
                    dx *= -1;
                if (random.nextInt(2) == 0)
                    dy *= -1;

                //add the ball to the arraylist
                balls.add(new Ball(colors[i], radius, x, y, dx, dy));
            }
        }else
            dimension=getSize();

        //draw the background
        g.setColor(Color.BLACK);
        g.fillRect(0, 0, dimension.width, dimension.height);

        //draw the balls
        for(Ball ball : balls)
        {
            ball.draw(g);
        }
    }

    /*
        run

        called when the thread starts
     */
    @Override
    public void run()
    {
        //plays the background music
        if(background!=null)
            background.loop(Clip.LOOP_CONTINUOUSLY);

        //while the thread continues
        while (Thread.currentThread() == thread)
        {
            //check collision
            //sets the collision index
            int collisionIndex = 0;

            //for each ball but the last
            for (int firstBall = 0; firstBall < balls.size() - 1; firstBall++)
            {
                //creates a rectangle for the current ball for collision detection
                Rectangle ballRec = new Rectangle(balls.get(firstBall).X1(), balls.get(firstBall).Y1(), balls.get(firstBall).getRadius() * 2, balls.get(firstBall).getRadius() * 2);

                //from the next ball to the end
                for (int otherBall = firstBall + 1; otherBall < balls.size(); otherBall++)
                {
                    //create a rectangle for the next ball
                    Rectangle otherBallRec = new Rectangle(balls.get(otherBall).X1(), balls.get(otherBall).Y1(), balls.get(otherBall).getRadius() * 2, balls.get(otherBall).getRadius() * 2);

                    //check for a new collision
                    if (ballRec.intersects(otherBallRec) && !collision[collisionIndex])
                    {
                        //handle the collision and set the collision to true
                        handleCollision(balls.get(firstBall), balls.get(otherBall));
                        collision[collisionIndex] = true;
                    }

                    //increase to the next collision
                    collisionIndex++;
                }
            }

            //clear old collisions
            collisionIndex = 0;

            //for each ball but the last
            for (int firstBall = 0; firstBall < balls.size() - 1; firstBall++)
            {
                //create the rectangle for the ball
                Rectangle ballRec = new Rectangle(balls.get(firstBall).X1(), balls.get(firstBall).Y1(), balls.get(firstBall).getRadius() * 2, balls.get(firstBall).getRadius() * 2);

                //for each other ball
                for (int otherBall = firstBall + 1; otherBall < balls.size(); otherBall++)
                {
                    //create other rectangle
                    Rectangle otherBallRec = new Rectangle(balls.get(otherBall).X1(), balls.get(otherBall).Y1(), balls.get(otherBall).getRadius() * 2, balls.get(otherBall).getRadius() * 2);

                    //check if there is no collision and there was one in the past
                    //if so clear the collision
                    if (!ballRec.intersects(otherBallRec) && collision[collisionIndex])
                        collision[collisionIndex] = false;

                    //go to next collision
                    collisionIndex++;
                }
            }

            //move each ball
            for (Ball ball : balls)
            {
                ball.move(dimension);
            }

            //redraw the screen
            repaint();

            try
            {
                //pause the thread
                Thread.sleep(1000 / frames);
            } catch (InterruptedException e)
            {
                //stops the background music
                if(background!=null)
                    background.stop();

                //return which leaves the while loop
                return;
            }
        }

        //stops the background music
        if(background!=null)
            background.stop();
    }

    /*
        handleCollision

        is call when ywo balls collide and handles how they bounce off
     */
    private void handleCollision(Ball ball1,Ball ball2)
    {
        //play the bounce sound
        ball1.playSound();

        //get the direction that the ball is going
        int ball1Vector=ball1.getVector();
        int ball2Vector=ball2.getVector();

        //if the same direction
        if(ball1Vector==ball2Vector)
        {
            int lowDx,highDx,lowDy,highDy;

            //get high and low dx values
            if(Math.abs(ball1.getDx())<=Math.abs(ball2.getDx()))
            {
                lowDx=ball1.getDx();
                highDx=ball2.getDx();
            }else
            {
                lowDx=ball2.getDx();
                highDx=ball1.getDx();
            }

            //get high and low dy values
            if(Math.abs(ball1.getDy())<=Math.abs(ball2.getDy()))
            {
                lowDy=ball1.getDy();
                highDy=ball2.getDy();
            }else
            {
                lowDy=ball2.getDy();
                highDy=ball1.getDy();
            }

            //get balls speed and set new movement based on the speed
            //the slower one gets the faster speed
            if(ball1.getSpeed()<=ball2.getSpeed())
            {
                ball1.setDx(highDx);
                ball1.setDy(highDy);

                ball2.setDx(lowDx);
                ball2.setDy(lowDy);
            }else
            {
                ball2.setDx(highDx);
                ball2.setDy(highDy);

                ball1.setDx(lowDx);
                ball1.setDy(lowDy);
            }

        }

        //same direction on x axis
        else if((ball1.getDx()>=0 && ball2.getDx()>=0) || (ball1.getDx()<0 && ball2.getDx()<0))
        {
            //swap the direction on the y
            ball1.setDy(ball1.getDy()*-1);
            ball2.setDy(ball2.getDy()*-1);
        }

        //same direction on y axis
        else if((ball1.getDy()>=0 && ball2.getDy()>=0) || (ball1.getDy()<0 && ball2.getDy()<0))
        {
            //swap the direction on the x
            ball1.setDx(ball1.getDx()*-1);
            ball2.setDx(ball2.getDx()*-1);
        }

        //final case
        else
        {
            //reverse direction on both x and y
            ball1.setDx(ball1.getDx()*-1);
            ball1.setDy(ball1.getDy()*-1);

            ball2.setDx(ball2.getDx()*-1);
            ball2.setDy(ball2.getDy()*-1);
        }
    }

    void setFrames(int frames)
    {
        this.frames=frames;
    }
}
