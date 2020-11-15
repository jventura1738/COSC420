// Justin Ventura

#include "csr.h"

/*
 * PAGE RANK ALGORITHM
 * 
 * This computes the page rank vector
 * and stores it into result.
 * 
 * Algorithm:
 * 
 * p <- d(A * p) + (1 - d)e
 * [repeat until converged]
 * 
 * s.t. d is the dampening factor
 *      A is row stochastic csr_matrix
 *      p & e vects of all ones
 *      [p updates, however]
 * 
 * Stores the page rank probability 
 * vector into 'result'.
*/
void page_rank(csr_matrix * graph, matrix * result) {

    // Dampening factor.
    double d = 0.85;

    // Variables we will use later.
    int n = graph->nvertices;
    int i, j;


    // Ensure the matrix is row stochastic.
    int fix[n];
    for(i = 0; i < n; i++) {

        fix[i] = 0;

    }

    // 
    int row_ptr = 0;
    int col_idx = 0;
    for(i = 0; i < n; i++) {

        if (graph->source_rows[i+1] != 0) {

            row_ptr = graph->source_rows[i+1] - graph->source_rows[i];
            fix[i] = row_ptr;

        }

    }
    for(i = 0; i < n; i++) {

        row_ptr = graph->source_rows[i+1] - graph->source_rows[i];

        for (j = 0; j < row_ptr; j++) {

            graph->source[col_idx] = graph->source[col_idx] / fix[i];
            col_idx++;

        }

    }

    // Initialize vector of all ones.
    double * p = (double*) malloc(sizeof(double) * n);
    for(i = 0; i < n; i++) {

        p[i] = 1.0;

    }

    int not_converged = 1;
    double * new_p = (double*) malloc(sizeof(double) * n);

    while (not_converged) {

        csr_dot(graph, p, new_p);

        // This is based on the formula given by Dr. Anderson
        // during lecture!
        double sum = 0.0;
        for(i = 0; i < n; i++) {

            new_p[i] = d * new_p[i] + (1.0 - d);
            sum += new_p[i];

        }
        for(i = 0; i < n; i++) {

            new_p[i] /= sum;

        }

        // If the vector converges, stop iterating!
        double error = 0.0;
        for(i = 0; i < n; i++) {

            error += fabs(new_p[i] - p[i]);

        }
        if (error < 0.000001) {

            not_converged = 0;

        }
        
        // Update p vector.
        for (i = 0; i < n; i++) {

            p[i] = new_p[i];

        }
        
    }

    // Store the resulting vector.
    result->data = p;

}
