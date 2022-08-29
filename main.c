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

#define PADDING "  "

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    int number_range,
        thread_num;

    if (argc >= 2) {
        number_range = atoi(argv[1]);

        if (argc >= 3) {
            thread_num = atoi(argv[2]);
        } else {
            printf("Insira o número de threads: ");
            scanf("%d", &thread_num);
        }
    } else {
        printf("Insira a quantidade de números a serem processados: ");
        scanf("%d", &number_range);

        printf("Insira o número de threads: ");
        scanf("%d", &thread_num);
    }

    printf(
        "INICIALIZANDO:\n"
        PADDING "Faixa de números a serem processados: 1..%d\n"
        PADDING "Total de threads a serem criadas: %d\n",
        number_range,
        thread_num
    );

    pthread_t *threads = malloc(sizeof(pthread_t) * thread_num);
    int next_number = 1;
    int count = 0;
    pthread_mutex_t lock;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        fprintf(stderr, "Erro ao inicializar mutex\n");
        return EXIT_FAILURE;
    }

    parallel_args_t args = {
        .current_number = &next_number,
        .lock = &lock,
        .max_number = number_range,
        .prime_count = &count
    };

    for (int i = 0; i < thread_num; i++) {
        pthread_create(&threads[i], NULL, &handler, &args);
    }

    for (int i = 0; i < thread_num; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    free(threads);

    printf(
        "\nFINALIZADO\n%s%d números primos foram encontrados\n",
        PADDING,
        count
    );

    return EXIT_SUCCESS;
}