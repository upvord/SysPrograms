#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define PERMS 0644
struct my_msgbuf {
  long mtype;
  char mtext[200];
};

int main(void) {
  struct my_msgbuf buf;
  int msqid;
  int len;
  key_t key = 1000;

  if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
    perror("msgget");
    exit(1);
  }

  // 1 msg hello
  printf("Enter msg type:");
  scanf("%lu", &buf.mtype);

  printf("Enter lines of text:");
  scanf("%s", buf.mtext);

  if (msgsnd(msqid, &buf, strlen(buf.mtext), 0) == -1) {
    perror("msgsnd");
    exit(1);
  }
  // 20 123456
  printf("Enter msg type:");
  scanf("%lu", &buf.mtype);

  printf("Enter lines of text:");
  scanf("%s", buf.mtext);

  if (msgsnd(msqid, &buf, strlen(buf.mtext), 0) == -1) {
    perror("msgsnd");
    exit(1);
  }

  // 100 3.14444444
  printf("Enter msg type:");
  scanf("%lu", &buf.mtype);

  printf("Enter lines of text:");
  scanf("%s", buf.mtext);

  if (msgsnd(msqid, &buf, strlen(buf.mtext), 0) == -1) {
    perror("msgsnd");
    exit(1);
  }

  /*
  if (msgctl(msqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(1);
  }
  */
  printf("message queue: done sending messages.\n");
  return 0;
}
