// Justin Ventura & Blaine Mason
// COSC420 Project Euler: totient_max.c

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>//gh    
#include "mpi.h"

// Relatively prime calc
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


// Euler Totient Function
int totient_of(int *N) {
    int i, totient = 0;

    for (i = 1; i <= *N; i++) {

        if (is_rel_prime(N, &i)) {

            totient += 1;

        }

    }

    return totient;

}

int main(int argc, char** argv){

    MPI_Init(&argc, &argv); // pass through cli args
    int worldSize, myRank;

    // This constant gets set by the MPI lib
    MPI_Comm world = MPI_COMM_WORLD;
    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank); 
    int N = 1000;
    double * totient_list = malloc((N - 2)*sizeof(double));

    int i;
    double max = 0.0;
    int range = N/worldSize;
    int low, high;
    if(myRank == 0){
        low = 2;
        high = low + range - 2;
    }else{
        low = myRank*range;
        high = low + range;
    }
    for (i = low; i <= high; i++) {

        totient_list[i-2] = ((i*1.0) / totient_of(&i));
        if ((i*1.0) / totient_of(&i) > max) {

            max = ((i*1.0) / totient_of(&i));

        }
        //printf("%d\n", i);

    }

    //puts("");
    if(myRank = 0){
        for (i = 0; i <= N - 2; i++) {

            if (totient_list[i] == max) {
                
                printf("%d ", i + 2);

            }

        }
        puts("");
    }
    MPI_Finalize();
    return 0;

}

