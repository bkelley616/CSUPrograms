
//IQueue Interface discussed in class, to be implemented by ArrayQueue and LLQueue
public interface IQueue {

    int size();
    boolean isEmpty();
    Object first();
    void add(Object item) throws QueueFullException;
    Object remove();


}
