#ifndef __PARALLEL_H__
#define __PARALLEL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct {
    int *current_number;
    pthread_mutex_t *lock;
    int max_number;
    int *prime_count;
} parallel_args_t;

void *handler(void *args);

#ifdef __cplusplus
}
#endif

#endif