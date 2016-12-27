#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "diretorio.h"
#include "arquivo.c"

//definição da estrutura de árvore de diretório
typedef struct arvdir{
    struct arvdir *pai, *filho, *irmao;
    int arquivo;
    void *info;
}TAD;

//definição dos métodos básicos de árvores
TAD *cria (char *c, int arq, int perm, char tipo){
    TAD *a = (TAD*) malloc (sizeof(TAD));
    if(arq){
        TArq *x = cria_arq(c, tipo, perm);
        a->info = (void*) x;
    }
    else{
        TDir *x = criar_dir(c);
        a->info = (void*) x;
    }
    a->pai = NULL;
    a->filho = NULL;
    a->irmao = NULL;
    a->info = criar_dir(c);
    a->arquivo = arq;
    return a;
};

//inserção de subarvore "filho" em uma arvore "pai"
void inserir (TAD *afilho, TAD *apai){
    if(apai->arquivo){
        printf("Insercoes apenas em diretorios\n");
        return;
    }
    afilho->irmao = apai->filho;
    afilho->pai = apai;
    apai->filho = afilho;
    if(!afilho->arquivo){
        TDir *aux = (TDir*)apai->info;
        aux->num_dir++;
    }
    else{
        TDir *aux = (TDir*)apai->info;
        aux->num_arq++;
    }
}

//liberar arvore
void liberar (TAD *a){
    TAD *p = a->filho;
    while(p){
        TAD *t = p->irmao;
        liberar(p);
        p = t;
    }
    free(a->info);
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
void destruir (TAD *a){
    if(!a->pai){
        destruir(a->filho);
    }
    TAD *i;
    i = a->pai->filho;
    if(i == a) a->pai->filho = a->irmao;
    else{
        while (i->irmao != a) i = i->irmao;
        i->irmao = a->irmao;
    }
    TAD *pai = a->pai;
    if(!pai->arquivo){
        TDir *aux = (TDir*)pai->info;
        aux->num_dir--;
    }
    else{
        TDir *aux = (TDir*)pai->info;
        aux->num_arq--;
    }
    liberar(a);
}
//busca e retorna o nó com o nome procurando-o na subárvore a
TAD* busca (TAD* a, char *c){
    if(a->arquivo){
        TArq *aux;
        aux = (TArq*) a->info;
        if (!strcmp(c, aux->nome)) return a;
        TAD *r, *p;
        for(p=a->filho;p;p=p->irmao){
            r = busca(p,c);
            if(r) return r;
        }
    }
    else{
        TDir *aux;
        aux = (TDir*) a->info;
        if (!strcmp(c, aux->nome)) return a;
        TAD *r, *p;
        for(p=a->filho;p;p=p->irmao){
            r = busca(p,c);
            if(r) return r;
            }
        }
    return NULL;
}

void imprime (TAD *a){
    TAD* p;
    TDir *aux = (TDir*)a->info;
    printf("%s\n",aux->nome);
    for (p=a->filho; p; p=p->irmao) imprime(p);
}
