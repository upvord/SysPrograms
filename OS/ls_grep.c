#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd[2];
  int pid;

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
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execlp("ls", "ls", NULL);
    perror("execlp");

  } else {
    int status;
    printf("Parent process reading from the pipe\n");
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    wait(&status);
    execlp("grep", "grep", argv[1], NULL);
    perror("execlp");
  }

  return 0;
}
