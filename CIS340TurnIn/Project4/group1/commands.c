//Brandon Kelley 2716916 & Paul Antonescu 2726151
#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#ifdef __linux__
#include <linux/minix_fs.h>
#endif

//define struct minix_super_block * getSuperBlock ()
struct minix_super_block * getSuperBlock (){

    if (fd < 0) // make sure file is mounted if not error
        fprintf(stderr,"Error: Image Not Mounted\n");

    struct minix_super_block *msb = malloc(sizeof(struct minix_super_block)); //allocate space to store super block
    lseek(fd, 1024, SEEK_SET); // superblock is second block in minix file system, lseek past bootblock to get there

    if(read(fd, msb, sizeof(struct minix_super_block)) == -1) //try to read in the data of superblock, else error
        return NULL; //and return null

    return msb; //if it worked return super block
}

//define struct minix_inode * getInode (struct minix_super_block * msb, int inodeNumber),  gets and returns an inode at the specified index
struct minix_inode * getInode (struct minix_super_block * msb, int inodeNumber){

    if (fd < 0) //check if file is mounted, if not error
        fprintf(stderr,"Error: Image Not Mounted\n"); //output must mount img
    struct minix_inode *inode = malloc(sizeof(struct minix_inode)); // allocate space for the inode

    //use superblock to navigate to starting point of inode array
    lseek(fd, 1024*(2 + msb->s_imap_blocks + msb->s_zmap_blocks) + (inodeNumber * sizeof(struct minix_inode)), SEEK_SET);

    //try to read data into inode, if fails output error
    if(read(fd, inode, sizeof(struct minix_inode)) == -1) {
        printf("failed to get inode");
        return NULL;
    }

    return inode; //return the inode
}

//define help(), prints out supported commands
void help(){
    printf("\nSupported Commands:\thelp     \tminixmount\tminixumount\tshowsuper\n");
    printf("                   \ttraverse [-l]\tshowzone\tshowfile\tquit\n\n");
}

//define minixmount(char*imgName), mounts imagefile give as argument
int minixmount (char*imgName) {

    fd = open(imgName, O_RDONLY ); //open file
    if(fd < 0) { //open file didn't work so output error
        fprintf(stderr,"Error: Could Not Mount %s\n", imgName);
        return -1;
    } //output that the mount worked
    printf("%s Was Mounted Successfully\n", imgName);
    return 0;
}

//define minixumount(), unmounts currently mounted imagefile if present
int minixumount () {

    if(close(fd) == -1) { //try to close open file, if it fails then error
        fprintf(stderr,"Error: Could Not Unmount");
        return 0;
    }

    printf("Unmount Successful\n"); // print out saying umount worked and return -1 to set mount status to unmounted
    return -1;
}

//define showsuper(), shows data stored in superblock of image
int showsuper() {

    struct minix_super_block *msb = getSuperBlock(); // get super block

    if(msb == NULL) //if its null then return -1 as error
        return -1;

    //print out formatted data areas of the structure
    printf("\n");
    printf("%-25s %d\n","number of inodes:", msb->s_ninodes);
    printf("%-25s %d\n","number of zones:", msb->s_nzones);
    printf("%-25s %d\n","number of imap_blocks:", msb->s_imap_blocks);
    printf("%-25s %d\n","number of zmap_blocks:", msb->s_zmap_blocks);
    printf("%-25s %d\n","first data zone:", msb->s_firstdatazone);
    printf("%-25s %d\n","log zone size:", msb->s_log_zone_size);
    printf("%-25s %d\n","max size:", msb->s_max_size);
    printf("%-25s %d\n","magic:", msb->s_magic);
    printf("%-25s %d\n","state:", msb->s_state);
    printf("%-25s %d\n","zone:", msb->s_zones);
    printf("\n");

    return 0;
}

//define Traverse(char* flag), returns directory data stored in first inode with optional -l flag for more data
int traverse(char* flag) {

    struct minix_super_block *superBlock = getSuperBlock(); //get superblock to find the offset of the inode array starting point

    if(superBlock == NULL) { //if its null then return -1 as error
        fprintf(stderr, "Error: Could Not Retrieve Super Block\n");
        return -1;
    }

    struct minix_inode *rootInode = getInode(superBlock, 0); //get root inode (first inode, index 0

    if(strcmp(flag, "") == 0){ // check for no flag option
        //printf("no flag\n"); //debug

        struct minix_dir_entry *directoryEntry; //declare directory entry
        char dataBlockBuffer[1024]; //get a buffer to hold the whole data block
        printf("\n");

        for (int i = 0; i <= 9; i++) { //10 zones total. first 8 are direct, last two are indirect
            if (rootInode->i_zone[i] == 0) // check if zone is empty, if so all following zones will be too so break
               break; //(inode fills zones in numeric order with last two being overflow for indirect zones)
            lseek(fd, rootInode->i_zone[i] * 1024, SEEK_SET); //set the pointer to corresponding zone
            if (read(fd, dataBlockBuffer, sizeof(dataBlockBuffer)) == -1) { //read file, error if needed
                fprintf(stderr,"Error: Could Not Read Data Block\n");
                return -1;
            }

            directoryEntry = (struct minix_dir_entry *) dataBlockBuffer;//get directory entry at starting point of datablockbuffer

            for (int j = 0; j < 1024 / sizeof(*directoryEntry); j++) { // max entries = blocksize/divided by entry size
                if (directoryEntry->name[0] == 0) //no name so continue loop
                    continue;
                if ((strcmp(directoryEntry->name, ".") == 0) || (strcmp(directoryEntry->name, "..") == 0)) {
                    directoryEntry = (void *) directoryEntry + sizeof(*directoryEntry) + 30;
                    continue; //ignore . and .. so increment directoryEntry and continue loop
                }
                //printf("\ni=%d    j=%d\n",i,j); //debug
                //printf("entry node: %d\n", directoryEntry->inode); //debug
                printf("%s\n", directoryEntry->name); //print name
                directoryEntry = (void *) directoryEntry + sizeof(*directoryEntry) + 30; //increment directory entry
            } //counted spaces between starting points of names on example showzone output to get 30
       }
        printf("\n");
        return 0;

    } else if (strcmp(flag, "-l") == 0){
        //printf("-l flag\n"); //debug

        struct minix_dir_entry *directoryEntry; //declare directory entry
        char dataBlockBuffer[1024]; //get a buffer to hold the whole data block
        printf("\n");

        for (int i = 0; i <= 9; i++) { //10 zones total. first 8 are direct, last two are indirect
            if (rootInode->i_zone[i] == 0) // check if zone is empty, if so all following zones will be too so break
                break; //(inode fills zones in numeric order with last two being overflow for indirect zones)
            lseek(fd, rootInode->i_zone[i] * 1024, SEEK_SET); //set the pointer to corresponding zone
            if (read(fd, dataBlockBuffer, sizeof(dataBlockBuffer)) == -1) {//read file, error if needed
                fprintf(stderr,"Error: Could Not Read Data Block\n");
                return -1;
            }
            directoryEntry = (struct minix_dir_entry *) dataBlockBuffer; //get directory entry at starting point of datablockbuffer

            for (int j = 0; j < 1024 / sizeof(*directoryEntry); j++) {  // max entries = blocksize/divided by entry size
                if (directoryEntry->name[0] == 0) //no name so continue loop
                    continue;
                if ((strcmp(directoryEntry->name, ".") == 0) || (strcmp(directoryEntry->name, "..") == 0)) {
                    directoryEntry = (void *) directoryEntry + sizeof(*directoryEntry) + 30;
                    continue; //ignore . and .. so increment directoryEntry and continue loop
                }

                //get the inode that has the data of the directory entry. note - 1 to get correct node (array format)
                struct minix_inode *directoryInode = getInode(superBlock, directoryEntry->inode - 1);

                //check is directory?
                if((directoryInode->i_mode&S_IFDIR) == 0040000)
                    printf("d");
                else
                    printf("-");

                //check owner permissions
                if((directoryInode->i_mode&S_IRUSR) == 00400)
                    printf("r");
                else
                    printf("-");

                if((directoryInode->i_mode&S_IWUSR) == 00200)
                    printf("w");
                else
                    printf("-");

                if((directoryInode->i_mode&S_IXUSR) == 00100)
                    printf("x");
                else
                    printf("-");


                //check group permissions
                if((directoryInode->i_mode&S_IRGRP) == 00040)
                    printf("r");
                else
                    printf("-");

                if((directoryInode->i_mode&S_IWGRP) == 00020)
                    printf("w");
                else
                    printf("-");

                if((directoryInode->i_mode&S_IXGRP) == 00010)
                    printf("x");
                else
                    printf("-");

                //check other permissions

                if((directoryInode->i_mode&S_IROTH) == 00004)
                    printf("r");
                else
                    printf("-");

                if((directoryInode->i_mode&S_IWOTH) == 00002)
                    printf("w");
                else
                    printf("-");

                if((directoryInode->i_mode&S_IXOTH) == 00001)
                    printf("x");
                else
                    printf("-");

                printf(" ");


                printf("%d ",directoryInode->i_uid); //get id
                printf("%d ",directoryInode->i_size);//get size (in bytes)

                //get time and format time according to given specifications
                char dateBuffer[32]; //buffer to store date string
                time_t rawTime = directoryInode->i_time; // raw time given as int
                strftime (dateBuffer, 100, "%b %d  %Y ", localtime (&rawTime)); //format time and store in buffer
                printf ("%s", dateBuffer); //print date

                printf("%s\n", directoryEntry->name); // print name

                directoryEntry = (void *) directoryEntry + sizeof(*directoryEntry) + 30; //increment to next entry
                //output shows them 30 spaces apart,
            }
        }
        printf("\n");
        return 0;

    } else { //flag not recognized so give error
        fprintf(stderr,"Error: Unsupported Flag\n");
        return -1;
    }

}

//define showzone(int zoneNumber), takes a zone number and displays the ascii contents
int showzone(int zoneNumber) {

    if (lseek(fd, 1024*zoneNumber, SEEK_SET) == -1) { //set fd to point to correct location
        fprintf(stderr, "Error: Could Not Find Zone\n");
        return -1;
    } else {

        char zoneDataBlockBuffer[1024]; //declare a buffer to hold zone data
        if (read(fd, zoneDataBlockBuffer, 1024) == -1) { //read in the zone (1 block in size)
            fprintf(stderr, "Error: Could Not Read Data Zone\n");
            return -1;
        } else { //print out the zone data if it is an ASCII value, if not print a space

            int counter = -16; //used to count line numbers

            for (int i = 0; i < 1024; i+=32) { //each word is 32 bytes, increment accordingly

                    counter += 16; //count by 16, each line should contain 16 hexadecimal
                    printf("\n"); //data strutcture requires a line of space
                    printf("%3x    ", counter); //start name line
                    counter += 16; //increment counter

                for (int j = i; j < i + 32; j++) {
                    if (isprint(zoneDataBlockBuffer[j])) { //use isprint to test if the value is ASCII
                        printf("%c ", zoneDataBlockBuffer[j]); //print char
                        //counter++;
                    }
                }
                printf("\n"); //go to next line
                printf("%3x    ", counter); //print line number

            } printf("\n\n");

        }
    }

    return 0;
}

//define showfile(char*fileName), takes a fileName and displays it's contents or not found (note must be in root directory)
int showfile (char*fileName) {

    if (strcmp(fileName, "") == 0) { //no file name given so error
        fprintf(stderr, "Error: Please enter file name\n");
        return -1;
    } else {

        struct minix_super_block *superBlock = getSuperBlock(); //get superblock to find the offset of the inode array starting point

        if (superBlock == NULL) { //if its null then return -1 as error
            fprintf(stderr, "Error: Could Not Retrieve Super Block\n");
            return -1;
        }

        struct minix_inode *rootInode = getInode(superBlock, 0); //get root inode (first inode, index 0

            struct minix_dir_entry *directoryEntry; //declare directory entry
            char dataBlockBuffer[1024]; //get a buffer to hold the whole data block

            for (int i = 0; i <= 9; i++) { //10 zones total. first 8 are direct, last two are indirect
                if (rootInode->i_zone[i] == 0) // check if zone is empty, if so all following zones will be too so break
                    break; //(inode fills zones in numeric order with last two being overflow for indirect zones)
                lseek(fd, rootInode->i_zone[i] * 1024, SEEK_SET); //set the pointer to corresponding zone
                if (read(fd, dataBlockBuffer, sizeof(dataBlockBuffer)) == -1) { //read file, error if needed
                    fprintf(stderr, "Error: Could Not Read Data Block\n");
                    return -1;
                }

                directoryEntry = (struct minix_dir_entry *) dataBlockBuffer;//get directory entry at starting point of datablockbuffer

                for (int j = 0;
                     j < 1024 / sizeof(*directoryEntry); j++) { // max entries = blocksize/divided by entry size
                    if (directoryEntry->name[0] == 0) //no name so continue loop
                        continue;
                    if ((strcmp(directoryEntry->name, ".") == 0) || (strcmp(directoryEntry->name, "..") == 0)) {
                        directoryEntry = (void *) directoryEntry + sizeof(*directoryEntry) + 30;
                        continue; //ignore . and .. so increment directoryEntry and continue loop
                    }

                    //printf("\ni=%d    j=%d\n",i,j); //debug
                    //printf("entry node: %d\n", directoryEntry->inode); //debug
                    //printf("%s\n", directoryEntry->name); //print name

                    if ((strcmp(directoryEntry->name, fileName)) == 0){
                        //printf("matches\n"); //debug
                        struct minix_inode *fileInode = getInode(superBlock, directoryEntry->inode - 1);
                        char fileDataBlockBuffer[1024];

                        for (int n = 0; n <= 7; n++) { //file will be less than 7 kb so go up to 7
                            if (fileInode->i_zone[n] == 0) // check if zone is empty, if so all following zones will be too so break
                                break;
                            lseek(fd, fileInode->i_zone[n] * 1024, SEEK_SET);
                            if (read(fd, fileDataBlockBuffer, sizeof(fileDataBlockBuffer)) == -1) { //read file, error if needed
                                fprintf(stderr, "Error: Could Not Read Data Block\n");
                                return -1;
                            }

                            for (int bytes = 0; bytes < 512; bytes++) //print the hex dump in the proper format.
                            {
                                if(bytes % 16 == 0) //if line has 16 bytes then go to next line
                                    printf("\n");

                                printf("%2x   ", fileDataBlockBuffer[bytes]); //print byte
                            }
                            printf("\n\n"); //formatting
                        }
                        return 0;
                    }
                    directoryEntry = (void *) directoryEntry + sizeof(*directoryEntry) + 30; //increment directory entry
                } //counted spaces between starting points of names on example showzone output to get 30
                fprintf(stderr, "Error: %s was not found", fileName); //file was not able to be found output error
            }
            printf("\n");
            return 0;

    }

}
