#include <stdlib.h>
#include "arvdir.c"

int main(){
    TAD *raiz = cria("marcelo caralho");
    TAD *filho1 = cria("no");
    inserir(filho1,raiz);
    TAD *irmao1 = cria("enfia");
    inserir(irmao1,raiz);
    TAD *filho2 = cria("cu");
    inserir(filho2,filho1);
    remover(filho1);
    imprime(raiz);
    liberar(raiz);
    return 0;
}
