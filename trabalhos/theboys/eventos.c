#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"

struct evento_t *evento_cria(int tipo, int tempo, int dado1, int dado2)
{
    struct evento_t *evento;

    if (!(evento = malloc(sizeof(struct evento_t))))
        return NULL;

    evento->tipo = tipo;
    evento->tempo = tempo;
    evento->dado1 = dado1;
    evento->dado2 = dado2;

    return evento;
}

struct evento_t *evento_destroi(struct evento_t *evento)
{
    if (!evento)
        return NULL;

    free(evento);
    evento = NULL;

    return evento;
}

int evento_chega(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
{
    struct evento_t *evento;
    int espera;

    if (!mundo)
        return 0;

    /*Atualizo a base do heroi*/
    mundo->heroi[id_heroi].id_base = id_base;

    /*se há vagas em B e a fila de espera em B está vazia*/
    if (cjto_card(mundo->base[id_base].presentes) < mundo->base[id_base].lotação && !fprio_tamanho(mundo->base[id_base].espera))
        espera = 1;
    else if (mundo->heroi[id_heroi].paciencia > (10 * (fprio_tamanho(mundo->base[id_base].espera))))
        espera = 1;
    else
        espera = 0;

    if (espera)
        evento = evento_cria(EV_ESPERA, tempo, id_heroi, id_base);
    else
        evento = evento_cria(EV_DESISTE, tempo, id_heroi, id_base);

    fprio_insere(mundo->fprio_eventos, evento, 0, 0);
}