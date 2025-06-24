#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
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
    struct cjto_t *uniao = NULL;
    struct cjto_t *tmp = NULL;
    int i;

    if (!mundo || id_base < 0 || id_base >= mundo->num_base)
        return NULL;

    uniao = cjto_cria(N_HABILIDADES);
    if (!uniao)
        return NULL;

    for (i = 0; i < mundo->num_herois; i++)
    {
        if (cjto_pertence(mundo->base[id_base].presentes, i) == 1)
        {
            if (!mundo->heroi[i].habilidades || !mundo->heroi[i].habilidades->flag)
            {
                printf("ERRO: herói %d com habilidades inválidas\n", i);
                cjto_destroi(uniao);
                return NULL;
            }

            tmp = cjto_uniao(uniao, mundo->heroi[i].habilidades);
            if (!tmp)
            {
                cjto_destroi(uniao);
                return NULL;
            }

            cjto_destroi(uniao);
            uniao = tmp;
        }
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
    if (cjto_card(mundo->base[id_base].presentes) < mundo->base[id_base].lotacao && !fila_tamanho(mundo->base[id_base].espera))
        espera = 1;
    else if (mundo->heroi[id_heroi].paciencia > (10 * (fila_tamanho(mundo->base[id_base].espera))))
        espera = 1;
    else
        espera = 0;

    /*Imprime o evento*/
    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) %s\n", tempo, id_heroi, id_base,
           cjto_card(mundo->base[id_base].presentes),
           mundo->base[id_base].lotacao, espera ? "ESPERA" : "DESISTE");

    /*se o heroi espera então cria evento ESPERA, se não cria evento DESISTE*/
    if (espera)
    {
        evento = evento_cria(EV_ESPERA, tempo, id_heroi, id_base, 0);
        fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
    }
    else
    {
        evento = evento_cria(EV_DESISTE, tempo, id_heroi, id_base, 0);
        fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
    }

    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_espera(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;
    int *id_copia;

    if (!mundo)
        return 0;

    /*Testa se herói está vivo*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*Imprime o herói na fila*/
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
           tempo, id_heroi, id_base,
           cjto_card(mundo->base[id_base].presentes));

    /*Aloca cópia do ID para inserir na fila genérica*/
    id_copia = malloc(sizeof(int));
    if (!id_copia)
        return 0;
    *id_copia = id_heroi;

    /* Insere herói na fila de espera da base */
    if (fila_insere(mundo->base[id_base].espera, id_copia) == -1)
    {
        free(id_copia); /*Libera memória se falhar a inserção*/
        return 0;
    }

    /*Atualiza tamanho máximo da fila se necessáriO*/
    int tamanho_fila = fila_tamanho(mundo->base[id_base].espera);
    if (tamanho_fila > mundo->base[id_base].fila_max)
        mundo->base[id_base].fila_max = tamanho_fila;

    /*Cria e agenda evento AVISA*/
    evento = evento_cria(EV_AVISA, tempo, id_heroi, id_base, 0);
    if (!evento || !fprio_insere(mundo->fprio_eventos, evento, 0, tempo))
        return 0;

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
    printf("%6d: DESIST HEROI %2d BASE %d\n", tempo, id_heroi, id_base);

    /*gera uma base aleatoria para o heroi seguir*/
    base_destino = gera_aleat(0, mundo->num_base - 1);

    /*testa e cria evento VIAJA*/
    if (!(evento = evento_cria(EV_VIAJA, tempo, id_heroi, base_destino, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_avisa(struct mundo_t *mundo, int tempo, int id_heroi, int id_base)
{
    struct evento_t *evento;
    struct fila_t *espera;
    struct cjto_t *presentes;
    int lotacao;
    int *id_ptr;

    if (!mundo)
        return 0;

    /*Acessa a fila de espera, conjunto de presentes e lotação da base informada*/
    espera = mundo->base[id_base].espera;
    presentes = mundo->base[id_base].presentes;
    lotacao = mundo->base[id_base].lotacao;

    /*Testa se o herói está vivo; se estiver morto, a função retorna sem efeito*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*Imprime o estado atual da base: número de heróis presentes e a fila de espera*/
    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [",
           tempo, id_base,
           cjto_card(presentes),
           lotacao);
    fila_imprime(espera);
    printf(" ]\n");

    /*Enquanto houver espaço na base e a fila de espera não estiver vazia*/
    while (cjto_card(presentes) < lotacao && espera->prim != NULL)
    {
        id_ptr = fila_retira(espera);
        if (!id_ptr)
            break;

        /*Extrai o id do herói da memória alocada e libera essa memória*/
        id_heroi = *id_ptr;
        free(id_ptr);

        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", tempo, id_base, id_heroi);

        if (!(cjto_insere(presentes, id_heroi)))
            return 0;

        /*Cria um novo evento do tipo ENTRA para esse herói e insere na fila de prioridade*/
        if (!(evento = evento_cria(EV_ENTRA, tempo, id_heroi, id_base, 0)))
            return 0;
        fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
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
    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, id_heroi, id_base,
           cjto_card(mundo->base[id_base].presentes),
           mundo->base[id_base].lotacao,
           tempo + tpb);

    /*testa e cria evento SAI*/
    if (!(evento = evento_cria(EV_SAI, tpb + tempo, id_heroi, id_base, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, 0, tempo + tpb);
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

    /*retira o heroi do conjunto de presentes da base*/
    if (!(cjto_retira(mundo->base[id_base].presentes, id_heroi)))
        return 0;

    /*imprime evento*/
    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, id_heroi, id_base,
           cjto_card(mundo->base[id_base].presentes),
           mundo->base[id_base].lotacao);

    /*gera uma base aleatoria de destino*/
    base_destino = gera_aleat(0, mundo->num_base - 1);

    /*testa, cria e insere o evento VIAJA */
    if ((evento = evento_cria(EV_VIAJA, tempo, id_heroi, base_destino, 0)))
        fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
    else
        return 0;

    /*testa, cria e insere evento AVISA*/
    if ((evento = evento_cria(EV_AVISA, tempo, 0, id_base, 0)))
        fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
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
    if (duracao == 0)
        duracao = 1;

    /*imprime evento*/
    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
           tempo, id_heroi, base_origem,
           id_base, distancia, mundo->heroi[id_heroi].velocidade, tempo + duracao);

    /*teste e cria evento CHEGA*/
    if (!(evento = evento_cria(EV_CHEGA, tempo + duracao, id_heroi, id_base, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, 0, tempo + duracao);
    atualiza_relogio(mundo, tempo);

    return 1;
}

int evento_morre(struct mundo_t *mundo, int tempo, int id_heroi, int id_base, int id_missao)
{
    struct evento_t *evento;

    if (!mundo)
        return 0;

    /*Verifica se o herói já está morto*/
    if (!heroi_testa(mundo, id_heroi))
        return 0;

    /*Se foi por missão com Composto V*/
    if (id_missao != -1)
    {
        /*Marca a missão como cumprida*/
        mundo->missao[id_missao].realizada = 1;
        mundo->total_missoes_cumpridas++;

        /*Incrementa experiência dos outros heróis da base*/
        for (int i = 0; i < mundo->num_herois; i++)
        {
            if (i != id_heroi && cjto_pertence(mundo->base[id_base].presentes, i) && mundo->heroi[i].status == 1)
                mundo->heroi[i].experiencia++;
        }
    }

    /*Retira o herói da base*/
    if (!cjto_retira(mundo->base[id_base].presentes, id_heroi))
        return 0;

    /*Atualiza status do herói para morto*/
    mundo->heroi[id_heroi].status = 0;
    mundo->total_mortes++;

    /*Imprime evento*/
    if (id_missao != -1)
        printf("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, id_heroi, id_missao);
    else
        printf("%6d: MORRE HEROI %2d\n", tempo, id_heroi);

    /*Avisa o porteiro sobre a vaga liberada*/
    if (!(evento = evento_cria(EV_AVISA, tempo, id_base, 0, 0)))
        return 0;

    fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
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
    int base_mp, i;
    int mais_experiente = -1;
    int max_exp = -1;

    /*Verifica validade dos parâmetros e do mundo*/
    if (!mundo || id_missao < 0 || id_missao >= mundo->num_missoes)
    {
        printf("ERRO: mundo ou id_missao inválido\n");
        return 0;
    }

    /*Ponteiro para a missão a ser processada*/
    struct missao_t *mis = &mundo->missao[id_missao];

    /*Verifica validade do conjunto de habilidades da missão*/
    if (!mis || !mis->habilidades || !mis->habilidades->flag || mis->habilidades->cap <= 0)
    {
        printf("ERRO: missão %d com conjunto inválido\n", id_missao);
        return 0;
    }

    /*Se a missão já foi abandonada anteriormente, ignora*/
    if (mis->realizada == -1)
    {
        printf("%6d: MISSAO %d IGNORADA (já abandonada)\n", tempo, id_missao);
        return 1;
    }

    /*Conjunto de habilidades exigidas pela missão*/
    struct cjto_t *hab = mis->habilidades;

    /*Obtém a base mais próxima da missão*/
    base_mp = retorna_base_prox(mundo, id_missao);
    if (base_mp < 0 || base_mp >= mundo->num_base)
    {
        printf("ERRO: base mais próxima inválida (%d)\n", base_mp);
        return 0;
    }

    /*Cria o conjunto união das habilidades dos heróis presentes na base*/
    uniao_base = uniao_habil(mundo, base_mp);
    if (!uniao_base || !uniao_base->flag || uniao_base->cap <= 0)
    {
        printf("ERRO: união de habilidades da base %d inválida\n", base_mp);
        return 0;
    }

    /*Atualiza o número de tentativas da missão*/
    mis->tentativas++;
    mundo->tentativas_por_missao[id_missao]++;

    /*Imprime habilidades presentes na base*/
    printf("%6d: HABS BASE %d: ", tempo, base_mp);
    cjto_imprime(uniao_base);
    printf("\n");

    /*Imprime habilidades requeridas pela missão*/
    printf("%6d: MISSAO %d TENT %d HAB REQ: ", tempo, id_missao, mis->tentativas);
    cjto_imprime(hab);
    printf("\n");

    /*A base tem todas as habilidades da missão*/
    if (cjto_contem(uniao_base, hab))
    {
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: ", tempo, id_missao, base_mp);
        cjto_imprime(uniao_base);
        printf("\n");

        /*Marca a missão como cumprida*/
        mis->realizada = 1;
        mundo->total_missoes_cumpridas++;
        mundo->base[base_mp].missoes++;

        /*Todos os heróis presentes e vivos ganham experiência*/
        for (i = 0; i < mundo->num_herois; i++)
        {
            if (cjto_pertence(mundo->base[base_mp].presentes, i) && mundo->heroi[i].status == 1)
                mundo->heroi[i].experiencia++;
        }

        cjto_destroi(uniao_base);
        return 1;
    }

    /*Tentativa de cumprir a missão com Composto V*/
    if (mundo->n_composto_v > 0 &&
        tempo % 2500 == 0 &&
        cjto_card(mundo->base[base_mp].presentes) > 0)
    {
        /*Encontra o herói mais experiente da base*/
        for (i = 0; i < mundo->num_herois; i++)
        {
            if (cjto_pertence(mundo->base[base_mp].presentes, i) &&
                mundo->heroi[i].status == 1 &&
                mundo->heroi[i].experiencia > max_exp)
            {
                max_exp = mundo->heroi[i].experiencia;
                mais_experiente = i;
            }
        }

        if (mais_experiente != -1)
        {
            printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: ", tempo, id_missao, base_mp);
            cjto_imprime(uniao_base);
            printf(" (COM COMPOSTO V)\n");

            /*Marca missão como realizada*/
            mis->realizada = 1;
            mundo->total_missoes_cumpridas++;
            mundo->base[base_mp].missoes++;
            mundo->n_composto_v--;

            /*Os outros heróis (vivos e diferentes do sacrificado) ganham experiência*/
            for (i = 0; i < mundo->num_herois; i++)
            {
                if (i != mais_experiente &&
                    cjto_pertence(mundo->base[base_mp].presentes, i) &&
                    mundo->heroi[i].status == 1)
                {
                    mundo->heroi[i].experiencia++;
                }
            }

            /*Agenda evento de morte para o herói mais experiente*/
            evento = evento_cria(EV_MORRE, tempo, mais_experiente, base_mp, id_missao);
            if (!evento || !fprio_insere(mundo->fprio_eventos, evento, 0, tempo))
            {
                cjto_destroi(uniao_base);
                return 0;
            }

            cjto_destroi(uniao_base);
            return 1;
        }
    }

    /*Missão impossível no momento*/
    printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo, id_missao);

    /*Se excedeu 10 tentativas, marca como abandonada*/
    if (mis->tentativas > 10)
    {
        printf("%6d: MISSAO %d ABANDONADA APÓS %d TENTATIVAS\n", tempo, id_missao, mis->tentativas);
        mis->realizada = -1;
        cjto_destroi(uniao_base);
        return 1;
    }

    /*Agenda nova tentativa após 1 dia (1440 minutos)*/
    evento = evento_cria(EV_MISSAO, tempo + 24 * 60, id_missao, 0, 0);
    if (!evento || !fprio_insere(mundo->fprio_eventos, evento, 0, tempo + 24 * 60))
    {
        cjto_destroi(uniao_base);
        return 0;
    }

    cjto_destroi(uniao_base);
    return 1;
}

int evento_fim(struct mundo_t *mundo, int tempo)
{
    int i, tentativas, min_tent = 1000000, max_tent = 0;
    double soma_tent = 0.0, media_tent = 0.0, taxa_morte = 0.0, taxa_sucesso = 0.0;

    if (!mundo)
        return 0;

    /*Exibe o tempo final da simulação*/
    printf("%d: FIM\n\n", tempo);

    /*imprime os status finais de cada heroi*/
    for (i = 0; i < mundo->num_herois; i++)
    {
        if (!mundo->heroi[i].habilidades)
            continue;

        if (mundo->heroi[i].status == 1)
        {
            printf("HEROI %2d VIVO  PAC %3d ", mundo->heroi[i].id, mundo->heroi[i].paciencia);
            printf("VEL %4d EXP %4d ", mundo->heroi[i].velocidade, mundo->heroi[i].experiencia);
            printf("HABS ");
            cjto_imprime(mundo->heroi[i].habilidades);
        }
        else
        {
            printf("HEROI %2d MORTO PAC %3d ", mundo->heroi[i].id, mundo->heroi[i].paciencia);
            printf("VEL %4d EXP %4d ", mundo->heroi[i].velocidade, mundo->heroi[i].experiencia);
            printf("HABS ");
            cjto_imprime(mundo->heroi[i].habilidades);
        }
    }

    /*imprime os status finais de cada base*/
    for (i = 0; i < mundo->num_base; i++)
    {
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",
               mundo->base[i].id_base,
               mundo->base[i].lotacao,
               mundo->base[i].fila_max,
               mundo->base[i].missoes);
    }

    /*imprime total de eventos processados*/
    printf("EVENTOS TRATADOS: %d\n", mundo->total_eventos_processados);

    /*imprime total de missoes cumpridas*/
    if (mundo->num_missoes > 0)
        taxa_sucesso = (mundo->total_missoes_cumpridas * 100.0) / mundo->num_missoes;

    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n",
           mundo->total_missoes_cumpridas,
           mundo->num_missoes,
           taxa_sucesso);

    /*calcula tentativas por missão (min, max, média)*/
    for (i = 0; i < mundo->num_missoes; i++)
    {
        tentativas = mundo->tentativas_por_missao[i];

        if (tentativas < min_tent)
            min_tent = tentativas;

        if (tentativas > max_tent)
            max_tent = tentativas;

        soma_tent += tentativas;
    }

    if (mundo->num_missoes > 0)
        media_tent = soma_tent / mundo->num_missoes;

    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",
           min_tent, max_tent, media_tent);

    /*taxa de mortalidade*/
    if (mundo->num_herois > 0)
        taxa_morte = (mundo->total_mortes * 100.0) / mundo->num_herois;

    printf("TAXA MORTALIDADE: %.1f%%\n", taxa_morte);

    atualiza_relogio(mundo, tempo);

    return 1;
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
        fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
    }

    /*cria evento MISSAO para cada missao*/
    for (i = 0; i < mundo->num_missoes; i++)
    {
        /*Gera tempo aleatorio de 0 até (525600 - 1)*/
        tempo = gera_aleat(0, T_FIM_DO_MUNDO -1);

        /*Testa e cria evento MISSAO*/
        if (!(evento = evento_cria(EV_MISSAO, tempo, i, 0, 0)))
            return 0;

        /*insere na fila de eventos*/
        fprio_insere(mundo->fprio_eventos, evento, 0, tempo);
    }

    /*Testa e cria evento FIM DO MUNDO*/
    if (!(evento = evento_cria(EV_FIM, T_FIM_DO_MUNDO, 0, 0, 0)))
        return 0;

    /*insere na fila de eventos*/
    fprio_insere(mundo->fprio_eventos, evento, 0, T_FIM_DO_MUNDO);

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
