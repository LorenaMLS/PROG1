#include "libConfeitaria.h"

struct frigobar cria_frigobar(struct frigobar frigo){
    int i;
    int j;

    for (i=0; i<20;i++){
        frigo.prat_cima[i] = 0;
    }


    for (j=0; i<10;j++){
        frigo.prat_baixo[j] = 0;
    }

    return frigo;
}


void aloca_produtos(struct frigobar frigobar){
    
};