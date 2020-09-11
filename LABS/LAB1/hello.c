// Justin Ventura & Blaine Mason
// COSC420 Lab 1: hello.c

#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){

    // worldSize will be the total number of
    // nodes in the communicator.
    // myRank will be the nodes' id within that
    // communicator.
    int worldSize, myRank;

    // as per documentation: 'MPI_MAX_PROCESSOR_NAME' space
    // need be allocated for the name. it will then return
    // the length of the process, hence why there is an int
    // len.

    char name[MPI_MAX_PROCESSOR_NAME]; 
    int len;

    MPI_Init(NULL, NULL);

    // This constant gets set by the MPI lib
    MPI_Comm world = MPI_COMM_WORLD;

    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    MPI_Get_processor_name(name, &len); // get the process name & its length

    if (myRank == 0) {
        printf("Hello from the master node!\n");
        printf("There are %d total nodes.\n", worldSize);

    }
    else {
        // executes in worker nodes
        printf("Hello from worker node %d\n", myRank);
        printf("My process name is %s\n", name);
    }

    // puts("Hello World!");
    // printf("Hello World!\n")

    MPI_Finalize();

    return 0;
}
