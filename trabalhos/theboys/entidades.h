#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "lista.h"
#include "fprio.h"
#include "conjunto.h"

struct heroi_t
{
    unsigned int id;
    unsigned int paciencia;
    unsigned int velocidade;
    unsigned int experiencia;
    int id_base;

    struct cjto_t *habilidades;
};

struct cordenadas_t
{
    unsigned int x;
    unsigned int y;
};

struct base_t
{
    int id_base;
    int lotação;
    struct cordenadas_t local;

    struct cjto_t *presentes;
    struct fprio_t *espera;
};

struct missao_t
{
    unsigned int id;
    unsigned int perigo;
    struct cordenadas_t local;
    
    struct cjto_t *habilidades;
};

struct mundo_t
{
    unsigned int num_herois;
    struct heroi_t *heroi;

    unsigned int num_base;
    struct base_t *base;

    unsigned int num_missao;
    struct missao_t *missao; 

    unsigned int num_habilidades;
    struct cordenadas_t tam;
    unsigned int relogio;
};

/*Retorna um inteiro aleatório entre min e max*/
int gera_aleat(int min, int max);

struct heroi_t *cria_herois (unsigned int num_herois);

struct heroi_t *destroi_herois (struct heroi_t *heroi);

struct base_t *cria_base (struct mundo_t *mundo);

struct base_t *destroi_base (struct base_t *base);

struct missao_t *cria_missao (unsigned int num_missao);

struct missao_t *destroi_missao (struct missao_t *missao);

struct mundo_t *cria_mundo ();

struct mundo_t *destroi_mundo (struct mundo_t *mundo);

#endif