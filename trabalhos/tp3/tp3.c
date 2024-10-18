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
int ler_vetor(struct racional **r, long n)
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
int imprime_vetor(struct racional **r, long n)
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
int elimina_invalidos(struct racional **r, long n)
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
      while (!valido_r(r[n - 1]) && n > 1)
      {
        destroi_r(r[n - 1]);
        n--;
      }

      /* estroi_r(r[i]);
      r[i] = r[n - 1];
      n--; */
      
    } 

  }

  return n;
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
int particiona(struct racional **vetor, int inicio, int fim)
{
  struct racional *pivo;
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
      troca(vetor[i], vetor[j]);
    }
  }

  troca(vetor[i + 1], vetor[fim]);

  return i + 1;
}

/*função que ordena o vetor de forma menos custosa*/
void quickSort(struct racional **vetor, int inicio, int fim)
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
int soma_tudo(struct racional **r, long n)
{
  int i;

  if (!r)
    return 0;

  for (i = 1; i < n; i++)
    soma_r(r[0], r[i], r[0]);

  if (!valido_r(r[0]))
    return 0;

  return 1;
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

  if (!(r = aloca_vetor(n)))
    return 0;

  if (!ler_vetor(r, n))
    return 0;

  printf("VETOR = ");
  imprime_vetor(r, n);

  printf("VETOR = ");
  n = elimina_invalidos(r, n);
  imprime_vetor(r, n);

  /*ordena vetor e imprime*/
  printf("VETOR = ");
  quickSort(r, 0, n - 1);
  imprime_vetor(r, n);

  /*soma racionais e imprime*/
  printf("SOMA = ");
  if (!soma_tudo(r, n))
    printf("0");
  else
    imprime_r(r[0]);
  printf("\n");

  destroi_vetor(r, n);

  return 0;
}
