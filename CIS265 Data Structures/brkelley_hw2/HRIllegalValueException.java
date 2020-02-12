//custom exception to be thrown if the file reads a negative number

public class HRIllegalValueException extends Exception {

    public HRIllegalValueException () {
        //print out reason for our custom exception in no argument constructor
        System.out.println("HRIllegalValueException: Input can't be negative.");
    }

}
