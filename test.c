// Justin Ventura COSC420
// Serial Project Euler
// Problem #159

#include <stdio.h>
#include <stdlib.h>

long int DR(long int n) {

    return (1 + ((n - 1) % (9)) );

}

int main() {

    long int i, j, N = 26;
    long int sum = 0;

    for (i = 2; i < N; i++) {

        long int max = 0;

        for (j = 1; j <= i; j++) {

            if (i % j == 0) {

                int test = DR(j) + DR(i/j);
                if (test > max) {

                    max = test;
                    if (DR(j) == 1 || DR(i/j) == 1) {

                        max -= 1;

                    }

                }

            }

        }

        printf("MDRS(%ld)=%ld\n", i, max);
        sum += max;

    }

    // long int max = 0;

        // for (j = 1; j <= 24; j++) {

        //     if (24 % j == 0) {

        //         int test = DR(j) + DR(24/j);
        //         if (test > max) {

        //             max = test;

        //         }

        //     }

        // }

        // sum = max;


    printf("sum = %ld\n", sum);

    return 0;

}