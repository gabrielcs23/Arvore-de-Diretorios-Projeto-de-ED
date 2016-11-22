#include <stdlib.h>
#include <stdio.h>

//definição da estrutura de árvore de diretório
typedef struct arvdir{
    struct arvdir *pai, *filho, *irmao;
    char *nome;
    int arquivo;
    void *info;

}TAD;

//definição dos métodos básicos de árvores
TAD * cria (char *c){
    TAD *a = (TAD*) malloc (sizeof(TAD));
    a->pai = NULL;
    a->filho = NULL;
    a->irmao = NULL;
    a->nome = c;
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

void imprime (TAD *a){
    TAD* p;
    printf("%s\n",a->nome);
    for (p=a->filho; p; p=p->irmao) imprime(p);
}
