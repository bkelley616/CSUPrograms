public class GiftCard implements Payable {
    private String pin;
    private double balance;


    //constructor takes amount and pin(string) and assigns the values
    public GiftCard (double amount, String pin) {

        if(amount >= 0)
        this.balance = amount;

        this.pin = pin;

    }


    //implement the makePayment method from the Payable interface
    //check if the correct pin is given, check for sufficient funds
    //if those are true then subtract payment from balance and print receipt statement

    public boolean makePayment(double amount, String name, String pin) {

        if (!this.pin.equals(pin)) {
            System.out.println("Incorrect Pin Entered");
            return false;}

        else if (amount > this.balance) {
            System.out.println("Insufficient Funds, Payment Declined");
            return false;}

        else {
            this.balance -= amount;
            System.out.println("Payment of $" + amount + " made to " + name );
            return true;

        }

    }


    //Override the default object toString Method to properly print out object in correct format
    public String toString() {
        return "Gift Card Pin: " + this.pin + "\nGift Card Balance: " + this.balance;
    }

}
