//abstract method to be implemented in AVLTreeMap
public abstract class AbstractMap {
    public abstract Object get(Object key);
    public abstract Object put(Object key, Object value);
    public abstract Object remove(Object key);
    public abstract boolean isEmpty();
    public abstract int size();
    //public abstract Iterable keySet();// don't need for this assignment? was causing error because
    // AVLTreeMap needed to implement keySet();?????????
}