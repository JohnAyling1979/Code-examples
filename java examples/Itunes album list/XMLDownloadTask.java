import java.util.ArrayList;
import java.util.List;
import javax.swing.*;
import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.helpers.DefaultHandler;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.ByteArrayInputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

/*
    This is the work class. It will download the information and save the album info
 */
public class XMLDownloadTask extends SwingWorker<List<Album>,Album>
{
    //instance variables
    private String urlString;
    private Displayer delegate;

    /*
        constructor which sets the url and a link to the class that calls it
     */
    XMLDownloadTask(String url, Displayer caller)
    {
        urlString=url;
        delegate=caller;
    }

    /*
        this is main function for the class. It is ran in a separate thread
     */
    public List<Album> doInBackground()
    {
        String page;
        HttpURLConnection connection = null;

        try
        {
            //create a URL from the string
            URL url = new URL(urlString);

            //create a connection
            connection = (HttpURLConnection) url.openConnection();

            //set it as get
            connection.setRequestMethod("GET");

            //check if we got a good response
            if(connection.getResponseCode() == HttpURLConnection.HTTP_OK)
            {
                //create a string builder
                StringBuilder pageBuilder = new StringBuilder();

                //create a buffer to read from the connection
                BufferedReader input = new BufferedReader(new InputStreamReader(connection.getInputStream()));

                //read the first line
                String strLine=input.readLine();

                //while we have something line
                while(strLine != null)
                {
                    //add to page and read the next line
                    pageBuilder.append(strLine);
                    strLine = input.readLine();
                }
                //close input
                input.close();

                //save final to a string
                page=pageBuilder.toString();

                //create the SAX parser
                SAXParserFactory factory = SAXParserFactory.newInstance();
                SAXParser saxParser = factory.newSAXParser();

                //parse the page
                saxParser.parse(new InputSource(new ByteArrayInputStream(page.getBytes("utf-8"))),new AlbumHandler());
            }
            //since for all the exception we were just printing the the message the IDE suggested to collapse them into one
        } catch(Exception e)
        {
            //display the message to console
            System.out.println(e.getMessage());
        }finally
        {
            //close the connection if it exists
            if(connection != null)
                connection.disconnect();
        }

        //required return
        return null;
    }

    /*
        called from time to time to process what has been published
     */
    @Override
    protected void process(List<Album> chunks)
    {
        for (Album album:chunks)
        {
            delegate.display(album);
        }
    }

    /*
        inner class which is used by the SAX parser. It controls what happens when tags are read
     */
    public class AlbumHandler extends DefaultHandler
    {
        private String albumName;
        private String artistName;
        private String genre;
        private String cover;
        private boolean firstCategory=false;
        private boolean albumNameBool=false;
        private boolean artistNameBool=false;
        private boolean coverBool=false;

        /*
            called when a start tag is reached
         */
        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes)
        {
            //if the tag is entry set the first category tag to true
            if(qName.equalsIgnoreCase("entry"))
            {
                firstCategory=true;
            }

            //if the tag was name clear out the old name and set the flag
            if(qName.equalsIgnoreCase("im:name"))
            {
                albumNameBool=true;
                albumName="";
            }

            //if the tag was artist the old artist is cleared and the flag is set
            if(qName.equalsIgnoreCase("im:artist"))
            {
                artistNameBool=true;
                artistName="";
            }

            //if it is category get the attribute and set the flag to false
            if(qName.equalsIgnoreCase("category") && firstCategory)
            {
                genre=attributes.getValue("label");
                firstCategory=false;
            }

            //if it is image clear out the old and set it true
            if(qName.equalsIgnoreCase("im:image"))
            {
                coverBool=true;
                cover="";
            }
        }

        /*
            called when the end tag is reached
         */
        @Override
        public void endElement(String uri, String localName, String qName)
        {
            //if it was name set the flag to false
            if(qName.equalsIgnoreCase("im:name"))
            {
                albumNameBool=false;
            }

            //if it was artist set the flag to false
            if(qName.equalsIgnoreCase("im:artist"))
            {
                artistNameBool=false;
            }

            //if it was entry create an album and publish it
            if(qName.equalsIgnoreCase("entry"))
            {
                publish(new Album(albumName,artistName,genre,cover));
            }

            //if it was image set the flag to false
            if(qName.equalsIgnoreCase("im:image"))
            {
                coverBool=false;
            }
        }

        /*
            is called when characters are found within the tags
         */
        @Override
        public void characters(char[] ch, int start, int length)
        {
            //if we are between a name tag add the character as a string to the album name
            if(albumNameBool)
            {
                albumName+=new String(ch,start,length);
            }

            //if we are between a artist tag add the character as a string to the album name
            if(artistNameBool)
            {
                artistName+=new String(ch,start,length);
            }

            //if we are between image tag add the characters as a sting to the cover variable
            if(coverBool)
            {
                cover+= new String(ch,start,length);
            }
        }
    }
}
