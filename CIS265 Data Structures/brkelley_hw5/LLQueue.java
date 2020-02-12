
//concrete implementation of a linked list based queue
public class LLQueue implements IQueue {

    private SinglyLL list;
    public LLQueue() { list = new SinglyLL();}
    public int size(){return list.size();}
    public boolean isEmpty() { return list.isEmpty();}
    public Object first() {return list.first();}
    public void add (Object item) { list.addLast(item);}
    public Object remove() { return list.removeFirst();}
}
