/*
 * Justin Ventura COSC420
 * arXiv Search Engine: interface file.
 * 
 * This file include a bunch of useful
 * functions to be called from the main.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INTERFACE_H
#define INTERFACE_H

#define BYTE_LIMIT 32

/*
 * GET USER INPUT FUNCTION
 * 
 * ARGS:
 * - [int*] word_count: this should be
 * passed by address from the client in
 * order to be modified to fit the length
 * of the returned char*[].
 * 
 * RETURNS:
 * - [char**] result_ptr: this will be
 * an array of words that the client has
 * entered such that result_ptr will be
 * a char*[word_count].
 * 
 * Gets the user input, and if there are
 * more than one words, it will split the
 * the words into an array of words.
 * 
 * INPUT FORMAT:
 *  - 1 space at most beween words.
 *  - no symbols.
 * 
 * Example:
 * word word word word
*/
char ** get_user_input(int * word_count) {

  // Read user input.
  char * input = (char*) malloc(BYTE_LIMIT);
  printf("--> ");
  scanf("%[^\n]%*c", input);
  printf("%s\n", input);

  // For tokenizing.
  int num_words = 1;
  int i = 0;
  int j = 0;
  int k = 0;
  while (input[i]) {

    if (input[i] == ' ') {

      num_words++;

    }

    i++;

  }

  // Sizes for each word.
  int word_sizes[num_words];

  // Still tokenizing.
  i = 0;
  while (input[i]) {

    if (input[i] == ' ') {

      word_sizes[j] = k;
      printf("%d\n", word_sizes[j]);
      j++;
      k = 0;

    } 
    else {

      k++;

    }

    i++;

  }
  word_sizes[j] = k;
  j = 0;

  // Pointer to the words.
  char ** result_ptr = (char**) malloc(num_words);
  char * delim = " ";
  char * token = strtok(input, delim);

  while (token) {

    result_ptr[j] = (char*) malloc(word_sizes[j] * sizeof(char));
    printf("token: %s, length: %d\n", token, word_sizes[j]);
    strcpy(result_ptr[j], token);
    token = strtok(NULL, delim);
    j++;

  }
  puts("");

  word_count = &num_words;
  return result_ptr;

}

#endif