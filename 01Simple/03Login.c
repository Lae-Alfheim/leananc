// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
#ifdef _WIN32
#include <conio.h>
#define clear() system(cls)
#else
#include <stdio.h>
#define clear() printf("\e[1;1H\e[2J")
#endif

#include <stdlib.h> // for system
#include <unistd.h> // used for sleep



void convertToUppercase(char *givenStr)
{
    int i;
    for (i = 0; givenStr[i] != '\0'; i++)
    {
        if (givenStr[i] >= 'a' && givenStr[i] <= 'z')
        {
            givenStr[i] = givenStr[i] - 32;
        }
    }
}

void start(void) { /* print the start */

    /* w e l c o m e   t o   t h e   h i v e */
    int i = 0;
    for (i <= 0; i < 38; i = i + 1) {
        printf("\n");
        printf("%*.*s", i, i, "w e l c o m e   t o   t h e   h i v e");
        usleep(20000);
        system("clear");
    }

    /* end */
    printf("\n");

}

void input(int p, char *text, char *past) { /* general animate */

    system("clear");
    printf("%s", past);

    int l = 0;
    while (l != p) {
        printf("%*.*s", l, l, text);
        printf("\n");
        usleep(40000);
        system("clear");
        printf("%s", past);
        l++;
    }

    //system("clear");
    //sleep(1);
    //printf("\n%s", past);
}


int main(void) {

    clear();
    printf("\033[1;1H");
    sleep(1);

    /* starting message */
    start();

    char* overflow;
    overflow = (char *)malloc(128 * sizeof(char)); /*using malloc to allocate*/

    /* login */
    int logint = 7;
    char *logins = "Login: ";
    char *loginpt = "w e l c o m e   t o   t h e   h i v e\n";
    input(logint, logins, loginpt);

    fflush(stdin); /* delete all previous input*/
    char* login;
    login = (char *)malloc(16 * sizeof(char)); /*using malloc to allocate*/
    printf("Login: ");
    scanf("%15s", login );
    fgets(overflow, 128, stdin);
    //https://stackoverflow.com/questions/28017232/scanf-text-overflow-in-c

    /* password */
    int passwdt = 10;
    char *passwds = "Password: ";
    char *passwdpt = "w e l c o m e   t o   t h e   h i v e\nLogin: ******** \n";
    input(passwdt, passwds, passwdpt);

    fflush(stdin);
    char* passwd;
    passwd = (char *)malloc(64 * sizeof(char)); /*using malloc to allocate*/
    printf("Password: ");
    scanf("%63s", passwd );


    /* debug */
    if (login == "debug") {
        printf("\n\nWARNING!!debug enabled!!\n%s\n%s", login, passwd);
    }

    /* end of login process */
    printf(login);
    clear();
    usleep(40000);
    printf("w e l c o m e   t o   t h e   h i v e\nLogin: ********\nPassword: ********");
    convertToUppercase(login);
    printf("\n\n\tW E L C O M E   B A C K   %s   T O   T H E   H I V E\n", login);
    usleep(0000);

    /* end */
    free(login);
    free(passwd);
    printf("\n");
    return 0;

}
