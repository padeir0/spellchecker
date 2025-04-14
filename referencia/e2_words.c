#include <stdio.h>
#include <stdbool.h> // é daqui que vem o tipo "bool"

/* Essa função verifica se o caractere é o que consideramos uma "palavra",
nesse caso, como `c` é um número, podemos olhar a tablela ASCII e verificar
somente se `c` está nas regiões que consideramos ser caracteres de palavras.
A expressão:
  (c >= 'a' && c <= 'z')
Pode ser lida como: "c está entre o caractere 'a' e 'z'".
Lembre-se: `&&` é conjunção lógica e `||` é disjunção lógica.
*/
bool is_word_char(char c) {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         c == '\'' || c == '-';
}

/* Essa função pega qualquer caractere e retorna ele minúsculo.
Só realmente precisamos fazer algo se a letra for maiuscula, por
isso verificamos:
  (c >= 'A' && c <= 'Z')
Quando isso é verdade, fazemos uma translação de `c`
por `'a'-'A'`, que da um slide na tabela ascii e faz
corresponder: 'A' com 'a', 'B' com 'b', etc.

Isso é um hack, não se preocupe se não pegou isso logo de primeira,
seria igualmente possivel criar uma condição pra cada letra:
  if (c == `A`) return 'a';
  ...
  else if (c == 'Z') return 'z';
Usando esse hack o código sai mais fácil.
*/
char lower_char(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a'-'A');
  }
  return c;
}

/* Aqui a gente aplica `lower_char` em cada caractere de uma string,
vê que eu peço o tamanho da string explicitamente com `length` ao invés
de pedir que a palavra termine com NULL (`\0`), como é usual em C.
*/
void lower_word(char* word, int length) {
  int i = 0;
  while (i < length) {
    word[i] = lower_char(word[i]);
    i++;
  }
}

/* Esse código popula uma array de caracteres `word` com as palavras.
Nós assumimos que as palavras são menores que 256 letras, não precisamos
se preocupar muito com isso agora.

Usamos a função `getchar` pra pegar os caracteres do STDIN, portanto, para
testar esse programa, podes rodar `cat ../iamgroot.txt | run e2_words.c`.
A função `getchar` retorna `EOF` quando não tem mais nada pra ler, EOF quer
dizer "End of File".

O algoritmo basicamente pega caracteres que julga ser parte de palavras do STDIN,
até que acha um caractere que não pode ser de uma palavra. Quando isso acontece,
se tivermos escrito alguma coisa em `word`, printamos na tela a palavra em minusculas.

Escrevemos as coisas em `word` usando a variável auxiliar `word_index`, que é incrementada
sempre que um caractere é escrito em `word`, e resetada pra zero `0` quando não precisamos
mais do conteúdo dentro de `word`, ie, logo após imprimirmos na tela.
*/
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
        lower_word(word, word_index);
        printf("%.*s\n", word_index, word);
      }
      word_index = 0; // de qualquer modo, resetamos o contador
    }
    
    c = getchar();
  }
}
