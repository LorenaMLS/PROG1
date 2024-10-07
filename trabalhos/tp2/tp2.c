/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*função que elimina os invalidos e retorna o tamanho*/
int elimina_invalidos(struct racional r[], long n)
{
  int i;

  if (!r)
    return 0;

  for (i = 0; i < n; i++)
  {
    /*se encontrei NaN troca pelo ultimo elemento do vetor*/
    if (!valido_r(r[i]))
    {
      /*enquanto o ultimo elemento for NaN, elimina ultimo*/
      while (!valido_r(r[n - 1]) && n > i)
        n--;

      r[i] = r[n - 1];
      n--;
    }
  }

  return n + 1;
}

void imprime_vetor(struct racional r[], long n)
{
  int i;

  if (!r)
    return;

  for (i = 0; i < n; i++)
  {
    imprime_r(r[i]);
    printf(" ");
  }
  printf("\n");
}

int ordena_vetor(struct racional r[], long n)
{
  
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
  n = elimina_invalidos(r, n);
  imprime_vetor(r, n);

  return 0;
}
