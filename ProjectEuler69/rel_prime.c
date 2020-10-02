// Justin Ventura & Blaine Mason
// COSC420 Project Euler: rel_prime.c

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h> 

int is_rel_prime(int *N, int *k);

int main(int argc, char ** argv) {

    int N = 30;
    int k = 14;

    int result = is_rel_prime(&N, &k);
    printf("%d and %d relatively prime: %d\n", N,  k, result);

    return 0;

}

int is_rel_prime(int *N, int *k) {

    int i;

    // assume k is smaller than N.
    for (i = 2; i < *k; i++) {

        if (*N % i == 0 && *k % i == 0) {

            return 0;

        }

    }

    return 1;

}