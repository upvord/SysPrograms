#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ELEMENTS 10
#define NUM_THREADS 2

// Structure to pass data to threads
typedef struct {
  int *array;
  int start;
  int end;
  int sum;
} ArraySegment;

// Thread function to calculate the sum of an array segment
void *calculate_sum(void *arg) {
  ArraySegment *segment = (ArraySegment *)arg;
  segment->sum = 0; // Initialize sum

  for (int i = segment->start; i < segment->end; i++) {
    segment->sum += segment->array[i];
  }

  pthread_exit((void *)segment);
}

int main() {
  int array[NUM_ELEMENTS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  pthread_t threads[NUM_THREADS];
  ArraySegment segments[NUM_THREADS];
  int totalSum = 0;

  // Divide the array and create threads
  for (int i = 0; i < NUM_THREADS; i++) {
    segments[i].array = array;
    segments[i].start = (NUM_ELEMENTS / NUM_THREADS) * i;
    segments[i].end = (NUM_ELEMENTS / NUM_THREADS) * (i + 1);
    if (pthread_create(&threads[i], NULL, calculate_sum,
                       (void *)&segments[i])) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  // Wait for the threads to finish and combine the results
  for (int i = 0; i < NUM_THREADS; i++) {
    ArraySegment *result;
    if (pthread_join(threads[i], (void **)&result)) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
    totalSum += result->sum;
  }

  // Output the results
  printf("Array: ");
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    printf("%d ", array[i]);
  }
  printf("\nTotal sum: %d\n", totalSum);

  return 0;
}
