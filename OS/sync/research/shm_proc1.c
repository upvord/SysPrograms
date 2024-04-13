#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

sem_t *s;

int main() {
  // Open or create a semaphore with initial value 1
  s = sem_open("/my_semaphore", O_CREAT, 0666, 1);
  int shmid;
  char *shared_memory;

  // Define a buffer of size 26 for the capital letters
  char buffer[27]; // 26 letters + 1 for the null terminator
  for (char letter = 'A'; letter <= 'Z'; letter++) {
    buffer[letter - 'A'] = letter;
  }
  buffer[26] = '\0'; // Null-terminate the string

  // Create shared memory segment with key 2222
  shmid = shmget((key_t)2222, 1024,
                 0666 | IPC_CREAT); // Ensure size is enough for your needs
  if (shmid == -1) {
    perror("shmget");
    return -1;
  }

  printf("Key of shared memory is %d\n", shmid);

  // Attach to the shared memory segment
  shared_memory = shmat(shmid, NULL, 0);
  if (shared_memory == (char *)-1) {
    perror("shmat");
    return -1;
  }

  printf("Process attached at %p\n", shared_memory);

  // Copy the buffer to shared memory
  while (1) {
    sem_wait(s); // Lock the semaphore before accessing shared memory

    // Copy buffer to shared memory
    strncpy(shared_memory, buffer, 27); // Use 27 to include the null terminator

    printf("Capital letters A-Z written to shared memory.\n");

    sem_post(s); // Unlock the semaphore
  }

  // Cleanup
  sem_close(s);
  sem_unlink("/my_semaphore");

  return 0;
}
