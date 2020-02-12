
// concrete HeapQueue Priority Queue that will be used to compare performance
public class HeapPQueue extends AbstractPQueue {

    private ArrayList heap ;//create a new array list called heap
    public HeapPQueue() {super();}
    public HeapPQueue(int cap) {super(); // needed to add this to be able to directly input the capacity in the performance comparison test file
        heap = new ArrayList(cap); // also changed the default capacity to 5000 just in case
    }

    public HeapPQueue( EntryComparator comp) { super(comp);}


    //given methods in class
    private int parent(int i) { return(i-1)/2 ;}
    private int left (int i) { return 2*i+1;}
    private int right (int i) { return 2*i+2;}
    private boolean hasLeft(int i) { return left(i) < heap.size();}
    private boolean hasRight(int i) { return right(i) < heap.size();}



    //constructor: your implementation

    public int size(){return heap.size();} //return size
    public boolean isEmpty() {return size()==0;} // return whether size is equal to zero

    //filter a value placed at the bottom upwards to maintain heap structure
    private void heapUp(int i) {
        try {
            //while the key of the parent is greater than the child, filter the child up, i must be positive too
            while ((compare((PQEntry) heap.get(parent(i)), (PQEntry) heap.get(i)) > 0) && i > 0) {
                //swap the values using a temp variable
                PQEntry tempVal = (PQEntry) heap.get(parent(i));
                heap.set(parent(i),heap.get(i));
                heap.set(i,tempVal);
            }
        } catch (OutOfRangeException exception) {}
    }


    //filter an item at the top of the heap down
    private void heapDown(int i) {

        int smallest = 0; //smallest value aloud in binary search tree
        try{ // check what has the smallest value
        if (hasLeft(i) && (compare((PQEntry) heap.get(left(i)), (PQEntry) heap.get(i)) < 0)) { // if has left and left is less than i
            smallest = left(i); // set smallest to left value
        } else if (hasRight(i) && (compare((PQEntry) heap.get(right(i)), (PQEntry) heap.get(smallest)) < 0)) { //if has right and right is less than i
            smallest = right(i);// set smallest value to right value
        } else
            smallest = i;//otherwise i is the smallest

        if (smallest != i) { //if current i is not the same as smallest, move it down by swapping
                PQEntry tempVal = (PQEntry) heap.get(smallest); //swap the values using a temp value
                heap.set(smallest, heap.get(i));
                heap.set(i, tempVal);
                heapDown(smallest); // repeat until heap we reach proper heap structure
        }
        } catch(OutOfRangeException exception){}
    }

    //insert value Priority Queue Entry at the bottom of the heap
    //then do "heap up" to filter it to where it needs to be to maintain heap structure
    //then return the object you inserted (Similar to ALPQueue Method)
    public PQEntry insert(Integer key, String value){
        PQEntry newest = new PQEntry (key, value);

        try {
            heap.add ( heap.size(), newest); //add to bottom of tree
        } catch ( OutOfRangeException exception) {}

        heapUp(heap.size()-1);//filter up very last PQEntry (item inserted)
        return newest;// return item just inserted

    }

    //method to get and remove min value
    public PQEntry removeMin(){
        try {
            if (!heap.isEmpty()) { // if not empty
                PQEntry answer = (PQEntry) heap.get(0); // get top object
                if (heap.size()>1) { // if more than one item, then get the last or bottom item in tree
                    PQEntry lastChild = (PQEntry) heap.remove(heap.size() - 1);
                    heap.set(0, lastChild); // then set the last item to the top and filter it down
                    heapDown(0);//move first entry at top down, (the PQEntry we moved to the top)
                }
                else // if only one item just remove it, heap becomes empty
                    heap.remove(0);

                return answer; //return answer
            }
        } catch (OutOfRangeException exception){}
        return null; //else return null
    }

    //method to get min value but not remove it similar to ALPQueue
    public PQEntry min(){

        try {
            if (!heap.isEmpty()) //if not empty, return top node
                return (PQEntry) heap.get(0);
        } catch (OutOfRangeException exception){}
        return null; //else return null
    }


}
