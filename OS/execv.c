#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Executing using execv..\n");

  // execl("/bin/ls", "ls", "-l", "-t", "-r", NULL);
  char *p[] = {"ls", "-l", "-t", "-r", NULL}; // ls -ltrh
  execv("/bin/ls", p);

  // execl("/Users/upvord/batch2/Sys/OS/a.out", "a.out", NULL);

  perror("execv");

  while (1) {
    printf("Is this printf getting executed or not\n");
    sleep(1);
  }
  return 1;
}
