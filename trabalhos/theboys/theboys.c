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
  struct mundo_t *mundo;

  // iniciar o mundo

  mundo = cria_mundo();

  if (!mundo)
    printf("mundo nao criado\n");

  printf("mundo criado\n");

  // executar o laço de simulação

  // destruir o mundo
  destroi_mundo(mundo);

  if (!mundo)
    printf("erro\n");
  
  printf("mundo destruido\n");

  return 0;
}
