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
    int i, habilidade;

    if (!mundo)
        return NULL;

    /*aloca o vetor de herois com a quantidade de herois no mundo*/
    if (!(vet_heroi = malloc(sizeof(struct heroi_t) * mundo->num_herois)))
        return NULL;

    /*atribução de variaveis*/
    for (i = 0; i < mundo->num_herois; i++)
    {
        vet_heroi[i].id = i;
        vet_heroi[i].experiencia = 0;
        vet_heroi[i].id_base = 0;
        vet_heroi[i].paciencia = gera_aleat(0, 100);
        vet_heroi[i].velocidade = gera_aleat(50, 5000);
        vet_heroi[i].habilidades = cjto_cria(gera_aleat(1, 3)); /*cria conjunto com cap de 1 até 3*/
        vet_heroi[i].status = 1;
        
        /*insere as habilidades no conjunto*/
        while (vet_heroi[i].habilidades->num < vet_heroi[i].habilidades->cap)
        {
            habilidade = gera_aleat(0, N_HABILIDADES);
            cjto_insere(vet_heroi[i].habilidades, habilidade);
        }
    }

    return vet_heroi;
}

struct heroi_t *destroi_herois(struct mundo_t *mundo)
{
    int i;

    if (!mundo)
        return NULL;

    /*destroi o conjundo de habilidades do heroi*/
    for (i = 0; i < mundo->num_herois; i++)
        cjto_destroi(mundo->heroi[i].habilidades);

    /*destroi o heroi*/
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

    /*aloca com a quantidade de bases no mundo*/
    if (!(base = malloc(sizeof(struct base_t) * mundo->num_base)))
        return NULL;

    /*atribuição de variaveis*/
    for (i = 0; i < mundo->num_base; i++)
    {
        base[i].id_base = i;
        base[i].lotação = gera_aleat(3, 10);
        base[i].local.x = gera_aleat(0, N_TAMANHO_MUNDO - 1);
        base[i].local.y = gera_aleat(0, N_TAMANHO_MUNDO - 1);
        base[i].presentes = cjto_cria(mundo->num_herois); /*averiguar*/
        base[i].espera = fprio_cria();
    }

    return base;
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

    /*destroi a base*/
    free(mundo->base);
    mundo->base = NULL;

    return mundo->base;
}

struct missao_t *cria_missao(struct mundo_t *mundo)
{
    struct missao_t *missao;
    int i, habilidade;

    if (!mundo)
        return NULL;

    /*aloca umvetor de missões com a qnt de missoes no mundo*/
    if (!(missao = malloc(sizeof(struct missao_t) * mundo->num_missao)))
        return NULL;

    /*atribuição de variaveis da struct*/
    for (i = 0; i < mundo->num_missao; i++)
    {
        missao[i].id = i;
        missao[i].perigo = gera_aleat(0, 100);
        missao[i].local.x = gera_aleat(0, N_TAMANHO_MUNDO - 1);
        missao[i].local.y = gera_aleat(0, N_TAMANHO_MUNDO - 1);

        /*cria conjunto com capacidade de 6 até 10*/
        missao[i].habilidades = cjto_cria(gera_aleat(6, 10));

        /*insere as habilidades no conjunto*/
        while (missao[i].habilidades->num < missao[i].habilidades->cap)
        {
            habilidade = gera_aleat(0, N_HABILIDADES);
            cjto_insere(missao[i].habilidades, habilidade);
        }
    }

    return missao;
}

struct missao_t *destroi_missao(struct mundo_t *mundo)
{
    int i;

    if (!mundo)
        return NULL;

    /*destroi o cojunto de habilidades nescessarias para a missão*/
    for (i = 0; i < mundo->num_missao; i++)
        cjto_destroi(mundo->missao[i].habilidades);

    /*destroi a missao*/
    free(mundo->missao);
    mundo->missao = NULL;

    return mundo->missao;
}

struct mundo_t *cria_mundo()
{
    struct mundo_t *mundo;

    if (!(mundo = malloc(sizeof(struct mundo_t))))
        return NULL;

    /*atribuição de variaveis da struct*/
    mundo->relogio.inicio = T_INICIO;
    mundo->relogio.fim = T_FIM_DO_MUNDO;
    mundo->tam.x = N_TAMANHO_MUNDO;
    mundo->tam.y = N_TAMANHO_MUNDO;
    mundo->num_habilidades = N_HABILIDADES;
    mundo->num_herois = mundo->num_habilidades / 5;
    mundo->num_base = (mundo->num_herois / 5) + 1;
    mundo->num_missao = T_FIM_DO_MUNDO / 100;

    /*cria prio, base, missao e herois*/
    mundo->fprio_eventos = fprio_cria();
    mundo->base = cria_base(mundo);
    mundo->missao = cria_missao(mundo);
    mundo->heroi = cria_herois(mundo);

    return mundo;
}

struct mundo_t *destroi_mundo(struct mundo_t *mundo)
{
    if (!mundo)
        return NULL;

    fprio_destroi(mundo->fprio_eventos);
    destroi_base(mundo);
    destroi_missao(mundo);
    destroi_herois(mundo);

    free(mundo);
    mundo = NULL;

    return mundo;
}

void heroi_imprime(struct mundo_t *mundo)
{
    int i;

    printf("IMPRIMINDO HEROIS\n");
    if (!mundo)
        return;

    /*status dos herois criados*/
    for (i = 0; i < mundo->num_herois; i++)
    {
        printf("quantidade de herois criados: %d\n", mundo->num_herois);
        printf("heroi id: %d\n", mundo->heroi[i].id);

        /*habilidades do heroi*/
        printf("heroi cap de habili: %d\n", mundo->heroi[i].habilidades->cap);
        printf("heroi habilidade num: %d\n", mundo->heroi[i].habilidades->num);
        printf("CONJUNTO DE HAB HEROI: ");
        cjto_imprime(mundo->heroi[i].habilidades);
        printf("\n");

        printf("heroi experiencia: %d\n", mundo->heroi[i].experiencia);
        printf("heroi paciencia: %d\n", mundo->heroi[i].paciencia);
        printf("heroi velocidade: %d\n", mundo->heroi[i].velocidade);
        printf("heroi id base: %d\n", mundo->heroi[i].id_base);
        printf("\n");
    }
    printf("\n");
}

void base_imprime(struct mundo_t *mundo)
{
    int i;

    printf("IMPRIMINDO BASES\n");

    if (!mundo)
        return;

    for (i = 0; i < mundo->num_base; i++)
    {
        /*status da base criada*/
        printf("base num: %d\n", mundo->num_base);
        printf("base id: %d\n", mundo->base[i].id_base);
        printf("base local x: %d\n", mundo->base[i].local.x);
        printf("base local y: %d\n", mundo->base[i].local.y);
        printf("base lotação: %d\n", mundo->base[i].lotação);

        /*imprime conjunto de herois presentes*/
        printf("base presentes: ");
        cjto_imprime(mundo->base->presentes);
        printf("\n");

        /*imprime fila de espera*/
        printf("base espera: ");
        fprio_imprime(mundo->base[i].espera);
        printf("\n");
    }
    printf("\n");
}

void missao_imprime(struct mundo_t *mundo)
{
    int i;

    printf("IMPRIMINDO MISSÕES\n");

    if (!mundo)
        return;

    /*status das missões criadas*/
    printf("missao num: %d\n", mundo->num_missao);
    for (i = 0; i < mundo->num_missao; i++)
    {
        printf("missao id: %d\n", mundo->missao[i].id);
        printf("missao perigo: %d\n", mundo->missao[i].perigo);
        printf("missao local x: %d\n", mundo->missao[i].local.x);
        printf("missao local y: %d\n", mundo->missao[i].local.y);

        printf("missao habilidades cap: %d\n", mundo->missao[i].habilidades->cap);
        printf("missao habilidades num: %d\n", mundo->missao[i].habilidades->num);
        printf("CONJUNTO DE HAB MISSAO: ");
        cjto_imprime(mundo->missao[i].habilidades);
        printf("\n");
    }
    printf("\n");
}