#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>
#include "list.h"  // linked list
#include "KWBST.h" // binary search tree for keywords
#include "mpi.h"

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
void nodeComp(FILE* fh, int z, docnode* p){
    char bigString[360000];
    char buffer[40000];
    char title[7000];
    char trash[50];
    char idBuffer[50];
    int i,j,ctr,k, x;
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
int main(int argc, char** argv) {
        
        MPI_Init(&argc, &argv);

        // This constant gets set by the MPI lib
        MPI_Comm world = MPI_COMM_WORLD;

        // worldSize will be the total number of
        // nodes in the communicator.
        // myRank will be the nodes id within that
        // communicator.
        int worldSize, myRank;

        MPI_Comm_size(world, &worldSize);
        MPI_Comm_rank(world, &myRank);
        buildTree(world, worldSize, myRank);
        
        //MPI_File_open(world, "datafile",
        //MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

        //MPI_File_read_at(fh, offset, nums, N, MPI_DOUBLE, MPI_STATUS_IGNORE);




        MPI_Finalize();
        return 0;
}