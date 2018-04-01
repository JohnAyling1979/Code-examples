/*
    Program:    Assignment 3
    Author:     John Ayling
    Due:        4/4/18
    Purpose:    To display song info downloaded from i-tunes
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

/*
    Main class
 */
public class XMLDownloader extends JFrame implements ActionListener
{
    //creates an XMLDownloadPanel and sets te pre checked values
    private XMLDownloadPanel xmlDownloadPanel=new XMLDownloadPanel("new-music",10,true);

    /*
        Main function
        called at the start
     */
    public static void main(String [] args)
    {
        //starts the GUI in the invoke later thread
        javax.swing.SwingUtilities.invokeLater(XMLDownloader::new);
    }

    /*
        Constructor for the class
     */
    private XMLDownloader()
    {
        //calls JFrame constructor to set the title
        super("ITunes Store Albums");

        //creates the GUI
        createAndShowGUI();
    }

    /*
        Creates the GUI
     */
    private void createAndShowGUI()
    {
        //sets the frame properties
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setPreferredSize(new Dimension(900,500));
        setMinimumSize(new Dimension(500,330));

        //sets the frame to a border layout
        setLayout(new BorderLayout());

        //panel going into the center
        add(xmlDownloadPanel,BorderLayout.CENTER);

        //creates the menu
        createMenu();

        //show the frame
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    /*
        Creates the menu interface
     */
    private void createMenu()
    {
        //creates the menu bar and 3 menus
        JMenuBar menuBar = new JMenuBar();
        JMenu typeMenu = new JMenu("Type");
        JMenu limitMenu = new JMenu("Limit");
        JMenu explicitMenu = new JMenu("Explicit");

        //adds the three menus to the bar
        menuBar.add(typeMenu);
        menuBar.add(limitMenu);
        menuBar.add(explicitMenu);

        //set Mnemonics
        typeMenu.setMnemonic(KeyEvent.VK_T);
        limitMenu.setMnemonic(KeyEvent.VK_L);
        explicitMenu.setMnemonic(KeyEvent.VK_E);

        //set tooltips
        typeMenu.setToolTipText("Select the type of albums");
        limitMenu.setToolTipText("Select number of albums to display");
        explicitMenu.setToolTipText("Select if to include explicit albums");

        //creates the 3 ButtonGroups
        ButtonGroup typeButtonGroup = new ButtonGroup();
        ButtonGroup limitButtonGroup = new ButtonGroup();
        ButtonGroup explicitButtonGroup = new ButtonGroup();

        //creates the buttons
        //type
        JRadioButtonMenuItem newButton = new JRadioButtonMenuItem("New Music");
        newButton.setSelected(true);
        JRadioButtonMenuItem recentButton = new JRadioButtonMenuItem("Recent Releases");
        JRadioButtonMenuItem topButton = new JRadioButtonMenuItem("Top Albums");
        //limit
        JRadioButtonMenuItem tenButton = new JRadioButtonMenuItem("10");
        tenButton.setSelected(true);
        JRadioButtonMenuItem tFiveButton = new JRadioButtonMenuItem("25");
        JRadioButtonMenuItem fiftyButton = new JRadioButtonMenuItem("50");
        JRadioButtonMenuItem hunButton = new JRadioButtonMenuItem("100");
        //explicit
        JRadioButtonMenuItem yesButton = new JRadioButtonMenuItem("Yes");
        yesButton.setSelected(true);
        JRadioButtonMenuItem noButton = new JRadioButtonMenuItem("No");

        //set accelerator
        newButton.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N,
                Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        recentButton.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_R,
                Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
        topButton.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_T,
                Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));

        //and buttons to group
        //type
        typeButtonGroup.add(newButton);
        typeButtonGroup.add(recentButton);
        typeButtonGroup.add(topButton);
        //limit
        limitButtonGroup.add(tenButton);
        limitButtonGroup.add(tFiveButton);
        limitButtonGroup.add(fiftyButton);
        limitButtonGroup.add(hunButton);
        //explicit
        explicitButtonGroup.add(yesButton);
        explicitButtonGroup.add(noButton);

        //add buttons to the menu
        //type
        typeMenu.add(newButton);
        typeMenu.add(recentButton);
        typeMenu.add(topButton);
        //limit
        limitMenu.add(tenButton);
        limitMenu.add(tFiveButton);
        limitMenu.add(fiftyButton);
        limitMenu.add(hunButton);
        //explicit
        explicitMenu.add(yesButton);
        explicitMenu.add(noButton);

        //sets the bar to the frame
        setJMenuBar(menuBar);

        //set the listeners
        newButton.addActionListener(this);
        recentButton.addActionListener(this);
        topButton.addActionListener(this);
        tenButton.addActionListener(this);
        tFiveButton.addActionListener(this);
        fiftyButton.addActionListener(this);
        hunButton.addActionListener(this);
        yesButton.addActionListener(this);
        noButton.addActionListener(this);

    }

    /*
        called when an action is performed
     */
    public void actionPerformed(ActionEvent event)
    {
        //sets the options
        switch (event.getActionCommand())
        {
            case "New Music":
                xmlDownloadPanel.setType("new-music");
                break;
            case "Recent Releases":
                xmlDownloadPanel.setType("recent-releases");
                break;
            case "Top Albums":
                xmlDownloadPanel.setType("top-albums");
                break;
            case "10":
                xmlDownloadPanel.setLimit(10);
                break;
            case "25":
                xmlDownloadPanel.setLimit(25);
                break;
            case "50":
                xmlDownloadPanel.setLimit(50);
                break;
            case "100":
                xmlDownloadPanel.setLimit(100);
                break;
            case "Yes":
                xmlDownloadPanel.setExplicit(true);
                break;
            case "No":
                xmlDownloadPanel.setExplicit(false);
                break;
        }
    }
}
