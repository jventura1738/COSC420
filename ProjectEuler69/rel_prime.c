// Justin Ventura & Blaine Mason
// COSC420 Project Euler: rel_prime.c

#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h> 

int is_rel_prime(int *N, int *k);
int totient_of(int *N);

int main(int argc, char ** argv) {

    int N = 10000;

    float * totient_list = malloc((N - 2)*sizeof(float));

    int i, counter = 0;
    float max = 0.0;
    for (i = 2; i <= N; i++) {

        totient_list[i-2] = ((i*1.0) / totient_of(&i));
        if ((i*1.0) / totient_of(&i) > max) {

            max = ((i*1.0) / totient_of(&i));

        }

    }

    for (i = 0; i <= N - 2; i++) {

        if (totient_list[i] == max) {

            printf("%d ", i + 2);
            counter++;

        }

    }

    puts("");

    return 0;

}

int is_rel_prime(int *N, int *k) {

    int i;

    // assume k is smaller than N.
    for (i = 2; i <= *k; i++) {

        if (*N % i == 0 && *k % i == 0) {

            return 0;

        }

    }

    return 1;

}

int totient_of(int *N) {

    int i, totient = 0;

    for (i = 1; i <= *N; i++) {

        if (is_rel_prime(N, &i)) {

            totient += 1;

        }

    }

    return totient;

}
