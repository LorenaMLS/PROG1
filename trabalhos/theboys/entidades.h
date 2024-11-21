#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "lista.h"
#include "fprio.h"
#include "conjunto.h"

/*descreve um heroi*/
struct heroi_t
{
    unsigned int id; /*id do heroi*/
    unsigned int paciencia; 
    unsigned int velocidade;
    unsigned int experiencia;
    int id_base; /* referencia onde esta localizado o heroi*/

    struct cjto_t *habilidades; /*habilidades do heroi*/
};

struct cordenadas_t
{
    unsigned int x;
    unsigned int y;
};

/*descreve a base*/
struct base_t
{
    int id_base; /*identificação da base*/
    int lotação; /*quantidade de pessoas na base*/
    struct cordenadas_t local; /*local da base*/

    struct cjto_t *presentes; /*identifica quantos herois há n base*/
    struct fprio_t *espera; /*fila de espera de herois*/
};

/*descreve a missao*/
struct missao_t
{
    unsigned int id; /*indentificação da missao*/
    unsigned int perigo; /*nivel de perigo da missao*/
    struct cordenadas_t local; /*local da missao*/
    
    struct cjto_t *habilidades; /*hablidades nescessarias*/
};

/*descreve o mundo*/
struct mundo_t
{
    unsigned int num_herois; /*quantidade de herois*/
    struct heroi_t *heroi; /*vetor de herois*/

    unsigned int num_base; /*quantidade de bases*/
    struct base_t *base; /*vetor de bases*/

    unsigned int num_missao; /*quantidade de missoes*/
    struct missao_t *missao; /*vetor de missoes*/

    unsigned int num_habilidades; /*quantidade de habilidades possiveis*/
    struct cordenadas_t tam; /*tamanho do mundo*/
    unsigned int relogio; /*tempo do mundo*/
};

/*Retorna um inteiro aleatório entre min e max*/
int gera_aleat(int min, int max);

/*cria um vetor de herois*/
/*retorno: um ponteiro o vetor criado ou NULL se erro*/
struct heroi_t *cria_herois (unsigned int num_herois);

/**/
struct heroi_t *destroi_herois (struct heroi_t *heroi);

struct base_t *cria_base (struct mundo_t *mundo);

struct base_t *destroi_base (struct mundo_t *mundo);

struct missao_t *cria_missao (unsigned int num_missao);

struct missao_t *destroi_missao (struct missao_t *missao);

struct mundo_t *cria_mundo ();

struct mundo_t *destroi_mundo (struct mundo_t *mundo);

#endif