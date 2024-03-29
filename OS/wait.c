#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

// Definitions of functions
int sum(int a, int b) { return a + b; }

int multiply(int a, int b) { return a * b; }

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
    int a, b;
    printf("Child Enter a: b:");
    scanf("%d %d", &a, &b);
    int res = sum(a, b);
    printf("Child --> Sum:%d\n", res);

  } else {
    printf("Parent Process return value:%d\n", pid);
    int a, b;
    printf("Parent: Enter a: b:");
    scanf("%d %d", &a, &b);
    int res = multiply(a, b);
    printf("Parent --> Multiply:%d\n", res);
    int st;
    wait(&st);
  }

  return 0;
}
