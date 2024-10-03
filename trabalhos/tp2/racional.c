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
  return (rand() % (max - min + 1)) + min;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc(long a, long b)
{
  if (!b)
    return a;
  return mdc(b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc(long a, long b)
{
  return a * b / mdc(a, b);
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

  /*simplifica o racional*/
  divisor = mdc(r.num, r.den);
  r.den /= divisor;
  r.num /= divisor;

  /*se o denominador for negativo logo ocorre mudanças e sinais*/
  if (r.den < 0)
  {
    r.den *= -1;
    r.num *= -1;
  }

  return r;
}

/* implemente as demais funções de racional.h aqui */

struct racional cria_r(long numerador, long denominador)
{
  struct racional r;

  r.num = numerador;
  r.den = denominador;

  return r;
}

int valido_r(struct racional r)
{
  if (!r.den)
    return 0;

  return 1;
}

struct racional sorteia_r(long min, long max)
{
  struct racional r;
  long num, den;

  /*cria a fração com numerador e denominador aleatorios
  entre min e max*/
  num = aleat(min, max);
  den = aleat(min, max);
  r = cria_r(num, den);
  
  return simplifica_r(r);
}

void imprime_r(struct racional r)
{
  r = simplifica_r(r);

  /*testa se o racional é invalido*/
  if (!valido_r(r))
    printf("NaN");
  else if (!r.num) /*se numerador = 0 imprime zero 0/5 = 0*/
    printf("0");
  else if (r.den == 1) /*2/1 = 2*/
    printf("%ld", r.num);
  else if (r.num == r.den) /*3/3 = 1*/
    printf("1");
  else 
    printf("%ld/%ld", r.num, r.den);

  return;
}

int compara_r(struct racional r1, struct racional r2)
{
  long denominador_comum;

  if (!valido_r(r1) || !valido_r(r2))
    return -2;

  /*compara se os dois racionais são iguais*/
  if (r1.num == r2.num && r1.den == r2.den)
    return 0;

  /*iguala as bases*/
  denominador_comum = mmc(r1.den, r2.den);
  /*divide a base pelos denominadores (r1 e r2) e multiplica pelo numeradores*/
  r1.num = denominador_comum / r1.den * r1.num;
  r2.num = denominador_comum / r2.den * r2.num;
  
  if (r1.num < r2.num)
    return -1;
  else
    return 1;
}

int soma_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r(r1) || !valido_r(r2) || !r3)
    return 0;

  if (r1.den != r2.den) /*3/10 diferente 5/8*/
  {
    r3->den = mmc(r1.den, r2.den);
    /* divide o denominador pelo mmc e multiplica pelo numerador,
    repetindo com o segundo racional e somando os dois*/
    r3->num = (r3->den / r1.den * r1.num) + (r3->den / r2.den * r2.num);
  }
  else
  {
    /*se os denominadores forem iguais repete e soma os numeradores*/
    r3->den = r1.den;
    r3->num = r1.num + r2.num;
  }

  *r3 = simplifica_r(*r3); /*não tenho ctz*/

  return 1;
}

int subtrai_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r(r1) || !valido_r(r2) || !r3)
    return 0;

  if (r1.den != r2.den) /*3/10 diferente 5/8*/
  {
    r3->den = mmc(r1.den, r2.den);
    /* divide o denominador pelo mmc e multiplica pelo numerador,
    repetindo com o segundo racional e subtraindo os dois*/
    r3->num = (r3->den / r1.den * r1.num) - (r3->den / r2.den * r2.num);
  }
  else
  {
    /*se os denominadores forem iguais repete e subtrai os numeradores*/
    r3->den = r1.den;
    r3->num = r1.num - r2.num;
  }

  *r3 = simplifica_r(*r3); /*não tenho ctz*/

  return 1;
}

int multiplica_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r(r1) || !valido_r(r2) || !r3)
    return 0;

  /*realiza a multiplicação dos racionais*/
  r3->num = r1.num * r2.num;
  r3->den = r1.den * r2.den;

  *r3 = simplifica_r(*r3); /*não tenho ctz*/

  return 1;
}

int divide_r(struct racional r1, struct racional r2, struct racional *r3)
{
  struct racional aux;

  if (!valido_r(r1) || !valido_r(r2) || !r3)
    return 0;

  /*inverte o segundo racional*/
  aux.num = r2.den;
  aux.den = r2.num;

  return multiplica_r(r1, aux, r3);
}