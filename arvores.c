#include <stdlib.h>
#include <time.h>

//defini��o da estrutura de �rvore de diret�rio
typedef struct arvdir{
    struct arvdir *pai, *filho, *irmao;
    char[] nome, dat_criacao, dat_atualiza, permissoes;
    int num_de_dir, arquivo;

}TAD;

//defini��o dos m�todos b�sicos de �rvores
TAD * cria (char[] c){
    TAD *a = (TAD*) malloc (sizeof(TAD));
    a.pai = NULL;
    a.filho = NULL;
    a.irmao = NULL;
    nome = c;

    sprintf(dat_criacao, "%d/%d/%d %d:%d:%d", )
};
