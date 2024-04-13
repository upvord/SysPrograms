#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int counter;
pthread_mutex_t lock; // m;

void *increment_counter(void *arg) {
  printf("Trying to access resource :%d\n", pthread_self());
  pthread_mutex_lock(&lock);
  for (int i = 0; i < 10; i++) {
    printf("t:%d -> %d\n", (int)pthread_self(), counter);
    counter++;
    sleep(1);
  }
  pthread_mutex_unlock(&lock);

  return NULL;
}

int main(int argc, char *argv[]) {

  pthread_mutex_init(&lock, NULL);

  pthread_t t1, t2;

  pthread_create(&t1, NULL, increment_counter, NULL);
  pthread_create(&t2, NULL, increment_counter, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("Final counter value: %d\n", counter);
  return 0;
}
