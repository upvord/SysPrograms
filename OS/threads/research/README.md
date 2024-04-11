# Homework Assignment: Parallel Sum Calculation

## Objective
Write a C program that uses pthreads to calculate the sum of an integer array. This program should:
- Divide the array into two parts.
- Calculate the sum of each part in separate threads.
- Combine the results to get the total sum.

This task is designed to help students practice creating threads, passing data to threads, and combining results from multiple threads.

## Requirements

### Array Initialization
- Begin with a static integer array containing at least 10 elements.
- Initialize this array with positive integers of your choice.

### Thread Creation
- Create two threads. Each thread is responsible for calculating the sum of one half of the array.
- Make sure to pass the appropriate portion of the array to each thread.

### Sum Calculation
- Implement a function that each thread will execute to calculate the sum of its array portion.
- This function should take a segment of the array as input and return its sum.

### Combining Results
- After both threads have completed their calculations, the main thread should combine their results to produce the total sum of the array elements.

### Output
- Print the original array, the sum calculated by each thread, and the total sum to the console.

## Hints
- You can use the `pthread_create` function to start each thread, passing it a structure containing the array segment to be summed.
- Use `pthread_join` to wait for each thread to complete before combining the results.
- Be mindful of how you pass the array segments to your threads to avoid issues with shared data.

## Sample Structure for Passing Data to Threads
```c
typedef struct {
    int *array;
    int start;
    int end;
    int sum;
} ArraySegment;

