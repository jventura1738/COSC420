#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "KWBST.h"
#include "wlist.h"
typedef struct docnode{
    char id[30];
    char title[300];
    char authors[30000];
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
void writeWords(FILE* fh, FILE* fw, int z){
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
}
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
int main(){
    FILE* fh = fopen("arXiv/Words.txt", "r");
    FILE* fw = fopen("arXiv/test.txt", "w");
    //NEED TO MAKE FILE FOR WRITING
    int c, z;
    z = 0;
    //while(z < 1000){
        //writeWords(fh, fw, z);
        //z++;
    //}
    
    cleanFile(fh, fw);
    return 0;
}