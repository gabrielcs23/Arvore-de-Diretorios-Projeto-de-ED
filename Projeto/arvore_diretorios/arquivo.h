#ifndef ARQUIVO_H_INCLUDED
#define ARQUIVO_H_INCLUDED

#include <stdlib.h>

typedef struct arq{
    char *nome, tipo, dat_criacao[22], dat_atualiza[22];
    int permissoes;
    FILE *arquivo;
}TArq;

TArq *cria_arq(char *c, char tipo, int perm){
    TArq *a = (TArq*)malloc(sizeof(TArq));
    a->nome = c;
    a->tipo = tipo;
    time_t tempo;
    time(&tempo);
    struct tm *info = localtime(&tempo);
    strftime(a->dat_criacao,22,"%d/%m/%Y - %H:%M:%S", info);
    strftime(a->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
    a->permissoes = perm;
    return a;
}

#endif // ARQUIVO_H_INCLUDED
