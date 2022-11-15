#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#define RESET       0
#define BRIGHT      1

#define BLACK       0
#define RED	        1
#define GREEN       2
#define YELLOW      3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define	WHITE       7
#define DONT_CARE   8
#define HELP        9

void textcolor(int,int,int);
int input_colour(char *);
int identify_digit(char);
void fix_digit(char, int, int);
int block_position(int );
void print_digit(int (*array)[6], int, int);
void print_colon(int, int);
int sig_caught=0; /* to chech posix signals */
void signal_handler(int sig) {  /* handels the signal for proper exit */
    if (sig == SIGINT) {        /* https://www.quora.com/How-do-I-create-continuous-looping-in-C-until-a-user-stops-it?share=1 */
        sig_caught=1;   /* https://man7.org/linux/man-pages/man2/signal.2.html */
    }
}

void help() {
    printf("\nAnalog :: Digital Analog Clock 0.6\nJhon Ana Doe (a) <a@a.com>\nThis is a simple Analog clock written in C\nUSAGE:\n    a.out [COLORS]\n\nCOLORS:\n    BLACK\n    RED\n    GREEN\n    YELLOW\n    BLUE\n    MAGENTA\n    CYAN\n    WHITE\n    HELP\n\n");
}


int main(int argc, char **argv) {
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "signal function registration failed\n\e[?25h");
        return 1;
    }


    int position;
    int i;
    int colour_1;

    if( argc==1 ) {
        /* defines default color: cyan */
        fprintf(stderr,"Please Specify A Color\n");
        help();
        return 0;
    } else if( argc != 1 && argc <= 3 ) {
        char *colour=(argv[1]);
        colour_1 = input_colour(colour);    /* required colour */
        if ( colour_1 == 8 ) {
            help();
            colour_1 = 6;
            return 0;
        } else if (colour_1==100) { /* if not color then quit */
            printf("You have input an invalid color\n\e[?25h");
            return 0;
        }
    } else { /* else to many arguments so show cursor and quit */
        printf("Too many arguments\n\e[?25h");
        return 0;
    }


    printf("\033[?25l");	// Hiding the cursor
    printf("\033[2J");		// Clear console

    while ( argc != 3 && argc == 2) { /* main loop */

        if (sig_caught) {
            printf("\ncaught signal - exiting \n\e[?25h"); /* exit when ^C is pressed
                with giving the cursor back */
            return 0;
        }

        char time_value[20];
        char date[20];
        time_t current_time; /* time_t is a data type used too store system time calues */
        current_time = time(NULL); /* time elapsed in seconds since Epoch */

        struct tm* brokentime = localtime(&current_time); /* converts to broken down time */

        strftime(time_value, 20, "%X", brokentime); /* current time*/
        strftime(date, 20, "%Y-%m-%d", brokentime); /* date */


        /* print out clock */
        for(position=0; position<2; position++) { /* printing out the fist two digits */
            fix_digit(time_value[position], position, colour_1);
        }

        print_colon(15, colour_1); /* print colon */

        for(position=3; position<5; position++)	// Print the second two digits
            fix_digit(time_value[position],position,colour_1);

        print_colon(34,colour_1);

        for(position=6; position<8; position++)		// Print the last two digits
            fix_digit(time_value[position],position,colour_1);


        printf("\033[8;23H");
        textcolor(BRIGHT, colour_1, DONT_CARE);

        for (i=0; i < 12; i++) { /* printf out date */
            printf("%c", date[i]);
        }

        putchar('\n');
        textcolor(RESET, WHITE, BLACK);
        sleep(1);
    }

    if (argc == 3) {
        /* this is to decide if it is a correct input digits,
                            and to formate it correctly for the next step*/
        /* TODO: make a specification for seconds, minuets, hours, days, to count down*/
    }
    while ( argc == 3 ) {
        if (sig_caught) {
            printf("\ncaught signal - exiting \n\e[?25h"); /* exit when ^C is pressed
                with giving the cursor back */
            return 0;
        }

        char *time_value = "6942042";

        fix_digit(time_value[1], 1, 2);
        fix_digit(time_value[2], 2, 2);
        fix_digit(time_value[3], 3, 2);
        fix_digit(time_value[4], 4, 2);


        printf("\n%s", time_value);
        putchar('\n');
        textcolor(RESET, WHITE, BLACK);
        //sleep(1);
        break;
    }

    printf("\e[?25h"); /* return the cursor */
    return 0;
}


void textcolor(int attr, int fg, int bg) {
    char command[13];
    printf("\033[0m");

    if (attr == BRIGHT) {
        if (fg == DONT_CARE) {
            printf("\033[%dm", bg +40);
        } else {
            printf("\033[%dm", fg +30);
        }
    }

    /*
     * Command is the control command to the terminal
         * textcolor(BRIGHT, BLACK, WHITE) will have characters printed in black in white background
         */
    //sprintf(command, "%c[%d;%dm", 0x1B, fg + 30, bg + 40);
    //sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
    //printf("%s", command);
}

int input_colour(char *input) { /* indentifying the input color */
    char *colours[]= {"black","red","green","yellow","blue","magenta","cyan","white","help"};
    int count;
    int array_size = sizeof(colours)/sizeof(colours[0]);

    for(count=0; count<array_size; count++) {
        if(strcmp(input, colours[count])==0) {
            return count;
        }
    }
    return 100;
}

int identify_digit(char input) { /* identifying the input digit */
    char digits[]= {'0','1','2','3','4','5','6','7','8','9'};
    int count;
    int array_size = sizeof(digits)/sizeof(digits[0]);

    for(count=0; count<array_size; count++) {
        if(input==digits[count]) {
            return count;
        }
    }
    return count;
}

void fix_digit(char input,int position,int colour) { /* defining an array for each digit */
    int digit_array[5][6];
    int digit=identify_digit(input);

    if(digit==0) {
        int digit_array[5][6]= {			// 0
            {1,1,1,1,1,1},
            {1,1,0,0,1,1},
            {1,1,0,0,1,1},
            {1,1,0,0,1,1},
            {1,1,1,1,1,1}
        };
    }

    else if(digit==1) {
        int digit_array[5][6]= {			// 1
            {0,0,0,0,1,1},
            {0,0,0,0,1,1},
            {0,0,0,0,1,1},
            {0,0,0,0,1,1},
            {0,0,0,0,1,1}
        };
    }

    else if(digit==2) {
        int digit_array[5][6]= {			// 2
            {1,1,1,1,1,1},
            {0,0,0,0,1,1},
            {1,1,1,1,1,1},
            {1,1,0,0,0,0},
            {1,1,1,1,1,1}
        };
    }

    else if(digit==3) {
        int digit_array[5][6]= {			// 3
            {1,1,1,1,1,1},
            {0,0,0,0,1,1},
            {1,1,1,1,1,1},
            {0,0,0,0,1,1},
            {1,1,1,1,1,1}
        };
    }

    else if(digit==4) {
        int digit_array[5][6]= {			// 4
            {1,1,0,0,1,1},
            {1,1,0,0,1,1},
            {1,1,1,1,1,1},
            {0,0,0,0,1,1},
            {0,0,0,0,1,1}
        };
    }

    else if(digit==5) {
        int digit_array[5][6]= {			// 5
            {1,1,1,1,1,1},
            {1,1,0,0,0,0},
            {1,1,1,1,1,1},
            {0,0,0,0,1,1},
            {1,1,1,1,1,1}
        };
    }

    else if(digit==6) {
        int digit_array[5][6]= {			// 6
            {1,1,1,1,1,1},
            {1,1,0,0,0,0},
            {1,1,1,1,1,1},
            {1,1,0,0,1,1},
            {1,1,1,1,1,1}
        };
    }

    else if(digit==7) {
        int digit_array[5][6]= {			// 7
            {1,1,1,1,1,1},
            {0,0,0,0,1,1},
            {0,0,0,0,1,1},
            {0,0,0,0,1,1},
            {0,0,0,0,1,1}
        };
    }

    else if(digit==8) {
        int digit_array[5][6]= {			// 8
            {1,1,1,1,1,1},
            {1,1,0,0,1,1},
            {1,1,1,1,1,1},
            {1,1,0,0,1,1},
            {1,1,1,1,1,1}
        };
    }

    else if(digit==9) {
        int digit_array[5][6]= {			// 9
            {1,1,1,1,1,1},
            {1,1,0,0,1,1},
            {1,1,1,1,1,1},
            {0,0,0,0,1,1},
            {1,1,1,1,1,1}
        };
    }

    print_digit(digit_array,position,colour);
}

void print_digit(int (*array)[6],int position, int colour) {

    int row_index, column_index;

    for(row_index=0; row_index < 5; row_index++) {
        for(column_index=0; column_index < 6; column_index++) {
            printf("\033[%d;%dH", row_index + 2, column_index + block_position(position));
            int value = array[row_index][column_index];
            if(value==0) {
                textcolor(RESET, WHITE, BLACK);
                printf(" ");
            } else if(value==1) {
                textcolor(BRIGHT, DONT_CARE, colour);
                printf(" ");
            }
        }
        textcolor(RESET, WHITE, BLACK);
    }
}

int block_position(int digit_position) {

    int spacing;

    if (digit_position==0 ) {
        spacing=2;
    } else if ( digit_position==1 ) {
        spacing=9;
    } else if ( digit_position==3 ) {
        spacing=21;
    } else if ( digit_position==4 ) {
        spacing=28;
    } else if ( digit_position==6 ) {
        spacing=40;
    } else if ( digit_position==7 ) {
        spacing=47;
    }

    return spacing;
}

// Printing the colon
void print_colon(int position, int colour) {

    int row_index,column_index;

    int array[5][6]= {  /* defining an array for a colon */
        {0,0,0,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,0,0,0}
    };

    for(row_index=0; row_index<=5; row_index++) {		// Printing the colon
        for(column_index=0; column_index<=6; column_index++) {
            printf("\033[%d;%dH",row_index+2,column_index+position);
            if(array[row_index][column_index]==0) {
                textcolor(RESET, WHITE, BLACK);
                printf(" ");
            }
            else if(array[row_index][column_index]==1) {
                textcolor(BRIGHT, DONT_CARE, colour);
                printf(" ");
            }

        }
        textcolor(RESET, WHITE, BLACK);
        putchar('\n');
    }
}


//ANSI codes
// 0      clear
// 1      bold
// 4      underline
// 5      blink
//
// 30-37  fg color
// 40-47  bg color
//
// 1K     clear line (to beginning of line)
// 2K     clear line (entire line)
// 2J     clear screen
// 0;0H   move cursor to 0;0
//
// 1A     move up 1 line
//
// Colors
//
// 0      black
// 1      red
// 2      green
// 3      yellow
// 4      blue
// 5      magenta
// 6      cyan
// 7      white
//
// Bash utilities
//
// hide_cursor() { printf "\e[?25l"; }
// show_cursor() { printf "\e[?25h"; }
//
//
// Analog :: Digital Analog Clock 0.4\nJhon Ana Doe (a) <a@a.com>\nThis is a simple Analog clock written in C\n// USAGE:\n    a.out [COLORS]\n// COLORS:\n    BLACK\n    RED\n    GREEN\n    YELLOW\n    BLUE\n    MAGENTA\n    CYAN\n    WHITE\n    DONT_CARE\n    HELP\n
//
// Analog :: Digital Analog Clock 0.4\nJhon Ana Doe (a) <a@a.com>
// This is a simple Analog clock written in C
//
// USAGE:
//     a.out [COLORS]
//
// COLORS:
//     BLACK
//     RED
//     GREEN
//     YELLOW
//     BLUE
//     MAGENTA
//     CYAN
//     WHITE
//     HELP
