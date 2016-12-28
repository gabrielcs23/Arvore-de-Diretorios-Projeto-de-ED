#ifndef DIRETORIO_H_INCLUDED
#define DIRETORIO_H_INCLUDED

#include <time.h>
//#include "arvdir.h"
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

/*TArq * TDtoTA(TDir *a, TAD *b){
    TArq * novo = (TArq*) malloc(sizeof(TArq));
    novo->nome = a->nome;
    novo->dat_criacao = a->dat_criacao;
    time_t tempo;
    time(&tempo);
    struct tm *info = localtime(&tempo);
    strftime(novo->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
    novo-> permissoes = a->permissoes;
    b->info = novo;
    free(a);
}*/

void renomear_dir(TDir *a, char* c){
    a->nome = c;
    time_t tempo;
    time(&tempo);
    struct tm *info = localtime(&tempo);
    strftime(a->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
}



#endif // DIRETORIO_H_INCLUDED
