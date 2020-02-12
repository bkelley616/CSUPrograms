
//abstract class to outline methods and variables in PQueue, implements PQueue and will be extended by
// by the concrete ALPQueue class and the concrete HeapQueue class
//used to compare values
public abstract class AbstractPQueue implements PQueue {

    private EntryComparator comp;

    protected AbstractPQueue ( EntryComparator c) {
        comp=c;
    }

    protected AbstractPQueue() { this (new EntryComparator());}

    protected int compare (PQEntry a, PQEntry b) {
        return comp.compare(a,b);
    }

    abstract public int  size();

    public boolean isEmpty() { return size() == 0; }

}
