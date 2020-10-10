#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"mpi.h"
#define MAX(a,b)((a > b) ? a:b)

long int DR(long int n){
    return (1 + ((n - 1) % (9)) );
}

int main(int argc, char** argv){
    MPI_Init(&argc, &argv); 
    int worldSize, myRank;

    MPI_Comm world = MPI_COMM_WORLD;
    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);
    long int i, j, k, range, extra, low, high;
    long int n = 100;
    long int sum = 0;
    long int Final_sum = 0;
    long int* mdrs = malloc(n*sizeof(long int));

    range = n / worldSize;
    extra = n % worldSize;
    if(myRank == 0){
        low = 2;
        high = low + range-2;
        printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
    }else{
        if(myRank == (worldSize - 1)){
            low = (myRank*range);
            high = low + range + extra;
            printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
        }else{
            low = (myRank*range);
            high = low + range;
            printf("Rank: %d Low: %ld High: %ld\n", myRank, low, high);
        }
    }   

    for(i = 2; i<n; i++){
        mdrs[i] = DR(i);
    }
    for(i = low; i < high; i++){
        //printf("%ld\n", i);
        for(j = 2; j*j <= i; j++){
            //printf("%ld ", i/j);
            if(i % j == 0){
                mdrs[i] = MAX(mdrs[i], mdrs[j] + mdrs[i/j]);
                //printf("%ld ", i/j);s
            }
        }
        printf("MDRS(%ld)=%ld\n", i, mdrs[i]);

    }
    printf("Rank: %d is done\n", myRank);
    
    for(k = low; k < high; k++){
        sum += mdrs[k];
    }
    MPI_Reduce(&sum, &Final_sum, 1, MPI_LONG, MPI_SUM, 0, world);
    if(myRank == 0){
        printf("Sum: %ld\n", Final_sum);
    }
    MPI_Finalize();
    return 0;
}