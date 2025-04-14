/* Esse código é a mesma coisa que `e2_words.c`,
exceto pela adição da função `remove_special`, `is_special_char`
e `fmt_print`.
*/
#include <stdio.h>
#include <stdbool.h>

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

/* Poderiamos ter colocado esse código dentro de `remove_special`,
mas mantendo ele aqui fora, podemos ver claramente o que queremos
dizer por um caractere ser "especial". Isso é apenas uma questão de
estilo.
*/
bool is_special_char(char c) {
  return c == '\'' || c == '-';
}

/* Esse algoritmo copia do vetor `s` pro vetor `dest`
cada caractere que falha a condição `is_special_char`,
isto é, ele copia todos os caracteres diferentes de `'\''` e `'-'`.

Veja que poderiamos ter escrito a condição:
  is_special_char(c) == false
como:
  !is_special_char(c)
mas escolhemos escrever desse jeito por estilo,
já que o operador lógico de negação `!`
as vezes é muito dificil de ver (tente debugar
esse código cansada, as 23 da noite e eu duvido que você
vai notar esse caracteres minúsculos)
*/
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

/* Extraimos essa função do meio da `main` pq
assim o código fica mais limpo.

Veja que eu to aplicando `remove_special` com os argumentos
`dest` e `s` apontando pra mesma string. Rode o algoritmo `remove_special`
no papel em palavras simples e bonitas tipo "anna-gama" e veja o porquê
podemos fazer isso.

É inteiramente possível usar outro vetor, sem ser o `word`, como o `dest`,
mas podemos diminuir o uso de memória assim. Isso não importa muito nesse contexto,
pq nossos vetores tem apenas 256 bytes e seu PC provavelmente tem uns 2^32 bytes.
*/
void fmt_print(char* word, int length) {
  lower_word(word, length);
  int new_len = remove_special(word, word, length);
  // pode acontecer de uma palavra ser composta apenas por caracteres especiais
  if (new_len > 0) {
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
      word_index = 0; // de qualquer modo, resetamos o contador
    }
    
    c = getchar();
  }
}
