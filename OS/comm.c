#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

  int pid;
  char buf[100];

  pid = fork();

  if (pid < 0) {
    perror("fork");
    return -1;
  }

  if (pid == 0) {
    printf("child reading from the std_in\n");
    read(0, buf, 100);
  } else {
    int status;
    printf("parent writing to the std_out\n");
    write(1, buf, 100);
    wait(&status);
    write(1, buf, 100);
  }
}
