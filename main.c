/*
Environment: Ubuntu 22.04.1 LTS
Compile Command: make
Run Command: ./T
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <pthread.h>
#include "src/parallel.h"

// Formatting
#define PADDING "  "

int main(int argc, char *argv[]) {
    // Set locale to Portuguese characters
    setlocale(LC_ALL, "Portuguese");

    // Input variables
    int number_range,
        thread_num;

    // Change the random seed based on time
    srand(time(NULL));

    // If at least one argument were passed, try to parse them
    if (argc >= 2) {
        // string to int conversion on first argument
        number_range = atoi(argv[1]);
        // If at least two arguments were passed, try to parse them
        if (argc >= 3) {
            // string to int conversion on second argument
            thread_num = atoi(argv[2]);
        } else {
            // If only first argument were passed, read the number of threads from the user
            printf("Insira o número de threads: ");
            scanf("%d", &thread_num);
        }
    } else {
        // If no arguments were passed, read the range of numbers from the user
        printf("Insira a quantidade de números a serem processados: ");
        scanf("%d", &number_range);

        // If no threads were passed, read the number of threads from the user
        printf("Insira o número de threads: ");
        scanf("%d", &thread_num);
    }

    // Initialize the parallel processing
    printf(
        "INICIALIZANDO:\n"
        PADDING "Faixa de números a serem processados: 1..%d\n"
        PADDING "Total de threads a serem criadas: %d\n",
        number_range,
        thread_num
    );

    // Create an array of threads to keep track of the progress
    pthread_t *threads = malloc(sizeof(pthread_t) * thread_num);

    // Initialize the global counters
    int next_number = 1;
    int count = 0;
    pthread_mutex_t lock;

    // Initialize the mutex lock, if failed abort
    if (pthread_mutex_init(&lock, NULL) != 0) {
        fprintf(stderr, "Erro ao inicializar mutex\n");
        return EXIT_FAILURE;
    }

    // Create the threads shared arguments
    parallel_args_t args = {
        .current_number = &next_number,
        .lock = &lock,
        .max_number = number_range,
        .prime_count = &count
    };

    // For each thread, create a new thread and pass the arguments
    for (int i = 0; i < thread_num; i++) {
        pthread_create(&threads[i], NULL, &handler, &args);
    }

    // Wait for all threads to finish
    for (int i = 0; i < thread_num; i++) {
        pthread_join(threads[i], NULL);
    }

    // Free all memory used by the threads
    pthread_mutex_destroy(&lock);
    free(threads);

    // Print the results
    printf(
        "\nFINALIZADO\n"
        PADDING
        "%d números primos foram encontrados\n",
        count
    );

    return EXIT_SUCCESS;
}