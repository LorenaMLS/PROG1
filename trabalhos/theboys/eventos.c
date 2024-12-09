#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"
#include "math.h"

void atualiza_relogio(struct mundo_t *mundo, int tempo)
{
    if (!mundo)
        return;

    mundo->relogio = tempo;
}

void evento_printar(struct evento_t *evento)
{
    if (!evento)
    {
        printf("evento vazio\n");
        return;
    }
    printf("\n");
    printf("TIPO: %d\n", evento->tipo);
    printf("DADO1: %d\n", evento->dado1);
    printf("DADO2: %d\n", evento->dado2);
    printf("DADO3: %d\n", evento->dado3);
    printf("TEMPO: %d\n", evento->tempo);
}

long calcula_distancia(struct cordenadas_t loc, struct cordenadas_t prox_loc)
{
    long distancia, x, y;

    /*Calcula a distancia entre dois pontos*/
    x = (prox_loc.x - loc.x) * (prox_loc.x - loc.x);
    y = (prox_loc.y - loc.y) * (prox_loc.y - loc.y);

    distancia = sqrt(x + y);

    return distancia;
}

/*função que verifica o status de heroi; testa se esta vivo = 1 ou morto =  0*/
int heroi_testa(struct mundo_t *mundo, int id_heroi)
{
    /*se o status do heroi for "morto"*/
    if (mundo->heroi[id_heroi].status == -1)
        return 0;

    return 1;
}

struct cjto_t *uniao_habil(struct mundo_t *mundo, int id_base)
{
    struct cjto_t *uniao;
    int i;

    /*Cria um conjunto vazio com a capacidade máxima de habilidades*/
    uniao = cjto_cria(N_HABILIDADES);
    if (!uniao)
        return 0;

    for (i = 0; i < mundo->num_herois; i++)
    {
        /*verifica se heroi esta na base e insere as habil do heroi no conjunto uniao */
        if (cjto_pertence(mundo->base[id_base].presentes, i))
            cjto_uniao(uniao, mundo->heroi[i].habilidades);
    }

    return uniao;
}

struct evento_t *evento_cria(int tipo, int tempo, int dado1, int dado2, int dado3)
{
    struct evento_t *evento;

    if (!(evento = malloc(sizeof(struct evento_t))))
        return NULL;

    evento->tipo = tipo;
    evento->tempo = tempo;
    evento->dado1 = dado1;
    evento->dado2 = dado2;
    evento->dado3 = dado3;

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

int evento_chega(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;
    int espera;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*Atualizo a base do heroi*/
    mundo->heroi[id_heroi].id_base = id_base;

    /*se há vagas em B e a fila de espera em B está vazia*/
    if (cjto_card(mundo->base[id_base].presentes) < mundo->base[id_base].lotacao && !lista_tamanho(mundo->base[id_base].espera))
        espera = 1;
    else if (mundo->heroi[id_heroi].paciencia > (10 * (lista_tamanho(mundo->base[id_base].espera))))
        espera = 1;
    else
        espera = 0;

    /*Imprime o evento*/
    printf("%6d: CHEGA  HEROI %2d ", tempo, id_heroi);
    printf("BASE %d (%2d/%2d) ", id_base, cjto_card(mundo->base[id_base].presentes), mundo->base[id_base].lotacao);

    /*se o heroi espera então cria evento ESPERA, se não cria evento DESISTE*/
    if (espera)
    {
        evento = evento_cria(EV_ESPERA, tempo, id_heroi, id_base, 0);
        fprio_insere(mundo->fprio_eventos, evento, EV_ESPERA, tempo);
    }
    else
    {
        evento = evento_cria(EV_DESISTE, tempo, id_heroi, id_base, 0);
        fprio_insere(mundo->fprio_eventos, evento, EV_DESISTE, tempo);
    }

    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_espera(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*imprime o heroi na lista*/
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, id_heroi, id_base, cjto_card(mundo->base[id_base].presentes));

    /*Insere heroi na lista de espera da base*/
    lista_insere(mundo->base[id_base].espera, id_heroi, L_FIM);

    /*testa e cria evento AVISA*/
    if (!(evento = evento_cria(EV_AVISA, tempo, id_heroi, id_base, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, EV_AVISA, tempo);
    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_desiste(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;
    int base_destino;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*imprime que o heroi desistiu de esperar*/
    printf("%6d: DESIST HEROI %2d BASE %d \n", tempo, id_heroi, id_base);

    /*gera uma base aleatoria para o heroi seguir*/
    base_destino = gera_aleat(0, mundo->num_base - 1);

    /*testa e cria evento VIAJA*/
    if (!(evento = evento_cria(EV_VIAJA, tempo, id_heroi, base_destino, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, EV_VIAJA, tempo);
    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_avisa(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d)", tempo, id_base, cjto_card(mundo->base[id_base].presentes), mundo->base[id_base].lotacao);
    lista_imprime(mundo->base[id_base].espera);

    /*enquanto houver vaga em B e houver heróis esperando na fila*/
    while (cjto_card(mundo->base[id_base].presentes) < mundo->base[id_base].lotacao && !lista_tamanho(mundo->base[id_base].espera))
    {
        /*Retira heroi da lista de espera da base*/
        lista_retira(mundo->base[id_base].espera, &id_heroi, L_INICIO);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, id_base, id_heroi);

        /*insere heroi no conjunto de herois presentes na base*/
        if (!(cjto_insere(mundo->base[id_base].presentes, id_heroi)))
            return 0;

        /*testa e cria evento ENTRA*/
        if (!(evento = evento_cria(EV_ENTRA, tempo, id_heroi, id_base, 0)))
            return 0;

        /*insere na fila de eventos*/
        fprio_insere(mundo->fprio_eventos, evento, EV_ENTRA, tempo);
    }

    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_entra(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;
    int tpb;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*calcula o tempo de permanência do heroi na base*/
    tpb = ((mundo->heroi[id_heroi].paciencia * gera_aleat(1, 20)) + 15);

    /*imprime evento*/
    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, id_heroi, id_base, cjto_card(mundo->base[id_base].presentes), mundo->base[id_base].lotacao, tempo + tpb);

    /*testa e cria evento SAI*/
    if (!(evento = evento_cria(EV_SAI, tpb + tempo, id_heroi, id_base, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, EV_SAI, tempo);
    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_sai(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;
    int base_destino;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*imprime evento*/
    printf("%6d: SAI  HEROI %2d BASE %d (%2d/%2d)\n", tempo, id_heroi, id_base, cjto_card(mundo->base[id_base].presentes), mundo->base[id_base].lotacao);

    /*retira o heroi do conjunto de presentes da base*/
    if (!(cjto_retira(mundo->base[id_base].presentes, id_heroi)))
        return 0;

    /*gera uma base aleatoria de destino*/
    base_destino = gera_aleat(0, mundo->num_base - 1);

    /*testa, cria e insere o evento VIAJA */
    if ((evento = evento_cria(EV_VIAJA, tempo, id_heroi, base_destino, 0)))
        fprio_insere(mundo->fprio_eventos, evento, EV_VIAJA, tempo);
    else
        return 0;

    /*testa, cria e insere evento AVISA*/
    if ((evento = evento_cria(EV_AVISA, tempo, id_heroi, id_base, 0)))
        fprio_insere(mundo->fprio_eventos, evento, EV_AVISA, tempo);
    else
        return 0;

    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_viaja(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;
    int distancia, duracao, base_origem;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*localiza a base do heroi*/
    base_origem = mundo->heroi[id_heroi].id_base;

    /*calcula a distancia entre a base de origem e base D*/
    distancia = calcula_distancia(mundo->base[base_origem].local, mundo->base[id_base].local);

    /*calcula a duração que o heroi leva até chegar na proxima base*/
    duracao = distancia / mundo->heroi[id_heroi].velocidade;

    /*imprime evento*/
    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, id_heroi, base_origem,
           id_base, distancia, mundo->heroi[id_heroi].velocidade, tempo + duracao);

    /*teste e cria evento CHEGA*/
    if (!(evento = evento_cria(EV_CHEGA, tempo + duracao, id_heroi, id_base, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, EV_CHEGA, tempo);
    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_morre(struct mundo_t *mundo, int tempo, int id_heroi, int id_base, int id_missao)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*retira o heroi do conjunto de herois da base*/
    if (!cjto_retira(mundo->base[id_base].presentes, id_heroi))
        return 0;

    /*Atualiza o status do herói para "morto"*/
    mundo->heroi[id_heroi].status = -1;

    /*imprime evento*/
    printf("%6d: MORRE  HEROI %2d MISSAO %d\n", tempo, mundo->heroi[id_heroi].id, id_missao);

    /*Testa e cria o evento AVISA*/
    if (!(evento = evento_cria(EV_AVISA, tempo, 0, id_base, id_missao)))
        return 1;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, EV_AVISA, tempo);
    atualiza_relogio(mundo, tempo);

    return 1;
}

int retorna_base_prox(struct mundo_t *mundo, int id_missao)
{
    int i, distancia_base, menor_dist, id_base;

    if (!mundo)
        return 0;

    /*atribuindo valor de refencia para base e menor distancia*/
    id_base = 0;
    menor_dist = calcula_distancia(mundo->base[0].local, mundo->missao[id_missao].local);

    /*percorre bases e calcula a distancia*/
    for (i = 1; i < mundo->num_base; i++)
    {
        distancia_base = calcula_distancia(mundo->base[i].local, mundo->missao[id_missao].local);

        /*testa qual base tem a menor distancia*/
        if (distancia_base < menor_dist)
        {
            menor_dist = distancia_base;
            id_base = i;
        }
    }

    return id_base;
}

int evento_missao(struct mundo_t *mundo, int tempo, int id_missao)
{
    struct evento_t *evento;
    struct cjto_t *uniao_base;
    int base_mp, i, risco;

    if (!mundo)
        return 0;

    mundo->missao[id_missao].tentativas = 1;
    printf("%6d: MISSAO %d TENT %d HAB REQ: ", tempo, id_missao, mundo->missao[id_missao].tentativas);
    cjto_imprime(mundo->missao[id_missao].habilidades);
    printf("\n");

    /*acha a base mais proxima*/
    base_mp = retorna_base_prox(mundo, id_missao);
    /*faz a uniao das habilidades dos herois presentes na base*/
    uniao_base = uniao_habil(mundo, base_mp);

    /*testa se os herois tem as habilidades para realizar a missao*/
    if (cjto_contem(uniao_base, mundo->missao[id_missao].habilidades))
    {
        /*missao realizada imprime e incrementa variavel*/
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: ", tempo, id_missao, base_mp);
        cjto_imprime(uniao_base);
        printf("\n");
        mundo->missao[id_missao].realizada = 1;

        /*calcula o risco da missao*/
        for (i = 0; i < mundo->num_herois; i++)
        {
            if (cjto_pertence(mundo->base[base_mp].presentes, i))
            {
                risco = (mundo->missao[id_missao].perigo / (mundo->heroi[i].paciencia + mundo->heroi[i].experiencia + 1.0));

                /*se o risco for maior*/
                if (risco > gera_aleat(0, 30))
                {
                    /*cria e insere evento MORRE*/
                    evento = evento_cria(EV_MORRE, tempo, i, 0, id_missao);
                    fprio_insere(mundo->fprio_eventos, evento, EV_MORRE, tempo);
                }
                else
                    /*incrementa a experiência de heroi*/
                    mundo->heroi[i].experiencia++;
            }
        }
    }
    else
    {
        /*Missão adiada para 24 horas*/
        evento = evento_cria(EV_MISSAO, tempo + 24 * 60, 0, 0, id_missao);
        fprio_insere(mundo->fprio_eventos, evento, EV_MISSAO, tempo);
        printf("%6d: MISSAO %d IMPOSSIVEL ", tempo, id_missao);
    }

    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_fim(struct mundo_t *mundo, int tempo)
{
    int i;

    if (!mundo)
        return 0;

    /*Exibe o tempo final da simulação*/
    printf("%d: FIM\n\n", tempo);

    /*imprime os status finais de cada heroi*/
    for (i = 0; i < mundo->num_herois; i++)
    {
        /*testa o status do heroi, vivo ou morto*/
        if (mundo->heroi[i].status == 1)
        {
            printf("HEROI %2d VIVO  PAC %3d ", mundo->heroi[i].id, mundo->heroi[i].paciencia);
            printf("VEL %4d EXP %4d ", mundo->heroi[i].velocidade, mundo->heroi[i].experiencia);
            printf("HABS ");
            cjto_imprime(mundo->heroi[i].habilidades);
        }
        else
        {
            printf("HEROI %2d MORTO  PAC %3d ", mundo->heroi[i].id, mundo->heroi[i].paciencia);
            printf("VEL %4d EXP %4d ", mundo->heroi[i].velocidade, mundo->heroi[i].experiencia);
            printf("HABS ");
            cjto_imprime(mundo->heroi[i].habilidades);
        }
    }

    /*Imprime os status finais de cada base*/
    for (i = 0; i < mundo->num_base; i++)
    {
        printf("BASE %2d LOT %2d ", mundo->base[i].id_base, mundo->base[i].lotacao);
        /* printf("FILA MAX %2d "); */
        lista_imprime(mundo->base[i].espera);
    }

    atualiza_relogio(mundo, tempo);

    return 0;
}

int evento_inicia(struct mundo_t *mundo)
{
    struct evento_t *evento;
    int i, base, tempo;

    if (!mundo)
        return 0;

    /*cria evento CHEGA para cada heroi*/
    for (i = 0; i < mundo->num_herois; i++)
    {
        /*gera base e tempo aleatorios*/
        base = gera_aleat(0, mundo->num_base - 1);
        tempo = gera_aleat(0, TEMPO_INICIAL);

        /*Testa e cria evento CHEGA*/
        if (!(evento = evento_cria(EV_CHEGA, tempo, i, base, 0)))
            return 0;

        /*insere na fila de eventos*/
        fprio_insere(mundo->fprio_eventos, evento, EV_CHEGA, tempo);
    }

    /*cria evento MISSAO para cada missao*/
    for (i = 0; i < mundo->num_missao; i++)
    {
        /*Gera tempo aleatorio de 0 até (525600 - 1)*/
        tempo = gera_aleat(0, T_FIM_DO_MUNDO - 1);

        /*Testa e cria evento MISSAO*/
        if (!(evento = evento_cria(EV_MISSAO, tempo, i, 0, 0)))
            return 0;

        /*insere na fila de eventos*/
        fprio_insere(mundo->fprio_eventos, evento, EV_MISSAO, tempo);
    }

    /*Testa e cria evento FIM DO MUNDO*/
    if (!(evento = evento_cria(EV_FIM, T_FIM_DO_MUNDO, 0, 0, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, EV_FIM, T_FIM_DO_MUNDO);

    return 1;
}

int retorna_dado1(struct evento_t *evento)
{
    if (!evento)
        return -1;

    return evento->dado1;
}

int retorna_dado2(struct evento_t *evento)
{
    if (!evento)
        return -1;

    return evento->dado2;
}

int retorna_dado3(struct evento_t *evento)
{
    if (!evento)
        return -1;

    return evento->dado3;
}
