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
void get_hub_scores(csr_matrix * graph, float * hubs) {

    int i;
    float * v = (float*) malloc(sizeof(float) * graph->nvertices);

    // making the e vect.
    for(i = 0; i < graph->nvertices; i++) {

        v[i] = 1;

    }

    hubs = csr_dot(graph, v);

}


/*
 * GET AUTH SCORES FUNCTION
 * 
 * Uses the hub scores to come up with the 
 * auth scores. 
*/
void get_auth_scores(csr_matrix * graph, float * hubs, float * auths) {

    int i, j;
    for(i = 0; i < graph->nvertices; i++) {

        auths[i] = 0;

    }

    if(graph->nedges == 0) return;

    for(i = 0; i < graph->nvertices; i++){

        int low = graph->node_offsets[i];
        int hi = graph->node_offsets[i + 1];

        for(j = low; j < hi; j++) {

            auths[graph->source_indices[j]] += hubs[i];

        }

    }

}


/*
 * HYPER-TEXT INDUCED TOPIC SEARCH
 * 
 * This is the actual algorithm.
*/
void hits_alg(csr_matrix * graph, float * hubs, float * auths) {

    get_hub_scores(graph, hubs);
    get_auth_scores(graph, hubs, auths);

}

#endif