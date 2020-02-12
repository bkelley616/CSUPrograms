
// abstract class to be extended by SavingAccount and CheckingAccount
public abstract class BankAccount {
    protected String firstname;
    protected String lastname;
    protected int ssn;

    //default abstract deposit method
    public abstract void deposit(double i);



    //default abstract withdraw method
   public abstract boolean withdraw(double i);





}