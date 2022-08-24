#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
//#include <time.h>
#include <termios.h>
#include <signal.h>

struct termios old_tio, new_tio;
unsigned int height=7;
unsigned int width=15;

unsigned int playerx= 8;
unsigned int playery= 8;

/**/
unsigned int blocky=0;
unsigned int block=0;
/**/

int sig_caught=0;
void signal_handler(int sig) {
  if (sig == SIGINT) {
    sig_caught=1;
  }
}

int getinput() {
    int value;
    char input = getchar();
    if (input == 27) {
        if (getchar() == 91) {
            switch(getchar()) {
                case 65: /* up */
                    value = 1;
                    break;
                case 66: /* down */
                    value = 2;
                    break;
                case 67: /* right */
                    value = 3;
                    break;
                case 68: /* left */
                    value = 4;
                    break;
            }
        } else {
            value = 6; /* esc */
        }
    } else if (input == 119 || input == 107) {
        value = 1;
    } else if (input == 114 || input == 106) {
        value = 2;
    } else if (input == 115 || input == 108 ) {
        value = 3;
    } else if (input == 97 || input == 104 ) {
        value = 4;
    }
    else if (input == 113) {
        value = 0;
    } else {
        value = 5;
    }
    return value;
}

void render() {
    register unsigned int x,y;
    unsigned int ax = width*4;
    unsigned int ay = height*4;

    unsigned int map[19][19]={
        {1,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
        {1,1,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2},
        {2,1,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2},
        {2,0,0,0,0,0,0,0,1,0,0,0,1,0,2,2,2,2,2},
        {2,2,0,0,1,1,0,0,0,0,0,0,1,2,2,2,2,2,2},
        {2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2},
        {2,1,1,1,1,0,0,0,0,0,0,1,1,2,2,2,2,2,2}
    };
    unsigned int dirt[4][4]={
        {1,0,1,1},
        {0,1,0,1},
        {1,0,0,1},
        {0,1,1,1}
    };
    unsigned int player[4][4]={
        {1,1,1,1},
        {0,1,1,0},
        {2,1,1,2},
        {1,0,0,1}
    };

    for (y=0; y<4*height; y++) {
        for (x=0; x<4*width; x++) {
            if (y == 0 || y == 4*height-1 ) { /* render the boarder first */
                printf("\e[1;47m        \e[0;37m");
                x = x + 3;
            } else if (x == 0 || x == 4*width-1) { /* rendering first means on top */
                printf("\e[1;47m  \e[0;0m");
            }
            else if ( x/4 == 7 && y/4 == 3) { /* render player */
                int sx = x-((x/4)*4);
                int sy = y-((y/4)*4);
                int sprite = player[sy][sx];
                if (sprite == 0) {
                    printf("\e[40m  \e[0m");
                } else if (sprite == 1) {
                    printf("\e[43m  \e[0m");
                } else {
                    printf("\e[1;41m  \e[0m");
                }

            }
            else {
                int sx = x-((x/4)*4);
                int sy = y-((y/4)*4);
                int sprite = dirt[sy][sx];
                if ((x/4)+(playerx-7) > 18 || (y/4)+(playery-4) > 18) { /* rendrers out mountians  */
                    printf("\e[0m^^");
                } else if (map[(y/4)+(playery-4)][(x/4)+(playerx-7)] == 1) { /* renders green */
                    printf("\e[43m%d%d", dirt[sy][sx], dirt[sy][sx]);
                } else if (map[(y/4)+(playery-4)][(x/4)+(playerx-7)] == 0) { /* renders yellow */
                    printf("\e[42m%d%d", dirt[sy][sx], dirt[sy][sx]);
                } else if (map[(y/4)+(playery-4)][(x/4)+(playerx-7)] == 2) { /* renders blue*/
                    printf("\e[44m~~");
                } else if (map[(y/4)+(playery-4)][(x/4)+(playerx-7)] == 3) { /* renders pure blue*/
                    printf("\e[44m\\\\");
                } else {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
}

void gameplay() {
    fputs("\033c", stdout);
    render();

    do {
        int input = getinput();
        printf("%d", input);
        if (input == 1) {
            if (playery <= 1) {
            } else {
                playery--;
            }
        } else if (input == 2) {
            if (playery >= 19) {
            } else {
                playery++;
            }
        } else if (input == 3) {
            if (playerx >= 18) {
            } else {
                playerx++;
            }
        } else if (input == 4) {
            if (playerx <= 0) {
            } else {
                playerx--;
            }
        }
        fputs("\033c", stdout);
        render();
        sleep(0.2); /* above this will produce screen taring */
    } while (1);
}

void menu() {
    register unsigned int i,e;
    int select=1;

    void printmenu() {
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
        printmenu();
        int input = getinput();
        if (input == 1) {
            if (select <= 1) {
            } else {
                select--;
            }
        } else if (input == 2) {
            if (select >= 4) {
            } else {
                select++;
            }
        } else if (input == 0) {
            break;
        } else if (input == 5) {
            if (select == 1) {
                gameplay();
                break;
            } else if (select == 4) {
                break;
            }
        } else { }
    fputs("\033c", stdout); /* Clear Screen */
    sleep(0.25);

    } while (select != 0);
}



int main() {

    unsigned char c;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    menu();

    /* EXIT */
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio); /* restore former settings */
    return 0;
}
