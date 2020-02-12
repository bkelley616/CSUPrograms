import java.io.IOException;
import java.util.InputMismatchException;
import java.io.FileReader;
import java.util.Scanner;
//import statements to read file

public class HeartRate {

    private static int badReadings; // variables to be used as counter for
    private static int goodReadings; // good and bad readings

    public static void printData() { //method to print the number of good and bad readings

        System.out.println("Good Data: " + goodReadings);
        System.out.println("Bad Data: " + badReadings);
    }


    //main method to test/run program
    public static void main(String[] args) throws IOException {

        //assign counter variables to 0 and create file reader
        badReadings = 0;
        goodReadings = 0;
        Scanner input = new Scanner(new FileReader("HR.txt"));

        //read file and get next Line of input
        while (input.hasNextLine()) {

            try {

                if (input.nextInt() < 0) {
                    //if negative number, throw our custom exception
                    throw new HRIllegalValueException();

                } else {
                    //data is good so increment goodReadings
                    goodReadings += 1;

                }
            } catch (InputMismatchException ex) {

                //input is not an int
                badReadings += 1;
                input.next(); // increment badReadings and then move past "bad" data

            } catch (HRIllegalValueException ex) {

                //value is negative, print out error and increment bad data
                badReadings += 1;


            }
        }


        printData(); // method to print number of good and bad data
    }


}
