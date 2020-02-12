
//hash map using linear probing
public class ProbeHashMap extends AbstractHashMap {

    private MapEntry[] table;
    private MapEntry DEFUNCT = new MapEntry(null, null);
    private int nCollisions = 0;

    public ProbeHashMap() { //default constructor using default capacity and prime of AbstractHashMap
        super();
    }


    public ProbeHashMap(int capacity, int prime) { //overloaded constructor that allows you to set the capacity and prime
        super(capacity, prime);
    }


    private boolean compareStr(String s, String t) { //used to count collisions on global level
        if (s.equals(t)) return true;
        nCollisions++;
        return false;
    }

    protected void createTable() {
        table = new MapEntry[capacity]; // initialize to an array of MapEntrys with a size of the capacity
    }

    //**class note to help** isAvailable checks if bucket is null or defunct, then the bucket is available
    private boolean isAvailable(int i) {
        if ((table[i] == null) || (table[i] == DEFUNCT))
            return true;
        else return false;
    }

    //**given in class**
    //return value is the bucket where we found key in the table
    //if return value is negative then the key was not found
    private int findSlot(int h, String k) {

        int avail = -1;
        //System.out.println(h);
        //if (h < 0) // had to add this because hashfunction was returning negative number, looking into it says possible overflow error? meaning we are putting too big of a number into int variable
           // h = h * -1;// this solved the issue
        int i = h % capacity; //added "% capacity"? was getting out of index error when passed to isAvailable
        //System.out.println(i);
        // System.out.println((long) h % capacity);
        do {
            if (isAvailable(i)) {
                if (avail == -1) avail = i;
                if (table[i] == null) break;
            } else if (compareStr(table[i].getKey(), k)) //not available/check for collision
                return i;

            i = (i + 1) % capacity; // this is linear probing part, change this for dblhash
        } while (i != h);
        return -(avail + 1);
    }


    protected Object bucketPut(int h, Object key, Object value) {
        int bucketIndex = findSlot(h, (String) key);// will find the index of key and return -1 if not found
        String answer;
        //System.out.println(bucketIndex);

        if (bucketIndex >= 0) {
            n++; //increase number on Entries
            return table[bucketIndex] = new MapEntry((String) key, (String) value); // return object stored
        } else {
            n++;//increase data entries
            // convert to the correct bucket index that may be a negative number - 1 from findSlot() method and put data in
            return table[-(bucketIndex + 1)] = new MapEntry((String) key, (String) value);
        }
    }


    protected Object bucketGet(int h, Object key) {
        int bucketIndex = findSlot(h, (String) key);// will find the index of key and return -1 if not found
        if (bucketIndex > 0)
            return table[bucketIndex].getValue();// return value at that index
        else
            return null;//not found/error return null
    }

    protected Object bucketRemove(int h, Object key) {
        int bucketIndex = findSlot(h, (String) key);// will find the index of key and return -1 if not found
        String answer; // used to store answer to be returned
        if (bucketIndex >= 0) {
            answer = (String) table[bucketIndex].getValue();
            n--; //decrease number of Entries
            table[bucketIndex] = DEFUNCT; // set value to DEFUNCT to remove the MapEntry, note this is different than null
            return answer; // return object stored
        } else
            return null;
    }

    //given method, creates an object from keys that we can use to iterate over keys with special for loop
    private class KeyIterable implements Iterable {
        public SArrayIterator iterator() {
            ArrayList buffer = new ArrayList(n);
            for (int i = 0; i < capacity; i++)
                try {
                    if (!isAvailable(i))
                        buffer.add(buffer.size(), table[i].getKey());
                } catch (OutOfRangeException e) {
                    System.out.println("keySet: Out Of Range");
                }

            return new SArrayIterator(buffer);
        }
    }

    //given method to create object with key values
    public Iterable keySet() {
        return new KeyIterable();
    }

    public int getCollisions() {
        return nCollisions;
    } //return number of collisions for comparison


    public String toString() {
        // convert the ProbeHashMap object to a string in the format of
        // "index key value" tuples, for example (not a real result)
        // 0       Lindor		SS ...
        // 6       Ramirez 		RP ...
        // 9       Carrasco		SP ...
        // ...
        //makes sure to return in correct format

        int bucketIndex = 0;
        String bucketKey = "";
        String bucketValue = "";

        //System.out.println(n);//debug to see if values are stored in hash table
        //System.out.println(table[0]);//debug to see if data is being stored
        //System.out.println(table[64]);
        if (n == 0)
            return "Hash Table is empty";
        else {
            for (int i = 0; i < capacity; i++) { //for loop to iterate through table and print data in the correct format
                if (table[i] != null) {
                    bucketIndex = i;
                    bucketKey = table[i].getKey();
                    bucketValue = table[i].getValue();
                    System.out.println(bucketIndex + "       " + bucketKey + "       " + bucketValue);

                }

            }

        }
        return "\n"; //used for formatting in test file
    }

}