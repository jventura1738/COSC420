// Justin Ventura COSC420
// Project 2

#include "csr.h"

/*
 * HYPTER-TEXT INDUCED TOPIC SEARCH.
 * 
 * This file contains the functions required
 * to perform the HITS algorithm in serial.
 * This is done in serial since the compressed
 * sparse row matrices are extraordinarily
 * efficient compared to the sparse matrices.
*/

#ifndef HITS_H
#define HITS_H

/*
 * GET HUB SCORES FUNCTION
 * 
 * Assigns the resulting hub scores to the
 * hubs pointer parameter.  Void return type
 * since this is not python, and I cannot
 * return lists of arrays.
*/
void get_hub_scores(csr_matrix * graph, double * hubs) {

    int i;
    double * v = (double*) malloc(sizeof(double) * graph->nvertices);

    // making the e vect.
    for(i = 0; i < graph->nvertices; i++) {

        v[i] = 1;

    }

    csr_dot(graph, v, hubs);

}


/*
 * GET AUTH SCORES FUNCTION
 * 
 * Uses the hub scores to come up with the 
 * auth scores. 
*/
void get_auth_scores(csr_matrix * graph, double * hubs, double * auths) {

    int i, j;
    for(i = 0; i < graph->nvertices; i++) {

        auths[i] = 0;

    }
    puts("");

    for(i = 0; i < graph->nvertices; i++) {

        int low = graph->source_rows[i];
        int hi = graph->source_rows[i + 1];

        for(j = low; j < hi; j++) {

            auths[graph->source_cols[j]] += hubs[i];

        }

    }

    puts("");

}


/*
 * HYPER-TEXT INDUCED TOPIC SEARCH
 * 
 * This is the actual algorithm.
*/
void hits_alg(csr_matrix * graph, double * hubs, double * auths) {

    get_hub_scores(graph, hubs);
    get_auth_scores(graph, hubs, auths);

}

#endif