//class to serve as the exception that occurs when we perform an action that is not in the current bounds of the ArrayList
public class OutOfRangeException extends Exception {

    public OutOfRangeException() { //default
        System.out.println("Error: OutOfRangeException Occurred");
    }

    public OutOfRangeException (String errorMessage) { //overloaded

        System.out.println(errorMessage);
    }
}

