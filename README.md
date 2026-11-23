# Wordle_in_C

Uma versão simples do **Wordle** para o terminal, escrita em C puro com fins educacionais.

O programa sorteia uma palavra de 5 letras de uma lista em português e você tenta descobri-la em até 10 tentativas, vendo a cada rodada quais letras já estão na posição certa.

## Como jogar

1. O jogo sorteia uma palavra de 5 letras do arquivo `palavras.txt`.
2. Digite um palpite de 5 letras e aperte Enter (maiúsculas e minúsculas são aceitas).
3. O jogo mostra a palavra "descoberta" até agora: as letras que você acertou **na posição correta** aparecem, e as demais ficam como `_`. Os acertos se acumulam entre as tentativas.
4. Você tem **10 tentativas**. Acertou a palavra inteira, ganhou; acabaram as tentativas, o jogo revela a palavra sorteada.

Palpites que não tenham exatamente 5 letras são recusados e **não** gastam tentativa. Para sair antes do fim, use `Ctrl+D` (fim de entrada).

### Exemplo de partida

Supondo que a palavra sorteada seja `troca`:

```
Digite uma palavra de 5 letras: festa
____a
Digite uma palavra de 5 letras: tarde
t___a
Digite uma palavra de 5 letras: troca
troca
Você acertou!
```

## Requisitos

- Um compilador C (por exemplo, `gcc` ou `clang`)
- Um terminal com suporte a UTF-8, para exibir os acentos das mensagens

## Compilando e executando

Clone o repositório e compile:

```bash
git clone https://github.com/NadolnyJoao/Wordle_in_C.git
cd Wordle_in_C
gcc -Wall -Wextra -std=c11 -o main main.c
```

Execute **de dentro da pasta do projeto**, porque o programa abre o `palavras.txt` pelo caminho relativo:

```bash
./main
```

## Estrutura do projeto

```
Wordle_in_C/
├── main.c         # código-fonte do jogo
├── palavras.txt   # lista de palavras (uma por linha)
└── README.md
```

## Como funciona por dentro

- **Sorteio (`sorteiaPalavra`)**: abre o arquivo e faz duas passagens. Na primeira, conta quantas linhas têm exatamente 5 caracteres. Em seguida sorteia um índice com `rand()` (semeado com `time(NULL)`), volta ao início com `rewind` e lê até chegar nele. A palavra é devolvida em memória alocada com `malloc` e liberada com `free` no fim do jogo.
- **Leitura de entrada**: `fgets` com remoção de `\r` e `\n` via `strcspn`, o que evita estouro de buffer e funciona com arquivos de fim de linha Unix ou Windows.
- **Comparação**: o palpite é convertido para minúsculas com `tolower` e comparado letra a letra com a palavra sorteada. Os acertos são acumulados em um vetor de 5 posições, que é exibido a cada tentativa.
- **Tratamento de erros**: se o arquivo não puder ser aberto, estiver sem palavras válidas ou faltar memória, o programa avisa e encerra com código `1`.

## Editando a lista de palavras

O `palavras.txt` aceita uma palavra por linha. Para que uma palavra possa ser sorteada, ela precisa ter **exatamente 5 bytes**. Na prática, isso significa:

- use apenas 5 letras, em minúsculas;
- evite caracteres acentuados ou `ç` (em UTF-8 ocupam mais de 1 byte, então palavras como `dança` e `preço` são ignoradas);
- linhas com outro tamanho são puladas silenciosamente.

## Limitações conhecidas e ideias para as próximas versões

- [ ] Dica de letras que existem na palavra mas estão na posição errada (as "amarelas" do Wordle original), por exemplo com cores ANSI no terminal
- [ ] Reduzir para 6 tentativas, como no jogo original
- [ ] Validar o palpite contra a lista de palavras
- [ ] Suporte a acentuação (UTF-8)
- [ ] Dividir o código em mais funções/arquivos (`.h` e `.c`)
- [ ] Adicionar um `Makefile`

## Autor

Feito por [João Vitor Nadolny](https://github.com/NadolnyJoao) como projeto de estudo em C.
