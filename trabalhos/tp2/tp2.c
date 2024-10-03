/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/* programa principal */
int main()
{
  struct racional r[100];
  int i;
  long n;

  srand(0);
  /* a completar! */
  do
  {
    scanf("%ld", &n);
  } while (n < 0 || n > 100);

  //printf ("VETOR = ");

  for (i = 0;i < n; i++)
  {
    /*eu não sorteio os racionais eu leio*/
    imprime_r(r[i]);
    printf (" ");
  }

    return (0);
}
