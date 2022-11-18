/* print the fahrenheit to celsius table */

#include <stdio.h>


int main() {
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temerature scale */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    printf("Fahrenheit\tCelsius\n");
    while (fahr <= upper) {
        celsius = 5 * (fahr-32) / 9;
        printf("%d\t\t%d\n", fahr, celsius);
        fahr = fahr + step;
    }
}

// vim: tw=60
