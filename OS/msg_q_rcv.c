#include <stdio.h>
#include <stdlib.h>
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

  if ((msqid = msgget(key, PERMS)) == -1) {
    perror("msgget");
    exit(1);
  }

  printf("Enter the message type:");
  scanf("%lu", &buf.mtype);

  if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
    perror("msgrcv");
    exit(1);
  }

  printf("Message queue: Received the data from type (%lu) is (%s)\n",
         buf.mtype, buf.mtext);
  /*
  if (msgctl(msqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(1);
  }
  */
  return 0;
}
