
// interface to be implemented by CheckingAccount and GiftCard
public interface Payable {

    //default method signature for makePayment
    public boolean makePayment(double amount, String name, String pin);

}