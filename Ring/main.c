#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include "list.h"   // linked list
#include "KWBST.h"  // binary search tree for keywords
#include "matrix.h" // matrix for doubles
#include "csr.h"    // compressed sparse row form
#include "hits.h"   // hyper-text induced topic search
#include "page.h"   // page rank algorithm for CSR
#include "mpi.h"    // MPI stuff
#include "interface.h"


int main(int argc, char ** argv){
    FILE* logo = fopen("logo.txt", "r");
    if(system("clear") != -1){
        int c;
        int z;
        char word[200];
        while((c = fgetc(logo)) != EOF){
            if(fgets(word, sizeof word, logo)){
                printf("%s", word);
            }
            for(z = 0; z < strlen(word); z++){
                word[z] = '\0';
            }
            if(feof(logo)){
                break;
            }
        }
        puts("");
    }else{
        printf("Imagine Using Windows...\n");
    }
    puts("");
    printf("Get the users search: \n");
    int word_count;
    char ** query_words = get_user_input(&word_count);
    printf("If a cla -verbose=on is used, display the status of the search.\n\n");
    printf("============================================\n");
    printf("Return Results Here!\n");


    /*
     * - Grab all articles with the words that match.
     * - Print the most relevant ones based on page_rank.
     * - 
    */
    
    
    return 0;
}