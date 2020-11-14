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
  float err = 0.01;

  for(i = 0; i < n; i++) {

    vector[i] = 1.0;
    result->data[i] = 0.0;

  }
  int count = 0;
  while(count < 10) {

    csr_dot(graph, vector, result->data);

    for (i = 0; i < n; i++) {

        printf("%f ", result->data[i]);

    }
    puts("");

    float eigen_value = result->data[0];
    for (i = 1; i < n; i++) {

        if (result->data[i] > eigen_value) {

            eigen_value = result->data[i];

        }

    }

    printf("eigen: %f\n", eigen_value);

    for(i = 0; i < n; i++) {

      result->data[i] /= eigen_value;

    }

    // if(isEqual(vector, result) == 1) {

    //   break;

    // }

    int z;
    for (z = 0; z < n; z++) {

        converged = 1;

        if (fabs(vector[z] - result->data[z]) > err) {

            converged = 0;

        }

    }

    for(z = 0; z < n; z++) {

      vector[i] = result->data[i];
      printf("%f ", vector[i]);

    }
    puts("");
    count++;
  }

}
