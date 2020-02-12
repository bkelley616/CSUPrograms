
// concrete implementation of array based queue
public class ArrayQueue implements IQueue {
    private int head;
    private int tail;
    private Object[] data;
    private static int CAP;

    public ArrayQueue() {
        this(100);
    }

    public ArrayQueue(int cap) {
        this.CAP = cap;
        this.data = new Object[cap];
        this.head = 0;
        this.tail = 0;
    }

    public int size() {
        if (head == tail) return 0;
        else if (head < tail)
            return tail -head;
        else
            return tail + CAP - head;
    }

    public boolean isEmpty() {
        return size () == 0;
    }

    public Object first() {
        if (isEmpty()) return null;
        return data[head];
        }

        public void add (Object item) throws QueueFullException {
            if(size() == CAP - 1)
                throw new QueueFullException("no space left");
            data[tail] = item;
            tail = (++tail) % CAP;
        }

        public Object remove() {
            if(isEmpty()) return null;
            Object answer = data[head];
            head = (++head) % CAP;
            return answer;
        }

    }
