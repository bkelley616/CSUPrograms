import java.util.Random;

public abstract class AbstractHashMap extends AbstractMap {
    protected int n = 0;          // the number of entries
    protected int capacity;       // size of the map
    private int prime;            // the prime number
    private long scale, offset;   // a = scale, b = offset

    public AbstractHashMap() {
        this(109, 999331); //was at 61 but changed to 109 to meet assignment requirements, prime was given
    }                            // im not sure if that's a hold over from a previous version? or why it was at 61

    public AbstractHashMap(int c, int p) {
        this.capacity = c;
        this.prime = p;
        Random rand = new Random();
        this.scale = rand.nextInt(prime - 1) + 1;
        this.offset = rand.nextInt(prime);
        createTable();
    }

    public int size() {return n;}
    public boolean isEmpty() {return n == 0;}

    private int hashValue(Object key) {
        return (int) ((Math.abs(key.hashCode()*scale+offset) % prime) % capacity);
    }

    public Object get(Object key) {
        int h = hashValue(key);
        return bucketGet(h, key);
    }

    public Object remove(Object key) {
        int h = hashValue(key);
        return bucketRemove(h, key);
    }

    public Object put(Object key, Object value) {
        int h = hashValue(key);
        return bucketPut(h, key, value);
    }

    protected abstract void createTable();
    protected abstract Object bucketGet(int h, Object k);
    protected abstract Object bucketRemove(int h, Object k);
    protected abstract Object bucketPut(int h, Object k, Object v);

}
