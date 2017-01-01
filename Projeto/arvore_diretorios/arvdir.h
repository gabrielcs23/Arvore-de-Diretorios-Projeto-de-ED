#ifndef ARVDIR_H_INCLUDED
#define ARVDIR_H_INCLUDED

//definição da estrutura de árvore de diretório
typedef struct arvdir{
    struct arvdir *pai, *filho, *irmao;
    int arquivo;
    void *info;
}TAD;

//definição dos métodos básicos de árvores
TAD *cria (char *name, int arq, int perm, char tipo){
    char *c = (char*)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(c,name);
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

//liberar arvore da memoria
void liberar (TAD *a){
    TAD *p = a->filho;
    while(p){
        TAD *t = p->irmao;
        liberar(p);
        p = t;
    }
    if(a->arquivo){
        TArq *x = (TArq*) a->info;
        free(x->nome);
    }
    else{
        TDir *x = (TDir*) a->info;
        free(x->nome);
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
    if(!a->arquivo){
        TDir *aux = (TDir*)b->info;
        aux->num_dir++;
    }
    else{
        TDir *aux = (TDir*)b->info;
        aux->num_arq++;
    }
}

//remove um nó e seus filhos
void destruir (TAD *a, int atual){
    // probido destruir a raiz
    // param atual indica se vc quiser destuir tudo abaixo de cur_dir
    if(atual){
        while(a->filho)
            destruir(a->filho,0);
        return;
    }
    TAD *i;
    i = a->pai->filho;
    if(i == a) a->pai->filho = a->irmao;
    else{
        while (i->irmao != a) i = i->irmao;
        i->irmao = a->irmao;
    }
    //acerta a quant de itens dentro do diretorio pai
    TDir *aux = (TDir*)a->pai->info;
    if(!a->arquivo){
        aux->num_dir--;
    }
    else{
        aux->num_arq--;
    }
    liberar(a);
}
//busca e retorna o nó com o nome procurando-o na subárvore a
TAD* busca (TAD* a, char *c){
    if(!a) return NULL;
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

char * getNome(TAD *a){
    if(!a) return NULL;
    if(a->arquivo){
        TArq *aux = (TArq*)a->info;
        return aux->nome;
    }
    else{
        TDir *aux = (TDir*)a->info;
        return aux->nome;
    }
}

//nao verifica duplicatas; é chamada pela mv e recebe o no a ser alterado
void renomear(TAD *a, char *new_name){
    time_t tempo;
    time(&tempo);
    struct tm *info = localtime(&tempo);
    char *novo = (char*)malloc(sizeof(char)*(strlen(new_name)+1));
    strcpy(novo,new_name);
    if(a->arquivo){
        TArq *ar = (TArq*) a->info;
        ar->nome = novo;
        strftime(ar->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
    }
    else{
        TDir *dir = (TDir*) a->info;
        dir->nome = novo;
        strftime(dir->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
    }
}

void ler_c(char* str)
{
    fgets(str, 8, stdin);
    int i = 0;
    while (str[i] != '\n') i++;
    str[i] = '\0';
}

void transformar(TAD *a){
    if(!a){
        printf("Parâmetro inválido\n");
        return;
    }
    char *nome;
     if(a->arquivo){
         TArq *x = (TArq*) a->info;
         TDir *novo = criar_dir(x->nome);
         strcpy(novo->dat_criacao,x->dat_criacao);
         free(a->info);
         a->info = (void*) novo;
         a->arquivo = 0;
         TDir *pai = (TDir*) a->pai->info;
         pai->num_arq--;
         pai->num_dir++;
     }
     else{
         char tip;
         char c[8];
         ler_c(c);
         tip = c[0];
         TDir *x = (TDir*) a->info;
         TArq *novo = cria_arq(x->nome,tip,x->permissoes);
         strcpy(novo->dat_criacao,x->dat_criacao);
         free(a->info);
         a->info = (void*) novo;
         a->arquivo = 1;
         TDir *pai = (TDir*) a->pai->info;
         pai->num_arq++;
         pai->num_dir--;

     }
 }

#endif // ARVDIR_H_INCLUDED
