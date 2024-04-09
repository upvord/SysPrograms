#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

sem_t *s;

int main() {
  // Open the semaphore created by Process 1
  s = sem_open("/my_semaphore",
               0); // Open existing semaphore, no need for O_CREAT
  if (s == SEM_FAILED) {
    perror("sem_open");
    return -1;
  }

  int shmid;
  char *shared_memory;

  // Define a buffer of size 26 for the lowercase letters
  char buffer[27]; // 26 letters + 1 for the null terminator
  for (char letter = 'a'; letter <= 'z'; letter++) {
    buffer[letter - 'a'] = letter;
  }
  buffer[26] = '\0'; // Null-terminate the string

  // Access the shared memory segment created by Process 1
  shmid = shmget((key_t)2222, 1024, 0666); // No IPC_CREAT flag needed here
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
    sem_wait(s); // Wait for the semaphore to be available

    // Find the end of the existing string in shared memory to append lowercase
    // letters
    char *end_of_shared_memory = shared_memory;
    while (*end_of_shared_memory != '\0')
      end_of_shared_memory++;

    // Copy buffer to shared memory right after the existing content
    strncpy(end_of_shared_memory, buffer,
            27); // Use 27 to include the null terminator

    printf("Lowercase letters a-z written to shared memory.\n");

    sem_post(s); // Release the semaphore
  }

  // Cleanup (No need to unlink the semaphore as it will be used/shared with
  // other processes)
  sem_close(s);

  return 0;
}
