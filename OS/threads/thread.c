#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *printEvenNumbers(void *threadId);

void *printOddNumbers(void *threadId) {
  printf("Thread created ID:%ld\n", (threadId));
  for (int i = 0; i < 50; i++) {
    if (i % 2 != 0) {
      printf("%d\n", i);
      sleep(1);
    }
  }
  pthread_exit(NULL);
}
void *printEvenNumbers(void *threadId) {
  printf("Thread created ID:%ld\n", (threadId));
  for (int i = 0; i < 50; i++) {
    if (i % 2 == 0) {
      printf("%d\n", i);
      sleep(1);
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  pthread_t tid;
  int ret_1, ret_2;

  ret_1 = pthread_create(&tid, NULL, printEvenNumbers, 0);
  if (ret_1) {
    printf("Error: pthread_create creation failed\n");
    return -1;
  }

  ret_2 = pthread_create(&tid, NULL, printOddNumbers, 0);
  if (ret_2) {
    printf("Error: pthread_create creation failed\n");
    return -1;
  }

  pthread_join(tid, NULL);

  return 0;
}
