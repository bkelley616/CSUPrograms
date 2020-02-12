
//exception to be thrown when the array queue reaches maximum capacity
public class QueueFullException extends Exception {

    public QueueFullException() { //default
        System.out.println("Error: The Queue is Full");
    }

    public QueueFullException (String errorMessage) { //overloaded
        System.out.println(errorMessage);
    }


}
