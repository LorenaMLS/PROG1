#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"


int gera_aleat(int min, int max)
{
    /*Gera um numero aleatorio entre min e max*/
    return (rand() % (max - min + 1)) + min;
}

struct heroi_t *cria_herois(struct mundo_t *mundo)
{
    struct heroi_t *vet_heroi;
    int i;

    if (!mundo)
        NULL;

    if (!(vet_heroi = malloc(sizeof(struct heroi_t) * mundo->num_herois)))
        return NULL;

    for (i = 0; i < mundo->num_herois; i++)
    {
        vet_heroi[i].id = i;
        vet_heroi[i].experiencia = 0;
        vet_heroi[i].id_base = 0;
        vet_heroi[i].paciencia = gera_aleat(0, 100);
        vet_heroi[i].velocidade = gera_aleat(50, 5000);
        vet_heroi[i].habilidades = cjto_cria(gera_aleat(1, 3));
    }

    return mundo->heroi = vet_heroi;
}

struct heroi_t *destroi_herois(struct mundo_t *mundo)
{
    int i;

    if (!mundo)
        return NULL;

    /*destroi o conjundo de habilidades do heroi*/
    for (i = 0; i < mundo->num_herois; i++)
        cjto_destroi(mundo->heroi[i].habilidades);

    free(mundo->heroi);
    mundo->heroi = NULL;

    return mundo->heroi;
}

struct base_t *cria_base(struct mundo_t *mundo)
{
    struct base_t *base;
    int i;

    if (!mundo)
        return 0;

    if (!(base = malloc(sizeof(struct base_t) * mundo->num_base)))
        return NULL;

    for (i = 0; i < mundo->num_base; i++)
    {
        base[i].id_base = i;
        base[i].lotação = gera_aleat(3, 10);
        base[i].presentes = cjto_cria(mundo->num_base);
        base[i].espera = fprio_cria();
        base[i].local.x = gera_aleat(0, N_TAMANHO_MUNDO - 1);
        base[i].local.y = gera_aleat(0, N_TAMANHO_MUNDO - 1);
    }

    return mundo->base = base;
}

struct base_t *destroi_base(struct mundo_t *mundo)
{
    int i;

    if (!mundo)
        return NULL;

    /*destroi o conjunto de herois presentes e
    fila de espera de herois*/
    for (i = 0; i < mundo->num_base; i++)
    {
        cjto_destroi(mundo->base[i].presentes);
        fprio_destroi(mundo->base[i].espera);
    }

    free(mundo->base);
    mundo->base = NULL;

    return mundo->base;
}

struct missao_t *cria_missao (struct mundo_t *mundo)
{
    struct missao_t *missao;
    int i;

    if (!mundo)
        return NULL;
    
    if (!(missao = malloc(sizeof(struct missao_t) * mundo->num_missao)))
        return NULL;
    
    for (i = 0; i < mundo->num_missao; i++)
    {
        missao[i].id = i;
        missao[i].perigo = gera_aleat(0,100);
        missao[i].habilidades = cjto_aleat(6, 10);
        missao[i].local.x = gera_aleat(0, N_TAMANHO_MUNDO - 1);
        missao[i].local.y = gera_aleat(0, N_TAMANHO_MUNDO - 1);
    }

    return mundo->missao = missao;
}

struct missao_t *destroi_missao (struct mundo_t *mundo)
{
    int i;

    if (!mundo)
        return NULL;
    
    /*destroi o cojunto de habilidades nescessarias para a missão*/
    for (i = 0; i < mundo->num_habilidades; i++)
        cjto_destroi(mundo->missao[i].habilidades);
    
    free(mundo->missao);
    mundo->missao = NULL;

    return mundo->missao;
}

struct mundo_t *cria_mundo ()
{
    struct mundo_t *mundo;

    if (!(mundo = malloc(sizeof(struct mundo_t))))
        return NULL;
    
    mundo->relogio.inicio = T_INICIO;
    mundo->relogio.fim = T_FIM_DO_MUNDO;
    mundo->tam.x = N_TAMANHO_MUNDO;
    mundo->tam.y = N_TAMANHO_MUNDO;
    mundo->num_habilidades = N_HABILIDADES;
    mundo->num_herois = mundo->num_habilidades / 5;
    mundo->num_base = mundo->num_herois / 5;
    mundo->num_missao = T_FIM_DO_MUNDO / 100;

    cria_base(mundo);
    cria_missao(mundo);
    cria_herois(mundo);

    return mundo;
}

struct mundo_t *destroi_mundo (struct mundo_t *mundo)
{
    if(!mundo)
        return NULL;
    
    destroi_base(mundo);
    destroi_missao(mundo);
    destroi_herois(mundo);

    free(mundo);
    mundo = NULL;

    return mundo;
}
