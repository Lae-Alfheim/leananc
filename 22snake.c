/*
 * https://pastebin.com/q9yj0g56
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <termios.h>


int tailx[1024], taily[1024];
int fruitx,fruity,playerx,playery;
int height = 20; /* height of playspace*/
int width = 20; /* width " " `!Excluding score+*/
int score = 0; /* start score */
int sp = 1; /* start speed */

void animate(const char *anime, int len) { /* Used to apply a simple animation to text */
/* https://stackoverflow.com/questions/27077505/printf-in-c-with-using-sleep-not-working
 * printf is buffered to the I/O, Need to force it with fflush */
    int i;
    for (i=0; i < len; i++) {
        printf("%.*s", 2, anime + i);
        fflush(stdout);
        usleep(50000);   //sleep
        i++;
    }
}


void gameover() {

    animate("\tG A M E   O V E R !\nENTER FIRST THREE: ", 42);
    /* https://www.tutorialspoint.com/cprogramming/c_input_output.html */
    char name[3];
    int i;
    for (i=0; i < 3; i++) {
        name[i] = getchar();
        putchar(name[i]);
    }

}
/* Function to draw board */
void draw() {
    int x, y, i;
    int tail = 1;

    for (y=0; y<height; y++) {
        for (x=0; x<width; x++) {
            if (y == 0 || y == height-1) {
                printf("YY");
            } else if (x == 0) {
                printf("X ");
            } else if (x == width-1) {
                printf(" X");
                if (y == 2) {
                    printf("  SCORE:%d", score*10);
                } else if (y == 4) {
                    printf("  SPEED:%d", sp);
                }
            } else {
                if (x == playerx && y == playery) {
                    printf("00");
                } else if (x == fruitx
                        && y == fruity) {
                    printf("cb");
                } else if (tail == 1){
                    for (i=0; i<10; i++) {
                        if (tailx[i] == x && taily[i] == y || taily[2] == y && tailx[2] == x) {
                            tail = 0;
                            printf("()");
                        }
                    } if (tail == 1) {
                        printf("  ");
                    }
                } else {
                    printf("  ");
                }
            }
        }
        printf("\n");

    }
}
void fruit() {
    time_t t;
    srand((unsigned) time(&t));

    int x,y;
    x = width/2;
    y = height/2;

    do {
        fruitx=rand()%(width-1);
    } while (fruitx == 0
            || fruitx == playerx);
    do {
        fruity=rand()%(height-1);
    } while (fruity == 0
            || fruity == playery);

}
void gameplay() {
    char input;
    int i;

    playerx = 2, playery = 2;
    fputs("\033c", stdout);
    fruit();
    draw();
    sleep(1);

    /* Main Gameplay Loop*/
    do {
        input = getchar();

        if (input == 119 || input == 107) {
            playery--;
        } else if (input == 97
                || input == 104) {
            playerx--;
        } else if (input == 114
                || input == 106) {
            playery++;
        } else if (input == 115
                || input == 108) {
            playerx++;
        } else if (input == 113) {
            break;
        }

        /* wrap detection */
        if (playery >= height-1) {
            playery = 1;
        } else if (playery == 0) {
            playery = height-2;
        } else if (playerx >= width-1) {
            playerx = 1;
        } else if (playerx ==0 ) {
            playerx = width-2;
        }

        if (playery == fruity
                && playerx == fruitx) {
            fruit();
            score++;
        }

        fputs("\033c", stdout); /* Clear Screen */
        draw();

        for (i=1; i<10; i++) {
            tailx[i] = tailx[i-1];
            taily[i] = taily[i-1];
        }

        tailx[2] = tailx[1];
        taily[2] = taily[1];
        tailx[1] = playerx;
        taily[1] = playery;

        sleep(0.25);

        printf("%d\n%d\n%d\n%d", tailx[2], taily[2], tailx[1], taily[1]);
    } while (1);
    gameover();
}
void menu() {
    int i,e;
    int select=1;

    void print() {
        fputs("\033c", stdout); /* Clear Screen */
        printf("\n\n");
        for (e=1; e<=4; e++) {
        /* https://www.theurbanpenguin.com/4184-2/
         * reset color */
            printf("\033[0;0m");
            for (i=0; i<width/4; i++) {
                printf("    ");
            }
            if (select == e) {
                printf("\033[1;37m>");
            }
            if (e == 1) {
                printf("START\033[0;0m\n");
            } else if (e == 2) {
                printf("SAVE\033[0;0m\n");
            } else if (e == 3) {
                printf("SETTINGS\033[0;0m\n");
            } else if (e == 4) {
                printf("QUIT\033[0;0m\n");
            } else {}
        }
    }
    do {
        print();
        char input = getchar();
        if (input == 27) {
            if (getchar() == 91) {
                switch(getchar()) {
                    case 65:
                        if (select <= 1) {
                            break;
                        } else {
                            select--;
                        }
                        break;
                    case 66:
                        if (select >= 4) {
                            break;
                        } else {
                            select++;
                            break;
                        }
                }
            }
        } else if (input == 113) {
            break;
        } else {
            if (select == 1) {
                gameplay();
            } else if (select == 4) {
                animate("SEE YA...", 9);
                break;
            }
        }
    fputs("\033c", stdout); /* Clear Screen */

    } while (select != 0);
}

int main() {
    struct termios old_tio, new_tio;
    unsigned char c;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    menu();
    //menu();

    /* exit */

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio); /* restore former settings */

    printf("\n%d\n%d\n", fruitx, fruity);
    return 0;
}


/* TODO:
 *
 * MAKE IT ACTUALLY WORK
 *
 * ADD PROPER EXIT
 * ADD BOMBS
 * ADD SCORE BOARD
 *  `WRITE TO /TMP
 * ADD SAVE OPTION
 * ADD DEV TOOLS
 *  `frequency of updates
 *  `frames since start of game
 * ADD SETTINGS
 *  `board size
 *  |`apply the size to
 *  | `score board storing
 *  `add save location
 *
 * ADD WINDOWS SUPPORT
 * PUT IT UP ON GITHUB
 * PRITTIFY IT
 *
 * */
