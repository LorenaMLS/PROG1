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
  int i;
  // iniciar o mundo

  mundo = cria_mundo();

  if (!mundo)
    printf("mundo nao criado\n");

  printf("mundo criado\n");

  /*status dos herois criados*/
  printf("HEROIS\n\n");
  printf("quantidade de herois criados: %d\n", mundo->num_herois);
  for (i = 0; i < mundo->num_herois; i++)
  {
    printf("heroi id: %d\n", mundo->heroi[i].id);

    /*habilidades do heroi*/
    printf("heroi cap de habili: %d\n", mundo->heroi[i].habilidades->cap);
    printf("heroi habilidade num: %d\n", mundo->heroi[i].habilidades->num);
    printf("CONJUNTO DE HAB HEROI: ");
    cjto_imprime(mundo->heroi[i].habilidades);
    printf("\n");

    printf("heroi experiencia: %d\n", mundo->heroi[i].experiencia);
    printf("heroi paciencia: %d\n", mundo->heroi[i].paciencia);
    printf("heroi velocidade: %d\n", mundo->heroi[i].velocidade);
    printf("heroi id base: %d\n", mundo->heroi[i].id_base);
    printf("HEROIS\n\n");
  }

  /*status da base criada*/
  printf("BASE\n\n");
  printf("base num: %d\n", mundo->num_base);
  printf("base id: %d\n", mundo->base->id_base);
  printf("base local x: %d\n", mundo->base->local.x);
  printf("base local y: %d\n", mundo->base->local.y);
  printf("base lotação: %d\n", mundo->base->lotação);

  printf("base presentes: ");
  cjto_imprime(mundo->base->presentes);
  printf("\n");

  /*falha de segmentação*/
  /* printf("base espera: ");
  fprio_imprime(mundo->base->espera); */

  /*status das missões criadas*/
  printf("MISSÕES\n\n");
  printf("missao num: %d\n", mundo->num_missao);
  for (i = 0; i < mundo->num_missao; i++)
  {
    printf("missao id: %d\n", mundo->missao[i].id);
    printf("missao perigo: %d\n", mundo->missao[i].perigo);
    printf("missao local x: %d\n", mundo->missao[i].local.x);
    printf("missao local y: %d\n", mundo->missao[i].local.y);

    /*habilidades da missao*/
    printf("missao habilidades cap: %d\n", mundo->missao[i].habilidades->cap);
    printf("missao habilidades num: %d\n", mundo->missao[i].habilidades->num);
    printf("CONJUNTO DE HAB MISSAO: ");
    cjto_imprime(mundo->missao[i].habilidades);
    printf("\n");
  }

  mundo = destroi_mundo(mundo);
  // executar o laço de simulação

  // destruir o mundo

  return 0;
}
