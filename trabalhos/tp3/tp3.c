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

/*função que aloca n posições de racionais e retorna 1 sucesso e 0 se falha*/
int ler_vetor(struct racional *r[], long n)
{
  int i;
  long num, den;

  if (!r)
    return 0;

  for (i = 0; i < n; i++)
  {
    scanf("%ld %ld", &num, &den);
    r[i] = cria_r(num, den);
  }

  return 1;
}

/*imprime o vetor de racionais, retorna 1 sucesso e 0 se falha*/
int imprime_vetor(struct racional *r[], long n)
{
  int i;

  if (!r)
    return 0;

  for (i = 0; i < n; i++)
  {
    imprime_r(r[i]);
    printf(" ");
  }
  printf("\n");

  return 1;
}

/*função que cria um vetor de ponteiros de ponteiros*/
struct racional **aloca_vetor(long n)
{
  struct racional **r;

  if (!(r = malloc(sizeof(struct racional) * n)))
    return NULL;

  return r;
}

/*função que destroi um vetor de ponteiros*/
void destroi_vetor(struct racional **r, long n)
{
  int i;
  if (!r)
    return;

  for (i = 0; i < n; i++)
  {
    destroi_r(r[i]);
  }

  free(r);
  r = NULL;
}

/*função que elimina os invalidos e retorna o novo tamanho do vetor*/
int elimina_invalidos(struct racional *r[], long n)
{
  int i;

  if (!r)
    return 0;

  for (i = 0; i < n; i++)
  {
    /*se encontrei NaN troca pelo ultimo elemento do vetor*/
    if (!valido_r(r[i]))
    {
      /*enquanto o r[n] for NaN, elimina ultimo*/
      while (!valido_r(r[n - 1]))
        n--;

      /*garante que não remove duas vezes, caso o ultimo elemento seja NaN*/
      if (n != i)
      {
        /*troca o ultimo elemento pelo r[i] e remove o ultimo*/
        r[i] = r[n - 1];
        n--;
      }
    }
  }

  return n;
}

/* programa principal */
int main()
{
  struct racional **r;
  long n;

  /*leitura do n*/
  do
  {
    scanf("%ld", &n);
  } while (n < 0 || n > 100);

  if(!(r = aloca_vetor(n)))
    return 0;

  if(!ler_vetor(r, n))
    return 0;

  printf("VETOR = ");
  imprime_vetor(r, n);

  printf("VETOR = ");
  n = elimina_invalidos(r, n);
  imprime_vetor(r, n);

  return 0;
}
