#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *sorteiaPalavra(const char *arquivo) {
  FILE *fp = fopen(arquivo, "r");
  if (fp == NULL) {
    return NULL;
  }

  char buffer[256];
  int totalPalavras = 0;

  /* Conta as palavras válidas. */
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (strlen(buffer) == 5) {
      totalPalavras++;
    }
  }

  if (totalPalavras == 0) {
    fclose(fp);
    return NULL;
  }

  int sorteada = rand() % totalPalavras;
  rewind(fp);

  /* Lê novamente até encontrar a palavra sorteada. */
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (strlen(buffer) == 5) {
      if (sorteada == 0) {
        char *palavraSorteada = malloc(6);

        if (palavraSorteada == NULL) {
          fclose(fp);
          return NULL;
        }

        strcpy(palavraSorteada, buffer);
        fclose(fp);
        return palavraSorteada;
      }

      sorteada--;
    }
  }

  fclose(fp);
  return NULL;
}
