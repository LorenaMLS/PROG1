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
int elimina_invalidos(struct racional r[], int n)
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    if (!valido_r(r[i]))
      for (j = n; j > i; j--) /*Substitui por um while*/
      {
        if (!valido_r(r[n]))
          n--;
        else
        {
          r[i] = r[j];
          n--;
          imprime_r(r[i]);
          printf(" ");
        }
      }
    imprime_r(r[i]);
    printf(" ");
  }
}

/* programa principal */
int main()
{
  struct racional r[100];
  int i;
  long n, num, den;

  srand(0);
  /* a completar! */
  do
  {
    scanf("%ld", &n);
  } while (n < 0 || n > 100);

  printf("VETOR = ");

  /*leitura dos racionais e impressão*/
  for (i = 0; i < n; i++)
  {
    scanf("%ld %ld", &num, &den);
    r[i] = cria_r(num, den);
    imprime_r(r[i]);
    printf(" ");
  }

  printf("\nVETOR = ");
  elimina_invalidos(r, n);

  return 0;
}
