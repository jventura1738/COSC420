// Justin Ventura

#include "csr.h"

/*
 * PAGE RANK ALGORITHM
 * 
 * This computes the page rank.
*/
void page_rank(csr_matrix * graph, matrix * result) {

    // dampening factor.
    double d = 0.85;
    int n = graph->nvertices;
    int i, j;

    int out_link[n];
    for(i = 0; i < n; i++) {

        out_link[i] = 0;

    }

    int rowel = 0;
    for(i = 0; i < n; i++) {

        if (graph->source_rows[i+1] != 0) {

            rowel = graph->source_rows[i+1] - graph->source_rows[i];
            out_link[i] = rowel;

        }

    }

    int curcol = 0;
    for(i = 0; i < n; i++) {

        rowel = graph->source_rows[i+1] - graph->source_rows[i];

        for (j = 0; j < rowel; j++) {

            graph->source[curcol] = graph->source[curcol] / out_link[i];
            curcol++;

        }

    }

    // Initialize p vector
    double * p = (double*) malloc(sizeof(double) * n);
    for(i = 0; i < n; i++) {

        p[i] = 1.0;

    }

    print_csr(graph);
    puts("");

    int looping = 1;
    int k = 0;
    double p_new[n];

    while (looping) {
    
        // Initialize p_new as a vector of n 0.0 cells
        for(i = 0; i < n; i++) {

            p_new[i] = 0.0;

        }
        
        rowel = 0;
        curcol = 0;
        
        // Page rank modified algorithm 
        for(i = 0; i < n; i++) {

            rowel = graph->source_rows[i+1] - graph->source_rows[i];

            for (j = 0; j < rowel; j++) {

                p_new[graph->source_cols[curcol]] += graph->source[curcol] * p[i];
                curcol++;

            }

        }

        // Adjustment to manage dangling elements 
        for(i = 0; i < n; i++) {

            p_new[i] = d * p_new[i] + (1.0 - d) / n;

        }

        // TERMINATION: check if we have to stop
        double error = 0.0;
        for(i = 0; i < n; i++) {

            error =  error + fabs(p_new[i] - p[i]);

        }
        //if two consecutive instances of pagerank vector are almost identical, stop
        if (error < 0.000001) {

            looping = 0;

        }
        
        // Update p[]
        for (i = 0; i < n; i++) {

            p[i] = p_new[i];

        }
        
        // Increase the number of iterations
        k++;
    }

    result->data = p;

}
