/* This exersise is for processing character data. The model
 * of input and output is supported by the library we have
 * been using, the standerd input and output, stdio,
 * library.
 * There are several methods the libraryr provides for
 * reading and writing one character at a time of which
 * getchar and putchar are the simples. Each time it is
 * called, getchar reads the next input character from a
 * textt stream then returns its value.
 *      c = getchar();
 * The cariable c contains the character. normally this
 * comes from the keyboard, for now we wont use input from
 * files.
 *
 * The function putchar prints a character each time it is
 * called:
 *     putchar(c);
 * In this case it prints the contencs of the integer
 * variable c.
 *
 * You can do alot just with input and output.
 * A simple example is shown bellow in the funciton
 * simpleInputOutput(). It takes an input and then prints it
 * backout. The thing EOF in the while loop, is a integer
 * defined in <stdio.h>, and stands for end of file.
 *
 * The "wordCounting();" function outputs how many lines
 * words and characters, take a look to see how it works.
 *
 * This line sets all three variables to zero:
 *      num1 = numw = numc = 0;
 */


#include <stdio.h>

/* void means that it does not return a value */
void simpleInputOutput() {
    printf("Simple Input to Output\n");
    int c;

    /* c = gethcar(); this can be moved into te while loop */
    while ((c = getchar()) != EOF) { /* != means Not Equalt To */
        putchar(c);
        c = getchar();
    }

}

void characterCounting() {
    printf("Character Counting\n");
    long numc;

    for (numc = 0; getchar() != EOF; ++numc) { ; }
    /* Use Control-D to stop or Conrtol-Z for Windows*/

    printf("\n%ld\n", numc);
}

void lineCounting() {
    printf("Line Counting\n");

    int c;
    int numl = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') { numl++; }
    }
    printf("\n%d\n", numl);
}


#define IN      1 /* inside a word*/
#define OUT     0 /* outside a word */

void wordCounting() {
    int c, numl, numw, numc, state;

    state = OUT;
    numl = numw = numc = 0;
    while ((c = getchar()) != EOF) {
        numc++;
        if (c == '\n') { numl++; }
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            numw++;
        }
    }
    printf("\nLines %3d\t Words %3d\t Characters %3d\n", numl, numw, numc);
}



int main() {
    //simpleInputOutput();
    //characterCounting();
    //lineCounting();
    wordCounting();
}


// vim: tw=60
