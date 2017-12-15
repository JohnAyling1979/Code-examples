import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Frame1 extends JFrame
{
	JPanel pane = new JPanel();
	JButton pressme = new JButton("Press Me");

	Frame1()
	{
		setTitle("My Simple Frame");
		setLayout(new FlowLayout());
//		pane.add(pressme);
		add(pane);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

	public static void main(String args[])
	{
		Frame1 mine=new Frame1();

		mine.setSize(300,225);
		mine.setVisible(true);
	}
}
