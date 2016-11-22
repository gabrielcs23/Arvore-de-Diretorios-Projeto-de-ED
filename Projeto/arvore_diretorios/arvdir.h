#ifndef ARVDIR_H_INCLUDED
#define ARVDIR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "diretorio.h"
//definição da estrutura de árvore de diretório
typedef struct arvdir{
    struct arvdir *pai, *filho, *irmao;
    int arquivo;
    struct diretorio *info;
}TAD;

//definição dos métodos básicos de árvores
TAD * cria (char *c){
    TAD *a = (TAD*) malloc (sizeof(TAD));
    a->pai = NULL;
    a->filho = NULL;
    a->irmao = NULL;
    a->info = criar_dir(c);
    return a;
};

//inserção de subarvore "filho" em uma arvore "pai"
void inserir (TAD *afilho, TAD *apai){
    afilho->irmao = apai->filho;
    afilho->pai = apai;
    apai->filho = afilho;
}

//liberar arvore
void liberar (TAD *a){
    TAD *p = a->filho;
    while(p){
        TAD *t = p->irmao;
        liberar(p);
        p = t;
    }
    free(a);
}

//mover nó a para ser filho de nó b
void mover(TAD *a, TAD*b){
    if(a == a->pai->filho){
        a->pai->filho = a->irmao;
    } else {
        TAD *p = a->pai->filho;
        while(p->irmao != a) p = p->irmao;
        p->irmao = a->irmao;
    }
    a->pai = b;
    a->irmao = b->filho;
    b->filho = a;
}

//remove um nó e seus filhos
void remover (TAD *a){
    TAD *i;
    i = a->pai->filho;
    if(i == a) a->pai->filho = a->irmao;
    else{
        while (i->irmao != a) i = i->irmao;
        i->irmao = a->irmao;
    }
    liberar(a);
}
//busca e retorna o nó com o nome procurando-o na subárvore a
TAD* busca (TAD* a, char* c){
    TAD* p;
    if (a->info->nome==c) return p;
    else {
        for (p=a->filho; p; p=p->irmao) {
        if (busca(p,c)) return p;
        }
    }
    return NULL;
}

void imprime (TAD *a){
    TAD* p;
    printf("%s\n",a->info->nome);
    for (p=a->filho; p; p=p->irmao) imprime(p);
}



#endif // ARVDIR_H_INCLUDED
