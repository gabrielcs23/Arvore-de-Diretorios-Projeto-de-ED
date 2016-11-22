#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//defini��o da estrutura de �rvore de diret�rio
typedef struct arvdir{
    struct arvdir *pai, *filho, *irmao;
    char *nome;
    int arquivo;
    void *info;

}TAD;

//defini��o dos m�todos b�sicos de �rvores
TAD * cria (char *c){
    TAD *a = (TAD*) malloc (sizeof(TAD));
    a->pai = NULL;
    a->filho = NULL;
    a->irmao = NULL;
    a->nome = c;
    return a;
};

//inser��o de subarvore "filho" em uma arvore "pai"
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

//remove um n� e seus filhos
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
