public class ArrayList implements IList {

    private int CAP;
    private int size;
    private Object[] elements;

    public ArrayList(){ this(100);} //changed the default size to 5000 before I got the constructor to work

    public ArrayList(int cap) {
        this.size=0;
        this.CAP=cap;
        this.elements = new Object[cap];
    }

    public int size() { return size;}

    public boolean isEmpty() { return size == 0;}

    public Object get (int index) throws OutOfRangeException {
        if (index < 0 || index >= size)
            throw new OutOfRangeException();
        return elements [index];
    }

    public void set (int index, Object e) throws OutOfRangeException {
        if (index < 0 || index >= size)
            throw new OutOfRangeException();
        elements[index] = e;
    }

    //next day in class

    public void add (int index, Object e) throws OutOfRangeException {
        if (index < 0 ||index > size())
            throw new OutOfRangeException();
        for(int i = size -1; i >= index; i--)
            elements[i+1] = elements [i];
        elements[index]=e;
        size++;
    }

    public Object remove (int index) throws OutOfRangeException {
        if ( index < 0 || index >= size)
            throw new OutOfRangeException();
        Object answer = elements[index];
        for (int i = index; i <size-1; i++)
            elements [i] = elements[i+1];
        size--;
        return answer;
    }
}