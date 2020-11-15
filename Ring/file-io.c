#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void rw(FILE* fh, FILE* fw, int z){
    char bigString[640000];
    char buffer[100000];
    int i,j,ctr,k, x;
    if(z == 0){
         for(x  = 0; x < 4; x++){
            fgets(buffer, sizeof buffer, fh);
            //fprintf(fw, "%s", buffer);
        }
    }else{
        for(x  = 0; x < 5; x++){
            fgets(buffer, sizeof buffer, fh);  
            //fprintf(fw, "%s", buffer); 
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
    //fprintf(fw, "%d", ctr);
    for(i=0;i < ctr; i++){
        //printf("%s",newString[i]);
        if(strcmp(newString[i], " ") != 0 || strcmp(newString[i], "the") != 0 || strcmp(newString[i], "a") != 0 || strcmp(newString[i], "and") != 0 || strcmp(newString[i], "of") != 0 || 
        strcmp(newString[i], "when") != 0 || strcmp(newString[i], "with") != 0 || strcmp(newString[i], "to") != 0 || strcmp(newString[i], "that") != 0 || strcmp(newString[i], "then") != 0){
            fprintf(fw, "%s\n", newString[i]);
        }
    }
    fprintf(fw, "\n");
}
int main(){
    FILE* fh;
    FILE* fw = fopen("arXiv/StructTest.txt", "w");
    
    fh = fopen("arXiv/Alphabetized.txt", "r");
    int c, z, counter;
    z = 0;
    while((c = fgetc(fh)) != EOF){
        printf("z = %d\n", z);
        rw(fh, fw, z);
        z++;
        if(feof(fh)){
            break;
        }

    }
    fclose(fh);
    fclose(fw);
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