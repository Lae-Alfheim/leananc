#include <stdlib.h>
#include <stdio.h>


int main(void) {

    srand(time(0));

    // intager
    int intagervar = rand();
    // string
    char charvar = 'A' + (random() % (RAND_MAX)/2000);



    // print out int
    printf("%d is an intager!\n", intagervar);


    // print out float
    int i;
    for ( i = 10; i < 20; i = i + 1 ) {
        if(i <= 10 || i == 15) {
            printf("\n%f ",(float)rand()/(float)(RAND_MAX/14));
        }
        else if(i <= 20) {
            printf(" %f ", (float)rand()/(float)(RAND_MAX/20));
        }
    }
    printf("\n%f  these are floats!", (float)rand()/(float)(RAND_MAX/19));


    // print out char
    int a = 10;
    printf("\n%c", charvar);
    for (a <= 10; a < 20; a = a + 1) {

        printf("%c", 'A' + (random() % 26));
    }
    printf(" this is a string! UwU");


    // end
    printf("\n");

    free(intagervar);
    free(charvar);
    free(i);
    free(a);
    return 0;
}

// format specifiers in c
//
// Data type                        Format Specifier
// Integer      short signed            %d or %I
//              short unsigned          %u
//              long signed             %ld
//              long unsigned           %lu
//              unsigned hexadecimal    %x
//              unsigned octal          %o
// Real         float                   %f
//              double                  %lf
// Character    signed character        %c
//              unsigned character      %c
// String          ---------->          %s
