#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "primes.h"

#define CHUNK_MIN_SIZE 10
#define CHUNK_MAX_SIZE 500

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
        int chunk_size = (rand() % (CHUNK_MAX_SIZE - CHUNK_MIN_SIZE + 1)) + CHUNK_MIN_SIZE;

        if ((*parallel_args->current_number) + chunk_size > parallel_args->max_number)
            chunk_size = parallel_args->max_number - (*parallel_args->current_number) + 1;

        int initial = (*parallel_args->current_number);

        (*(parallel_args->current_number)) += chunk_size;
    
        pthread_mutex_unlock(parallel_args->lock);

        int l = initial + chunk_size,
            counter = 0;

        for (int i = initial; i < l; i++) {
            // Process the number
            bool prime = is_prime(i);
            if (prime) counter++;

            // Print the result found
            printf("Thread %lu: %d %sé número primo\n", tid, i, prime ? "" : "não ");
        }

        pthread_mutex_lock(parallel_args->lock);
        // Increment the prime count if the number is prime
        (*(parallel_args->prime_count)) += counter;

        // Unlock the mutex, to allow other threads to access the data
        pthread_mutex_unlock(parallel_args->lock);
    }
    
    return NULL;
}