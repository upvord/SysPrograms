#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Executing using execl..\n");

  // execl("/bin/ls", "ls", "-l", "-t", "-r", NULL);
  execl("/Users/upvord/batch2/Sys/OS/a.out", "a.out", NULL);

  perror("execl");

  while (1) {
    printf("Is this printf getting executed or not\n");
    sleep(1);
  }
  return 1;
}
