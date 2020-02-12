
//Program using recursion to test if the inputted string is elfish (contains the letters "e" "l" "f" or
// xish, meaning the second string inputted contains the all the letters of the first string

public class Testish {

    public static boolean containsE = false; // create these variables to hold the value
    public static boolean containsL = false; // of whether or not the word contains each letter
    public static boolean containsF = false; // of elf

    // test if the string contains "e" "l" "f"
    public static boolean elfish(String word) {

        word.toLowerCase(); // since capital letters are different values, make sure we are testing letters only and not case

        if (word.isEmpty()) { // (base case) if we reach the end of the word, only return true if each letter has been found

            if (containsE && containsL && containsF)
                return true;
            else
                return false;
        }

        //check if the current character is an e l or f
        if (word.charAt(0) == 'e')
            containsE = true;
        if (word.charAt(0) == 'l')
            containsL = true;
        if (word.charAt(0) == 'f')
            containsF = true;

        //return recursive method call of elfish but use substring to remove the first letter of the word to move to the next
        return elfish(word.substring(1));

    }

    // test if the string word contains the letters of the string x
    public static boolean xish(String x, String word) {

        x.toLowerCase(); // since capital letters have a diffrent value, convert
        word.toLowerCase(); // both x and word to lower case so the case of the letters dont matter just the letters themselves

        if(x.isEmpty()) //if the string doesn't contain any characters we are finished (base case)
            return true;
        if(word.indexOf(x.charAt(0)) == -1) //if there is no index of the character in word then it returns -1
            return false; // therefore return false since the character is not in word
        else
            return xish(x.substring(1),word); //if the character is present, move to the next test character by
        // creating a substring at the second char, this removes the firs char, then recursively call the method again
        // with same word but x value "shifted" by one

    }

    // main method to run code and takes the intial command line arguments
    //if prints out message for 0 arguments provided, calls elfish method for one argument provided
    //and calls xish if two arguments are provided
    public static void main(String[] args) {

        if (args.length == 0) { // print error message
            System.out.println("Please provide one or two strings");

        } else if (args.length == 1) { // call elfish, print statement depending on the return value of method

            if (elfish(args[0]))
                System.out.println(args[0] + " is elfish");
            else
                System.out.println(args[0] + " is not elfish");

        } else { // call xish, print statement depending on the return value of method

            if (xish(args[0], args[1]))
                System.out.println(args[1] + " contains " + args[0]);
            else
                System.out.println(args[1] + " does not contain " + args[0]);

        }
    }

}
