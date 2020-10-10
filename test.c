// Justin Ventura COSC420
// Serial Project Euler
// Problem #159

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#define MAX(a,b)((a > b) ? a:b)

long int max_of_three(long int a, long int b, long int c) {

    if(a >= b && a >= c) {

        return a;

    } 
    else if(b >= c && b >= a) {

        return b;

    }
    
    return c;

}

long int DR(long int n) {

    return (1 + ((n - 1) % (9)) );

}

long int * prime_factors(long int n) {

    long int * factors = malloc(50 * sizeof(long int));
    long int i, idx = 0;

    // Print the number of 2s that divide n 
    while (n%2 == 0) {

        factors[idx++] = 2; 
        n = n/2;

    } 
  
    // n must be odd at this point.  So we can skip  
    // one element (Note i = i +2) 
    for (i = 3; i <= sqrt(n); i = i+2) {

        // While i divides n, print i and divide n 
        while (n%i == 0) {

            factors[idx++] = i; 
            n = n/i; 

        } 

    } 
  
    // This condition is to handle the case when n  
    // is a prime number greater than 2 
    if (n > 2) 
        factors[idx++] = n;

    return factors;

}

int is_prime(int x) {

    long int buffer = sqrt(x);

    // If the N has a factor, print them and abort the program.
    long int i;
    for(i = 2; i <= buffer; i++) {
        
        if(x % i == 0){

            return 0;
            
        }

    }

    return 1;

}


int main(int argc, char** argv) {

    MPI_Init(&argc, &argv); 
    int worldSize, myRank;

    MPI_Comm world = MPI_COMM_WORLD;
    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank); 

    long int i, j, N = 100;
    long int final, sum = 0;
    long int range, low, high, extra;


    range = N / worldSize;
    extra = N % worldSize;
    if(myRank == 0){
        low = 2;
        high = low + range-2;
    }else{
        if(myRank == (worldSize - 1)){
            low = (myRank*range);
            high = low + range + extra;
        }else{
            low = (myRank*range);
            high = low + range;
        }
    }


    for (i = low; i < high; i++) {

        long int max = 0;

        if (is_prime(i)) {

            //printf("%ld IS PRIME!\n", i);

            max = DR(i);
            sum += max;
            printf("MDRS(%ld)=%ld\n", i, max);
            continue;

        }

        //printf("Factors of %ld are: ", i);
        for (j = 2; j < i; j++) {

            if (i % j == 0) {

                long int * prime_1 = prime_factors(j);
                long int * prime_2 = prime_factors(i/j);
                long int z, sum1 = 0, sum2 = 0;
                for (z = 0; prime_1[z]; z++) {

                    sum1 += DR(prime_1[z]);

                }
                for (z = 0; prime_2[z]; z++) {

                    sum2 += DR(prime_2[z]);

                }
                long int test = MAX(DR(j), sum1) + MAX(DR(i/j), sum2);
                if (test > max) {
 
                    max = test;
 
                }

            }

        }
        //printf("%ld\n", j);

        printf("MDRS(%ld)=%ld\n", i, max);
        //printf("j=%ld, DR(%ld)=%ld\n", j, j, DR(j));
        sum += max;

    }

    /* --------------------------------------- */


    printf("Node %d has local sum = %ld\n", myRank, sum);

    MPI_Reduce(&sum, &final, 1, MPI_LONG, MPI_SUM, 0, world);

    if (myRank == 0) {

        printf("resulting sum: %ld\n", final);

    }

    MPI_Finalize();

    return 0;

}