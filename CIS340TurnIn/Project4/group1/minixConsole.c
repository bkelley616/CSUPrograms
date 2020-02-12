//Brandon Kelley 2716916 & Paul Antonescu 2726151

//minixConsole.c contains the main driver code that controls the high level logic


//import needed libraries
#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef __linux__
#include <linux/minix_fs.h>
#endif

int fd = -1; //used to get the location of file pointer  if fd == -1 then fd not set.    if fd >= 0 then fd is set
int mounted = -1; //unmounted status = -1              mounted status = 0


    int main() { //start program

    char command[256], arg[256], flag[256]; //declare buffers to hold the command that will be split into two parts: arg, flag

    while(1) {


        printf("minix:~$ "); //print prompt statement
        scanf("%[^\n]", command);
        while ((getchar()) != '\n'); //fflush(stdin); not supported officially (meant for output buffer), this is better way

        strcpy(arg, strtok(command , " ")); //get the first argument entered and store it in arg buffer

        char *nextToken; //declare pointer to the next token
        nextToken = strtok(NULL, " "); // split by whitespace and get the next token
        
        if(nextToken != NULL) //if next token isn't null then store that in flag variable
            strcpy(flag, nextToken);
        else
            strcpy(flag, ""); //else the flag is empty

        //printf("arg= %s\n", arg); //debug
        //printf("flag= %s\n", flag); //debug

        if (strcmp(arg, "help") == 0) { //no flag: print as is
            help();

        } else if (strcmp(arg, "minixmount") == 0) { //mount supplied file name or error
            //flag in this case is the file name
            mounted = minixmount(flag);

        } else if (strcmp(arg, "minixumount") == 0) { //unmount currently mounted file or error
            mounted = minixumount();

        } else if (strcmp(arg, "showsuper") == 0) { //show the superblock, output error if the command fails

            if(showsuper() == -1)
                fprintf(stderr,"showsuper failed...\n");

        } else if (strcmp(arg, "traverse") == 0) {  // traverse directory entries in root directory
            //note -l flag results in more detailed information
            if(traverse(flag) == -1)
                fprintf(stderr,"traverse failed...\n");

        } else if (strcmp(arg, "showzone") == 0) { // show the corresponding zone if not error

            if(mounted == -1) { //image not mounted, output error
                fprintf(stderr,"Error: Image Not Mounted\n");
            } else if (strcmp(flag, "") == 0)
                fprintf(stderr,"Error: zone not given\n");
            else if(showzone(atoi(flag)) == -1)
                fprintf(stderr,"showzone failed...\n");

        } else if (strcmp(arg, "showfile") == 0) { //show the corresponding file (must be in the root directory) or error

            if(mounted == -1) { //image not mounted, output error
                fprintf(stderr,"Error: Image Not Mounted\n");
            } else if (strcmp(flag, "") == 0)
                fprintf(stderr,"Error: File Name not given\n");
            else if(showfile(flag) == -1)
                fprintf(stderr,"showfile failed...\n");

        } else if (strcmp(arg, "quit") == 0) { //close file if open, then exit program

            if (mounted == 0)
                close(fd);
            printf("exiting...\n");
            return 0;
        } else { //error, command was not recognized
            fprintf(stderr,"%s: Command not found.\n",arg);
        }

    }



}