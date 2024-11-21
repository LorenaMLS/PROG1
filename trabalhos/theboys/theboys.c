// programa principal do projeto "The Boys - 2024/2"
// Autor: Lorena Moreira, GRR 20221244

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "conjunto.h"
#include "lista.h"
#include "fprio.h"

// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main()
{
  struct heroi_t *heroi;
  // iniciar o mundo

  heroi = cria_herois(2);

  if (!heroi)
  {
    printf("heroi não criado\n");
    return 0;
  }

  printf("heroi criado\n");

  heroi = destroi_herois(heroi);

  if (!heroi)
  {
    printf("heroi não destruido\n");
    return 0;
  }

  printf("heroi destuido");
  // executar o laço de simulação

  // destruir o mundo

  return 0;
}
