#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

sem_t *s;

int main() {

  s = sem_open("/my_semaphore", 0);
  char *shared_memory;
  char alphabet = 'a';
  int shmid;

  shmid = shmget((key_t)2222, sizeof(char), 0666);
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
    sem_wait(s); // lock the resource of use the resource (busy)
    while (alphabet <= 'z') {
      fflush(stdout);
      printf("%c ", alphabet);
      *shared_memory = alphabet;
      alphabet++;
    }
    // sleep(1); // Sleep for 1 second between each write
    alphabet = 'a';
    sem_post(s); // free the resource or unlock the resource
  }

  return 0;
}
