

import java.util.Random; //needed to calculate a random acctNumber

public class SavingAccount extends BankAccount {
    private double interest;
    private int acctNumber;
    private double balance;


        //constructor takes firstname, lastname, and ssn #
        //uses Random class (imported) to get random 6 digit number
        //assigns the default balance and interest rate
    public SavingAccount(String firstname, String lastname, int ssn) {

        super.firstname = firstname;
        super.lastname = lastname;
        super.ssn = ssn;

        //calculates random number with bound 900000 and adds it to first 6 digit number 100000
        //always will result in a random 6 digit number
        this.acctNumber = new Random().nextInt(900000) + 100000;


        this.interest = 1;
        this.balance = 0.0;

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

    //Override the default object toString Method to properly print out object in correct format
    public String toString() {
        return "Firstname: " + super.firstname + "\nLastname: " + super.lastname + "\nSaving's Account Number: " + this.acctNumber + "\nBalance: " + this.balance + "\nInterest: " + this.interest + "%";
    }
}