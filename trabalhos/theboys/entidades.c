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

struct heroi_t *cria_herois(unsigned int num_herois)
{
    struct heroi_t *vet_heroi;
    int i;

    if (!(vet_heroi = malloc(sizeof(struct heroi_t) * num_herois)))
        return NULL;

    for (i = 0; i < num_herois; i++)
    {
        vet_heroi->id = i;
        vet_heroi->experiencia = 0;
        vet_heroi->id_base = 0;
        vet_heroi->paciencia = gera_aleat(0, 100);
        vet_heroi->velocidade = gera_aleat(50, 5000);
        vet_heroi->habilidades = cjto_cria(gera_aleat(1, 3));
    }

    return vet_heroi;
}

struct heroi_t *destroi_herois(struct heroi_t *heroi)
{
    if (!heroi)
        return NULL;

    free(heroi);
    heroi = NULL;

    return heroi;
}

struct base_t *cria_base(struct mundo_t *mundo)
{
    struct base_t *base;
    int i;

    if (!(base = malloc(sizeof(struct base_t) * mundo->num_base)))
        return NULL;

    for (i = 0; i < mundo->num_base; i++)
    {
        base->id_base = i;
        base->lotação = gera_aleat(3, 10);
        base->presentes = cjto_cria(mundo->num_base);
        base->espera = fprio_cria();
        /* base->local = cjto_aleat(0, mundo->tam - 1); */
    }

    return base;
}

struct base_t *destroi_base(struct mundo_t *mundo)
{
    if (!mundo)
        return NULL;

    if (!mundo->base)
        return NULL;
    

}