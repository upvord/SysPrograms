#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  int pid;

  char buff[100] = "Hey guys dont get sleep";
  char another_buff[100];

  if (pipe(fd) == -1) {
    perror("pipe");
    return -1;
  }

  if ((pid = fork()) < 0) {
    perror("fork");
    return -1;
  }

  if (pid == 0) {
    printf("Child process writing to the pipe...\n");
    write(fd[1], buff, 100);
    close(fd[0]);

  } else {
    int status;
    printf("Parent process reading from the pipe\n");
    read(fd[0], another_buff, 100);
    close(fd[1]);
    printf("After reading from pipe [%s]\n", another_buff);
    wait(&status);
  }

  return 0;
}
