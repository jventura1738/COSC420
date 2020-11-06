#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    char* wordBank[] = {"The", "quick", "brown", "Fox"};
    int i;
    for(i = 0; i < 4; i++){
        printf("%s \n", wordBank[i]);
    }
}