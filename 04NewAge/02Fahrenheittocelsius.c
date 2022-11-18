/* print the fahrenheit to celsius table */

#include <stdio.h>


#define LOWER 0     /* Lower limit of the table */
#define UPPER 300   /* upper limit */
#define STEP 20     /* step size */

int main() {
    printf("Fahrenheit\tCelsius\n");

    for (int fahr = LOWER; fahr <=UPPER; fahr += STEP) {
        printf("%3d\t\t%6.1f\n", fahr, (5.0/9.0) * (fahr-32)); }
}

// vim: tw=60
