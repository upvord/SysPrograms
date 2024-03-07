#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void usr_handler(int sig_num) {
  printf("SIGHANDLER: Parent ID:%d received the SIGUSER1:%d\n", getpid(),
         sig_num);

  return;
}

int main() {

  int pid;

  pid = fork();

  if (pid < 0) {
    printf("Fork failed\n");
  } else if (pid > 0) {
    // Parent
    int status;
    printf("Parent process:%d\n", getpid());
    signal(SIGUSR1, usr_handler);

    pause();
    printf("Parent: Waiting for the chile to complete...\n");

    wait(&status);
  } else {
    // Child
    printf("Child process:%d\n", getpid());
    kill(getppid(), SIGUSR1);

    sleep(5);
    printf("Just woke up sorry for late joining\n");
  }

  return 0;
}
