// Justin Ventura

#include "csr.h"

/*
 * PAGE RANK ALGORITHM
 * 
 * This computes the page rank.
*/
void page_rank(csr_matrix * graph, matrix * result) {

  int n = graph->nvertices;

  float vector[n];
  int i, converged = 0;
  float err = 0.000001;

  for(i = 0; i < n; i++) {

    vector[i] = 1.0;
    result->data[i] = 0.0;

  }

  while(converged == 0) {

    csr_dot(graph, vector, result->data);

    float eigen_value = result->data[0];
    for (i = 1; i < n; i++) {

        if (result->data[i] > eigen_value) {

            eigen_value = result->data[i];

        }

    }

    for(i = 0; i < n; i++) {

      result->data[i] /= eigen_value;

    }

    // if(isEqual(vector, result) == 1) {

    //   break;

    // }

    int z;
    for (z = 0; z < n; z++) {

        converged = 1;

        if (abs(vector[z] - result->data[z]) > err) {

            converged = 0;

        }

    }

    for(z = 0; z < n; z++) {

      vector[i] = result->data[i];

    }

  }

}