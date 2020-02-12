
// concrete array stack class, using the IStack interface from class
public class ArrayStack implements IStack {

    public static int CAP;
    private Object[] data;
    private int size;
    public ArrayStack() {
        this(100);
    }

    public ArrayStack(int cap) {
        this.CAP = cap;
        this.size = 0;
        this.data = new Object[cap];
    }

    public int size() { return size; }

    public  boolean isEmpty() {return size == 0;}

    public Object top() {
        if(isEmpty()) return null;
        return data[size-1];
    }

    public Object pop() {
        if(isEmpty()) return null;
        Object answer = data[size -1];
        data[size -1] = null;
        size--;
        return answer;
    }

    public void push (Object item) throws StackFullException {//throws StackFullException {
        if (size == CAP)
        throw new StackFullException();
        data[size++] = item; //preforms increment after setting item to size
    }


}
