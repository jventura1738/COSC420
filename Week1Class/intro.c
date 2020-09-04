#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
    MPI_Init(NULL, NULL);

    // This constant gets set by the MPI lib
    MPI_Comm world = MPI_COMM_WORLD;

    // worldSize will be the total number of
    // nodes in the communicator.
    // myRank will be the nodes id within that
    // communicator.
    int worldSize, myRank;

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    if ( myRank == 0) {
        printf("Hello from the master node!\n");
        printf("There are %d total nodes.\n", worldSize);
    }
    else {
        // executes in worker nodes
        printf("Hello from worker node %d", myRank);
    }

    // puts("Hello World!");
    // printf("Hello World!\n")

    MPI_Finalize();
    return 0;
}