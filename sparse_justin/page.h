// Justin Ventura

#include "csr.h"

/*
 * PAGE RANK ALGORITHM
 * 
 * This computes the page rank.
*/
void page_rank(csr_matrix * graph, matrix * result) {

  int n = graph->nvertices;

  double vector[n];
  int i, converged = 0;
  double err = 0.1;

  for(i = 0; i < n; i++) {

    vector[i] = 1.0;
    result->data[i] = 0.0;

  }

  int count = 0;
  while(converged == 0) {

    csr_dot(graph, vector, result->data);

    puts("A * v: ");
    for (i = 0; i < n; i++) {

        printf("%f ", result->data[i]);

    }
    puts("");

    double eigen_value = result->data[0];
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

    puts("v / eigen val");
    for(z = 0; z < n; z++) {

      vector[z] = result->data[z];
      printf("%f ", vector[i]);

    }
    puts("");
    count++;
  }

}
