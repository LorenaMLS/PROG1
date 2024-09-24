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
  return r.den;
}

struct racional sorteia_r (long min, long max)
{ 
  struct racional fracao;

  /*crio a fração com numerador e denominador aleatorios 
  entre min e max*/
  fracao = cria_r(aleat(min,max), aleat(min,max));
  
  /*se for invalida não precisa calcular o mdc
  e retorna a fração invalida*/
  if (!valido_r(fracao))
    return fracao;

  return simplifica_r(fracao);
}

void imprime_r (struct racional r)
{
  
  r = simplifica_r(r);
  
  /*testa se o racional é invalido*/
  if (!valido_r(r))
    printf("INVALIDO");
  else if (!r.num)  /*se numerador = 0 imprime zero 0/5 = 0*/
    printf("0");
  else if (r.den == 1) /*2/1 = 2*/
    print("%d", r.num);
  else if (r.num == r.den) /*3/3 = 1*/
    printf("1");
  else if (r.num < 0 && r.den < 0) /*se os dois forem negativos logo racional positivo*/
    printf ("%d/%d", r.num * -1, r.den * -1);
  else if (r.den < 0) /*se denominador negativo inverte sinal */
    printf ("%d/%d", r.num * -1, r.den * -1);
  else
    printf("%d/%d", r.num, r.den); /*imprime o caso onde o numerador é negativo e denominador positivo*/

  return;
}