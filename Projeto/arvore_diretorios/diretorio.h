#ifndef DIRETORIO_H_INCLUDED
#define DIRETORIO_H_INCLUDED

#include <stdlib.h>

typedef struct diretorio{
    char *nome, dat_criacao[22], dat_atualiza[22];
    int permissoes, num_arq, num_dir;
}TDir;

TDir* criar_dir(char *c){
    TDir *n = (TDir*) malloc(sizeof(TDir));
    n->nome = c;
    time_t tempo;
    time(&tempo);
    struct tm *info = localtime(&tempo);
    strftime(n->dat_criacao,22,"%d/%m/%Y - %H:%M:%S", info);
    strftime(n->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
    n->num_arq = 0;
    n->num_dir = 0;
    n->permissoes = 0;
    return n;
}

#endif // DIRETORIO_H_INCLUDED
