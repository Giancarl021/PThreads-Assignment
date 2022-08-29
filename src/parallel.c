#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "primes.h"

// Defines the arguments for the parallel handler function
typedef struct {
    int *current_number;
    pthread_mutex_t *lock;
    int max_number;
    int *prime_count;
} parallel_args_t;

// Defines the handler function for the parallel threads
void *handler(void *args) {
    // Cast the arguments to the parallel_args_t struct
    parallel_args_t *parallel_args = (parallel_args_t *) args;
    // Get the current thread number
    pthread_t tid = pthread_self();

    // While the current number is less than the max number, process the next number
    while (*parallel_args->current_number <= parallel_args->max_number) {
        // Lock the mutex, to avoid concurrency
        pthread_mutex_lock(parallel_args->lock);

        // Get the next number to process
        int num = *(int *)parallel_args->current_number;
        // Process the number
        bool prime = is_prime(num);
        // Print the result found
        printf("Thread %lu: %d %sé número primo\n", tid, num, prime ? "" : "não ");

        // Increments the next number to process
        (*(parallel_args->current_number))++;
        // Increment the prime count if the number is prime
        (*(parallel_args->prime_count)) += prime ? 1 : 0;

        // Unlock the mutex, to allow other threads to access the data
        pthread_mutex_unlock(parallel_args->lock);

        // Sleep for 1/100th of a second, to avoid a single thread to always grab the mutex lock
        sleep(.001);
    }
    
    return NULL;
}