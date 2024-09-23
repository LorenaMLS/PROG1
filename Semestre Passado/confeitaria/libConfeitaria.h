struct frigobar {
    struct bolo_pote *prat_cima[20];
    struct tortinhas *prat_baixo[10];

};

struct bolo_pote {
    char sabor;
    int dataFabr;
};

struct tortinhas {
    int dataFabr;
    int diasConsu;
};

struct data {
    int dia;
    int mes;
    int ano;
};



struct frigobar cria_frigobar();

void cria_produtos();

void aloca_produtos();

void lista_produtos();

void destroi_produtos();

void destroi_frigobar();
