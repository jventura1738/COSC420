/*
 * Justin's Script File COSC420
 * arXiv Search Engine 'Ring'
 * 
 * This file contains preprocessing
 * methods that will be used to prepare
 * the files to be used in the actual
 * program.
 * 
 * This is made for Blaine to use.
*/

#ifndef PREPROCESS_H
#define PREPROCESS_H

/*
 * CITATION PRE-PROCESS METHOD FOR BLAINE
 * 
 * This function will take the first N
 * papers in the 'arxiv-citations.txt'
 * data file, and store them in a new
 * file with a format that Blaine can 
 * use in his part of the preprocessing.
 * 
 * Given: <citations-fn.txt>
 * Writes into: 'arxiv-cit-preproc.txt'
*/
void format_citations_preprocess(char * filename, int N) {

  // Attempt to open the file.
  FILE * fh = fopen(filename, "r");
  if (!fh) {

    printf("[file_load_adj] -> Unable to open %s.\n", filename);
    exit(EXIT_FAILURE);

  }
  else {

    // Prepare to filter the file.
    int MAX_BYTES = 25;
    int num_papers = 0;
    char * line = malloc(MAX_BYTES);
    char * prev = malloc(MAX_BYTES);
    strcpy(prev, "+++++\n");

    // This will be the file that is written to.
    FILE * new_file = fopen("arXiv/IDs.txt", "w");

    while (fgets(line, MAX_BYTES, fh) && num_papers < N) {

      if (strcmp(prev, "+++++\n") == 0) {

        fputs(line, new_file);
        num_papers++;

      }

      strcpy(prev, line);

    }

    free(line);
    free(prev);
    fclose(new_file);
  }
  
  fclose(fh);

}

#endif