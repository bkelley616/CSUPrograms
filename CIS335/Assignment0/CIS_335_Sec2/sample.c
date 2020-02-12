#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char className[] = "CIS ";
    char classNum[] = "335";
    char sectionNum[] = "2";


    strcat(className,classNum);
    printf(" Hello %s Section %s",className,sectionNum);


    return 0;
}