#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Nós incluimos o dicionário aqui ao invés de puxar os valores de um arquivo,
   desse jeito, não precisamos nos preocupar com toda burocracia de abrir arquivos.
*/
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

bool spellcheck(char* word, int length) {
  int i = 0;
  while (i < NUM_WORDS) {
    char* dict_word = dict[i];
    int dict_word_length = (int)strlen(dict_word);
    if (dict_word_length == length &&
        strncmp(dict_word, word, (unsigned)length) == 0) {
      return true;
    }
    i++;
  }
  return false;
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
