#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//#include <termios.h>
//#include <signal.h>

int length=50;

//int sort[16] = {7,1,22,3,2,4,8,5,9,12,13,10,11,25,17,29};
int sort[50];

void render (int i) {
    fputs("\033c", stdout); /* Clear Screen */
    fputs("\x1b[23A\n",stdout);
    register int y;
    for (y=0; y<length; y++) {
        if (i == y) {
            printf("\e[0;31m%d%*c#%d \e[0m",y+1,sort[y],'#',sort[y]);
        } else {
            printf("%d%*c#%d",y+1,sort[y]*2,'#',sort[y]);
        }
        printf("\n");
    }
}

int main() {

    time_t t1; // declare time variable
    srand ( (unsigned) time (&t1)); // pass the srand() parameter
    for (register int i = 1; i <= length; i++) {
        sort[i] = rand() % 92 + 1; // use rand() function to get the random number
    }


    render(0);

    int temp;
    register int wrap = 0;
    do {
        for (register int i=wrap; i<length-1; i++) {
            if (sort[i] > sort[i+1]) {
                temp = sort[i];
                sort[i] = sort[i+1];
                sort[i+1] = temp;
                temp = 1;
                usleep(50000);
                render(i+1);
            }
        }
        render(0);
        if (temp == 0) {
            break;
        }

        temp = 0;
    } while (1);

    printf("\n");

    return 0;
}
