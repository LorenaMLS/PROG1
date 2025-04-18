/*Trabalho por: Lorena Moreira Leite Dos Santos, GRR:20221244*/

/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*função que elimina os invalidos e retorna o novo tamanho do vetor*/
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

/*imprime o vetor de racionais*/
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

/*função que troca dois racionais*/
void troca(struct racional *a, struct racional *b)
{
  struct racional troca;
  troca = *a;
  *a = *b;
  *b = troca;
}

/*função que particiona vetor em vetores menores e ordena os subvetores*/
int particiona(struct racional vetor[], int inicio, int fim)
{
  struct racional pivo;
  int i;

  if (!vetor)
    return 0;

  /*pivo recebe o ultimo elemento do vetor*/
  pivo = vetor[fim];
  i = inicio - 1;

  for (int j = inicio; j < fim; j++)
  {
    if (compara_r(vetor[j], pivo) <= 0)
    {
      i++;
      troca(&vetor[i], &vetor[j]);
    }
  }

  troca(&vetor[i + 1], &vetor[fim]);

  return i + 1;
}

/*função que ordena o vetor de forma menos custosa*/
void quickSort(struct racional vetor[], int inicio, int fim)
{
  int pivo_indice;

  if (!vetor)
    return;

  if (inicio < fim)
  {
    pivo_indice = particiona(vetor, inicio, fim);
    quickSort(vetor, inicio, pivo_indice - 1);
    quickSort(vetor, pivo_indice + 1, fim);
  }
}

/*função que soma todos os racionais*/
struct racional soma_tudo(struct racional r[], long n)
{
  struct racional aux;
  int i;

  if (!r)
    return cria_r(0, 1);

  aux = r[0];
  for (i = 1; i < n; i++)
    soma_r(r[i], aux, &aux);

  if (!valido_r(aux))
    return cria_r(0, 1);

  return aux;
}

/* programa principal */
int main()
{
  struct racional r[100];
  int i;
  long n, num, den;

  srand(0);

  /*leitura do n*/
  do
  {
    scanf("%ld", &n);
  } while (n < 0 || n > 100);

  /*leitura dos racionais e impressão*/
  printf("VETOR = ");
  for (i = 0; i < n; i++)
  {
    scanf("%ld %ld", &num, &den);
    r[i] = cria_r(num, den);
    imprime_r(r[i]); /*aproveitando o mesmo For para imprimir*/
    printf(" ");
  }

  /*elimina invalidos e imprime*/
  printf("\nVETOR = ");
  n = elimina_invalidos(r, n);
  imprime_vetor(r, n);

  /*ordena vetor e imprime*/
  printf("VETOR = ");
  quickSort(r, 0, n - 1);
  imprime_vetor(r, n);

  /*soma racionais e imprime*/
  printf("SOMA = ");
  imprime_r(soma_tudo(r, n));
  printf("\n");

  return 0;
}
