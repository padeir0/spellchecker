#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "dict_10k.h"

bool is_word_char(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         c == '\'' || c == '-';
}

char lower_char(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a'-'A');
  }
  return c;
}

void lower_word(char* word, int length) {
  int i = 0;
  while (i < length) {
    word[i] = lower_char(word[i]);
    i++;
  }
}

bool is_special_char(char c) {
  return c == '\'' || c == '-';
}

int remove_special(char* dest, char* s, int length) {
  int i = 0;
  int written = 0;
  while (i < length) {
    char c = s[i];
    if (is_special_char(c) == false) {
      dest[written] = c;
      written++;
    }
    i++;
  }
  return written;
}

int minimum(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

int compare(char* A, int A_size, char* B, int B_size) {
  int min_length = minimum(A_size, B_size);
  int result = strncmp(A, B, (unsigned)min_length);

  if (result == 0) {
    // Definimos que, se duas strings são iguais até certo ponto,
    // a maior string é aquela com maior tamanho.
    if (A_size < B_size) {
      return -1;
    } else if (A_size > B_size) {
      return 1;
    }
    return 0;
  }
  return result;
}

bool binsearch(char* word, int length, int min, int max) {
  if (min > max) {
    return false;
  }

  int middle = (min+max)/2;
  char* middle_word = dict[middle];
  int middle_word_length = (int)strlen(middle_word);

  int result = compare(word, length, middle_word, middle_word_length);

  if (result == 0) {       // word == middle_word
    return true;
  } else if (result < 0) { // word < middle_word
    return binsearch(word, length, min, middle-1);
  } else {                 // middle_word < word
    return binsearch(word, length, middle+1, max);
  }
}

bool spellcheck(char* word, int length) {
  return binsearch(word, length, 0, NUM_WORDS);
}

void fmt_print(char* word, int length) {
  lower_word(word, length);
  int new_len = remove_special(word, word, length);
  if (new_len == 0) {
    return;
  }
  if (spellcheck(word, length) == false) {
    printf("%.*s\n", new_len, word);
  }
}

int main(void) {
  char word[256];
  int input = getchar();
  int word_index = 0;
  while (input != EOF) {
    char c = (char)input;
    if (is_word_char(c)) {
      word[word_index] = c;
      word_index++;
    } else {
      if (word_index > 0) {
        fmt_print(word, word_index);
      }
      word_index = 0;
    }
    
    input = getchar();
  }
}
