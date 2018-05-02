import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import java.awt.*;

/*
    center panel class
 */
public class XMLDownloadPanel extends JPanel implements Displayer
{
    //instance variables
    private String colNames[]={"Name","Artist","Genre","Album Cover"};
    private JButton getAlbumsButton = new JButton("Get Albums");
    private JLabel timeTF = new JLabel("0:00");
    private String type;
    private int limit;
    private boolean explicit;
    private int time=0;
    private Timer timer;
    private JTable output =new JTable(new DefaultTableModel(colNames,0)
    {
        //used to set the 4th column to ImageIcon
        @Override
        public Class<?> getColumnClass(int column)
        {
            switch(column)
            {
                case 0: return String.class;
                case 1: return String.class;
                case 2: return String.class;
                case 3: return ImageIcon.class;
                default: return Object.class;
            }
        }
    });

    /*
        constructor
     */
    XMLDownloadPanel(String type, int limit, boolean explicit)
    {
        //set start values
        this.type=type;
        this.limit=limit;
        this.explicit=explicit;

        //set layout
        setLayout(new BorderLayout());

        //created panels
        JPanel top = new JPanel(new FlowLayout());
        JScrollPane scrollPane = new JScrollPane(output);

        //table properties
        output.setFillsViewportHeight(true);
        //getWidth would always return 0 so just hard coded 900
        //still work if you expand the screen
        int tW = 900;
        int columnCount = output.getColumnModel().getColumnCount();
        float[] columnWidthPercentage = {50.0f, 30.0f, 10.0f,10.0f};
        for (int i = 0; i < columnCount; i++)
        {
            TableColumn column = output.getColumnModel().getColumn(i);
            int pWidth = Math.round(columnWidthPercentage[i] * tW);
            column.setPreferredWidth(pWidth);
        }
        //sets so it can't be selected
        output.setEnabled(false);

        //sets the height for our 50x50 cover art
        output.setRowHeight(70);

        //add button to the top panel
        top.add(getAlbumsButton);
        top.add(timeTF);

        //add to main panel
        add(top,BorderLayout.PAGE_START);
        add(scrollPane,BorderLayout.CENTER);

        //set up listener
        getAlbumsButton.addActionListener(e ->
        {
            //clear the table
            DefaultTableModel model = (DefaultTableModel) output.getModel();
            model.setRowCount(0);

            //download the info
            download();
        });
    }

    /*
        a collection of setters
     */
    void setType(String type)
    {
        this.type = type;
    }
    void setLimit(int limit)
    {
        this.limit = limit;
    }
    void setExplicit(boolean explicit)
    {
        this.explicit = explicit;
    }

    /*
        will create the url and execute the task
     */
    private void download()
    {
        //creates the start of the url
        StringBuilder url=new StringBuilder("https://rss.itunes.apple.com/api/v1/us/itunes-music/");

        //builds the rest of the URL
        url.append(type);
        url.append("/all/");
        url.append(limit);
        if(explicit)
            url.append("/explicit.atom");
        else
            url.append("/non-explicit.atom");

        //create a new download task
        XMLDownloadTask task= new XMLDownloadTask(url.toString(),this);

        //create and set the listener
        task.addPropertyChangeListener(evt -> {
            if (evt.getPropertyName().equals("state"))
                switch ((SwingWorker.StateValue) evt.getNewValue())
                {
                    //at the start
                    case STARTED:
                        //disable button
                        getAlbumsButton.setEnabled(false);

                        //reset the time
                        time = 0;
                        timeTF.setText("0:00");

                        //create the timer
                        timer = new Timer(1000, e ->
                        {
                            time++;
                            String timeSTR = secondsToTime(time);
                            timeTF.setText(timeSTR);
                        });

                        //start the timer
                        timer.start();
                        break;
                    //at the end
                    case DONE:
                        //turn on the button and stop the timer
                        getAlbumsButton.setEnabled(true);
                        timer.stop();
                        break;
                }
        });

        //execute the task
        task.execute();
    }

    /*
        used to display album info to the screen(required by interface)
     */
    public void display(Object object)
    {
        //cast to an Album
        Album album =(Album) object;

        //create a row
        Object[] row = { album.getAlbumName(), album.getArtistName(), album.getGenre(), album.getCover() };

        //add the row to the table
        ((DefaultTableModel) output.getModel()).addRow(row);
    }

    /*
        converts the second to a formatted minute and second string
     */
    private String secondsToTime(int second)
    {
        int m=second/60;
        int s=second-m*60;

        return String.format("%d:%02d", m,s);
    }
}

/*
    interface so that task can print to the panel
 */
interface Displayer
{
    void display(Object object);
}