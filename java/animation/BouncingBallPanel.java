/*
    Program:        Assignment 4
    Author:         John Ayling
    Due:            4/16
    Notes:          Added to Assignment 3 to show animation
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/*
    Panel class to hold the animation frame and some buttons
 */
public class BouncingBallPanel extends JPanel implements ActionListener
{
    //instance variables
    private JButton startButton;
    private JButton stopButton;
    private  AnimationPanel animationPanel;
    private JSlider fps;

    /*
        Constructor

        sets up the panel and sets the button listeners
     */
    BouncingBallPanel()
    {
        //sets up the panel
        createPanel();

        //set up the listeners
        setListeners();
    }

    /*
        createPanel

        sets the layout
     */
    private void createPanel()
    {
        //sets the starting size of the panel, layout and frame rate
        setLayout(new BorderLayout());

        //creates a panel for the top area
        JPanel top=new JPanel(new FlowLayout());
        top.setPreferredSize(new Dimension(300,80));

        //creates the two buttons, animationPanel, and slider
        startButton=new JButton("Start");
        stopButton=new JButton("Stop");
        animationPanel=new AnimationPanel(30);
        fps = new JSlider(JSlider.HORIZONTAL, 10, 100, 30);

        //sets up the tick values and show the slider.
        fps.setMajorTickSpacing(10);
        fps.setPaintTicks(true);
        fps.setPaintLabels(true);

        //add all the components to the panel
        top.add(startButton);
        top.add(stopButton);
        top.add(fps);
        add(top,BorderLayout.PAGE_START);
        add(animationPanel,BorderLayout.CENTER);

        //disable stop button
        stopButton.setEnabled(false);
    }

    /*
        setListeners

        sets the listeners for the three controls
     */
    private void setListeners()
    {
        startButton.addActionListener(this);
        stopButton.addActionListener(this);
        fps.addChangeListener(e ->
        {
            JSlider in = (JSlider)e.getSource();
            animationPanel.setFrames(in.getValue());
        });
    }

    /*
        actionPerformed

        Used since implements actionListener. Controls the action
        for start and stop buttons
     */
    @Override
    public void actionPerformed(ActionEvent e)
    {
        //when start button is pressed
        if(e.getActionCommand().equals("Start"))
        {
            //swap which buttons are enabled
            startButton.setEnabled(false);
            stopButton.setEnabled(true);

            //start the animation
            animationPanel.start();
        }

        //when stop button is pressed
        if(e.getActionCommand().equals("Stop"))
        {
            //swap which buttons are enabled
            stopButton.setEnabled(false);
            startButton.setEnabled(true);

            //stop the animation
            animationPanel.stop();
        }
    }
}