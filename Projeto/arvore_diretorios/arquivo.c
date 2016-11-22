#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

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

void abrir_arq(TArq *a){
    char formato[2];
    formato[0] = 'r';
    strcat(formato,&a->tipo);
    a->arquivo = fopen(a->nome,formato);
    if(!a->arquivo){
        printf("Arquivo não encontrado!");
        fclose(a->arquivo);
        return;
    }
    char info[50];
    while((fgets(info,50,a->arquivo)) != NULL)
        printf("%s",info);
    fclose(a->arquivo);
}

void renomear_arq(TArq *a, char *novo_nome){
    char f1[2], f2[2];
    f1[0] = 'r';
    f2[0] = 'w';
    strcat(f1,&a->tipo);
    strcat(f2,&a->tipo);
    a->arquivo = fopen(a->nome,f1);
    if(!a->arquivo){
        printf("Arquivo não encontrado!");
        fclose(a->arquivo);
        return;
    }
    FILE *novo = fopen(novo_nome,f2);
    char info[50];
    while((fgets(info,50,a->arquivo)) != NULL)
        fprintf(novo,"%s",info);
    fclose(a->arquivo);
    fclose(novo);
    remove(a->nome);
    a->nome = novo_nome;
}
