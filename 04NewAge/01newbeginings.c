/*
 * To new beginings - This is a combined to get me back up to speed
 *  When it comes to c, and a few new methods as well.
 *
 */

#include <stdio.h>
#include <string.h>


/* meet.c - to greet using inputs from function
 * to use greeting(firstname, secondname);
 */
void greeting(char *temp1, char *temp2) {
    char name[512];
    strcpy(name, temp2);
    printf("Hello %s %s\n", temp1, name);
    printf("BYE\n");
    /* greeting(argv[1], argv[2]); */
}

int main(int argc, char * argv[]) {
    greeting(argv[1], argv[2]);
}


// vim: tw=80
