#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>

sem_t *s;

int main() {
  // Open the semaphore created by Process 1
  s = sem_open("/my_semaphore", 0); // Assuming the semaphore is already created
  if (s == SEM_FAILED) {
    perror("sem_open");
    return -1;
  }

  int shmid;
  char *shared_memory;

  // Access the shared memory segment created by Process 1
  shmid = shmget((key_t)2222, 1024, 0666);
  if (shmid == -1) {
    perror("shmget");
    exit(EXIT_FAILURE);
  }

  // Attach to the shared memory segment
  shared_memory = shmat(shmid, NULL, 0);
  if (shared_memory == (char *)-1) {
    perror("shmat");
    exit(EXIT_FAILURE);
  }

  printf("Process attached at %p\n", shared_memory);

  // Ensure this process runs after Processes 1 and 2 have completed their
  // writes
  while (1) {
    sem_wait(s); // Wait for the semaphore to ensure exclusive access

    // Read and print the shared memory contents
    printf("--- Shared Memory Contents ---\n");
    printf("%s\n", shared_memory);
    printf("--- End of Shared Memory Contents ---\n");

    sem_post(s); // Release the semaphore
    sleep(1);    // Sleep for a bit to allow other processes to operate
  }

  // Cleanup
  sem_close(s);
  // Do not unlink the semaphore here, as it's shared across processes

  return 0;
}
