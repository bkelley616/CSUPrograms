
//our custom exception to use from class that is thrown when the stack is full
public class StackFullException extends Exception {

    public StackFullException() { //default
        System.out.println("The stack is at maximum capacity");
    }

    public StackFullException(String errorMessage) { //overloaded
        System.out.println(errorMessage);
    }

}
