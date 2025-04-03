/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
 */

/* retorna um número aleatório entre min e max, inclusive. */
long aleat(long min, long max)
{
  long aleatorio;
  aleatorio = 0;

  aleatorio = rand();
  return (aleatorio % (max - min + 1) + min);
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc(long a, long b)
{
  if (b == 0)
    return a;
  return mdc(b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc(long a, long b)
{
  return ((a * b) / mdc(a, b));
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r(struct racional r)
{
  long divisor;

  if (!valido_r(r))
    return r;

  /*realiza o mdc do numerador e denominador*/
  divisor = mdc(r.num, r.den);

  /*divide pelo maximo divisor comum entre eles*/
  r.num /= divisor;
  r.den /= divisor;

  return r;
}

/* implemente as demais funções aqui */
struct racional cria_r(long numerador, long denominador)
{
  struct racional fracao;

  fracao.num = numerador;
  fracao.den = denominador;

  return fracao;
}

int valido_r(struct racional r)
{
  if (!r.den)
    return 0;

  return 1;
}

struct racional sorteia_r(long min, long max)
{
  struct racional fracao;
  long num, den;

  /*cria a fração com numerador e denominador aleatorios
  entre min e max*/
  num = aleat(min, max);
  den = aleat(min, max);
  fracao = cria_r(num, den);

  /*se for invalida não precisa calcular o mdc
  e retorna a fração invalida*/
  if (!valido_r(fracao))
    return fracao;

  return simplifica_r(fracao);
}

void imprime_r(struct racional r)
{

  r = simplifica_r(r);

  /*testa se o racional é invalido*/
  if (!valido_r(r))
    printf("INVALIDO ");
  else if (!r.num) /*se numerador = 0 imprime zero 0/5 = 0*/
    printf("0 ");
  else if (r.den == 1) /*2/1 = 2*/
    printf("%ld ", r.num);
  else if (r.num == r.den) /*3/3 = 1*/
    printf("1 ");
  else if (r.num < 0 && r.den < 0) /*se os dois forem negativos logo racional positivo*/
    printf("%ld/%ld ", r.num * -1, r.den * -1);
  else if (r.den < 0) /*se denominador negativo inverte sinal */
    printf("%ld/%ld ", r.num * -1, r.den * -1);
  else
    printf("%ld/%ld ", r.num, r.den); /*imprime o caso onde o numerador é negativo e denominador positivo*/

  return;
}

struct racional soma_r(struct racional r1, struct racional r2)
{
  struct racional aux;

  if (!valido_r(r2))
    return r2;

  else if (r1.den != r2.den) /*3/10 diferente 5/8*/
  {
    aux.den = mmc(r1.den, r2.den);
    /* divide o denominador pelo mmc e multiplica pelo numerador,
    repetindo com o segundo racional e somando os dois*/
    aux.num = (aux.den / r1.den * r1.num) + (aux.den / r2.den * r2.num);
  }
  else
  {
    /*se os denominadores forem iguais repete e soma os numeradores*/
    aux.den = r1.den;
    aux.num = r1.num + r2.num;
  }

  return simplifica_r(aux);
}

struct racional subtrai_r(struct racional r1, struct racional r2)
{
  struct racional aux;

  if (!valido_r(r2))
    return r2;

  else if (r1.den != r2.den) /*3/10 diferente 5/8*/
  {
    aux.den = mmc(r1.den, r2.den);
    /* divide o denominador pelo mmc e multiplica pelo numerador,
    repetindo com o segundo racional e subtrai os dois*/
    aux.num = (aux.den / r1.den * r1.num) - (aux.den / r2.den * r2.num);
  }
  else
  {
    /*se os denominadores forem iguais repete e subtrai os numeradores*/
    aux.den = r1.den;
    aux.num = r1.num - r2.num;
  }

  return simplifica_r(aux);
}

struct racional multiplica_r(struct racional r1, struct racional r2)
{
  struct racional aux;

  if (!valido_r(r2))
    return r2;

  /*realiza a multiplicação dos racionais*/
  aux.num = r1.num * r2.num;
  aux.den = r1.den * r2.den;

  return simplifica_r(aux);
}

struct racional divide_r(struct racional r1, struct racional r2)
{
  struct racional aux;

  if (!valido_r(r2))
    return r2;

  /*inverte o denominador pelo numerador,
  chama a função multiplica_r que já simplifica*/
  aux.num = r2.den;
  aux.den = r2.num;
  aux = multiplica_r(aux, r1);

  return aux;
}
