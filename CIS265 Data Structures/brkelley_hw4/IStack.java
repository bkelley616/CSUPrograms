
//IStack interface implementation from class
public interface IStack {

    int size();
    boolean isEmpty();
    Object top();
    void push(Object Item) throws StackFullException;
    Object pop();

}
