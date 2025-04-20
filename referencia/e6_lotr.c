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

#define NUM_CHARS 256
int letter_start[NUM_CHARS] = {0};
int letter_end[NUM_CHARS] = {0};

/* Esse algoritmo é meio mágico, então tome um cuidado especial quando ler.
Ele varre linearmente a lista de palavras no dicionário e usa duas
variáveis para manter o começo e fim de cada região.

Esse algoritmo tem dois estados;
 - Quando curr_char == '\0', isto é, quando ele ta resetado
 - Quando curr_char != '\0', isto é, quando ele aponta para algum caractere

Veja que quando o algoritmo inicia, temos curr_char == '\0'
e, a partir do momento que sabemos qual o caractere que estamos lendo,
atribuimos `curr_char = c;`

Também note que os limites das regiões são assimétricas,
se uma palavra começa com a letra 'a', então ela está na região:
          0 <= i < 720
Isto é, se o letter_end de 'a' é 720, então a última palavra
que começa com 'a' tem índice 719.

Para ter certeza de como o algoritmo funciona, execute ele usando
papel e lápis, ou enfie um `printf` no meio do loop e deixe o computador
te falar oq ele ta fazendo.
*/
void compute_ranges(void) {
  int i = 0;
  char curr_char = '\0';
  while (i < NUM_WORDS) {
    char c = dict[i][0]; // pegamos a primeira letra da palavra
    if (curr_char == '\0') {
      curr_char = c;
    }
    if (c != curr_char) {
      letter_end[(int)curr_char] = i;
      letter_start[(int)c] = i;
      curr_char = '\0';
    }
    // pode usar esse print pra debugar, por exemplo:
    // printf("curr_char: %c, i: %d, palavra: %s\n", curr_char, i, dict[i]);
    i++;
  }
  // letter_end['z'] é 10000, como já sabemos.
  letter_end[(int)curr_char] = i;
}

/* É sempre bom fazer umas funções auxiliares para ajudar a gente a debugar
o programa. Eu não escrevi a função compute_ranges certo de primeiro,
tive que testar varias vezes e verificar o output.
*/
void print_ranges(void) {
  int i = 'a';
  while (i <= 'z') {
    printf("%c, start: %d, end: %d\n", i, letter_start[i], letter_end[i]);
    i++;
  }
}

/* Veja que mudamos poucas coisas nessa função, apenas adicionamos
as variáveis `c`, `start`, `end` e fizemos o loop começar em `start`
e terminar em `end`.
*/
bool spellcheck(char* word, int length) {
  char c = word[0];
  int start = letter_start[(int)c];
  int end = letter_end[(int)c];

  int i = start;
  while (i < end) {
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
  compute_ranges();
  // print_ranges(); // usa isso pra debugar, se quiser
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
