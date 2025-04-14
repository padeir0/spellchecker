/* Aqui finalmente implementamos a função `spellcheck`
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

#define NUM_WORDS 3
char* dict[NUM_WORDS] = {
  "i",
  "am",
  "groot",
};

/* Essa função simplesmente verifica se `word`
está em `dict`. Fazemos isso com uma busca linear, ie,
verificamos palavra por palavra do dicionário, tentando
verificar se as palavras são iguais.
Atenção especial em:
  if (dict_word_length == length &&
      strncmp(dict_word, word, length) == 0) {
    return true;
  }
Se `dict_word_length != length` então as palavras são diferentes.
Se os comprimentos são diferentes, a segunda parte da condição,
ie, `strncmp(dict_word, word, length) == 0`, nem mesmo executa.
Por outro lado, se `dict_word_length == length`,
então as palavras tem o mesmo tamanho e podemos utilizar tanto `length`
ou `dict_word_length` na chamada de função.
*/
bool spellcheck(char* word, int length) {
  int i = 0;
  while (i < NUM_WORDS) {
    char* dict_word = dict[i];
    int dict_word_length = strlen(dict_word);
    if (dict_word_length == length &&
        strncmp(dict_word, word, length) == 0) {
      return true;
    }
    i++;
  }
  return false;
}

void fmt_print(char* word, int length) {
  lower_word(word, length);
  int new_len = remove_special(word, word, length);
  /* Por questão de estilo, fazemos um _early return_ quando a
    palavra tem tamanho nulo. Essa técnica é muito útil para refatorar
    o código.
  */ 
  if (new_len == 0) {
    return;
  }
  /* Se a palavra não existe no dicionário, printamos ela na tela.
  */
  if (spellcheck(word, length) == false) {
    printf("%.*s\n", new_len, word);
  }
}

int main(void) {
  char word[256];
  int c = getchar();
  int word_index = 0;
  while (c != EOF) {
    if (is_word_char(c)) {
      word[word_index] = c;
      word_index++;
    } else {
      if (word_index > 0) {
        fmt_print(word, word_index);
      }
      word_index = 0;
    }
    
    c = getchar();
  }
}
