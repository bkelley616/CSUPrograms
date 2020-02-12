import java.io.IOException;
import java.util.InputMismatchException;
import java.io.FileReader;
import java.util.Scanner;
//imported to read file the same way as hw2

//class to test the hash tables and the collisions that occur for each type
public class Test {

    //method to insert data into the hash table
    public static void insertData(AbstractHashMap hash, Object [] keys, Object [] values, String hashType){

        for(int indexOfArray = 0; indexOfArray < keys.length; indexOfArray++ ) {
            hash.put(keys[indexOfArray],values[indexOfArray]);
        }
        System.out.println("\ninserted " + keys.length + " data items " + "into " + hashType + "\n");
    }

    //method to iterate over each key in order it is stored in hashtable
    public static void iterateKeys (AbstractHashMap hash) {
        Iterable hashKeyList = hash.keySet();
        for(Object keyList: hashKeyList){
            System.out.println(keyList);
        }
    }

    //method to test code, print out put and will be used to compare collisions of each type of hash table
    public static void main(String[] args) throws IOException {

            Scanner input = new Scanner(new FileReader("broster.txt"));
            //used the same way to read files from hw2 heartbeat file

            int lineCount = 0;//used to know how big to make key and value arrays

            while (input.hasNextLine()) {
                    //System.out.println(input.nextLine()); test to see if input is working
                    input.nextLine();
                    lineCount++; //count lines, use this to know size of key and value string and value arrays
            }
            //System.out.println(lineCount); //prints out 65

            String[] keys = new String[lineCount];
            String[] values = new String[lineCount];

            input = new Scanner(new FileReader("broster.txt")); // reset file to original after counting lines
            for (int i = 0; i < lineCount; i++) {

                while (input.hasNextLine()) {

                    String[] parts = input.nextLine().split("\\s+",2); //split into two parts, split based on whitespace
                    keys[i] = parts[0]; // first half, insert key into key array
                    values[i] = parts[1]; // second half, insert value into value array
                    i++;
                    //test we are storing the whole file in the correct format
                    //System.out.println(keys[i]);
                    //System.out.println(values[i]);
                }
            }

        ProbeHashMap linearProbingHashTable = new ProbeHashMap(); // creat each type of hash table
        DblHashMap doubleHashingHashTable = new DblHashMap();

        //insert data, print the hash table, iterate over the keys, and output the number of collisions for linear probing hashtable
        insertData(linearProbingHashTable, keys, values, "Linear Probing Hash Table");
        System.out.println(linearProbingHashTable.toString());
        iterateKeys(linearProbingHashTable);
        System.out.println("\n" + linearProbingHashTable.getCollisions() + " collisions occurred using linear probing");

        //insert data, print the hash table, iterate over the keys, and output the number of collisions for double-hash hashtable
        insertData(doubleHashingHashTable, keys, values, "Double-Hash Hash Table");
        System.out.println(doubleHashingHashTable.toString());
        iterateKeys(doubleHashingHashTable);
        System.out.println("\n" + doubleHashingHashTable.getCollisions() + " collisions occurred using double hashing");


    }
}
