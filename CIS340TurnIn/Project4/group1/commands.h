//Brandon Kelley 2716916 & Paul Antonescu 2726151

#ifndef PROJECT4_COMMANDS_H
#define PROJECT4_COMMANDS_H

//globals
extern int fd;
extern int mounted;

//utility commands
struct minix_super_block * getSuperBlock ();
struct minix_inode * getInode (struct minix_super_block * msb, int inodeNumber);

//project commands
void help();
extern int minixmount (char*imgName);
extern int minixumount ();
int showsuper();
int traverse(char* flag);
int showzone(int zoneNumber);
//Note quit is in minixConsole.c

//Bonus Command
int showfile (char*fileName);


#endif //PROJECT4_COMMANDS_H
