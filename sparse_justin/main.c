/*
 * COSC420 arXiv Search Test.
 * 
 * The testing file for our BST.
 * - Justin Ventura
*/

#include "list.h"   // linked list
#include "KWBST.h"  // binary search tree for keywords
#include "matrix.h" // matrix for doubles
#include "csr.h"    // compressed sparse row form
#include "hits.h"   // hyper-text induced topic search
#include "mpi.h"    // MPI stuff

int main (int argc, char ** argv) {

    MPI_Init(&argc, &argv);
    MPI_Comm world = MPI_COMM_WORLD;

    int worldSize, myRank;
    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    matrix hub_vect, auth_vect;

    if (myRank == 0) {

        matrix * adj = (matrix*) malloc(sizeof(matrix));
        int N = 10;
        initMatrix(adj, N, N);

        file_load_adj("test.txt", N, adj);
        printMatrix(adj);
        puts("");

        csr_matrix * Graph = (csr_matrix*) malloc(sizeof(csr_matrix));
        puts("----------------------------");
        to_csr(adj, Graph);
        test_print(Graph);
        puts("----------------------------");
        print_csr(Graph);

        double * hubs =  (double*) malloc(Graph->nvertices * sizeof(double));
        double * auths = (double*) malloc(Graph->nvertices * sizeof(double));

        hits_alg(Graph, hubs, auths);
        puts("");

        int i;
        for (i = 0; i < Graph->nvertices; i++) {

            printf("%f ", hubs[i]);

        }
        puts("");
        for (i = 0; i < Graph->nvertices; i++) {

            printf("%f ", auths[i]);

        }
        puts("");

        init_vector(&hub_vect, hubs, 10);
        init_vector(&auth_vect, auths, 10);

    }

    MPI_Barrier(world);
    double * norm_hub = normalize(&hub_vect, world, worldSize, myRank);

    if (myRank == 0) {

        int z;
        for (z = 0; z < hub_vect.rows; z++) {

            printf("%f ", norm_hub[z]);

        }

    }

    //double * norm_auth = normalize(auth_vect, world, worldSize, myRank);

    puts("thank the lord");
    MPI_Finalize();

    return 0;
}
