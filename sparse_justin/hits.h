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
void get_hub_scores(csr_matrix * graph, int * v, int * hubs) {

    int i;
    int * v = (int*) malloc(sizeof(int) * graph->nvertices);

    // making the e vect.
    for(i = 0; i < graph->nvertices; i++) {

        v[i] = 1;

    }

    hubs = csr_dot(graph, v);

}

/*
 * GET AUTH SCORES FUNCTION
 * 
 * todo tomorrow
*/
void get_auth_scores(csr_matrix * graph, int * v, float * auths) {

    puts("TODO");

}

#endif