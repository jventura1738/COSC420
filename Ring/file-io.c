#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "KWBST.h"
#include "wlist.h"
typedef struct docnode{
    char id[30];
    char title[300];
    char authors[5000];
    int wordCount;
    char** abstract;

} docnode;

void rw(FILE* fh, FILE* fw, int z, docnode p){
    char bigString[360000];
    char newString[600][600];
    char buffer[30000];
    int i,j,ctr,k, x;
    if(z == 0){
         for(x  = 0; x < 3; x++){
            fgets(buffer, sizeof buffer, fh);
            fprintf(fw, "%s", buffer);
        }
    }else{
        for(x  = 0; x < 4; x++){
            fgets(buffer, sizeof buffer, fh);  
            fprintf(fw, "%s", buffer); 
        }
    }

        
    fgets(bigString, sizeof bigString, fh);

    j=0; ctr=0;
    for(i=0;i<=(strlen(bigString));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(bigString[i]==' '|| bigString[i]=='\0')
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
    //puts("");
    //printf("Strings or words after split by space are :\n");
    for(i=0;i < ctr;i++){

    }
    char temp[360000];

    for(j=0;j<=i;j++){
        for(k=j+1;k<=i;k++){
            if(strcasecmp(newString[j],newString[k]) > 0){
                strcpy(temp,newString[j]);
                strcpy(newString[j],newString[k]);
                strcpy(newString[k],temp);
            }
        }
    }
    fprintf(fw, "%d", ctr);
    for(i=0;i < ctr;i++){
        //printf(" %s ",newString[i]);
        fprintf(fw, " %s ", newString[i]);
    }
    fprintf(fw, "\n");
}

void nodeComp(FILE* fh, int z, docnode* p){
    char bigString[360000];
    char buffer[30000];
    char idBuffer[50];
    int i,j,ctr,k, x;
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
        fgets(buffer, sizeof buffer, fh);
        fgets(buffer, sizeof buffer, fh);
        strcpy(p->id, buffer);
        fgets(buffer, sizeof buffer, fh);
        strcpy(p->title, buffer);
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
    //puts("");
    //printf("Strings or words after split by space are :\n");
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
    for(i=0;i < 256 && p->abstract[i];i++){
        printf(" %s ", p->abstract[i]);
    }
    puts("");
}
void writeWords(FILE* fh, FILE* fw, int z){
    docnode* n = NULL;
    n = calloc(1, sizeof(docnode));
    nodeComp(fh,z, n);
    printN(n);

    keyword_node * ROOT = NULL;

    printf("%s\n", n->id);
    // //printf("%f\n", atof(n->id));

    int i;
    // int count = 0;
    // for (i = 0; i < 256 && n->abstract[i]; i++) {
    //     ROOT = insert(ROOT, n->abstract[i]);
    //     append(ROOT->MASTER, atof(n->id));
    //     count++;
    // }
    
    // //in_order(ROOT);
    // //puts("");
    // clear_tree(ROOT);
    //printN(n);
    
    wmaster_node* master = winit_master();
    for(i = 0; i < 256; i++){
        if(n->abstract[i][0] ==' '|| n->abstract[i][0] =='\0' || isalpha(n->abstract[i][0]) == 0){
            continue;
        }
        wappend(master, n->abstract[i]);
        fprintf(fw, "%s\n", n->abstract[i]);
        printf("%s\n", n->abstract[i]);
    }
    //wprint(master);
    free(master);
    for (i = 0; i < 256; i++) {

        free(n->abstract[i]);

    }

    //free(n->abstract);
    //free(n);
}
int main(){
    FILE* fh;
    FILE* fw = fopen("arXiv/StructTest.txt", "w");
    //NEED TO MAKE FILE FOR WRITING
    fh = fopen("arXiv/Alphabetized.txt", "r");
    int c, z;
    z = 0;
    //writeWords(fh, fw, z);
    //z++;
    //writeWords(fh, fw, z);
    while((c = fgetc(fh)) != EOF){
        printf("z = %d\n", z);
        writeWords(fh, fw, z);
        z++;
        if(feof(fh)){
            break;
        }
    
    }
    
    return 0;
}

/* while((c = fgetc(fh)) != EOF){
        printf("z = %d\n", z);
        rw(fh, fw, z);
        z++;
        if(feof(fh)){
            break;
        }
        
    } */