#include <stdio.h>
#include <unistd.h>

int main() {
  int pid;

  pid = fork();
  if (pid < 0) {
    printf("Process creation failed\n");
    return -1;
    // Failure
  }

  // Success
  if (pid == 0) {
    printf("Child Process return value:%d\n", pid);
  } else {
    printf("Parent Process return value:%d\n", pid);
  }

  printf("Current process pid:%d\n", pid);

  while (1)
    ;

  return 0;
}
