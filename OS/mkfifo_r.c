#include "stdio.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char msg[100];

  int fd;

  fd = open("mk_fifo", O_RDONLY);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  while (1) {
    read(fd, msg, 100);

    printf("FIFO > %s\n", msg);
  }
}
