#include "stdio.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  if (mkfifo("mk_fifo", 0666) == -1) {
    perror("mkfifo");
    return -1;
  }

  printf("Successfully created the FIFO\n");

  int fd;

  fd = open("mk_fifo", O_WRONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  char msg[100];
  while (1) {
    printf("Enter msg:");
    scanf("%s", msg);

    write(fd, msg, (size_t)(strlen(msg)) + 1);
  }
}
