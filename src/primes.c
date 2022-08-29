#include <stdio.h>
#include <stdbool.h>

bool is_prime(int number) {
    // Negatives and zero are not prime numbers
    if (number <= 0) return false;
    // 1, 2 and 3 are prime numbers
    if (number <= 3) return true;
    // Even numbers are not prime numbers
    if (number % 2 == 0) return false;

    int l = number / 2;

    for (int i = 3; i < l; i += 2) {
        if (number % i == 0) return false;
    }

    return true;
}