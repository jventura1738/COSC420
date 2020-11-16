
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "include/list.h"   // linked list
#include "include/KWBST.h"  // binary search tree for keywords
#include "include/matrix.h" // matrix for doubles
#include "include/csr.h"    // compressed sparse row form
#include "include/hits.h"   // hyper-text induced topic search
#include "include/page.h"   // page rank algorithm for CSR
#include "mpi.h"    // MPI stuff


/*
* The struct docnode holds the following:
*   -ID
*   -Title
*   -Author(s)
*   -Abstract Word Count
*   -Abstract
*/
typedef struct docnode{
    char id[30];
    char title[300];
    char authors[30000];
    int wordCount;
    char** abstract;

} docnode;

void mpiFileIn(MPI_Comm world, int worldSize, int myRank){
    int c,z;
    char buffer[50];
    MPI_File fh;
    FILE* fr = fopen("arXiv/Words.txt", "r");
    MPI_Offset offset;
    MPI_File_open(world, "out",
    MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
    while((c = fgetc(fr)) != EOF){
            offset = z;
            printf("z = %d\n", z);
            buffer[0] = c;
            fgets(buffer+1, sizeof buffer, fr);
            if(isalpha(c) != 0 || buffer[0] == '\n'){
                printf("%s", buffer);
                printf("Rank: %d, Buffer: %s\n", myRank, buffer); 
                MPI_File_write(fh,buffer, strlen(buffer), MPI_CHAR, MPI_STATUS_IGNORE);
            }
            
            if(feof(fr)){
                break;
            }
            z++;
        }
       
        fclose(fr);
        MPI_File_close(&fh);
}

/*
* printN
*   -IN: docnode object
*   -OUT: All information about the document
*/
void printN(docnode* p){
    printf("%s", p->id);
    printf("%s", p->title);
    printf("%s", p->authors);
    printf("%d\n", p->wordCount);
    int i;
    for(i=0;i < 256*p->wordCount && p->abstract[i];i++){
        printf(" %s ", p->abstract[i]);
    }
    puts("");
}


/*
* nodeComp:
*   IN: File Handle fh, integer z, docnode* p
*   OUT: A node p that contains the information
*        from the document.
*/
void nodeComp(FILE* fh, int z, docnode* p){
    char bigString[360000];
    char buffer[40000];
    char title[7000];
    char trash[50];
    char idBuffer[50];
    int i,j,ctr;
    for(i = 0; i < 40000; i++){
        buffer[i] = '\0';
    }
    if(z == 0){
        fgets(idBuffer, sizeof idBuffer, fh);
        strcpy(p->id, idBuffer);
        fgets(buffer, sizeof buffer, fh);
        strcpy(p->title, buffer);
        fgets(buffer, sizeof buffer, fh);
        strcpy(p->authors, buffer);
        fgets(buffer, sizeof buffer, fh);
        p->wordCount = atof(buffer);
    }else{
        fgets(trash, sizeof trash, fh);
        fgets(buffer, sizeof buffer, fh);
        strcpy(p->id, buffer);
        fgets(title, sizeof title, fh);
        strcpy(p->title, title);
        fgets(buffer, sizeof buffer, fh);
        strcpy(p->authors, buffer);
        fgets(buffer, sizeof buffer, fh);
        p->wordCount = atof(buffer);
    }

    char newString[p->wordCount][256];
    fgets(bigString, sizeof bigString, fh);

    j=0; ctr=0;
    for(i=0;i<=(strlen(bigString));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(bigString[i]==' '|| bigString[i]=='\0' || isalpha(bigString[i]) == 0)
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j]=bigString[i];
            j++;
        }
    }
    p->abstract = malloc(p->wordCount*256);
    for(j = 0; j < ctr; j++){
        p->abstract[j] = (char*)malloc(256);
    }
    
    for(i=2;i < ctr;i++){
        strcpy(p->abstract[i], newString[i]);
    }
}

/*
* writeWordsFromAbstracts:
*   IN: File Handle fh, File Handle fw
*   OUT: The words from the given abstract are 
*        outputted to a file.
*/
void writeWordsFromAbstracts(FILE* fh, FILE* fw){
    int z = 0;
    int c;
    while((c = fgetc(fh)) != EOF){
        docnode* n = NULL;
        n = calloc(1, sizeof(docnode));
        nodeComp(fh,z, n);
        keyword_node * ROOT = NULL;
        printf("%s\n", n->id);

        if(n->wordCount < 30){
            return;
        }
        int i;
        int count = 0;
        for (i = 0; i < 256*n->wordCount && n->abstract[i]; i++) {
            ROOT = insert(ROOT, n->abstract[i]);
            append(ROOT->MASTER, atof(n->id));
            count++;
        }
        
        in_order(ROOT);
        clear_tree(ROOT);
        free(n->abstract);
        free(n);
        
        z++;
        if(feof(fh)){
            break;
        }
    }
    
}
/*
* readWriteAbstracts:
*   IN: NULL
*   OUT: A text file that containts the
*        abstracts of the documents selected
*/
void readWriteAbstracts(){
    int z = 0;
    FILE* fh = fopen("arXiv/Alphabetized.txt", "r");
    FILE* ids = fopen("arXiv/tempID.txt", "r");
    FILE* fw = fopen("arXiv/List_of_Abstracts.txt", "w");
    char bigString[640000];
    char buffer[100000];
    char buferID[100];
    char id[25];
    int i,j,ctr,k, x, c, cc;
    while((cc = fgetc(ids))!= EOF){
        id[0] = cc;
        fgets(id+1, sizeof id, ids);
        FILE* fh = fopen("arXiv/Alphabetized.txt", "r");
        z = 0;
        printf("ID: %s\n", id);
        while((c = fgetc(fh)) != EOF){
            //printf("z = %d\n", z);
            if(z == 0){
                buferID[0] = c;
                fgets(buferID + 1, sizeof buferID, fh);
                if(strcmp(buferID, id) != 0){
                    z++;
                    //printf("BUFFER: %s\n", buferID);
                    fgets(buffer, sizeof buffer, fh);
                    fgets(buffer, sizeof buffer, fh);
                    fgets(buffer, sizeof buffer, fh);
                    fgets(buffer, sizeof buffer, fh);
                    continue;
                }else{
                    z++;
                    printf("ID: %s\n", id);
                    printf("BUFFER: %s\n", buferID);
                    fprintf(fw, "%s", buferID);
                    fgets(buffer, sizeof buffer, fh);
                    fprintf(fw, "%s", buffer);
                    fgets(buffer, sizeof buffer, fh);
                    fprintf(fw, "%s", buffer);
                    fgets(buffer, sizeof buffer, fh);
                    fprintf(fw, "%s", buffer);
                    fgets(buffer, sizeof buffer, fh);
                    fprintf(fw, "%s", buffer);
                }
            }else{
                fgets(buffer, sizeof buffer, fh);
                fgets(buferID, sizeof buferID, fh);
                //printf("ID: %s\n", id);
                //printf("BUFFER: %s\n", buferID);
                if(strcmp(buferID, id) != 0){
                    //printf("BUFFER: %s\n", buferID);
                    z++;
                    fgets(buffer, sizeof buffer, fh);
                    fgets(buffer, sizeof buffer, fh);
                    fgets(buffer, sizeof buffer, fh);
                    fgets(buffer, sizeof buffer, fh);
                    continue;
                }else{
                    z++;
                    fprintf(fw, "%s", buffer);
                    printf("ID: %s\n", id);
                    printf("BUFFER: %s\n", buferID);
                    fprintf(fw, "%s", buferID);
                    fgets(buffer, sizeof buffer, fh);
                    fprintf(fw, "%s", buffer);
                    fgets(buffer, sizeof buffer, fh);
                    fprintf(fw, "%s", buffer);
                    fgets(buffer, sizeof buffer, fh);
                    fprintf(fw, "%s", buffer);
                    fgets(buffer, sizeof buffer, fh);
                    fprintf(fw, "%s", buffer);
                }
            }
            j=0; ctr=0;
            fgets(bigString, sizeof bigString, fh);
            char newString[800][800];
            for(i = 0; i < 800; i++){
                for(j = 0; j < 800; j++){
                    newString[i][j] = '\0';
                }
            }
            j=0; i = 0;
            while(bigString[i] != '\0')
            {
                // if space or NULL found, assign NULL into newString[ctr]
                if(bigString[i]== ' ')
                {
                    newString[ctr][j]='\040';
                    ctr++;  //for next word
                    j=0;    //for next word, init index to 0
                }
                else if(isalpha(bigString[i]) == 0){
                    newString[ctr][j]='\040';
                    ctr++;  //for next word
                    j=0;    //for next word, init index to 0
                }
                else
                {
                    newString[ctr][j]=bigString[i];
                    j++;
                }
                i++;
            }
            for(i=0;i < ctr; i++){
                if(strcmp(newString[i], " ") != 0 || strcmp(newString[i], "the") != 0 || strcmp(newString[i], "a") != 0 || strcmp(newString[i], "and") != 0 || strcmp(newString[i], "of") != 0 || 
                strcmp(newString[i], "when") != 0 || strcmp(newString[i], "with") != 0 || strcmp(newString[i], "to") != 0 || strcmp(newString[i], "that") != 0 || strcmp(newString[i], "then") != 0){
                    fprintf(fw, "%s", newString[i]);
                }
            }

            fprintf(fw, "\n");
            
            if(feof(fh)){
                break;
            }
        }
        if(feof(ids)){
            break;
        }
        fclose(fh);

    }
}
/*
* cleanFile:
*   IN:  File Handle fr, File Handle fw
*   OUT: A text file with common words removed from the 
*        list of words in the abstract.
*/
void cleanFile(FILE* fr, FILE* fw){
    int c, i;
    int z = 0;
    char word[200];
    while((c = fgetc(fr)) != EOF){
        word[0] = c;
        printf("z = %d\n", z);
        fgets(word+1, sizeof(word), fr);
        if((isalpha(c) != 0 || word[0] == '\n') && strcasecmp(word, "the\n") != 0 && strcasecmp(word, "and\n") != 0 && strcasecmp(word, "their\n") != 0 && strlen(word) != 2 &&
        strcasecmp(word, "for\n") != 0 && strcasecmp(word, "is\n") != 0 && strcasecmp(word, "of\n") != 0 && strcasecmp(word, "are\n") != 0 && strcasecmp(word, "at\n") != 0 &&
        strcasecmp(word, "in\n") != 0 && strcasecmp(word, "can\n") != 0 && strcasecmp(word, "on\n") != 0 && strcasecmp(word, "for\n") != 0 && strcasecmp(word, "well\n") != 0 
        && strcasecmp(word, "its\n") != 0 && strcasecmp(word, "to\n") != 0){
            fprintf(fw, "%s", word);
        }else{
            printf("%s", word);
        }
        z++;
        if(feof(fr)){
            break;
        }
        for(i = 0;  i < 200; i++){
            word[i] = '\0';
        }
    }
}
/*
* cleanFile:
*   IN:  NULL
*   OUT: From the file of words and abstracts,
*        a text file containing the word and the IDS
*        for the papers the hold that word in the abstract.
*/
void buildTree(){
    int c,z, count;
    z = 0;
    char buffer[100];
    FILE* fr = fopen("arXiv/FinalList.txt", "r");
    FILE* fr2 = fopen("arXiv/test.txt", "r");
    FILE* fw = fopen("arXiv/BST.txt", "w");
    keyword_node* ROOT = NULL;
    while((c = fgetc(fr)) != EOF){
        printf("z = %d\n", z);
        buffer[0] = c;
        fgets(buffer+1, sizeof buffer, fr);
        //printf("%s\n", buffer);
        insert(ROOT, buffer);
        int wordcnt = 0;
        int realcount = 0;
        count = 0;
        FILE* fr2 = fopen("arXiv/test.txt", "r");
        /*
        * Actual bounds are 1000, but for now we will use the first 10 documents
        */
        while(count < 100){
            //printf("%s\n", buffer);
            docnode* n = NULL;
            n = calloc(1, sizeof(docnode));
            nodeComp(fr2, count, n);
            //printf("%s", n->id);
            keyword_node * TEMPROOT = NULL;
            /*
            * Build tree with the words in the abstract
            */
            int i;
            for (i = 0; i < 256*n->wordCount && n->abstract[i]; i++) {
                TEMPROOT = insert(TEMPROOT, n->abstract[i]);
                //printf("N ABSTRACT: %s\n", n->abstract[i]);
                append(TEMPROOT->MASTER, atof(n->id));
                wordcnt++;
            }
            /*
            * Remove edge cases
            */
            int j;
            for(j = 0; isalpha(buffer[j]) != 0; j++){
                realcount++;
            }
            if(count == 0 && strlen(buffer) != realcount){
                buffer[strlen(buffer) - 1] = '\0';
            }
            /*
            * Find Word
            */
            keyword_node * test = find(TEMPROOT, buffer);
            //printf("Word : %s \n", test->keyword);
            if(test->keyword){
                append(test->MASTER, atof(n->id));        
                fprintf(fw,"%f ", test->MASTER->tail->ID);
            }
            free(n->abstract);
            free(n);
            clear_tree(TEMPROOT);
            //printf("%d \n", count);
            count++;
            realcount = 0;
        
        }
        fprintf(fw, "to %s\n", buffer);
        in_order(ROOT);
        puts("");
        clear_tree(ROOT);
        fclose(fr2);
        //ROOT = insert(ROOT, buffer);

        //keyword_node * test = find(ROOT, buffer);
        //append(test->MASTER, 0);
        //printf("-> %f to %s\n", test->MASTER->tail->ID, test->keyword);
        if(feof(fr)){
            break;
        }
        z++;
    }
    
       
    fclose(fr);
}
/*
* Flow of operations:
*   Start:
*   Select the number of documents to compile.
*   |
*   '->Compute the page rank for each document.
*      |
*      '->Strip the words of the given abstracts, filter,
*         and write them to a text file. 
*         |
*         '->Run the search and return in order of their page rank.
*            |
*            '->Fin.
*/
int main (int argc, char ** argv) {

    MPI_Init(&argc, &argv);
    MPI_Comm world = MPI_COMM_WORLD;

    int worldSize, myRank;
    MPI_Comm_size(world, &worldSize);
    MPI_Comm_rank(world, &myRank);

    csr_matrix * Graph;
    matrix hub_vect, auth_vect;

    matrix * adj = (matrix*) malloc(sizeof(matrix));
    int N = 100;
    initMatrix(adj, N, N);

    file_load_adj("arxiv-citations.txt", N, adj);
    //printMatrix(adj);
    puts("");

    Graph = (csr_matrix*) malloc(sizeof(csr_matrix));
    puts("----------------------------");
    to_csr(adj, Graph);
    // test_print(Graph);
    puts("----------------------------");
    //print_csr(Graph);

    matrix result;
    init_vector(&result, NULL, Graph->nvertices);

    page_rank(Graph, &result);

    int z;
    for(z = 0; z < Graph->nvertices; z++) {

        printf("%f ", result.data[z]);

    }
    puts("");






    // MPI_Finalize();
    

    return 0;
}