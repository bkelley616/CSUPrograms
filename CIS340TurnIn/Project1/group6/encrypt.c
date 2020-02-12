// Brandon Kelley 2716916 & Anastasiya Kalinina 2754066
// encrypt.c is a simple transposition cipher that works by dividing the string in half and swapping the subsets of the string using a recursive method

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//recursive method that splits the string in half and swaps the the string subsets assuming the string argument is >2 characters
char *encrypt(char *rawString, int stringLength) {

    char* subString1, *subString2; //split the string into subsets at k
    int k,i; // use to split string and counter for loops
    int index;//index location when copying string
    char *encodedString; //char pointer variable to hold the encoded String
    char *answer;// store result of recursion in answer that way we can free memory before returning
    encodedString = (char*)malloc(sizeof(char) * (stringLength)); // allocate enough space for the size of the string given

    if (stringLength <= 2)//base case for recursive loop
        return rawString;
    else { //recursive case of function
        k = stringLength / 2;

        //determine if string has even or odd number of characters to be able to allocate either k or k+1 to second substring
        if ((stringLength % 2) == 0) { //number is even so both substrings will have the same length

            subString1 = (char*)malloc(k);
            subString2 = (char*)malloc(sizeof(char) * (k));

            index = 0; //build substring 1 backwards
            for (i = k - 1; i >= 0; i--) { //reverse the letters of the substring (first half)
                subString1[index++] = rawString[i];
            }

            index = 0; //build substring 2 backwards
            for (i = stringLength - 1; i >= k; i--) { //reverse the letters of the substring (second half)
                subString2[index++] = rawString[i];
            }

            return strcat(encrypt(subString1,k),encrypt(subString2,k)); //return the substrings (already backwards) concatenated together

        }
        else { // number is odd, since int division rounds down,second substring will always have one more letter

            subString1 = (char*)malloc(k);
            subString2 = (char*)malloc(sizeof(char) * (k+1)); //*note* k+1

            index = 0; //build substring 1 backwards
            for (i = k - 1; i >= 0; i--) { //reverse the letters of the substring (first half)
                subString1[index++] = rawString[i];
            }

            index = 0; //build substring 2 backwards
            for (i = stringLength - 1; i >= k; i--) { //reverse the letters of the substring (second half)
                subString2[index++] = rawString[i];
            }

            return strcat(encrypt(subString1, k), encrypt(subString2, k+1)); //return the substrings (already backwards) concatenated together **note** k+1 cause it had odd number of letters

        }

    }

}

int main() {

    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t\t\t\tString Encrypter: \n\n\tPlease Enter in a String to Encrpyt:\n\n\t\t");
    char rawString[8194], *encodedString; //create string of size 8194 as specified by project
    int stringLength;
    scanf("%8194[^\n]", rawString); //needed to not have strings split by space with regular scanf
    stringLength = strlen(rawString);// get length of string

    /* small debugging test for correct values
    printf("\n\t\t%s\n", rawString);
    printf("\t\t%d\n", stringLength);
    */

    encodedString = encrypt(rawString, stringLength); //must be a pointer variable because you can't assign without an index for array
    printf("\n\tString Length: %d Character(s)\n\tEncrypted String: %s\n\n", stringLength, encodedString);
    printf("-------------------------------------------------------------------------------------------------------\n\n");

    return 0;
}

