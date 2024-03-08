#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void catch_int(int sig_num) {
  printf("Caught the SIGNINT i.e. Ctrl + C\n");

  fflush(stdout);

  return;
}

int main() {
  // signal(2, catch_int);
  signal(9, SIG_IGN);

  printf("Have a Great day\n");

  while (1) {
    printf("Happy Maha Shivratri\n");
    sleep(1);
  }

  pause();

  printf("Yeahyy Thank you\n");

  return 0;
}
