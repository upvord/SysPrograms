#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void catch_int(int sig_num) {
  printf("Caught the SIGNINT i.e. Ctrl + C\n");

  fflush(stdout);

  return;
}

int main() {
  signal(2, catch_int);

  printf("Have a Great day\n");

  pause();

  printf("Yeah Thank you\n");

  return 0;
}
