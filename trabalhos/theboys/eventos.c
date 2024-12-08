#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"
#include "math.h"

/*Calcula a discancia entre dois pontos*/
long calcula_distancia(struct cordenadas_t loc, struct cordenadas_t prox_loc)
{
    long distancia, x, y;

    /*Calcula a distancia entre dois pontos*/
    x = (prox_loc.x - loc.x) * (prox_loc.x - loc.x);
    y = (prox_loc.y - loc.y) * (prox_loc.y - loc.y);

    distancia = sqrt(x + y);

    return distancia;
}

/*função que calcula a distancias entres a bases e a duração que o heroi leva para percorre-la*/
int distancia_calc(struct mundo_t *mundo, unsigned int id_base, unsigned int id_heroi)
{
    struct cordenadas_t *distancia, *base_destino;
    int duracao;

    if (!mundo)
        return 0;

    base_destino = malloc(sizeof(struct cordenadas_t));
    if (!base_destino)
        return 0;

    /*gera uma base aleatoria de destino*/
    base_destino->x = gera_aleat(0, mundo->base - 1);
    base_destino->y = gera_aleat(0, mundo->base - 1);

    /*calcula a distancia entre a base do heroi e a proxima*/
    distancia->x = (mundo->base[id_base].local.x - base_destino->x);
    distancia->y = (mundo->base[id_base].local.y - base_destino->y);

    /*calcula a duração que o heroi leva até chegar na proxima base*/
    duracao = ((distancia->x + distancia->y) / mundo->heroi[id_heroi].velocidade);

    return duracao;
}

/*função que verifica o status de heroi; testa se esta vivo = 1 ou morto =  0*/
int heroi_testa(struct mundo_t *mundo, unsigned int id_heroi)
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
        /*Verifica se o herói "i" está presente na base*/
        if (cjto_pertence(mundo->base[id_base].presentes, i))
        {
            /*Faz a união das habilidades do herói com as do conjunto "uniao"*/
            struct cjto_t *habilidades_heroi = mundo->heroi[i].habilidades;
            struct cjto_t *uniao_temp = cjto_uniao(uniao, habilidades_heroi);

            cjto_destroi(uniao);
            uniao = uniao_temp;
        }
    }

    return uniao;
}

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

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*Atualizo a base do heroi*/
    mundo->heroi[id_heroi].id_base = id_base;

    /*se há vagas em B e a fila de espera em B está vazia*/
    if (cjto_card(mundo->base[id_base].presentes) < mundo->base[id_base].lotacao && !fprio_tamanho(mundo->base[id_base].espera))
        espera = 1;
    else if (mundo->heroi[id_heroi].paciencia > (10 * (fprio_tamanho(mundo->base[id_base].espera))))
        espera = 1;
    else
        espera = 0;

    /*Imprime o evento*/
    printf("%6d: CHEGA  HEROI %2d ", tempo, id_heroi);
    printf("BASE %d (%2d/%2d) ", id_base, cjto_card(mundo->base[id_base].presentes), mundo->base[id_base].lotacao);

    /*se o heroi espera então cria evento ESPERA, se não cria evento DESISTE*/
    if (espera)
        evento = evento_cria(EV_ESPERA, tempo, id_heroi, id_base);
    else
        evento = evento_cria(EV_DESISTE, tempo, id_heroi, id_base);

    /*insere na fila de eventos*/
    fprio_insere(retorna_evento, evento, 0, 0);

    return 1;
}

int evento_espera(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*imprime o heroi na fila*/
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, id_heroi, id_base, cjto_card(mundo->base[id_base].presentes));

    /*Insere heroi na lista de espera da base*/
    lista_insere(mundo->base[id_base].espera, id_heroi, L_FIM);

    /*testa e cria evento AVISA*/
    if (!(evento = evento_cria(EV_AVISA, tempo, id_heroi, id_base)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(retorna_evento, evento, 0, 0);

    return 1;
}

int evento_desiste(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
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
    if (!(evento = evento_cria(EV_VIAJA, tempo, id_heroi, base_destino)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(retorna_evento, evento, 0, 0);

    return 1;
}

int evento_avisa(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d)", tempo, id_base, cjto_card(mundo->base[id_base].presentes), mundo->base[id_base].lotacao);
    printf("FILA ");
    fprio_imprime(mundo->base[id_base].espera);

    /*enquanto houver vaga em B e houver heróis esperando na fila*/
    while (cjto_card(mundo->base[id_base].presentes) < mundo->base[id_base].lotacao && !fprio_tamanho(mundo->base[id_base].espera))
    {
        /*Retira heroi da fila de espera da base*/
        fprio_retira(mundo->base[id_base].espera, id_heroi, L_INICIO);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, id_base, id_heroi);

        /*insere heroi no conjunto de herois presentes na base*/
        if (!(cjto_insere(mundo->base[id_base].presentes, id_heroi)))
            return 0;

        /*testa e cria evento ENTRA*/
        if (!(evento = evento_cria(EV_ENTRA, tempo, id_heroi, id_base)))
            return 0;

        /*insere na fila de eventos*/
        fprio_insere(retorna_evento, evento, 0, 0);
    }

    return 1;
}

int evento_entra(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
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
    if (!(evento = evento_cria(EV_SAI, tpb + tempo, id_heroi, id_base)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(retorna_evento, evento, 0, 0);

    return 1;
}

int evento_sai(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
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
    base_destino = gera_aleat(0, mundo->base - 1);

    /*testa, cria e insere o evento VIAJA */
    if (evento = evento_cria(EV_VIAJA, tempo, id_heroi, base_destino))
        fprio_insere(retorna_evento, evento, 0, 0);
    else
        return 0;

    /*testa, cria e insere evento AVISA*/
    if ((evento = evento_cria(EV_AVISA, tempo, id_heroi, id_base)))
        fprio_insere(retorna_evento, evento, 0, 0);
    else
        return 0;

    return 1;
}

int evento_viaja(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base)
{
    struct evento_t *evento;
    struct cordenadas_t *distancia, *base_destino;
    int duracao;

    if (!mundo)
        return 0;

    /*testa se heroi está vivo ou morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*calcula a duração que o heroi leva até chegar na proxima base*/
    duracao = distancia_calc(mundo, id_base, id_heroi);

    /*imprime evento*/
    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, id_heroi, base_destino,
           id_base, distancia, mundo->heroi[id_heroi].velocidade, tempo + duracao);

    /*teste e cria evento CHEGA*/
    if (!(evento = evento_cria(EV_CHEGA, tempo + duracao, id_heroi, id_base)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(retorna_evento, evento, 0, 0);

    return 1;
}

int evento_morre(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base, unsigned int id_missao)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*retira o heroi do conjunto de herois da base*/
    if (!cjto_retira(mundo->base[id_base].presentes, id_heroi))
        return 0;

    /*Atualiza o status do herói para "morto"*/
    mundo->heroi[id_heroi].status = -1;

    /*imprime evento*/
    printf("%6d: MORRE  HEROI %2d MISSAO %d\n", tempo, id_heroi, mundo->missao[id_missao].id);

    /*Testa e cria o evento AVISA*/
    if (!(evento = evento_cria(EV_AVISA, tempo, 0, id_base)))
        return 1;

    /*insere na fila de eventos*/
    fprio_insere(retorna_evento, evento, 0, 0);

    return 1;
}

int evento_missao(struct mundo_t *mundo, unsigned int tempo, unsigned int id_missao)
{
    struct evento_t *evento;
    struct cjto_t *uniao_h;
    int base_apta, i, j;
    int distancia_base;

    if (!mundo)
        return 0;

    printf("%6d: MISSAO %d HAB REQ: ", tempo, id_missao);
    set_print(mundo->missao[id_missao].habilidades);
    printf("\n");

    /*Incrementa o número de tentativas da missão e seta a base_apta*/
    mundo->missao[id_missao].tentativas++;
    base_apta = -1;

    /*Percorre todas as bases*/
    for (i = 0; i < mundo->num_base; i++)
    {
        /*Calcula a distância da base à missão*/
        distancia_base = calcula_distancia(mundo->base[i].local, mundo->missao[id_missao].local);

        /*Cria a união das habilidades dos heróis presentes nesta base*/
        uniao_h = uniao_habil(mundo, i);

        printf("%6d: MISSAO %d HAB BASE %d DIST %d: ", tempo, id_missao, i, distancia_base);
        cjto_imprime(uniao_h);
        printf("\n");

        /*Verifica se as habilidades da base são suficientes para a missão*/
        if (cjto_contem(uniao_h, mundo->missao[id_missao].habilidades))
        {
            base_apta = i; /*Base apta encontrada*/
            cjto_destroi(uniao_h);
            break;
        }

        /*Libera a memória do conjunto de habilidades*/
        cjto_destroi(uniao_h);
    }

    /*Se encontrou uma base apta*/
    if (base_apta >= 0)
    {
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HEROIS: ", tempo, id_missao, base_apta);
        cjto_imprime(mundo->base[base_apta].presentes);
        printf("\n");

        mundo->missao[id_missao].realizada = 1;

        /*Incrementa a experiência dos heróis presentes na base*/
        for (j = 0; j < mundo->num_herois; j++)
            if (cjto_pertence(mundo->base[base_apta].presentes, j))
                mundo->heroi[j].experiencia++;
    }
    else
    {
        /*Se não encontrou uma base apta, missão é impossível*/
        printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo, id_missao);
        mundo->n_miss_impos++;

        /*Testa e cria um evento para tentar novamente em 24 horas*/
        if (!(evento = cria_evento(tempo + 24 * 60, EV_MISSAO, id_missao, 0)))
            return 0;

        /*insere na fila de eventos*/
        fprio_insere(retorna_evento, evento, 0, 0);
    }

    return 1;
}

int evento_fim(struct mundo_t *mundo, unsigned int tempo)
{
    if (!mundo)
        return 0;

    /*Exibe o tempo final da simulação*/
    printf("%d: FIM\n\n", tempo);

    

    
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
        if (!(evento = evento_cria(EV_CHEGA, tempo, i, base)))
            return 0;

        /*insere na fila de eventos*/
        fprio_insere(retorna_evento, evento, 0, 0);
    }

    /*cria evento MISSAO para cada missao*/
    for (i = 0; i < mundo->num_missao; i++)
    {
        /*Gera tempo aleatorio de 0 até (525600 - 1)*/
        tempo = gera_aleat(0, T_FIM_DO_MUNDO - 1);

        /*Testa e cria evento MISSAO*/
        if (!(evento = evento_cria(EV_MISSAO, tempo, i, 0)))
            return 0;

        /*insere na fila de eventos*/
        fprio_insere(retorna_evento, evento, 0, 0);
    }

    /*Testa e cria evento FIM DO MUNDO*/
    if (!(evento = evento_cria(EV_FIM, T_FIM_DO_MUNDO, 0, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(retorna_evento, evento, 0, 0);

    return 1;
}

int evento_seleciona(struct mundo_t *mundo, struct evento_t *evento)
{

}