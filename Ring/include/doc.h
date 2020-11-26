// #include <stdlib.h>
// #include <stdio.h>
// #include <cstring>

// #ifndef DOC
// #define DOC

// #define MAX_BYTES 25

// typedef struct Document {

//   char id[MAX_BYTES];

//   double * hub_score;
//   double * auth_score;
//   double * page_rank;

// } doc;

// void print_document(struct Document* d) {

//   printf("%s\n%s\n%s\n%s\n", d->id, d->title, d->authors, d->abstract);

// }

// void create_new_document(struct Document* d,
//                     char *_id,
//                     char* _title,
//                     char* _authors,
//                     //int _authornum,
//                     char* _abstract) {
//   //assert(strlen(_id) < 41);
//   // d->id = _id;
//   strcpy(d->id, _id);
//   // d->title = _title;
//   strcpy(d->title, _title);
//   // d->authors = _authors;
//   strcpy(d->authors, _authors);
//   //d->authornum = _authornum;
//   // d->abstract = _abstract;
//   strcpy(d->abstract, _abstract);
// }
// void set_document_values(struct Document* d,
//                     int matrixindex,
//                     float hs,
//                     float as,
//                     float pr) {

//   d->hubscore = hs;
//   d->authscore = as;
//   d->pagerank = pr;
// }
// void create_document(struct Document* d,
//                     char *_id,
//                     char* _title,
//                     char* _authors,
//                     //int _authornum,
//                     char* _abstract,

//                     int matrixindex,
//                     float hs,
//                     float as,
//                     float pr){
//   create_new_document(d, _id, _title, _authors, /*_authornum,*/ _abstract);
//   set_document_values(d, matrixindex, hs, as, pr);
// }

// #endif

// #ifndef DOCINDEX
// #define DOCINDEX

// typedef struct DocIndex {

//   char* doc_id;
//   struct Document* doc;
//   int matrix_index;

// } doc_idx;

// void print_DocIndex(const doc_idx* di) {

//   printf("%s: %d\n", di->doc->id, di->matrix_index);

// }

// void create_DocIndex(doc_idx ** ptr, struct Document* d, int index) {

//   *ptr = (doc_idx*)malloc(sizeof(DocIndex));
//   (*ptr)->matrix_index = index;
//   (*ptr)->doc = d;

// }
// #endif