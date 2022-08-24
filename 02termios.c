#include <stdio.h>
#include <termios.h>
#include <unistd.h>

char c, c1, c2;

int main() {
  struct termios old_tio, new_tio;
  unsigned char c;

  /* get the terminal settings for stdin */
  tcgetattr(STDIN_FILENO, &old_tio);

  /* we want to keep the old setting to restore them a the end */
  new_tio = old_tio;

  /* disable canonical mode (buffered i/o) and local echo */
  new_tio.c_lflag &= (~ICANON & ~ECHO);

  /* set the new settings immediately */
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

  do {
    //sleep(1);
    c2 = c1;
    c1 = c;
    c = getchar();

    if (c == 27) {
      printf("o27o");
    } else {
        printf("%d ", c);
    }
  } while (c != 'q');

  printf("\n %d %d %d \n", c, c1, c2);

  /* restore the former settings */
  tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

  return 0;
}
