#include <stdio.h>
#include <unistd.h>

int main() {

  fork();
  fork();
  fork();
  printf("Current process pid:%d\n", getpid());

  return 0;
}
