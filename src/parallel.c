#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "primes.h"

typedef struct {
    int *current_number;
    pthread_mutex_t *lock;
    int max_number;
    int *prime_count;
} parallel_args_t;

void *handler(void *args) {
    parallel_args_t *parallel_args = (parallel_args_t *) args;
    pthread_t tid = pthread_self();

    while (*parallel_args->current_number <= parallel_args->max_number) {
        pthread_mutex_lock(parallel_args->lock);

        int num = *(int *)parallel_args->current_number;
        bool prime = is_prime(num);
        printf("Thread %lu: %d %sé número primo\n", tid, num, prime ? "" : "não ");

        (*(parallel_args->current_number))++;
        (*(parallel_args->prime_count)) += prime ? 1 : 0;

        pthread_mutex_unlock(parallel_args->lock);
        // Avoid a single thread to always grab the mutex lock
        sleep(.001);
    }
    
    return NULL;
}