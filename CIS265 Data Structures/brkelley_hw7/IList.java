public interface IList {
    public int size();
    public boolean isEmpty() ;
    public Object get( int index) throws OutOfRangeException;
    public void set (int index, Object e) throws OutOfRangeException;
    public void add (int index, Object e) throws OutOfRangeException;
    public Object remove (int index) throws OutOfRangeException;
}
