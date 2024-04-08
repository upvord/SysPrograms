#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
  int i = 0;
  char *shared_memory;
  char data = '0'; // Pointer to int to write numeric data
  int shmid;

  shmid = shmget((key_t)2222, sizeof(int), 0666 | IPC_CREAT);
  if (shmid == -1) {
    perror("shmget");
    return -1;
  }

  printf("Key of shared memory is %d\n", shmid);

  shared_memory = shmat(shmid, NULL, 0);
  if (shared_memory == NULL) {
    perror("shmat");
    return -1;
  }

  printf("Process attached at %p\n", shared_memory);

  while (1) {
    fflush(stdout);
    printf("%c ", data);
    *shared_memory = data;
    data++;
    if (data > '9')
      data = '0';
    // sleep(1);
  }

  return 0;
}
