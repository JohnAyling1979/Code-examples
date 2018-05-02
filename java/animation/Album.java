import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;

/*
    this is a storage class it contains information about the album
 */
public class Album
{
    private String albumName;
    private String artistName;
    private String genre;
    private ImageIcon cover;

    /*
        constructor for the class
        it initializes the values
     */
    Album(String albumName, String artistName, String genre, String cover)
    {
        try
        {
            //create the url
            URL url = new URL(cover);

            //create the Icon and save it
            this.cover = new ImageIcon(getScaledImage(ImageIO.read(url)));
        } catch (IOException e)
        {
            System.out.println(e.getMessage());
        }
        this.albumName = albumName;
        this.artistName = artistName;
        this.genre = genre;
    }

    /*
        overrides the toString function to display the album information
     */
    @Override
    public String toString()
    {
        return albumName + ' ' + artistName + ' ' + genre + '\n';
    }

    /*
        getters for the table
     */
    String getAlbumName()
    {
        return albumName;
    }
    String getArtistName()
    {
        return artistName;
    }
    String getGenre()
    {
        return genre;
    }
    ImageIcon getCover()
    {
        return cover;
    }

    /*
        used to resize the image(given)
     */
    private Image getScaledImage(Image sourceImage)
    {
        //create storage for the new image
        BufferedImage resizedImage = new BufferedImage(50, 50,
                BufferedImage.TYPE_INT_ARGB);

        //create a graphic from the image
        Graphics2D g2 = resizedImage.createGraphics();

        //sets the rendering options
        g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
                RenderingHints.VALUE_INTERPOLATION_BILINEAR);

        //copies the source image into the new image
        g2.drawImage(sourceImage, 0, 0, 50, 50, null);

        //clean up
        g2.dispose();

        //return 50 x 50 image
        return resizedImage;
    }
}
