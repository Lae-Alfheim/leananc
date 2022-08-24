#include <stdio.h> // needed for printf and scanf
#include <stdlib.h> // malloc
#include <unistd.h> // used for sleep
/* defined vale of pi */
#define PIE 3.14159265358979
/* cross platform clear operation */
#ifdef _WIN32
#include <conio.h>
#define clear() system(cls)
#else
#include <stdio.h>
#define clear() printf("\e[1;1H\e[2J")
#endif






void animate(int p, char *text, char *past) { /* general animate */
    clear();
    printf("%s", past);

    int l = 0;
    while (l != p) {
        printf("%*.*s", l, l, text);
        printf("\n");
        usleep(60000);
        clear();
        printf("%s", past);
        l++;
    }
    printf("%s", text);
}
void circle(void) {

    /* get input */
    fflush(stdin);
    float radius;
    scanf("%15f", &radius );
    //https://stackoverflow.com/questions/28017232/scanf-text-overflow-in-c

    /* calculate answer and print */
    float answer;
    answer = PIE * (radius * radius);
    printf("%f\n", answer);
    printf("\n             *  *\n          *        *    PIE * ( %f * %f )\n         *__________*       AREA = %f\n         *    %f\n          *        *\n             *  *\n\n", radius, radius, answer, radius * 2);

}

int main(void) {

    char *overflow;
    overflow = (char *)malloc(128 * sizeof(char)); /*using malloc to allocate*/

    /* call functionos */
    clear(); /* clear */
    animate(17, "Radius of Circle: ", "\0");
    circle();

    fgets(overflow, 128, stdin);

    if (overflow == "shrek") {
        sleep(2);
        printf("          c,_.--.,y\n            7 =.=(\n           (   ,_Y)\n           :  '_-_;\n       ___.'\\.  - (\n     .`'''S,._'--'_2..,_\n     |    ':::::=:::::  \\ \n     .     f== ;-,---.' T\n      Y.   r,-,_/_      |\n      |:\\___.---' '---./\n      |'`             )\n       \             ,\n       ':;,.________.;L\n       /  '---------' |\n       |              \\\n       L---'-,--.-'--,-'\n        T    /   \\   Y\n        |   Y    ,   |\n        |   \\    (   |\n        (   )     \\,_L\n        7-./      )  `,\n       /  _(      '._  \\ \n     '---'           '--'\n");
        sleep(2);

    }

    printf("======\n%ld%s\n======", sizeof_var(overflow), overflow);

    /* end */
    return 0;
}

//
//
//         c,_.--.,y
//           7 =.=(
//          (   ,_Y)
//          :  '_-_;
//      ___.'\.  - (
//    .`'''S,._'--'_2..,_
//    |    ':::::=:::::  \
//    .     f== ;-,---.' T
//     Y.   r,-,_/_      |
//     |:\___.---' '---./
//     |'`             )
//      \             ,
//      ':;,.________.;L
//      /  '---------' |
//      |              \
//      L---'-,--.-'--,-'
//       T    /   \   Y
//       |   Y    ,   |
//       |   \    (   |
//       (   )     \,_L
//       7-./      )  `,
//      /  _(      '._  \
//     '--'           '--'
//
//
//         "c,_.--.,y\n            7 =.=(\n           (   ,_Y)\n           :  '_-_;\n       ___.'\.  - (\n     .`'''S,._'--'_2..,_\n     |    ':::::=:::::  \\n     .     f== ;-,---.' T\n      Y.   r,-,_/_      |\n      |:\___.---' '---./\n      |'`             )\n       \             ,\n       ':;,.________.;L\n       /  '---------' |\n       |              \\n       L---'-,--.-'--,-'\n        T    /   \   Y\n        |   Y    ,   |\n        |   \    (   |\n        (   )     \,_L\n        7-./      )  `,\n       /  _(      '._  \\n     '---'           '--'\n"
