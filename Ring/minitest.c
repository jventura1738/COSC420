#include <stdio.h>
#include <stdlib.h>
//#include "matrix.h"
//#include "preprocess.h"
#include "interface.h"
//#include "include/csr.h"
//#include "include/page.h"

int main(int argc, char ** argv) {

  // csr_matrix * Graph;
  // matrix hub_vect, auth_vect;

  // matrix * adj = (matrix*) malloc(sizeof(matrix));
  // int N = 1000;
  // initMatrix(adj, N, N);

  // file_load_adj("test_citation.txt", N, adj);
  // //printMatrix(adj);
  // puts("");

  // Graph = (csr_matrix*) malloc(sizeof(csr_matrix));
  // puts("----------------------------");
  // to_csr(adj, Graph);
  // test_print(Graph);
  // puts("----------------------------");
  // print_csr(Graph);

  // matrix result;
  // init_vector(&result, NULL, Graph->nvertices);

  // page_rank(Graph, &result);

  // int z;
  // double sum = 0.0;
  // for(z = 0; z < Graph->nvertices; z++) {

  //     sum += result.data[z];
  //     printf("%f ", result.data[z]);
  //     if ((z+1) % 10 == 0) {

  //       puts("");

  //     }

  // }
  // puts("");
  // printf("%f\n", sum);

  int word_count;
  char ** input = get_user_input(&word_count);

  int i = 0;
  for (i = 0; i < word_count; i++) {

    printf("%s ")

  }
  puts("");

  return 0;
}