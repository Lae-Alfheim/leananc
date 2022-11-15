#include <stdio.h>
#include <unistd.h>

int main() {

    int i;

    //char *anime[8] = "h", "e", "e";
    const char *anime = "G A M E   O V E R";
    for (i=0; i < 18; i++) {
        printf("%.*s", 2, anime + i);
        fflush(stdout);
        usleep(50000);   //sleep 1s
        i++;
    }

    return 0;
}
