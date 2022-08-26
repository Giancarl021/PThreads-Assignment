/*
Environment: Ubuntu 22.04.1 LTS
Compile Command: make
Run Command: ./T
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

    return EXIT_SUCCESS;
}