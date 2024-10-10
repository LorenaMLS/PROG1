/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
 */

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc(long a, long b)
{
  if (!b)
    return a;
  return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc(long a, long b)
{
  return a * b / mdc(a, b);
}

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */
int simplifica_r(struct racional *r)
{
  long divisor;

  if (!r || !valido_r(r))
    return r;

  /*simplifica o racional*/
  divisor = mdc(r->num, r->den);
  r->den /= divisor;
  r->num /= divisor;

  /*se o denominador for negativo logo ocorre mudanças e sinais*/
  if (r->den < 0)
  {
    r->den *= -1;
    r->num *= -1;
  }

  return r;
}

/* implemente as demais funções de racional.h aqui */

struct racional *cria_r(long numerador, long denominador)
{
  struct racional *r;

  if (!(r = malloc(sizeof(struct racional))))
    return NULL;

  r->num = numerador;
  r->den = denominador;

  return r;
}

void destroi_r(struct racional *r)
{
  if (!r)
    return;

  free(r);
  r = NULL;
}

int valido_r(struct racional *r)
{
  if (!r || !r->den)
    return 0;

  return 1;
}

void imprime_r(struct racional *r)
{
  /*simplifica retorna 0 se nor NULL caso contrario simplifica*/
  if (!simplifica_r(r))
  {
    printf("NULL");
    return;
  }

  /*testa se o racional é invalido*/
  if (!valido_r(r))
    printf("NaN");
  else if (!r->num) /*se numerador = 0 imprime zero 0/5 = 0*/
    printf("0");
  else if (r->den == 1) /*2/1 = 2*/
    printf("%ld", r->num);
  else if (r->num == r->den) /*3/3 = 1*/
    printf("1");
  else
    printf("%ld/%ld", r->num, r->den);

  return;
}

int compara_r(struct racional *r1, struct racional *r2)
{
  long fracao1, fracao2;

  if (!simplifica_r(r1) || !simplifica_r(r2))
    return -2;

  /*realiza multiplicação cruzada para saber qual racional é maior
  1/2 > -1/2, pois fracao1= 1 * 2 e fracao2 = -1 * 2, portanto fracao1
  é maior neste exemplo*/
  fracao1 = r1->num * r2->den;
  fracao2 = r2->num * r1->den;

  if (fracao1 == fracao2)
    return 0;
  else if (fracao1 < fracao2)
    return -1;
  else
    return 1;
}

int soma_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (!r3 || !simplifica_r(r1) || !simplifica_r(r2))
    return 0;

  if (r1->den != r2->den) /*3/10 diferente 5/8*/
  {
    r3->den = mmc(r1->den, r2->den);
    /* divide o denominador pelo mmc e multiplica pelo numerador,
    repetindo com o segundo racional e subtraindo os dois*/
    r3->num = (r3->den / r1->den * r1->num) + (r3->den / r2->den * r2->num);
  }
  else
  {
    /*se os denominadores forem iguais repete e subtrai os numeradores*/
    r3->den = r1->den;
    r3->num = r1->num + r2->num;
  }

  return simplifica_r(r3);
}

int subtrai_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (!r3 || !simplifica_r(r1) || !simplifica_r(r2))
    return 0;

  if (r1->den != r2->den) /*3/10 diferente 5/8*/
  {
    r3->den = mmc(r1->den, r2->den);
    /* divide o denominador pelo mmc e multiplica pelo numerador,
    repetindo com o segundo racional e subtraindo os dois*/
    r3->num = (r3->den / r1->den * r1->num) - (r3->den / r2->den * r2->num);
  }
  else
  {
    /*se os denominadores forem iguais repete e subtrai os numeradores*/
    r3->den = r1->den;
    r3->num = r1->num - r2->num;
  }

  return simplifica_r(r3);
}

int multiplica_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (!r3 || !simplifica_r(r1) || !simplifica_r(r2))
    return 0;

  /*realiza a multiplicação dos racionais*/
  r3->num = r1->num * r2->num;
  r3->den = r1->den * r2->den;

  return simplifica_r(r3);
}

int divide_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
  struct racional *aux;

  if (!r3 || !simplifica_r(r1) || !simplifica_r(r2))
    return 0;

  /*inverte o segundo racional*/
  aux = cria_r(r2->den, r2->num);

  if (!multiplica_r(r1, aux, r3))
    return 0;

  destroi_r(aux);

  return 1;
}