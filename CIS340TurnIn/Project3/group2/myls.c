//Brandon Kelley 2716916 & Nicholas Bolyard 2709848

//myls is a program that takes a directory and an optional flag (no flag for no ordering, -f for ascending order,
// -b for descending order) then prints out the directory contents correspondingly

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "stringout.h"

#define  CURRENTDIRECTORY   "." //improve readability by setting a macro for the "current directory"

//buildDirectoryArray takes a directory name and builds a corresponding
//array of pointers to the directories contents
const char **buildDirectoryArray(char dirname[]) {
    //declare pointer and directory structure variables
    DIR *dir_ptr;
    struct dirent *direntp;

    //try to open the given directory, if not possible then give error
    if ((dir_ptr = opendir(dirname)) == NULL) {
        //Could not open: not a directory or other error
        fprintf(stderr, "Cannot open %s\n", dirname);
        const char **directoryArray = malloc(sizeof(char *));
        return directoryArray;
    } else {

        int directorySize = 0; // initialize directory size

        // get directory size
        while ((direntp = readdir(dir_ptr)) != NULL) {
            directorySize++;
        }

        //reset pointer to beginning of directory and allocate appropriate amount of memory
        rewinddir(dir_ptr);
        const char **directoryArray = malloc((directorySize + 1) * sizeof(char *)); //+1 for null terminating character

        int i = 0; //initialize counter variable and entryLength variable
        int entryLength;


        while ((direntp = readdir(dir_ptr)) != NULL) {

            entryLength = strlen(direntp->d_name) + 1; //get directory length
            directoryArray[i] = malloc(entryLength); //allocate corresponding amount of memory in array
            strcpy((char *) directoryArray[i], direntp->d_name); //copy the string into the array

            i++;
        }
        directoryArray[i] = "\0"; //null terminate the array

        closedir(dir_ptr); //close the directory when done
        return directoryArray; //return the array of directory contents
    }
}


//driver code, determines what directory and flag to use if provided
int main(int argc, char *argv[]) {

    const char **directoryEntries; // array of pointers to strings that will be passed to string out

    if (argc == 1) { //no argument; use current directory and empty flag.

        directoryEntries = buildDirectoryArray(CURRENTDIRECTORY);
        stringout(directoryEntries, "");

    } else if (argc == 2) { // one argument, determine if it's a directory or flag

        if (strcmp(argv[1], "-f") == 0) { //-f flag, use current directory and sort in ascending order

            directoryEntries = buildDirectoryArray(CURRENTDIRECTORY);
            stringout(directoryEntries, "-f");

        } else if (strcmp(argv[1], "-b") == 0) { //-b flag, use current directory and sort in descending order

            directoryEntries = buildDirectoryArray(CURRENTDIRECTORY);
            stringout(directoryEntries, "-b");

        } else { //not a recognizable flag, so must be directory. use no flag

            directoryEntries = buildDirectoryArray(argv[1]);
            stringout(directoryEntries, "");

        }

    } else if (argc == 3) { //2 arguments, first is directory, second is flag

        directoryEntries = buildDirectoryArray(argv[1]);
        stringout(directoryEntries, argv[2]);

    } else { //greater than two arguments (directory and optional flag expected), print error
        fprintf(stderr, "\n\tError: Too many arguments\n\t\tPlease enter a directory followed by an optional flag");
    }


}

