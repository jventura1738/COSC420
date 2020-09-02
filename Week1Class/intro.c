#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    // This constant gets set by the MPI lib
    MPI_Comm world = MPI_COMM_WORLD;

    puts("Hello World!");
    // printf("Hello World!\n")

    MPI_Finalize();
    return 0;
}