
//interface that gets implemented by the AbstractPQueue class and therefore the concrete classes that extend it
// (ALPQueue and HeapQueue)
public interface PQueue {
    int size();
    boolean isEmpty();
    PQEntry insert ( Integer k, String v);
    PQEntry min();
    PQEntry removeMin();
}
