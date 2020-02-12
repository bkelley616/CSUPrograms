

import java.util.Random; // used to calculate random number


public class CheckingAccount extends BankAccount implements Payable {

    private double interest;
    private int acctNumber;
    private double balance;
    private String pin;

    //constructor takes firstname, lastname,ssn#,and pin(string)
    //uses Random class (imported) to get random 7 digit number
    //assigns the default balance and interest rate
    public CheckingAccount(String firstname, String lastname, int ssn, String pin) {

        super.firstname = firstname;
        super.lastname = lastname;
        super.ssn = ssn;
        this.pin = pin;

        this.interest = .1; // percent or decimal
        this.balance = 0.0;

        this.acctNumber = new Random().nextInt(9000000) + 1000000; // ask about in class 7 digits

    }

    //if  balance is sufficient subtract amount from balance
    public boolean withdraw(double amount) {

        if (amount > balance) {
            System.out.println("Unable to complete transaction, withdraw amount is greater than current balance");
            return false;
        } else {
            balance -= amount;
            System.out.println("Successful withdraw of $" + amount);
            return true;
        }
    }

    // if amount is positive, add amount to balance
    public void deposit(double amount) {
        if (amount > 0)
            balance += amount;

    }

    //implement the makePayment method from the Payable interface
    //check if the correct pin is given, check for sufficient funds
    //if those are true then subtract payment from balance and print receipt statement

    public boolean makePayment(double amount, String name, String pin) {

        if (!this.pin.equals(pin)) {
            System.out.println("Incorrect Pin Entered");
            return false;
        } else if (amount > this.balance) {
            System.out.println("Insufficient Funds, Payment Declined");
            return false;
        } else {
            this.balance -= amount;
            System.out.println("Payment of $" + amount + " made to " + name);
            return true;

        }

    }


    //Override the default object toString Method to properly print out object in correct format
    public String toString() {
        return "Firstname: " + super.firstname + "\nLastname: " + super.lastname + "\nCheckings Account Number: " + this.acctNumber + "\nBalance: " + this.balance + "\nInterest: " + this.interest + "%" + "\nPin: " + this.pin;
    }


}