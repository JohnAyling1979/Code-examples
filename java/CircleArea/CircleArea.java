import java.awt.*;
import java.awt.event.*;
import java.text.DecimalFormat;
import javax.swing.*;

public class CircleArea extends JFrame implements ActionListener {

    private static final long serialVersionUID = 1L;

    private JButton calculateButton;
    private JButton clearButton;
    private JTextField radiusField;
    private JTextField areaField;

    public static void main(String[] args) {
    EventQueue.invokeLater(()->
    {
        CircleArea frame = new CircleArea("Compute Circle Area");
        frame.createAndShowGUI();
    });
    }

    private CircleArea(String title) {
        super(title);
    }

    /**
     * Create the GUI and show it. For thread safety, this method should
     * be invoked from the event-dispatch thread.
     */
    private void createAndShowGUI() {

        initComponents();
        addListeners();

        // Display the window.
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }

    /**
     * Set the frame's layout, create the UI components, and add them to the layout
     */
    private void initComponents() {
        // TODO code application logic here
        //create the controls
        calculateButton = new JButton("Calculate");
        clearButton = new JButton("Clear");
        radiusField = new JTextField();
        areaField = new JTextField();

        //set the layout to grid and lock size
        setLayout(new GridLayout(3,2,20,10));
        setResizable(false);

        //set the preferred size and center to the screen
        setLocationRelativeTo(null);
        setPreferredSize(new Dimension(300,150));

        //add the components to the grid
        add(new JLabel("Radius"));
        add(radiusField);
        add(new JLabel("Area"));
        add(areaField);
        add(calculateButton);
        add(clearButton);

        //set the area field to uneditable
        areaField.setEditable(false);
    }

    /**
     * Add listeners for the "Calculate" and "Clear" buttons
     */
    private void addListeners() {
        // TODO code application logic here

        //connect the buttons to the listener
        calculateButton.addActionListener(this);
        clearButton.addActionListener(this);
    }

    /**
     * Handle ActionEvents from the "Calculate" and "Clear" buttons
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        // TODO code application logic here
        //for the calculate button
        if(e.getActionCommand().equals("Calculate"))
        {
            try
            {
                //create the pattern
                DecimalFormat df = new DecimalFormat("#0.00");

                //calculate the area
                double area = Math.PI * Double.parseDouble(radiusField.getText()) * Double.parseDouble(radiusField.getText());

                //update the GUI
                areaField.setText(df.format(area));
            }catch (NumberFormatException ex)
            {
                //if the radius was not a number display message
                areaField.setText("Invalid radius");
            }
        }

        //for the clear button
        if(e.getActionCommand().equals("Clear"))
        {
            //empty both values
            radiusField.setText("");
            areaField.setText("");
        }
    }
}
