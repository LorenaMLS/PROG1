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

    /*se o heroi espera então cria evento ESPERA, se não cria evento DESISTE*/
    if (espera)
        evento = evento_cria(EV_ESPERA, tempo, id_heroi, id_base);
    else
        evento = evento_cria(EV_DESISTE, tempo, id_heroi, id_base);

    /*insere na fila de espera o evento*/
    fprio_insere(mundo->fprio_eventos, evento, 0, 0);

    return 1;
}

int evento_espera(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*Insere heroi na lista de espera da base*/
    lista_insere(mundo->base[id_base].espera, id_heroi, L_FIM);

    /*testa e cria evento AVISA*/
    if (!(evento = evento_cria(EV_AVISA, tempo, id_heroi, id_base)))
        return 0;

    /*insere na fila de espera o evento*/
    fprio_insere(mundo->fprio_eventos, evento, 0, 0);

    return 1;
}

int evento_desiste(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
{
    struct evento_t *evento;
    int base_destino;

    if (!mundo)
        return 0;

    /*gera uma base aleatoria para o heroi seguir*/
    base_destino = gera_aleat(0, mundo->num_base - 1);

    /*testa e cria evento VIAJA*/
    if (!(evento = evento_cria(EV_VIAJA, tempo, id_heroi, base_destino)))
        return 0;

    /*insere na fila de espera o evento*/
    fprio_insere(mundo->fprio_eventos, evento, 0, 0);

    return 1;
}

int evento_avisa(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*enquanto houver vaga em B e houver heróis esperando na fila*/
    while (cjto_card(mundo->base[id_base].presentes) < mundo->base[id_base].lotação && !fprio_tamanho(mundo->base[id_base].espera))
    {
        /*Retira heroi da fila de espera da base*/
        fprio_retira(mundo->base[id_base].espera, id_heroi, L_INICIO);

        /*insere heroi no conjunto de herois presentes na base*/
        if (!(cjto_insere(mundo->base[id_base].presentes, id_heroi)))
            return 0;

        /*testa e cria evento ENTRA*/
        if (!(evento = evento_cria(EV_ENTRA, tempo, id_heroi, id_base)))
            return 0;

        /*insere na fila de espera o evento*/
        fprio_insere(mundo->fprio_eventos, evento, 0, 0);
    }

    return 1;
}

int evento_entra(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;
    
    
}