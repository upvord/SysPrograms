#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

sem_t *s;

int main() {
  s = sem_open("/my_semaphore", 0);
  int i;
  void *shared_memory;
  char buff[100];
  int shmid;
  shmid = shmget((key_t)2222, sizeof(int), 0666);
  if (shmid == -1) {
    perror("shmget");
    return -1;
  }
  // creates shared memory segment with key 2345, having size 1024 bytes.
  // IPC_CREAT is used to create the shared segment if it does not exist. 0666
  // are the permissions on the shared segment
  printf("Key of shared memory is %d\n", shmid);
  shared_memory = shmat(shmid, NULL, 0);
  if (shared_memory == NULL) {
    perror("shmat");
    return -1;
  }
  // process attached to shared memory segment
  printf("Process attached at %p\n", shared_memory);
  // this prints the address where the segment is attached with this process
  strcpy(buff, shared_memory); // data written to shared memoryo
  int *data = NULL;
  while (1) {
    data = (int *)shared_memory;
    printf("%c ", *data);
    fflush(stdout);
    // usleep(500000);
  }
}
