# Spell checker

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
Nele, você vai ver os autores do livro de C que eu te emprestei,
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

## Pré-requisitos

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

## Comandos básicos do terminal

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

## As etapas

O projeto vai ficar cada vez mais complexo,
e vai ser realizado em etapas.
Após a conclusão de cada etapa, você vai me
mostrar o código e rodar ele, com isso, vai
ganhar o dinheiro referente àquela etapa.

Vou sempre listar os capítulos do livro
que te emprestei, o K&R, pra você
ler antes de resolver uma tarefa.
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

### Hello World (R$1)

**Essa etapa não tem requisitos.**

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

### Requisitos antes de continuar (R$20)

Você vai precisar aprender C, siga
[esse tutorial](https://www.learn-c.org/) e
faça todos os exercícios da seção "Learn the basics".

Depois disso, passe o olho na introdução e no
primeiro capítulo ("A tutorial introduction")
do livro que te emprestei (Kerningham & Ritchie).

Se você não tiver entendido funções ainda,
[funções](https://www.w3schools.com/c/c_functions.php),
[funções](https://users.cs.utah.edu/~germain/PPS/Topics/C_Language/c_functions.html)
e [funções](https://www.geeksforgeeks.org/c-functions/).
Veja se algum desses tutoriais te agrada.

### Reconhecendo as palavras (R$10)

Printar as palavras do stdin, uma por linha, só isso.
**Definir melhor o que é uma "palavra"**

### I Am Groot (R$5)

Construir em cima do anterior, 
fazer verificação usando um dicionário,
mas o dicionário é só uma array com "I", "Am" e "Groot".

### 5 mil palavras (R$10)

Abra o dicionário de 5 mil palavras incluso no repositório,
jogue na memória e verifique as palavras do mesmo jeito que
você fez com _I Am Groot_.

### 10 mil palavras (R$30)

As coisas começam a ficar mais complicadas,
O dicionário é grande e você vai ter que checar
capítulos inteiros de Senhor dos Anéis.
Você vai ter que ordernar o dicionário e fazer uma busca binária.

### 370 mil palavras (R$50)

Fudeu! É coisa pra caralho. Você vai ter que esquecer a precisão
aqui. Uma função de hash vai ser usada pra criar um conjunto,
existe uma possibilidade de erro, mas vamos admitir ser muito
pequena.

Vou lhe fornecer a função de hash, chamada MurmurHash.
Você vai preprocessar o dicionário e salvar apenas as hashs.
Boa sorte.

### Sugestões (R$50)

Basicamente, tu vai pegar um dos dicionários menores,
como o de 5 mil palavras e, se uma palavra estiver errada,
você vai tentar dar uma sugestão de correção.
Existem várias maneiras de fazer isso, um jeito simples
é contar o número de letras em cada palavra e tentar
achar outras palavras com número similar de letras.

Para melhorar o algoritmo, você pode percorrer as palavras em ordem,
se mais que 70% das letras estiverem no lugar certo, você emite
uma sugestão.

Se esse teste falhar, procure a maior substring em comum das duas
palavras, se for menos que 3 caracteres, não emita nenhuma sugestão.

<!--https://blog.codingconfessions.com/p/how-unix-spell-ran-in-64kb-ram-->
