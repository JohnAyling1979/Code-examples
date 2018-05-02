import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Scanner;

public class Format
{
        //main program
        public static void main(String[] args)
        {
            //variables
            String fileName;
            StringBuilder line;
            File inFile;
            FileWriter outFile;
            PrintWriter outPrint;
            Scanner scIn = new Scanner(System.in);
            Scanner scInFile;

            System.out.println("This program will take your downloaded output and return");
            System.out.println("a formated version saved in a file called output.txt");
            System.out.println();
            System.out.println("Enter file name including extension if any");
            fileName = scIn.next();

            //make a file object
            inFile = new File(fileName);
            try
            {
                //open the file and attach to a scanner
                scInFile = new Scanner(inFile);

                //open output file to printwriter
                outFile = new FileWriter("output.txt");
                outPrint = new PrintWriter(outFile);

                //read entire file
                while (scInFile.hasNextLine())
                {
                    //get line
                    line = new StringBuilder(scInFile.nextLine());

                    //input spaces based on CC
                    switch (line.charAt(0))
                    {
                        case '-':
                            outPrint.println("");
                            outPrint.println("");
                            break;
                        case '1':
                            outPrint.println("\f");
                            break;
                        case '0':
                            outPrint.println("");
                            break;
                    }

                    //remove CC
                    line.setCharAt(0,' ');

                    //print to file
                    outPrint.println(line);
                }

                System.out.println("Formating is complete.");
                System.out.println("Open output.txt to verify before submitting");

                //close all file/streams
                outPrint.close();
                scIn.close();
                scInFile.close();
            }
            catch (Exception e)
            {
                System.out.println(e.getMessage());
            }
        }
}
