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

    printf("%ld\n", numc);
}

int main() {
    //simpleInputOutput();
    printf("%d", EOF);
    characterCounting();
}


// vim: tw=60
