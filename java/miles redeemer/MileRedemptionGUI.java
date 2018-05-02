/*
    Program:    Assignment 2
    Author:     John Ayling
    Due:        3/21/2018
    Function:   This program creates a GUI where the user can enter miles to check what tickets could
                be purchased
 */

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

/*
    Class:      MileRedemptionGUI

    Notes:      This class contains the main function and inherits from JFrame
 */
public class MileRedemptionGUI extends JFrame
{
    //constant
    private final int INFO_COL_WIDTH = 10;
    private final String[] MONTHS = getMonthStrings();
    private final Color CITY_COLOR = new Color(150,150,200);
    private final Color MILES_COLOR = new Color(200,200,210);
    private final Color FRAME_COLOR = new Color(0,0,0);

    //components
    private JList<String> cityList = new JList<>(MilesRedeemer.getCityNames());
    private JLabel normalMilesLabel = new JLabel("Required Miles:",SwingConstants.RIGHT);
    private JLabel upgradeMilesLabel = new JLabel("Miles for Upgrading:",SwingConstants.RIGHT);
    private JLabel superSaverMilesLabel = new JLabel("Miles for SuperSaver:",SwingConstants.RIGHT);
    private JLabel monthsLabel = new JLabel("Months for SuperSaver:",SwingConstants.RIGHT);
    private JLabel accumulatedMilesLabel = new JLabel("Your Accumulated Miles:",SwingConstants.RIGHT);
    private JLabel monthOfDLabel = new JLabel("Month of Departure:",SwingConstants.RIGHT);
    private JLabel remainingMilesLabel = new JLabel("Your Remaining Miles:",SwingConstants.RIGHT);
    private JTextField normalMilesText = new JTextField(INFO_COL_WIDTH);
    private JTextField upgradeMilesText = new JTextField(INFO_COL_WIDTH);
    private JTextField superSaverMilesText = new JTextField(INFO_COL_WIDTH);
    private JTextField monthsText = new JTextField(INFO_COL_WIDTH);
    private JTextField accumulatedMilesText = new JTextField(INFO_COL_WIDTH);
    private JTextField remainingMilesText = new JTextField(INFO_COL_WIDTH);
    private JTextArea output = new JTextArea("",10,37);
    private JSpinner monthOfDSpinner = new JSpinner(new SpinnerListModel(MONTHS));
    private JButton redeemButton = new JButton("Redeem Tickets >>>");

    //Entry method
    public static void main(String[] args)
    {
        try
        {
            //open the file
            File inFile = new File("miles.txt");
            Scanner scInFile = new Scanner(inFile);

            //read the file
            MilesRedeemer.readDestinations(scInFile);
        }catch(FileNotFoundException e)
        {
            System.out.println(e.getMessage());
            System.exit(1);
        }

        javax.swing.SwingUtilities.invokeLater(()->
                new MileRedemptionGUI("Airline Mileage Redemption"));
    }

    //constructor
    private MileRedemptionGUI(String title)
    {
        //set the title and assign window properties
        super(title);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setResizable(false);

        //adds the components to the various panels
        addComponentsToPane(getContentPane());

        //set listeners
        setListeners();

        //show the frame
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    /*
        Method:     addComponentsToPane

        Usage:      creates the various panels and adds the components
     */
    private void addComponentsToPane(Container pane)
    {
        //local constant
        final int V_GAP = 10;
        final int H_GAP = 10;

        //create panels
        JPanel mainCityPanel = new JPanel(new GridLayout(2,1,H_GAP,V_GAP));
        JPanel redeemPanel = new JPanel(new BorderLayout(H_GAP,V_GAP));
        JPanel redeemTopPanel = new JPanel(new GridLayout(3,2,H_GAP,V_GAP));
        JPanel redeemBottomPanel = new JPanel(new GridLayout(1,2,H_GAP,0));
        JPanel infoPanel = new JPanel(new GridLayout(4,2,H_GAP,V_GAP));
        JScrollPane cityPanel = new JScrollPane(cityList);
        JScrollPane outputPanel = new JScrollPane(output);

        //set textFields to uneditable
        normalMilesText.setEditable(false);
        upgradeMilesText.setEditable(false);
        superSaverMilesText.setEditable(false);
        monthsText.setEditable(false);
        remainingMilesText.setEditable(false);
        output.setEditable(false);
        //taken from stack overflow
        ((JSpinner.DefaultEditor) monthOfDSpinner.getEditor()).getTextField().setEnabled(false);
        ((JSpinner.DefaultEditor) monthOfDSpinner.getEditor()).getTextField().setDisabledTextColor(Color.BLACK);

        //add to info panel
        infoPanel.add(normalMilesLabel);
        infoPanel.add(normalMilesText);
        infoPanel.add(upgradeMilesLabel);
        infoPanel.add(upgradeMilesText);
        infoPanel.add(superSaverMilesLabel);
        infoPanel.add(superSaverMilesText);
        infoPanel.add(monthsLabel);
        infoPanel.add(monthsText);

        //add to redeem top
        redeemTopPanel.add(accumulatedMilesLabel);
        redeemTopPanel.add(accumulatedMilesText);
        redeemTopPanel.add(monthOfDLabel);
        redeemTopPanel.add(monthOfDSpinner);
        redeemTopPanel.add(new JLabel(""));//to skip a cell
        redeemTopPanel.add(redeemButton);

        //add to redeem bottom
        redeemBottomPanel.add(remainingMilesLabel);
        redeemBottomPanel.add(remainingMilesText);

        //add to city panel
        mainCityPanel.add(cityPanel);
        mainCityPanel.add(infoPanel);

        //add to redeem panel
        redeemPanel.add(redeemTopPanel,BorderLayout.PAGE_START);
        redeemPanel.add(outputPanel,BorderLayout.CENTER);
        redeemPanel.add(redeemBottomPanel,BorderLayout.PAGE_END);

        //add borders
        mainCityPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),"List of Destination Cities"));
        redeemPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),"Redeem Tickets"));

        //set background colors
        pane.setBackground(FRAME_COLOR);
        mainCityPanel.setBackground(CITY_COLOR);
        cityPanel.setBackground(CITY_COLOR);
        infoPanel.setBackground(CITY_COLOR);
        redeemPanel.setBackground(MILES_COLOR);
        redeemTopPanel.setBackground(MILES_COLOR);
        redeemBottomPanel.setBackground(MILES_COLOR);

        //add panels to the frame
        pane.add(mainCityPanel,BorderLayout.LINE_START);
        pane.add(redeemPanel, BorderLayout.CENTER);
    }

    /*
        Method:     setListeners

        Usage:      contains all the listeners used in the program
     */
    private void setListeners()
    {
        //listener for the list selector
        cityList.addListSelectionListener(e ->
        {
            //get the destination info
            Destination currentCity= MilesRedeemer.findDestination(cityList.getSelectedValue());

            if(currentCity!=null)
            {
                //updates the info and breaks out of loop
                normalMilesText.setText(String.valueOf(currentCity.getNormalMiles()));
                upgradeMilesText.setText(String.valueOf(currentCity.getMilesToUpgrade()));
                superSaverMilesText.setText(String.valueOf(currentCity.getSupersaverMiles()));
                monthsText.setText(MONTHS[currentCity.getStartMonth() - 1] + " to " +
                        MONTHS[currentCity.getEndMonth() - 1]);
            }else
                output.setText("Unknown city :(");//will never run
        });

        //listener for when button is clicked
        redeemButton.addActionListener(e ->
        {
            //local variables
            ArrayList<String> tickets;
            String month=(String)monthOfDSpinner.getValue();
            int monthInt=0;

            //changes string value to int
            for(;monthInt<MONTHS.length;monthInt++)
                if(month.equals(MONTHS[monthInt]))
                    break;
            monthInt++;

            //try for valid values
            try
            {
                //get ticket list from MilesRedeemer
                tickets = MilesRedeemer.redeemMiles(Integer.parseInt(accumulatedMilesText.getText()), monthInt);

                //reset output
                output.setText("Your accumulated miles can be used to redeem the following air tickets\n\n");

                //add tickets to output
                for(String ticket : tickets)
                {
                    output.append(ticket);
                    output.append("\n");
                }

                //update the remaining miles
                remainingMilesText.setText(String.valueOf(MilesRedeemer.getRemainingMiles()));
            }
            //if a non number was entered from miles
            catch (NumberFormatException ex)
            {
                output.setText("Invalid miles amount");
                remainingMilesText.setText("");
            }
        });
    }

    //taken from assignment removes empty string at end and returns the array
    private String[] getMonthStrings() {
        String[] months = new java.text.DateFormatSymbols().getMonths();
        int lastIndex = months.length - 1;
        if (months[lastIndex] == null || months[lastIndex].length() <= 0) {
            //last item empty
            String[] monthStrings = new String[lastIndex];
            System.arraycopy(months, 0, monthStrings, 0, lastIndex);
            return monthStrings;
        } else {
            //last item not empty
            return months;
        }
    }
}
