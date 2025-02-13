# Spell checker

<details>

<summary>Contents</summary>

 - [Pré-requisitos](#prerequisitos)
 - [Comandos básicos do terminal](#comandosbasicos)
 - [As Etapas](#etapas)
   - [Hello World](#hello)
   - [Requisitos: Básico de C](#req1)
   - [Reconhecendo as palavras](#recwords)
   - [Requisitos: Essencial de C](#req2)
   - [I Am Groot](#groot)
   - [Requisitos: Arquivos](#req3)
   - [5 mil palavras](#cincomil)
   - [Senhor dos Anéis](#lotr)
   - [Busca Binária](#binary)
   - [Expandindo o dicionário](#expand)
   - [Sugestões](#sugest)
   - [Easter Eggs](#easter)
 - [Leitura adicional](#more)

</details>

Você vai aprender a fazer um _spell checker_.
Um programa que vai receber como entrada
um texto, e vai emitir todas as palavras
que ele acha que estão escritas erradas.

Pode parecer bobo, mas não é um problema trivial.
O comando `spell` do sistema UNIX tinha que
fazer exatamente isso, mas, em 1982,
ele precisava rodar em 64KB de memória.

Você vai começar do básico e vai criar programas
cada vez mais sofisticados, até ter algo equivalente
ao `spell` do UNIX.

Se eu te conheço,
você vai gostar de assistir [esse video](https://www.youtube.com/watch?v=tc4ROCJYbm0)
sobre o sistema UNIX.
Nele, você vai ver os autores do livro de C (K&R) que eu te emprestei,
o [Dennis Ritchie](https://en.wikipedia.org/wiki/Dennis_Ritchie)
e o [Brian Kerningham](https://en.wikipedia.org/wiki/Brian_Kernighan).
Também vai ver a lenda do [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson).

Vou divagar só um pouquinho pq eu acho essa história muito legal.
O Ken Thompson era um entusiasta de motores de xadrez. Na
época, nenhuma CPU conseguia ser rápida o suficiente
pra implementar um motor decente. Sabe o que Ken fez?
Ele fez tudo analógico. Criou um monstro do tamanho
de uma mala de viagem, cheia de circuito, um em cima do outro.
Tudo que esse computador analógico fazia era achar o próximo
movimento num jogo de xadrez. O problema? Quando ele tentava
viajar com essa máquina todo mundo achava que era uma
bomba. De saco cheio, uma vez
ele virou pro agente de segurança e falou
"meu filho, a única forma de eu usar isso como uma arma
é se eu jogar essa porra na cabeça de alguém".

## Pré-requisitos <a name="prerequisitos"></a>

A linguagem de programação C foi
criada _especificamente_ para implementar o UNIX,
por consequência, a linguagem é fortemente
atrelada a esse sistema operacional.

Linux é baseado no UNIX, por isso o "x" no final. Na verdade,
o nome original ia ser "Freax", mas sinceramente esse nome é
um lixo e um cara convenceu o Linus Torvalds, criador do linux,
de usar o nome Linus + Unix = Linux. Se tiver curiosa, olha [aqui](https://en.wikipedia.org/wiki/History_of_Linux#Naming).

Anyway, você vai ter que programar dentro de um Linux
pra preservar sua sanidade. Temos três opcões:

 - Usar o [Github Codespaces](https://github.com/codespaces);
 - Instalar [WSL](https://learn.microsoft.com/pt-br/windows/wsl/install) no Windows;
 - Instalar Linux direto na máquina.

O Codespaces, se não estiver lagado e lento, é a opção mais acessível.
O WSL demora um pouco mais pra instalar mas não vai ter problema nenhum
com lag. Instalar Linux direto já é um comprometimento, é melhor começar
pelo WSL e migrar quando estiver segura.

## Comandos básicos do terminal <a name="comandosbasicos"></a>

O terminal é simples, mas demora até você pegar a manha.
Eu vou passar alguns comandos aqui pra você se acostumar.
Essas preliminares são importantes, não pule!

A linguagem padrão dos terminais no Linux é o _bash_.
Abra o terminal WSL e digite o seguinte:

```bash
echo "Hello, Anna!"
```

Nesse caso, dizemos que `echo` é um comando que recebe
o argumento `"Hello, Anna!"`. Tudo que ele faz é emitir
o argumento no terminal de volta.

Praticamente tudo de relevante que você for fazer no bash
vai ter essa mesma cara: um comando seguido de alguns argumentos.

O terminal tem um estado interno que salva qual pasta ele
ta olhando naquele momento.
Pra saber qual diretório você se encontra, usa
o comando `pwd`, sem argumentos. Ele vai imprimir na tela
o caminho do diretório atual.

Um outro comando essencial é o `ls`,
lembre dele e leia ele como "list".
Esse cara lista os arquivos e pastas em um diretório.
Ele aceita alguns argumentos, por exemplo,
`ls -a` lista tudo (leia "list all"),
incluindo arquivos e pastas
que começam com `.`, por exemplo a pasta `.config`.
Você vai ver dois pseudo-diretórios com o `ls -a` que são
importantes: `.` e `..`. O diretório `.` é o diretório atual,
enquanto o `..` é o diretório anterior (ou _parent directory_).

Para mudar o diretório do seu terminal, use o comando `cd`.
Por padrão usar `cd` sem argumentos te leva direto pra sua
pasta de usuário. Executar `cd .` não te leva pra lugar nenhum:
você ta indo pro diretório atual. Executar `cd ..`
te leva pro diretório parente.

Os caminhos (ou _paths_) no linux são bem parecidos com o
do Windows, mas usam `/` ao invés de `\`. Por que caralhos
o Windows usa `\`? Eu não sei, mas é um dos motivos
que eu xingaria o Bill Gates.

Okay, agora você sabe exibir o conteudo de uma pasta,
navegar pelas pastas e descobrir onde você parou.

Agora o comando mais importante de todos: `man`.
Não, esse programa não chama nenhum homem pra te ajudar,
eu tentei. Talvez ele fosse mais util se toda vez que você
invocasse ele, o Linus Torvalds aparecesse de rapel na sua
janela, e depois de cuspir meio milhão de ofensas
(como é classico dele), te ensinasse a mexer nessa jossa
que ele fez.

Pois é mentira: `man` é só abreviação de "manual".
Você pode digitar `man ls` e vai aparecer o manual do
comando `ls`. Tem muita coisa pra cada comando,
não tente gravar, é perda de tempo.
Pra ser sincero, nos tempos
modernos, o `man` deveria só invocar o ChatGPT.

Pra navegar numa pagina de manual, usa as setinhas.
Pra pesquisar, digite `/`, pesquise e use aperta `n` para achar as próximas ocorrências.
Pra sair, digite `q`.

Se não existir uma página de um comando no `man`,
tente passar o argumento `--help`, `-help`, `-h`
ou qualquer uma dessas variações pro comando que
você quer usar. Pro `cd` você escreve `cd --help`.

Quando for usar o ChatGPT, se você quer ajuda com algum comando,
comece o prompt com "Estou usando Linux, em um terminal Bash.
Como faço para fazer ...". O GPT é mestre na linha de comando,
e na maioria dos casos eu recorro a ele.

## As etapas <a name="etapas"></a>

O projeto vai ficar cada vez mais complexo,
e vai ser realizado em etapas.
Cada etapa tem uma recompensa.

Vou sempre listar os capítulos do livro K&R e uns tutoriais
para você seguir antes de usar numa tarefa.
Se tiver dificuldade com qualquer coisa, pode me perguntar,
as vezes eu consigo ajudar.

Passe a limpo todos os exemplos do livro, execute,
tenha certeza que entende tudo antes de continuar. Tirando
a primeira, o resto das etapas não vão conter todo código
do programa, você vai ter que descobrir sozinha como resolver.

Todo problema pode ser quebrado em partes menores,
pra que cada parte seja implementada individualmente.
É por isso que aprender a usar funções é importante:
cada função resolve um pedaço simples do problema.
Entretanto, saber _como_ quebrar o problema requer experiência,
então pode ser que você trave um pouco no começo, mas não se abale:
é normal.

### Hello World <a name="hello"></a>

Agora o objetivo é ter certeza que o ambiente
está pronto pra gente programar.
Precisamos de um compilador, nesse
caso o `gcc` e um editor de texto de sua escolha, pode ser
o VS Code, mas na dúvida tem o `vim`.
Pra sair do `vim`, digite `:q!` e dê enter.
Se por acaso você quiser virar 100% hippie digital, com
um toque leve de masoquismo,
você consegue acessar um tutorial de vim digitando
`vimtutor` na linha de comando.

Coloca isso aqui num arquivo chamado `hello.c`:

```c
#include <stdio.h>

int main()
{
    printf("Hello, World!\n");
}
```

Você pode compilar esse arquivo com o `gcc` executando `gcc hello.c`.
Por padrão, o nome do arquivo executavel é `a.out`. Basta
chamar esse arquivo como se fosse um comando `./a.out`,
que o terminal vai executar e você deve ver um `Hello, World!`
ser impresso.

Queremos o máximo de ajuda do compilador, então ao invés de
escrevermos simplesmente `gcc arquivo.c` para compilar o código,
vamos usar um monte de argumento do `gcc`:

```bash
gcc -Wall -Wextra -Werror -std=c99 hello.c
```

Só pra você saber, caso queira remover um desses argumentos:
 - `-Wall` ativa todas as _warnings_, os avisos que o compilador
pode te dar sobre código possivelmente errado.
 - `-Wextra` ativa ainda mais _warnings_ pq aparentemente "all"
não significa "tudo" no mundo do `gcc`.
 - `-Werror` impede um programa com _warnings_ de ser compilado,
mais especificamente, ele trata "warning as errors".
 - `-std=c99` especifica a versão do C que vamos usar,
C tem várias versões: ansi, C89, C99, C11. É importante
sempre ter uma flag dessa por questões de compatibilidade.
 - `arquivo.c` é o arquivo que queremos compilar.

Escrever isso tudo toda hora é um saco, o ideal é que tenha
alguma forma de automatizar isso, afinal, a gente ta usando
o computador, deixe ele fazer o trabalho pra gente.

Vamos usar um script em Bash para compilar o código e
rodar. Para isso, crie um arquivo `run` na pasta
do projeto e coloque o seguinte script bash:

```bash
#!/bin/bash
# ^ essa primeira linha se chama shebang
# e indica qual interpretador vai rodar esse arquivo

# compila o programa que você pediu
gcc -Wall -Wextra -Werror -ansi -std=c99 "$1" -o "out123"
# roda o programa
./out123
# exclui o binário gerado
rm out123
```

Para tornar esse arquivo executável,
você vai precisar conversar com o Linux.
Execute o comando `chmod +x run`,
e quando vc rodar `ls` na pasta, o arquivo `run`
deve ter mudado de cor. Cor verde no `ls`
geralmente quer dizer que o arquivo é executavel.

Agora podemos executar `./run hello.c`
e o programa vai ser compilado, executado e o binário
vai ser deletado.

### Requisitos: Básico de C <a name="req1"></a>

Você vai precisar aprender C, siga
[esse tutorial](https://www.learn-c.org/) e
faça todos os exercícios da seção "Learn the basics".

Depois disso, passe o olho na introdução e no
primeiro capítulo ("A tutorial introduction")
do K&R.

Se você não tiver entendido funções ainda,
[funções](https://www.w3schools.com/c/c_functions.php),
[funções](https://users.cs.utah.edu/~germain/PPS/Topics/C_Language/c_functions.html)
e [funções](https://www.geeksforgeeks.org/c-functions/).
Veja se algum desses tutoriais te agrada.

### Reconhecendo as palavras <a name="recwords"></a>

Antes de verificar a ortografia das palavras,
é necessário achar as palavras.
Nessa etapa você vai ler o texto como input
e vai imprimir as palavras, uma por linha.

Podemos definir uma palavra como uma
sequência de letras (minusculas ou maiusculas)
misturadas com apostrofes `'` e hifens `-`
e separadas por espaço.

Seu programa vai ter que converter as letras
pra minúsculas antes de imprimir.

Por exemplo:
```
 - That's not what I said!
```
Vai ser separado em:
`That's`, `not`, `what`, `I`, `said`.
E seu programa deve imprimir:

```
that's
not
what
i
said
```

Dicas:
 - O livro do K&R tem um programa para contar
 palavras no primeiro capitulo, você pode começar entendendo como
 ele funciona (seção 1.5.4).
 - Você pode escrever uma função `bool is_word_char(char c)`
 que verifica se um caractere pode ser parte de uma palavra,
 isto é: se ele é uma letra (maiuscula ou minuscula), um apostrofe
 ou um hifen.
 - Caracteres são números e as letras são representadas por números
 adjacentes. Verifique a [tabela ascii](https://www.ime.usp.br/~kellyrb/mac2166_2015/tabela_ascii.html).
 Você pode verificar se um caractere `c`
 é uma letra minuscula usando a expressão `c >= 'a' && c <= 'z'`.
 - Para cada caractere que `is_word_char` retornar verdadeiro,
 você pode preencher uma array global `char word[256];` até
 que algum caractere retorne falso. Assim que isso acontecer,
 esse buffer vai conter sua palavra. Não se esqueça de resetar o
 buffer sempre que terminar de imprimir uma palavra.
 - Para colocar a palavra como minuscula, você pode escrever duas funções:
 `char lower_char(char c)` que pega um único caractere e converte para
 minuscula e
 `void lower_word(char* word)` que toma a sua palavra
 no argumento `word`, transformando cada caractere usando `lower_char`.

### Requisitos: Essencial de C <a name="req2"></a>

Para a próxima etapa, você vai precisar usar alocação dinâmica.
Portanto, faça as seções 
"Pointers", 
"Structures", 
"Function arguments by reference",
"Dynamic allocation" e
"Arrays and Pointers" do [primeiro tutorial](https://www.learn-c.org/).
Dê uma passada de olho no capítulo 4 e 5, e na seção 6.3 e 6.4
do livro K&R.

Como vamos usar dicionários em inglês,
vamos ter que lidar com `'` em palavras
como "can't".
Modifique seu programa para formatar as palavras
e remover os caracteres especiais.
 
Dica:
 - Para remover os caracteres especiais, você pode criar uma função
 genérica `void remove_special(char* dest, char* s)`
 que copia _apenas as letras_ da string `s` e passa pra string `dest`.

### I Am Groot <a name="groot"></a>

Seu dicionário são apenas as palavras "i", "am" e "groot".
Tem um diálogo do filme dos Guardiões no arquivo `iamgroot.txt`.
Seu programa vai ler esse diálogo e imprimir todas as palavras
que não estão no seu dicionário.

Dicas:
 - Você pode representar seu dicionário como uma array global
```c
#define NUM_WORDS 3
char* dict[NUM_WORDS] = {
  "i",
  "am",
  "groot",
}
```
 - Para verificar se uma palavra está no dicionário,
 você pode criar uma função `bool spellcheck(char* word)`
 que verifica se a palavra está no dicionário `dict`
 usando uma _busca linear_. Nesse caso, sua busca linear
 vai ser simplesmente comparar a palavra `word` em sequência
 com cada uma das palavras do dicionário.
 - Tenha certeza de que a palavra está formatada em minusculo
 e sem caracteres especiais antes de fazer a busca.

### Requisitos: Arquivos <a name="req3"></a>"

Você vai ter que usar a função `fopen` da biblioteca `stdio.h`,
pode ler o arquivo todo em memória e depois processar as palavras,
nós temos memória para dar e vender. Você provavelmente vai ter que
usar alocação de memória dinâmica com o `malloc`.

Aprender a lidar com arquivos é necessário,
siga [esse tutorial](https://www.geeksforgeeks.org/basics-file-handling-c/)
e dê uma passada de olho no capítulo 7 do livro do K&R.

### 5 mil palavras <a name="cincomil"></a>

Agora iremos crescer o dicionário, mas colocar
ele como uma array global não vai ser legal.
Ao invés disso, você vai ter que abrir o arquivo
`words_5k.txt` dentro do seu programa e usar
essas palavras para criar seu dicionário.

Deve verificar o mesmo arquivo `iamgroot.txt`
e imprimir as palavras que não estão no dicionário.

Dica:
 - O arquivo `words_5k.txt` tem uma palavra por linha, e essas palavras
 já estão formatadas em minusculo e sem caracteres especiais.
 - Você já sabe que temos 5000 palavras, então pode usar uma array
 global `char* dict[5000];` para colocar elas.

### Senhor dos Anéis <a name="lotr"></a>

As coisas começam a ficar mais complicadas.
O dicionário é o mesmo, mas você vai ter que checar
todo os 6 livros do senhor dos anéis, totalizando 528 mil
palavras.
O livro
do senhor dos anéis se encontra em `LOTR.txt`. Eu preenchi
minuciosamente o texto com vários erros de ortografia.

Dicas:
 - Para conseguir terminar isso, você vai ter que otimizar seu código.
Observe o seguinte: o dicionário está ordenado, isso significa
que todas as palavras que começam com "a" precedem as palavras
que começam com "b", e assim vai até chegar em "z". Existem
apenas 342 palavras começando com "a", apenas 238 palavras
começando com "b", etc. Quando você ler uma palavra do
input, você pode checar a primeira letra dela, e ao invés
de procurar no dicionário todo, você procura apenas
nas palavras que começam com essa mesma letra.
 - Para separar o dicionário em multiplas partes, você
 pode ter duas arrays de indices: `int letter_start[26]` e
 `int letter_end[26]`.
 Para cada letra, você marca o começo e fim da seção do dicionário
 nessas arrays. Desse jeito, você pode verificar somente
 as palavras entre o começo e fim de cada região.
 - Se `c` é uma letra entre `'a'` e `'z'`, você pode converter
 ela para um ìndice da array usando `c - 'a'`, ou seja,
 para ver onde uma região começa, dado o caractere `c`,
 você faz `letter_start[c - 'a']`.

### Busca Binária <a name="binary"></a>

A idéia que apresentei na seção anterior pode ser aplicada multiplas
vezes: se eu tenho uma palavra "alive", eu não preciso necessariamente
checar ela contra _todas_ as 342 palavras que começam com "a", afinal,
a segunda letra dessa palavra é "l" e existem apenas 29
palavras que começam com "al".
Além do mais, existem apenas 2 palavras que começam com "ali" e
apenas 1 palavra que começa com "aliv".

Apesar disso, separar as palavras em letras é um pouco complicado.
Ao invés disso, vamos separar em classes: A letra 'n' e
letras antes de 'n'; e letras depois de 'n'.

No dicionário de 5 mil palavras, existem 2926 palavras
que começam com letras antes de 'n', e existem
apenas 1755 palavras que começam com duas letras
antes de 'n' em sequência.

Podemos aplicar essa idéia multiplas vezes até sobrar uma
pequena quantidade de palavras para verificar
(talvez 10 seja um bom número).
Quando isso acontecer,
verificamos as palavras uma a uma.

O nome desse algoritmo é _busca binária_ em contraste, o algoritmo
que usavamos anteriormente se chama _busca linear_.
Você pode estudar [esse tutorial](https://www.geeksforgeeks.org/binary-search-a-string/),
[ver esse video](https://www.youtube.com/watch?v=P3YID7liBug) e
dar uma olhada nas seções 3.3 e 6.3 do livro do K&R.

Na pasta tem outros dois dicionários, um de 10 mil palavras (`words_10k.txt`)
e um de 370 mil palavras (`words_370k.txt`). Troque o dicionário,
meça a diferença de tempo que o programa leva para ler senhor dos anéis.
(você pode usar o comando `time` pra medir o tempo de execução
de um programa, basta executar `time ./run seuprograma.c`).

Dica:
 - Faça a sua busca binária retornar apenas os indices do
 começo e fim de uma região. Você pode retornar uma estrutura
 como a seguinte:
```c
typedef struct {
 int begin;
 int end;
} Region;
```
 - Pegue a região retornada pela busca binária e faça uma busca linear.

### Expandindo o dicionário <a name="expand"></a>

Muitos dos nomes de pessoas e lugares no livro do senhor dos anéis
vão ser reportados como erros gramaticais. Melhore seu programa
e adicione esses nomes no seu dicionário.

Dica:
 - Você pode usar o comando `sort` para reordenar o dicionário
 depois de adicionar os nomes.
 - Você pode colocar o output do seu programa em novo arquivo
 usando o operador `>`, isto é: `./run seuprograma.c > palavras`.

### Sugestões <a name="sugest"></a>

Basicamente, tu vai pegar um dos dicionários menores,
como o de 5 mil palavras e, se uma palavra estiver errada,
você vai tentar dar uma sugestão de correção.
Existem várias maneiras de fazer isso, um jeito simples
é contar o número de letras em cada palavra e tentar
achar outras palavras com número similar de letras.

Essa estratégia nos permite verificar a ocorrência
de erros de tipografia como "teh" ao invés de "the",
ie, _erros de transposição_.

Para isso, vamos usar a região da busca binária:
se a busca linear na região falhar, olhe as palavras
dessa região uma por uma e vê quais são similares.

Vamos definir duas palavras similares da seguinte forma:
duas palavras são similares se:
 - Começam com as mesmas letras (isso a busca binária já garante pra gente)
 - Tem a mesma distribuição de letras.

Imprima a sugestão na mesma linha que a palavra,
usando um `:\t` para separar elas.

Dica:
 - Faça uma função `bool is_similar(char* word, char* word)`
 que conta a quantidade de letras de cada palavra e retorna
 verdadeiro se for igual.
 - Para contar a quantidade de letras, crie uma função
 `void count_letters(char letters[26], char* word)`.
 Use a array `char letters[26]` para contar o número de letras
 da palavra. Indexe ela com o caractere, da mesma forma que fizemos
 anteriormente: `letters[c-'a']`.

### Easter Eggs <a name="easter"></a>

Tem 5 números escritos por extenso em português no livro
do senhor dos anéis. Modifique seu programa para
te ajudar a achar esses números. Quando achar todos os 5,
me envie.

Dica: todos os números tem 2 digitos.

## Leitura adicional <a name="more"></a>

 - [Como que o `spell` do UNIX cabia em 64KB de memória](https://blog.codingconfessions.com/p/how-unix-spell-ran-in-64kb-ram).
 - [Livro alternativo ao K&R](https://beej.us/guide/bgc/).
 - [Levenshtein Distance](https://en.wikipedia.org/wiki/Levenshtein_distance).
 Eu nunca consegui implementar esse algoritmo direito, mas se quiser se aventurar:
 [tutorial](https://www.geeksforgeeks.org/edit-distance-dp-5/),
 [tutorial](https://www.youtube.com/watch?v=MiqoA-yF-0M).
