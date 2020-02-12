//Brandon Kelley 2716916 & Nicholas Bolyard 2709848

#include <stdio.h>
#include <string.h>
#include <sys/types.h>


//stringout takes an array of directory entry strings and prints them as is, in ascending, or descending order
void stringout(const char **directoryEntries, const char *flag) {

    int length = 0; //get length of the directory
    while (directoryEntries[length] != NULL)
        length++;

    int i = 0; // initialize loop variables
    int j = 0;

    if (strcmp(flag, "") == 0) { //no flag: print as is

        //print out contents
        for (i = 0; directoryEntries[i] != NULL; i++) {
            printf("%s\n", directoryEntries[i]);
        }

    } else if (strcmp(flag, "-f") == 0) { // -f flag: print in ascending order
        //sort using bubble sort
        const char *temp;
        for (i = 0; i < length - 1; i++) {
            for (j = i + 1; j < length; j++) {
                if (strcmp(directoryEntries[i], directoryEntries[j]) > 0) {
                    temp = directoryEntries[i];
                    directoryEntries[i] = directoryEntries[j];
                    directoryEntries[j] = temp;
                }
            }
        }

        //print out contents
        for (i = 0; directoryEntries[i] != NULL; i++)
            printf("%s\n", directoryEntries[i]);


    } else if (strcmp(flag, "-b") == 0) { // -b flag: print in descending order
        //sort using bubble sort
        const char *temp;
        for (i = 0; i < length - 1; i++) {
            for (j = i + 1; j < length; j++) {
                if (strcmp(directoryEntries[i], directoryEntries[j]) < 0) {
                    temp = directoryEntries[i];
                    directoryEntries[i] = directoryEntries[j];
                    directoryEntries[j] = temp;
                }
            }
        }

        //print out contents
        for (i = 0; directoryEntries[i] != NULL; i++) {
            printf("%s\n", directoryEntries[i]);
        }

    } else { // unrecognized/unsupported flag, print out error
        fprintf(stderr,
                "\n\tError: Unrecognized Flag\n\t\tuse -f for ascending order\n\t\tuse -b for descending order");
    }

}