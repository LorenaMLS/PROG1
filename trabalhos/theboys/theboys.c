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
  srand(0);
  mundo = cria_mundo();

  if (!mundo)
    printf("MUNDO NÃO CRIADO\n");

  printf("MUNDO CRIADO\n");

  heroi_imprime(mundo);
  base_imprime(mundo);
  missao_imprime(mundo);

 

  // executar o laço de simulação

  // destruir o mundo
  mundo = destroi_mundo(mundo);

  return 0;
}
