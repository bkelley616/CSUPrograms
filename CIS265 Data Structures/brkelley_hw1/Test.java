public class Test {

    // tests the program to see if it produces the correct output
    public static void main(String[] args) {
        BankAccount[] accts = {	new SavingAccount("Cody", "Allen", 3428765),
                new CheckingAccount("Shane", "Bieber", 3284842, "1234"),
                new SavingAccount("Adam", "Cimber", 8097423)};

        Payable[] items = {	new CheckingAccount("Corey", "Kluber", 79872487, "4321"),
                new GiftCard(1000, "gift")};

        accts[0].deposit(500);
        accts[1].deposit(1200);
        accts[2].deposit(1500);
        ((CheckingAccount)items[0]).deposit(2000);

        for (int i = 0; i<accts.length; i++) {
            accts[i].withdraw(800);
        }

        items[0].makePayment(2000, "Alonso", "4321");
        items[1].makePayment(2000, "Barnes", "gifts");
        ((CheckingAccount)accts[1]).makePayment(2000, "Diaz", "1234");

        for (int i = 0; i<accts.length; i++)
            System.out.println(accts[i]);

        for (int i = 0; i<items.length; i++)
            System.out.println(items[i]);
    }
}
