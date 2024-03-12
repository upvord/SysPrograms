#include <stdio.h>
#include <unistd.h>

int main() {
  char buf[100] = "";

  if (read(0, buf, 100) < 0) {
    perror("read");
    return -1;
  }

  if (write(1, buf, sizeof(buf)) < 0) {
    perror("write");
    return -1;
  }

  return 0;
}
