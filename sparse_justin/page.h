// Justin Ventura

#include "csr.h"

/*
 * PAGE RANK ALGORITHM
 * 
 * This computes the page rank.
*/

void page_rank(csr_matrix * graph, float * result){

  int n = graph->nvertices;

  if(csr.nedges == 0) return;

  float vector[n];
  int i;

  //init vectors
  for(i = 0; i < n; i++) {

    vector[i] = 1.0;
    result[i] = 0.0;

  }

  while(1) {

    sparsemult_f(csr, vector, result, n);

    float eigenValue = findmax(result, n);
    for(i = 0; i < n; i++) {

      result[i] /= eigenValue;

    }

    if(isEqual(vector, result, n) == 1) {

      break;

    }

    for(i = 0; i < n; i++) {

      vector[i] = result[i];

    }

  }

}