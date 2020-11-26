#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#ifndef DOC
#define DOC

#define MAXDOCIDLEN 40
#define MAXDOCTITLELEN 300
#define MAXDOCAUTHORSLEN 200
#define MAXDOCABSTRACTLEN 2000

struct Document {
    char id[MAXDOCIDLEN];
    char title[MAXDOCTITLELEN];
    char authors[MAXDOCAUTHORSLEN];
    char abstract[MAXDOCABSTRACTLEN];
    //int authornum;

    int matrixindex;
    float hubscore;
    float authscore;
    float pagerank;
};

void print_document(struct Document* d) {

  printf("%s\n%s\n%s\n%s\n", d->id, d->title, d->authors, d->abstract);

}

void create_new_document(struct Document* d,
                    char *_id,
                    char* _title,
                    char* _authors,
                    //int _authornum,
                    char* _abstract) {
  //assert(strlen(_id) < 41);
  // d->id = _id;
  strcpy(d->id, _id);
  // d->title = _title;
  strcpy(d->title, _title);
  // d->authors = _authors;
  strcpy(d->authors, _authors);
  //d->authornum = _authornum;
  // d->abstract = _abstract;
  strcpy(d->abstract, _abstract);
}
void set_document_values(struct Document* d,
                    int matrixindex,
                    float hs,
                    float as,
                    float pr) {

  d->hubscore = hs;
  d->authscore = as;
  d->pagerank = pr;
}
void create_document(struct Document* d,
                    char *_id,
                    char* _title,
                    char* _authors,
                    //int _authornum,
                    char* _abstract,

                    int matrixindex,
                    float hs,
                    float as,
                    float pr){
  create_new_document(d, _id, _title, _authors, /*_authornum,*/ _abstract);
  set_document_values(d, matrixindex, hs, as, pr);
}
// #include <mpi.h>
// int process_to_doc(struct Document* d, char* input, int len) {
//   int cnt = 0;
//   char* info[4];

//   assert(input[0] != '\n');
//   int last = 0; int next;
//   //printf("%s\n", input);
//   int rank;
//   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//   for(next = last+1; next < len && cnt < 4; next++) {
//     if(input[next] == '\n' || input[next] == '\0') {
//       info[cnt] = malloc((next-last)*sizeof(char));
//       memcpy(info[cnt], input+last, next-last);
//       info[cnt][next] = '\0';
//       next++;
//       last = next;
//       cnt++;
//     }
//   }
//   next+=6;
//   assert(cnt==4);
//   //printf("%c\n", info[0][9]);
//   //printf("%s\n", info[0]);
//   create_new_document(d, info[0], info[1], info[2], info[3]);
//   return next;
// }
#endif

#ifndef DOCINDEX
#define DOCINDEX

typedef struct DocIndex {

  char* doc_id;
  struct Document* doc;
  int matrix_index;

} doc_idx;

void print_DocIndex(const doc_idx* di) {

  printf("%s: %d\n", di->doc->id, di->matrix_index);

}

void create_DocIndex(doc_idx ** ptr, struct Document* d, int index) {

  *ptr = (doc_idx*)malloc(sizeof(DocIndex));
  (*ptr)->matrix_index = index;
  (*ptr)->doc = d;

}
#endif