#ifndef EVENTOS_H
#define EVENTOS_H

#include "lista.h"
#include "fprio.h"
#include "conjunto.h"

/*Define Lista*/
#define L_FIM -1
#define L_INICIO 0
/*Tipos de eventos que vao entrar na lef:
NAO usar 0 ou -1 pois sao #defines da lista_t*/
#define EV_CHEGA 1
#define EV_ESPERA 2
#define EV_DESISTE 3
#define EV_AVISA 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_VIAJA 7
#define EV_MISSAO 8
#define EV_FIM 9

struct evento_t
{
    int tempo; /* tempo logico do evento */
    int tipo;  /* inteiro para diferenciar os diferentes tipos de evento */
    int dado1; /* um inteiro para guardar dados do evento */
    int dado2; /* um inteiro para guardar dados do evento */
};

/*cria evento e retorna ponteiro ou NULL se erro*/
struct evento_t *evento_cria ();

/*destroi estrutura de dados do evento*/
/*retorno NULL*/
struct evento_t *evento_destroi (struct evento_t *evento);

/*Representa um herói H chegando em uma base B no instante T.*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_chega(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base);

/*O herói H entra na fila de espera da base B. Assim que H entrar na fila,
 o porteiro da base B deve ser avisado para verificar a fila*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_espera(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base);

/*herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja para lá*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_desiste(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base);

/*Porteiro da base B trata a fila de espera*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_avisa(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base);

/*Herói H entra na base B. Ao entrar, o herói decide quanto tempo vai ficar e agenda sua saída da base*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_entra(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base);

/*Herói H sai da base B. Ao sair, escolhe uma base de destino para viajar;
porteiro de B é avisado, pois uma vaga foi liberada*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_sai(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base);

/*Herói H se desloca para uma base D (que pode ser a mesma onde já está)*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_viaja(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base);

/*Herois morre no instante T; O herói é retirado da base B e libera vaga e o porteiro avisado;
Eventos futuros de um herói morto devem ser ignorados*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_morre(struct mundo_t *mundo, unsigned int tempo, unsigned int id_heroi, unsigned int id_base);

/*Missão é iniciada no instante T*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_missao(struct mundo_t *mundo, unsigned int tempo);

/*Encerra a simulação de mundo no instante T*/
/*retorno: 1 se sucesso ou 0 se erro*/
int evento_fim(struct mundo_t *mundo, unsigned int tempo);

#endif