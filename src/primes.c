#include <stdio.h>
#include <stdbool.h>

bool is_prime(int number) {
    // Negatives and zero are not prime numbers
    if (number <= 0) return false;
    // 1, 2 and 3 are prime numbers
    if (number <= 3) return true;
    // Even numbers are not prime numbers
    if (number % 2 == 0) return false;

    // A number is prime if not divisible by any number starting from 2 until half the number itself
    int l = number / 2;

    // Loop every number until the half of the number itself
    for (int i = 3; i < l; i += 2) {
        // If the number is divisible by any number starting from 3 until half the number itself, it is not prime
        if (number % i == 0) return false;
    }

    // If the number is not divisible by any number starting from 3 until half the number itself, it is prime
    return true;
}