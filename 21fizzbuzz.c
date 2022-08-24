#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


unsigned int n;

void fizzbuzz() {
    unsigned int i;
    unsigned int fizz = 3;
    unsigned int buzz = 5;

    for (i = 0; i <= n; i++) {
        if (i == fizz && i == buzz) {
            fprintf(stdout, "fizzbuzz\n");
            fizz = fizz + 3;
            buzz = buzz + 5;
        } else if (i == fizz) {
            fprintf(stdout, "fizz\n");
            fizz = fizz + 3;
        } else if (i == buzz) {
            fprintf(stdout, "buzz\n");
            buzz = buzz + 5;
        } else {
            fprintf(stdout, "%d\n", i);
        }
    }

}
void fizzbuzz1() {
    unsigned int i;
    unsigned int fizz = 3;
    unsigned int buzz = 5;

    for (i = 0; i <= n; i++) {
        if (i % 3==0 && i % 5==0) {
            fprintf(stdout, "fizzbuzz\n");
        } else if (i % 3==0) {
            fprintf(stdout, "fizz\n");
        } else if (i % 5==0) {
            fprintf(stdout, "buzz\n");
        } else {
            fprintf(stdout, "%d\n", i);
        }

    }
}
int main (int argc, char **argv) {


    n = 15;
    if (argc <= 1) {
        fprintf(stderr, "No Arguments Inputed\n");
    } else if (argc > 2) {
        fprintf(stderr, "Too many Arguments inputed\n");
        return 1;
    } else {
        n = atoi(argv[1]);
    }

    //fizzbuzz(); /* Slightly faster */
    //fprintf(stderr, "\n");7
    //fizzbuzz1(); /**/


    clock_t begin = clock();

    fizzbuzz();

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    fprintf(stdout, "%f\n", time_spent);



    return 0;
}
