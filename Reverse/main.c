#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"
int main(int argc, char** argv){
    MPI_Init(&argc, &argv); 
    int worldSize, myRank;

    MPI_Comm world = MPI_COMM_WORLD;
    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank); 
    size_t n = 1000000000;
    size_t Final_sum = 0;
    size_t count = 0;
    size_t reverse = 0;
    size_t last, i, sum, temp, range, low, high, extra;
    int isEven;
    range = n / worldSize;
    extra = n % worldSize;
    if(myRank == 0){
        low = 0;
        high = low + range;
    }else{
        if(myRank == (worldSize - 1)){
            low = (myRank*range);
            high = low + range + extra;
        }else{
            low = (myRank*range);
            high = low + range;
        }
    }
    for(i = low; i < high; i++){
        if(i % 10 == 0){
            count++;
            continue;
        }
        temp = i;
        sum = 0;
        reverse = 0;
        while(temp > 0){
            last = temp % 10;
            reverse = (reverse*10) + last;
            temp /= 10;
        }
        sum = reverse + i;
        isEven = 0;
        while(sum > 0){
            last = sum % 10;
            if(last % 2 == 0){
                isEven = 1;
                break;
            }
            sum /= 10;
        }  
        if(isEven == 1){
            count++;
        }  
    }
    MPI_Reduce(&count, &Final_sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, world);
    
    if(myRank == 0){
        printf("Sum: %zu\n", n - Final_sum);
    }
    MPI_Finalize();
    return 0;
}