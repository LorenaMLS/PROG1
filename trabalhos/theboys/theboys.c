// programa principal do projeto "The Boys - 2025/1"
// Autor: Lorena Moreira, GRR 20221244

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "eventos.h"

// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main()
{
  struct mundo_t *mundo;
  struct evento_t *evento = NULL;
  int aux;

  // iniciar o mundo
  srand(0);
  mundo = cria_mundo();

  if (!mundo)
    printf("MUNDO NÃO CRIADO\n");

  printf("MUNDO CRIADO\n");

  evento_inicia(mundo);
  fprio_imprime(mundo->fprio_eventos);

  while (retorna_relogio(mundo) < T_FIM_DO_MUNDO)
  {
    evento = fprio_retira(retorna_evento(mundo), &aux, &aux);
    evento_printar(evento);

    switch (evento->tipo)
    {
    case EV_CHEGA:
      evento_chega(mundo, retorna_relogio(mundo), retorna_dado1(evento), retorna_dado2(evento));
      break;

    case EV_ESPERA:
      evento_espera(mundo, retorna_relogio(mundo), retorna_dado1(evento), retorna_dado2(evento));
      break;

    case EV_DESISTE:
      evento_desiste(mundo, retorna_relogio(mundo), retorna_dado1(evento), retorna_dado2(evento));
      break;

    case EV_AVISA:
      evento_avisa(mundo, retorna_relogio(mundo), retorna_dado1(evento), retorna_dado2(evento));
      break;

    case EV_ENTRA:
      evento_entra(mundo, retorna_relogio(mundo), retorna_dado1(evento), retorna_dado2(evento));
      break;

    case EV_SAI:
      evento_sai(mundo, retorna_relogio(mundo), retorna_dado1(evento), retorna_dado2(evento));
      break;

    case EV_VIAJA:
      evento_viaja(mundo, retorna_relogio(mundo), retorna_dado1(evento), retorna_dado2(evento));
      break;

    case EV_MORRE:
      evento_morre(mundo, retorna_relogio(mundo), retorna_dado1(evento), retorna_dado2(evento), retorna_dado3(evento));
      break;

    case EV_MISSAO:
      evento_missao(mundo, retorna_relogio(mundo), retorna_dado1(evento));
      break;

    case EV_FIM:
      evento_fim(mundo, retorna_relogio(mundo));
      break;

    default:
      break;
    }
    evento_destroi(evento);
  }

  // destruir o mundo
  mundo = destroi_mundo(mundo);

  return 0;
}