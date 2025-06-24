// programa principal do projeto "The Boys - 2025/1"
// Autor: Lorena Moreira, GRR 20221244

#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "entidades.h"
#include "eventos.h"

#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABILIDADES * 3)

// programa principal
int main()
{
  struct mundo_t *mundo;
  struct evento_t *evento = NULL;
  int prioridade, tempo;

  srand(0);
  mundo = cria_mundo();

  if (!mundo)
  {
    printf("MUNDO NÃO CRIADO\n");
    return 1;
  }

  printf("MUNDO CRIADO\n");

  evento_inicia(mundo);

  while ((evento = fprio_retira(mundo->fprio_eventos, &prioridade, &tempo)))
  {
    if (!evento)
    {
      printf("evento vazio (NULL)\n");
      continue;
    }

    evento_printar(evento);
    atualiza_relogio(mundo, evento->tempo);

    switch (evento->tipo)
    {
    case EV_CHEGA:
      evento_chega(mundo, evento->tempo, evento->dado1, evento->dado2);
      break;

    case EV_ESPERA:
      evento_espera(mundo, evento->tempo, evento->dado1, evento->dado2);
      break;

    case EV_DESISTE:
      evento_desiste(mundo, evento->tempo, evento->dado1, evento->dado2);
      break;

    case EV_AVISA:
      evento_avisa(mundo, evento->tempo, evento->dado1, evento->dado2);
      break;

    case EV_ENTRA:
      evento_entra(mundo, evento->tempo, evento->dado1, evento->dado2);
      break;

    case EV_SAI:
      evento_sai(mundo, evento->tempo, evento->dado1, evento->dado2);
      break;

    case EV_VIAJA:
      evento_viaja(mundo, evento->tempo, evento->dado1, evento->dado2);
      break;

    case EV_MORRE:
      evento_morre(mundo, evento->tempo, evento->dado1, evento->dado2, evento->dado3);
      break;

    case EV_MISSAO:
      evento_missao(mundo, evento->tempo, evento->dado1);
      break;

    case EV_FIM:
      evento_fim(mundo, evento->tempo);
      break;

    default:
      printf("Evento desconhecido: tipo %d\n", evento->tipo);
      break;
    }

    evento_destroi(evento);
    mundo->total_eventos_processados++;
  }

  mundo = destroi_mundo(mundo);
  return 0;
}
