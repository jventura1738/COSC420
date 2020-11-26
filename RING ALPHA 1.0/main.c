#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include "list.h"   // linked list
#include "KWBST.h"  // binary search tree for keywords
#include "matrix.h" // matrix for doubles
#include "include/csr.h"    // compressed sparse row form
#include "include/hits.h"   // hyper-text induced topic search
#include "include/page.h"   // page rank algorithm for CSR
//#include "mpi.h"    // MPI stuff
#include "interface.h"


int main(int argc, char ** argv){
    FILE* logo = fopen("logo.txt", "r");
    if(system("clear") != -1){
        int c;
        int z;
        char word[200];
        while((c = fgetc(logo)) != EOF){
            if(fgets(word, sizeof word, logo)){
                printf("%s", word);
            }
            for(z = 0; z < strlen(word); z++){
                word[z] = '\0';
            }
            if(feof(logo)){
                break;
            }
        }
        puts("");
    }else{
        printf("Imagine Using Windows...\n");
    }
    puts("");
    printf("Get the users search: \n");
    int word_count;
    char ** query_words = get_user_input(&word_count);
    printf("If a cla -verbose=on is used, display the status of the search.\n\n");
    printf("============================================\n");
    printf("Return Results Here!\n");

    //PageRank
    csr_matrix * Graph;
    //matrix hub_vect, auth_vect;

    matrix * adj = (matrix*) malloc(sizeof(matrix));
    int N = 9;
    initMatrix(adj, N, N);

    file_load_adj("temp_citations.txt", N, adj);
    puts("adj matrix");
    printMatrix(adj);
    puts("");

    Graph = (csr_matrix*) malloc(sizeof(csr_matrix));
    puts("----------------------------");
    to_csr(adj, Graph);
    puts("line 1: rowptrs, line 2: col idx, line 3: vals");
    test_print(Graph);
    puts("----------------------------");
    print_csr(Graph);

    matrix result;
    init_vector(&result, NULL, Graph->nvertices);

    page_rank(Graph, &result);

    puts("\nPage rank vector:");

    int z;
    for(z = 0; z < Graph->nvertices; z++) {

        printf("%f ", result.data[z]);

    }

    double * hub_vect = (double*) malloc(Graph->nvertices * sizeof(double));
    double * auth_vect = (double*) malloc(Graph->nvertices * sizeof(double));

    hits_alg(Graph, hub_vect, auth_vect);

    puts("Hubs vector:");
    for(z = 0; z < Graph->nvertices; z++) {

        printf("%f ", hub_vect[z]);

    }
    puts("");

    puts("Auths vector:");
    for(z = 0; z < Graph->nvertices; z++) {

        printf("%f ", auth_vect[z]);

    }
    puts("");

    /*
     * - Grab all articles with the words that match.
     * - Print the most relevant ones based on page_rank.
     * - 
    */
    
    
    return 0;
}