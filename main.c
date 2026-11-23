#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *sorteiaPalavra(const char *arquivo);

int main(void) {
  srand((unsigned int)time(NULL));

  char *palavra = sorteiaPalavra("palavras.txt");
  if (palavra == NULL) {
    printf("Erro ao sortear palavra.\n");
    return 1;
  }
  char pUsr[256];
  char descobertas[6] = "_____";
  int acertou = 0;
  int tentativas = 0;
  int entradaEncerrada = 0;

  while (!acertou && tentativas < 10) {
    printf("Digite uma palavra de 5 letras: ");

    if (fgets(pUsr, sizeof(pUsr), stdin) == NULL) {
      entradaEncerrada = 1;
      break;
    }

    pUsr[strcspn(pUsr, "\r\n")] = '\0';

    if (strlen(pUsr) != 5) {
      printf("Insira uma palavra válida de 5 letras.\n");
      continue;
    }

    for (int i = 0; i < 5; i++) {
      pUsr[i] = (char)tolower((unsigned char)pUsr[i]);
    }

    int certas = 0;

    for (int i = 0; i < 5; i++) {
      if (pUsr[i] == palavra[i]) {
        descobertas[i] = palavra[i];
        certas++;
      }
    }

    puts(descobertas);
    tentativas++;

    if (certas == 5) {
      acertou = 1;
    }
  }

  if (acertou) {
    printf("Você acertou!\n");
  } else if (entradaEncerrada) {
    printf("\nEntrada encerrada.\n");
  } else {
    printf("Suas tentativas acabaram. A palavra era: %s\n", palavra);
  }

  free(palavra);
  return 0;
}

char *sorteiaPalavra(const char *arquivo) {
  FILE *fp = fopen(arquivo, "r");
  if (fp == NULL) {
    return NULL;
  }

  char buffer[256];
  int totalPalavras = 0;

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
