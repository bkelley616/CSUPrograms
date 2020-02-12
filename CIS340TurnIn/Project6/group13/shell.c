//Brandon Kelley 2716916 & Quan Nguyen 2729679



//CIS 340 Project 6
//implement pipes (up to two) and re-direction to existing shell

//Import needed functions
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

//controls shell logic and function
int main() {

    int pid,status; //int variables used to determine child/parent process and wait status

    while(1) {

        char commandLineInput[256]; // declare needed string buffers for command and path
        char path[256];

        memset(commandLineInput,0,256);


        printf("MYSHELL:~$ "); // print prompt statement

        scanf("%[^\n]", commandLineInput); //get a line of user input
        while ((getchar()) != '\n'); //flush the input buffer

        int argCount = 0; //initial argument count to 0

        char *arg = strtok(commandLineInput, " "); //split command into tokens by whitespace
        char *argList[17] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
        //this shell supports 16 arguments (last is NULL terminator)


        while (arg != NULL) { //while loop to initialize command to appropriate location in argument list array
            argList[argCount++] = arg;
            arg = strtok(NULL, " ");
        } //also count the number of arguments



        if(argList[0] == NULL) //check for no command
            continue;

        //begin internal commands cd, path, path +, path -, and quit
        if(strcmp(argList[0], "cd") == 0) { //cd command, change directory

            if (argList[1] == NULL) //if no directory is given go to home
                chdir(getenv("HOME"));
            else
                chdir(argList[1]); //else go to specified directory

        } else if ((strcmp(argList[0], "path") == 0) && (argList[1] == NULL)) { //path command, print path
            printf("%s\n",path);

        } else if ((strcmp(argList[0], "path") == 0) && (strcmp(argList[1], "+") == 0)) { //path + command, append to path

            if(argList[2] != NULL) //append given string to tail of path buffer
                strcat(path, argList[2]);
            else
                printf("Error: No Additional Pathway Given\n");


        } else if ((strcmp(argList[0], "path") == 0) && (strcmp(argList[1], "-") == 0)) {// path - command, delete from path

            if(argList[2] != NULL) { //remove given string from the path buffer

                char *start = strstr(path, argList[2]);//create pointer to start of string to be deleted

                if (start == NULL) { //error check if string is not in the path
                    printf("Error: Argument not in Path\n");
                    continue;
                }

                char *end = start + strlen(argList[2]);//create pointer to the end of the string to be deleted

                //copy without the removed string, (destination,source,size)
                memmove(start, start + strlen(argList[2]), strlen(end) + 1);

            } else
                printf("Error: No Additional Remove Pathway Given\n");


        } else if (strcmp(argList[0], "quit") == 0) { //quit command, exit shell
            printf("Exiting Shell...\n");
            exit(0);

        } else { //else not an internal command


            //needed variables to determine if we have pipes/redirection in the command
            int numOfPipes = 0;
            int p1Index,p2Index = 0;
            char *inputFile = NULL;
            char *outputFile = NULL;
            int inStatus, outStatus = 0;

            //check for pipes
            int index = 0;
            while (argList[index] != NULL) {

                if ((strcmp(argList[index], "|") == 0)) {

                    if (numOfPipes == 0)
                        p1Index = index; //first pipe index
                    else
                        p2Index = index; //second pipe index

                    numOfPipes++;
                    argList[index] = NULL;

                    index++;

                } else {

                    index++;
                    continue;
                }
            }

            //no pipes, test if redirection in present
            if (numOfPipes < 1) {
                int index2 = 0;
                while (argList[index2] != NULL) {

                    if ((strcmp(argList[index2], ">") == 0)){ //output
                        outStatus = 1;
                        if(argList[index2 + 1] == NULL){
                            outputFile = "";
                            break;
                        }
                        outputFile = strdup(argList[index2 + 1]); // get the file
                        argList[index2] = NULL;
                        index2++;

                    } else if (strcmp(argList[index2], "<") == 0){//input
                        inStatus = 1;
                        if(argList[index2 + 1] == NULL){
                            inputFile = "";
                            break;
                        }
                        inputFile = strdup(argList[index2 + 1]); // get the file
                        argList[index2] = NULL;
                        index2++;

                    } else {

                        index2++;
                        continue;
                    }
                }

            }

            if(numOfPipes > 0){ // contains pipes (max of two)

                // setup variables for potential redirection in each part of the command pipeline
                char *inputFile1 = NULL;
                char *outputFile1 = NULL;
                int inStatus1, outStatus1 = 0;

                char *inputFile2 = NULL;
                char *outputFile2 = NULL;
                int inStatus2, outStatus2 = 0;

                char *inputFile3 = NULL;
                char *outputFile3 = NULL;
                int inStatus3, outStatus3 = 0;

                if (numOfPipes == 1) { // 1 pipe, split into two commands

                    // make a copy of the path for the second command to use when calling strtok
                    // (strtok edits the orginal string)
                    char * pathCopy =  NULL;
                    pathCopy = strdup(path);

                    // declare and initialize argList 2 for second command
                    char *argList2[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL};
                    int n = 0;
                    p1Index += 1;

                    while (argList[p1Index] != NULL) {
                        argList2[n] = argList[p1Index];
                        n++;
                        p1Index++;
                    }

                    //check first command for re-direction and set proper variables
                    int i = 0;
                    while (argList[i] != NULL) {

                        if ((strcmp(argList[i], ">") == 0)){
                            outStatus1 = 1;
                            if(argList[i + 1] == NULL){
                                outputFile1 = "";
                                break;
                            }
                            outputFile1 = strdup(argList[i + 1]);
                            argList[i] = NULL;
                            i++;

                        } else if (strcmp(argList[i], "<") == 0){
                            inStatus1 = 1;
                            if(argList[i + 1] == NULL){
                                inputFile1 = "";
                                break;
                            }
                            inputFile1 = strdup(argList[i + 1]);
                            argList[i] = NULL;
                            i++;

                        } else {
                            i++;
                            continue;
                        }
                    }

                    //check second command for re-direction and set proper variables
                    int i2 = 0;

                    while (argList2[i2] != NULL) {

                        if ((strcmp(argList2[i2], ">") == 0)){
                            outStatus2 = 1;
                            if(argList2[i2 + 1] == NULL){
                                outputFile2 = "";
                                break;
                            }

                            outputFile2 = strdup(argList2[i2 + 1]);
                            argList2[i2] = NULL;
                            i2++;

                        } else if (strcmp(argList2[i2], "<") == 0){
                            inStatus2 = 1;
                            if(argList2[i2 + 1] == NULL){
                                inputFile2 = "";
                                break;
                            }
                            inputFile2 = strdup(argList2[i2 + 1]);
                            argList2[i2] = NULL;
                            i2++;

                        } else {
                            i2++;
                            continue;
                        }
                    }

                    int myPipe[2]; //create pipe
                    pipe(myPipe);
                    pid = fork(); // fork into two processes

                    if (pid == -1) //error with fork command
                        printf("Error: Fork Failed");


                    if (pid == 0) {
                        //default to write to pipe
                        dup2(myPipe[1], STDOUT_FILENO);
                        close(myPipe[0]);
                        close(myPipe[1]);

                        //handle redirection cases to divert I/O
                        if(outStatus1 == 1){
                            int fd = open(outputFile1, O_WRONLY | O_CREAT | O_TRUNC, 777);
                            close(1);
                            dup(fd);
                            close(fd);
                        }

                        if(inStatus1 == 1){

                            int fd = open(inputFile1, O_RDONLY);
                            close(0);
                            dup(fd);
                            close(fd);

                        }

                        //build and run command
                        char *entry = strtok(path, ":"); //delimit into path entry tokens by :
                        char filename[256];//declare filename buffer

                        while (entry != NULL) { // while entries are remaining
                            strcpy(filename, ""); // erase filename

                            strcat(filename,entry); //build filename with entry + "/" + command
                            strcat(filename,"/");
                            strcat(filename,argList[0]);
                            execv(filename, argList); //execute file, if it works it doesn't return else continue to next entry
                            entry = strtok(NULL, ":");

                        }

                        perror("Command Not Found"); // exhausted all entries, command was not found
                        exit(1); //exit child process
                    }
                    else {


                        int pid2 = fork(); //fork to next child

                        if (pid2 == -1) //error with fork command
                            printf("Error: Fork Failed");

                        if(pid2 == 0) {

                            //default to read pipe

                            dup2(myPipe[0], STDIN_FILENO);
                            close(myPipe[0]);
                            close(myPipe[1]);

                            //handle re-direction
                            if(outStatus2 == 1){
                                int fd = open(outputFile2, O_WRONLY | O_CREAT | O_TRUNC, 777);
                                close(1);
                                dup(fd);
                                close(fd);
                            }

                            if(inStatus2 == 1){

                                int fd = open(inputFile2, O_RDONLY);
                                close(0);
                                dup(fd);
                                close(fd);

                            }

                            //run command
                            char *entry2 = strtok(pathCopy, ":"); //delimit into path entry tokens by :
                            char filename2[256];//declare filename buffer


                            while (entry2 != NULL) { // while entries are remaining
                                strcpy(filename2, ""); // erase filename

                                strcat(filename2, entry2); //build filename with entry + "/" + command
                                strcat(filename2, "/");
                                strcat(filename2, argList2[0]);

                                execv(filename2, argList2);
                                entry2 = strtok(NULL, ":");

                            }

                            perror("Command Not Found"); // exhausted all entries, command was not found
                            exit(1); //exit child process


                        } else {

                            //close pipe and wait for last child to terminate
                            close(myPipe[0]);
                            close(myPipe[1]);
                            waitpid(pid2,&status,0);

                        }
                    }

                } else { // two pipes, split into 3 commands

                    //create copys of paths to use with strtok
                    char * pathCopy2 =  NULL;
                    pathCopy2 = strdup(path);

                    char * pathCopy3 =  NULL;
                    pathCopy3 = strdup(path);

                    //create argList2 and fill
                    char *argList2[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL};
                    int n = 0;
                    p1Index += 1;

                    while (argList[p1Index] != NULL) {
                        argList2[n] = argList[p1Index];
                        n++;
                        p1Index++;
                    }

                    //create argList3 and fill
                    char *argList3[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                        NULL, NULL, NULL, NULL, NULL};
                    int k = 0;
                    p2Index += 1;

                    while (argList[p2Index] != NULL) {
                        argList3[k] = argList[p2Index];
                        k++;
                        p2Index++;
                    }


                    //check each argList for redirection and assign proper variables
                    int i = 0;
                    while (argList[i] != NULL) {

                        if ((strcmp(argList[i], ">") == 0)){
                            outStatus1 = 1;
                            if(argList[i + 1] == NULL){
                                outputFile1 = "";
                                break;
                            }
                            outputFile1 = strdup(argList[i + 1]);
                            argList[i] = NULL;
                            i++;

                        } else if (strcmp(argList[i], "<") == 0){
                            inStatus1 = 1;
                            if(argList[i + 1] == NULL){
                                inputFile1 = "";
                                break;
                            }
                            inputFile1 = strdup(argList[i + 1]);
                            argList[i] = NULL;
                            i++;

                        } else {
                            i++;
                            continue;
                        }
                    }


                    int i2 = 0;
                    while (argList2[i2] != NULL) {

                        if ((strcmp(argList2[i2], ">") == 0)){
                            outStatus2 = 1;
                            if(argList2[i2 + 1] == NULL){
                                outputFile2 = "";
                                break;
                            }
                            outputFile2 = strdup(argList2[i2 + 1]);
                            argList2[i2] = NULL;
                            i2++;

                        } else if (strcmp(argList2[i2], "<") == 0){
                            inStatus2 = 1;
                            if(argList2[i2 + 1] == NULL){
                                inputFile2 = "";
                                break;
                            }
                            inputFile2 = strdup(argList2[i2 + 1]);
                            argList2[i2] = NULL;
                            i2++;

                        } else {
                            i2++;
                            continue;
                        }
                    }


                    int i3 = 0;
                    while (argList3[i3] != NULL) {

                        if ((strcmp(argList3[i3], ">") == 0)){
                            outStatus3 = 1;
                            if(argList3[i3 + 1] == NULL){
                                outputFile3 = "";
                                break;
                            }
                            outputFile3 = strdup(argList3[i3 + 1]);
                            argList3[i3] = NULL;
                            i3++;


                        } else if (strcmp(argList3[i3], "<") == 0){
                            inStatus3 = 1;
                            if(argList3[i3 + 1] == NULL){
                                inputFile3 = "";
                                break;
                            }
                            inputFile3 = strdup(argList3[i3 + 1]);
                            argList3[i3] = NULL;
                            i3++;

                        } else {
                            i3++;
                            continue;
                        }
                    }

                    //create pipes
                    int pipe1[2];
                    int pipe2[2];
                    pipe(pipe1);
                    pipe(pipe2);

                    pid = fork(); //fork to first child

                    if (pid == -1) //error with fork command
                        printf("Error: Fork Failed");

                    if (pid == 0) {
                       // default to writing to pipe1
                        dup2(pipe1[1], STDOUT_FILENO);
                        close(pipe1[0]);
                        close(pipe1[1]);
                        close(pipe2[0]);
                        close(pipe2[1]);

                        //handle re-direction
                        if(outStatus1 == 1){
                            int fd = open(outputFile1, O_WRONLY | O_CREAT | O_TRUNC, 777);
                            close(1);
                            dup(fd);
                            close(fd);
                        }

                        if(inStatus1 == 1){

                            int fd = open(inputFile1, O_RDONLY);
                            close(0);
                            dup(fd);
                            close(fd);

                        }

                        //build and run command
                        char *entry = strtok(path, ":"); //delimit into path entry tokens by :
                        char filename[256];//declare filename buffer


                        while (entry != NULL) { // while entries are remaining
                            strcpy(filename, ""); // erase filename

                            strcat(filename,entry); //build filename with entry + "/" + command
                            strcat(filename,"/");
                            strcat(filename,argList[0]);
                            execv(filename, argList); //execute file, if it works it doesn't return else continue to next entry
                            entry = strtok(NULL, ":");

                        }

                        perror("Command Not Found"); // exhausted all entries, command was not found
                        exit(1); //exit child process
                    }
                    else {

                        int pid2 = fork(); //fork to second child

                        if (pid2 == -1) //error with fork command
                            printf("Error: Fork Failed");

                        if(pid2 == 0) {
                            //default to read pipe 1 and write to pipe2
                            dup2(pipe1[0], STDIN_FILENO);
                            dup2(pipe2[1], STDOUT_FILENO);
                            close(pipe1[0]);
                            close(pipe1[1]);
                            close(pipe2[0]);
                            close(pipe2[1]);

                            //handle redirection
                            if(outStatus2 == 1){
                                int fd = open(outputFile2, O_WRONLY | O_CREAT | O_TRUNC, 777);
                                close(1);
                                dup(fd);
                                close(fd);
                            }

                            if(inStatus2 == 1){

                                int fd = open(inputFile2, O_RDONLY);
                                close(0);
                                dup(fd);
                                close(fd);

                            }

                            // build and execute command
                            char *entry2 = strtok(pathCopy2, ":"); //delimit into path entry tokens by :
                            char filename2[256];//declare filename buffer


                            while (entry2 != NULL) { // while entries are remaining
                                strcpy(filename2, ""); // erase filename

                                strcat(filename2, entry2); //build filename with entry + "/" + command
                                strcat(filename2, "/");
                                strcat(filename2, argList2[0]);

                                execv(filename2, argList2);
                                entry2 = strtok(NULL, ":");

                            }

                            perror("Command Not Found"); // exhausted all entries, command was not found
                            exit(1); //exit child process


                        } else {

                            int pid3 = fork(); // fork to third child

                            if (pid3 == -1) //error with fork command
                                printf("Error: Fork Failed");

                            if(pid3 == 0) {
                                // default to read from pipe 2
                                dup2(pipe2[0], STDIN_FILENO);
                                close(pipe1[0]);
                                close(pipe1[1]);
                                close(pipe2[0]);
                                close(pipe2[1]);

                                // handle redirection

                                if(outStatus3 == 1){
                                    int fd = open(outputFile3, O_WRONLY | O_CREAT | O_TRUNC, 777);
                                    close(1);
                                    dup(fd);
                                    close(fd);
                                }

                                if(inStatus3 == 1){

                                    int fd = open(inputFile3, O_RDONLY);
                                    close(0);
                                    dup(fd);
                                    close(fd);

                                }

                                // build and execute command
                                char *entry3 = strtok(pathCopy3, ":"); //delimit into path entry tokens by :
                                char filename3[256];//declare filename buffer

                                while (entry3 != NULL) { // while entries are remaining
                                    strcpy(filename3, ""); // erase filename

                                    strcat(filename3, entry3); //build filename with entry + "/" + command
                                    strcat(filename3, "/");
                                    strcat(filename3, argList3[0]);

                                    execv(filename3, argList3);
                                    entry3 = strtok(NULL, ":");

                                }

                                perror("Command Not Found"); // exhausted all entries, command was not found
                                exit(1); //exit child process


                            } else {

                                //close pipes and wait for last child before preceding to next usr input
                                close(pipe1[0]);
                                close(pipe1[1]);
                                close(pipe2[0]);
                                close(pipe2[1]);
                                waitpid(pid3,&status,0);

                            }
                        }
                    }
                }

            } else if (outStatus == 1){ // output redirection, no pipe(s)
                int fd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 777); //create/open file

                pid = fork(); //fork to create child process to run command, main process will wait for child termination
                //determined by process id

                if (pid == -1) //error with fork command
                    printf("Error: Fork Failed");
                if (pid == 0) { //child process code
                    close(1); //set output to file
                    dup(fd);


                    char *entry = strtok(path, ":"); //delimit into path entry tokens by :
                    char filename[256];//declare filename buffer

                    while (entry != NULL) { // while entries are remaining
                        strcpy(filename, ""); // erase filename

                        strcat(filename,entry); //build filename with entry + "/" + command
                        strcat(filename,"/");
                        strcat(filename,argList[0]);

                        execv(filename, argList); //execute file, if it works it doesn't return else continue to next entry
                        entry = strtok(NULL, ":");
                    }

                    perror("Command Not Found"); // exhausted all entries, command was not found
                    exit(1); //exit child process

                } else { //parent process , wait for child process to terminate before continuing loop
                    close(fd);
                    wait(&status);

                }

            } else if (inStatus == 1){ // input redirection, no pipe

                int fd = open(inputFile, O_RDONLY); // open file

                pid = fork(); //fork to create child process to run command, main process will wait for child termination
                //determined by process id

                if (pid == -1) //error with fork command
                    printf("Error: Fork Failed");
                if (pid == 0) { //child process code
                    close(0); //set to read from file
                    dup(fd);


                    char *entry = strtok(path, ":"); //delimit into path entry tokens by :
                    char filename[256];//declare filename buffer

                    while (entry != NULL) { // while entries are remaining
                        strcpy(filename, ""); // erase filename

                        strcat(filename,entry); //build filename with entry + "/" + command
                        strcat(filename,"/");
                        strcat(filename,argList[0]);

                        execv(filename, argList); //execute file, if it works it doesn't return else continue to next entry
                        entry = strtok(NULL, ":");
                    }

                    perror("Command Not Found"); // exhausted all entries, command was not found
                    exit(1); //exit child process

                } else { //parent process , wait for child process to terminate before continuing loop
                    close(fd);
                    wait(&status);

                }


            } else { //no pipes or redirection

                pid = fork(); //fork to create child process to run command, main process will wait for child termination
                //determined by process id

                if (pid == -1) //error with fork command
                    printf("Error: Fork Failed");
                else if (pid == 0) { //child process code

                    char *entry = strtok(path, ":"); //delimit into path entry tokens by :
                    char filename[256];//declare filename buffer

                    while (entry != NULL) { // while entries are remaining
                        strcpy(filename, ""); // erase filename

                        strcat(filename,entry); //build filename with entry + "/" + command
                        strcat(filename,"/");
                        strcat(filename,argList[0]);

                        execv(filename, argList); //execute file, if it works it doesn't return else continue to next entry
                        entry = strtok(NULL, ":");
                    }

                    perror("Command Not Found"); // exhausted all entries, command was not found
                    exit(1); //exit child process

                } else { //parent process , wait for child process to terminate before continuing loop
                    wait(&status);
                }
            }
        }
    }

    return 0;
}


