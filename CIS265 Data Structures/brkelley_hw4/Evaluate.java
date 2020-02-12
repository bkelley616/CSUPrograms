import java.util.Scanner;

//class to take user input, contains evaluate method to solve expressions, and run the code
public class Evaluate {

    // declare the ArrayStack variables which will later be used in expression
    static ArrayStack valStk;
    static ArrayStack opStk;

    //assigns precedence by using int value. greater value means greater precedence
    //returns 0 if not a supported operator/character
    public static int precedence(char operator) {

       // if (operator == '$') //arbitrary unit for future use talked about in class, such as inequalities
           // return 0;
        if (operator == '+' || operator == '-')
            return 1;
        if (operator == '*')
            return 2;
       // if (operator == '(') extra credit?
            //return 3;
        else
            return 0;
    }

    //method that performs the operation and returns the value (from pseudo code in class)
    public static void doOp() {

        char operator = ((char) opStk.pop());
        int x = ((int) valStk.pop());
        int y = ((int) valStk.pop());

        try {

           // if (operator == '$') //arbitrary unit for future use talked about in class, such as inequalities
               // valStk.push(0);
            if (operator == '+')
                valStk.push(y + x);
            if (operator == '-')
                valStk.push(y - x); //make sure correct order
            if (operator == '*')
                valStk.push(y * x);
            //if (operator == '(') //extra credit?
               // valStk.push(0);
           // else
                //System.out.println("Error: Operation Not Supported");
        }
        catch (StackFullException exception){

        }

    }

    //method that performs that repeats the doOp Method (from pseudo code in class)
    public static void repeatOps (char refOp){ //make sure there are values in valstk and the precedence is correct
        while((valStk.size() > 1) && (precedence(refOp) <= precedence((char) opStk.top()))) {
            doOp();
        }

    }


    // calculates the value of the expression given (from pseudo code in class)
    public static int expression(String str) {

        valStk = new ArrayStack(str.length());
        opStk = new ArrayStack(str.length());
        String value = "";

        for (int i = 0;i < str.length();i++){

            char z=str.charAt(i);
            if (Character.isDigit(z)) {
                value += z;

            }
            else {

                if(!value.isEmpty()) {
                    int number = Integer.parseInt(value);
                    //System.out.println(number); //test to see if it getting multiple digit numbers
                    value = "";
                    try {valStk.push(number);}
                    catch(StackFullException exception){}
                }

                repeatOps(z);
                try{opStk.push(z);}
                catch (StackFullException exception){}

            }

        }
            repeatOps('$');
            return (int) valStk.top();

    }

    //runs code and allows user to solve multiple expressions
    public static void main(String[] args) {

        // loop to ask user for input and determine to evaluate the expression or exit the program
        while (true) {

            System.out.println("\nPlease enter an expression to be solved, \nto exit the program, type \"exit\"\n");
            Scanner input = new Scanner(System.in);
            String userInput = input.nextLine() + " ";
            if (userInput.toLowerCase().equals("exit ")) {
                System.out.println("\nExiting Program...");
                System.exit(0);
            } else {
                System.out.println("\nSolving: " + userInput);
                System.out.println("Answer: " + expression(userInput));
            }
        }
    }
}

