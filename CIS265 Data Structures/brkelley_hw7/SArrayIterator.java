import java.util.Iterator;

public class SArrayIterator implements Iterator {
    private ArrayList data;
    private int i = 0;
    private boolean removable = false;

    public SArrayIterator(ArrayList a) {
        data = a;
    }

    public boolean hasNext() {return i < data.size();}

    public Object next() {
        Object answer = null;
        if (i == data.size())
            return null;
        try {
            answer = data.get(i++);
        } catch (OutOfRangeException e) {
            System.out.println("Out Of Range");
        }
        removable = true;
        return answer;
    }

    public void remove() {
        if (!removable)
            throw new IllegalStateException("nothing to remove");
        try {
            data.remove(i-1);
        } catch (OutOfRangeException e) {
            System.out.println("Out of Range");
        }
        i--;
        removable = false;
    }
}