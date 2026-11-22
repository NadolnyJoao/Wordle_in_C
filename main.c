#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *sorteiaPalavra(char *arquivo) {
  char *palavraSorteada = malloc(6 * sizeof(char));
  FILE *fp = fopen(arquivo, "r");
  if (fp == NULL || palavraSorteada == NULL) {
    free(palavraSorteada);
    return NULL;
  }
  int linhas = 0, linhaAtual = 1;
  int ch;
  int encontrou = 0;
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n')
      linhas++;
  }
  int linhaSortida = rand() % linhas - 1;
  rewind(fp);
  while (!encontrou) {
    linhaAtual++;
    if (linhaAtual == linhaSortida) {
    }
  }
  return palavraSorteada;
}
