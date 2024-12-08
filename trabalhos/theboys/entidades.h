#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "lista.h"
#include "fprio.h"
#include "conjunto.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10

/*descreve um heroi*/
struct heroi_t
{
    unsigned int id; /*id do heroi*/
    unsigned int paciencia;
    unsigned int velocidade;
    unsigned int experiencia;
    int status; /*status do heroi; vivo = 1, morto = - 1*/
    int id_base; /* referencia onde esta localizado o heroi*/

    struct cjto_t *habilidades; /*habilidades do heroi*/
};

/*cordenadas do mundo no plano cartesiano*/
struct cordenadas_t
{
    unsigned int x;
    unsigned int y;
};

/*descreve a base*/
struct base_t
{
    unsigned int id_base;      /*identificação da base*/
    unsigned int lotação;      /*quantidade de pessoas na base*/
    struct cordenadas_t local; /*local da base*/

    struct cjto_t *presentes; /*identifica quantos herois há na base*/
    struct fprio_t *espera;   /*fila de espera de herois*/
};

/*descreve a missao*/
struct missao_t
{
    unsigned int id;           /*indentificação da missao*/
    unsigned int perigo;       /*nivel de perigo da missao*/
    struct cordenadas_t local; /*local da missao*/

    struct cjto_t *habilidades; /*hablidades nescessarias*/
};

/*tempo do mundo*/
struct tempo_t
{
    unsigned int inicio;
    unsigned int fim;
};

/*descreve o mundo*/
struct mundo_t
{
    int num_herois;        /*quantidade de herois*/
    struct heroi_t *heroi; /*vetor de herois*/

    int num_base;        /*quantidade de bases*/
    struct base_t *base; /*vetor de bases*/

    int num_missao;          /*quantidade de missoes*/
    struct missao_t *missao; /*vetor de missoes*/

    int num_habilidades;     /*quantidade de habilidades possiveis*/
    struct cordenadas_t tam; /*tamanho do mundo*/
    struct tempo_t relogio;  /*tempo do mundo*/

    struct fprio_t *fprio_eventos;  /*fila de prioridades*/
};

/*Retorna um inteiro aleatório entre min e max*/
int gera_aleat(int min, int max);

/*cria um vetor de herois*/
/*retorno: um ponteiro do vetor criado ou NULL se erro*/
struct heroi_t *cria_herois(struct mundo_t *mundo);

/*destroi a estrutuda de dados do vetor de herois,
inclusive o conjunto de habilidades*/
/*retorno NULL*/
struct heroi_t *destroi_herois(struct mundo_t *mundo);

/*cria a base com suas especificações*/
/*retorno: um ponteiro da base criada ou NULL se erro*/
struct base_t *cria_base(struct mundo_t *mundo);

/*destroi a estrutuda de dados da base*/
/*retorno NULL*/
struct base_t *destroi_base(struct mundo_t *mundo);

/*cria as missões*/
/*retorno: um ponteiro para o vetor de missões ou NULL se erro*/
struct missao_t *cria_missao(struct mundo_t *mundo);

/*destroi a estrutuda de dados do vetor de missões,
inclusive o conjunto de habilidades*/
/*retorno NULL*/
struct missao_t *destroi_missao(struct mundo_t *mundo);

/*função que cria o mundo com suas especificações */
/*retorno: um ponteiro do mundo criado ou NULL se erro*/
struct mundo_t *cria_mundo();

/*destroi a estrutuda de dados do mundo*/
/*retorno NULL*/
struct mundo_t *destroi_mundo(struct mundo_t *mundo);

/*função que imprime os status do heroi*/
void heroi_imprime(struct mundo_t *mundo);

/*função qe imprime o status da base*/
void base_imprime(struct mundo_t *mundo);

/*função que imprime os status da missao*/
void missao_imprime(struct mundo_t *mundo);

#endif