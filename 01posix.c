#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int sig_caught=0;
sig_caught = (int)malloc(1 * sizeof(int)); /*using malloc to allocate*/

void signal_handler(int sig) {
  if (sig == SIGINT) {
    sig_caught=1;
  }
}

int main(void) {
  if (signal(SIGINT, signal_handler) == SIG_ERR) {
    fprintf(stderr, "signal func registration failed\n");
    return 1;
  }

  while(1) {
    if (sig_caught) {

      printf("\ncaught signal - exiting \n");
      return 0;
    }
  }

  /* NOTREACHED */

  return 0;
}
