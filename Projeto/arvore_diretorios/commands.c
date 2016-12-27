#define BUFFER_SIZE 256
#define MAX_NAME_SIZE 100
#define SEPARADOR '/'

#include <stdio.h>
#include "arvdir.c"

void print_info(TAD* a);
TAD* busca_filhos (TAD* a, char* c);
//TAD* busca_genu (TAD* a, char *c);

// ls

void ls(TAD* cur_dir)
{
	TAD *p;
	int tamNome = 0;
	for (cur_dir->filho; p; p->irmao)
	{
		if(p->arquivo){
            TArq *aux = (TArq*)p->info;
            printf(aux->nome);
            tamNome = strlen(aux->nome);
		}
		else{
            TDir *aux = (TDir*)p->info;
            printf("/");
            printf(aux->nome);
            tamNome = strlen(aux->nome);
		}
		// espaços pra deixar mais bonitinho:
		int i;
		for (i = tamNome; i < MAX_NAME_SIZE; i++)
		{
			printf(" ");
		}

		print_info(p);
	}
}

// cd

TAD* cd(TAD* cur_dir, char* command_line)	// bugres: "cd //////////filho1/filho1filho1" funciona.
{
	TAD* original_dir = cur_dir;
	char address[MAX_NAME_SIZE];
	int i = 2, j = 0;

	// cd .. para ir um nível acima
	if ((command_line[2] == ' ') && (command_line[3] == '.') && (command_line[4] == '.'))
	{
		if(cur_dir->pai)
			cur_dir = cur_dir->pai;
		i += 2;
	}

	while ((command_line[i] != '\n') || (command_line[i] != '\0'))
	{
		i++;
		if (command_line[i] == SEPARADOR || command_line[i] == '\0')
		{
			if (j > 0) // se 'address' não for vazia
			{
				address[j] = '\0';

				TAD* new_dir = busca_filhos(cur_dir, address);
				if (new_dir) // se encontrar o endereço, continua até o final do comando
					cur_dir = new_dir;
				else // se não encontrar o endereço, cancela o comando
					return original_dir;

				j = 0;
			}
		}
		else
		{
			address[j] = command_line[i];
			j++;
		}
	}

	return cur_dir;
}

// mv

void mv(TAD* a, char* command_line)
{
	// fazer um "getxxxxx()" baseado no formato do cd e no diretorio atual. usar aqui e no cd...

}

// rename

// rm

// mkdir
void mkdir(TAD *a, char* command_line)
{
	char address[MAX_NAME_SIZE];
	int i = 2, j = 0;
	while ((command_line[i] != '\n') || (command_line[i] != '\0'))
	{
		i++;
		if (command_line[i] == '\0')
		{
			if (j > 0) // se 'address' não for vazia
			{
				address[j] = '\0';
				TAD *ins = cria(address,0,0,'n');
				inserir(ins,a);
			}
		}
		else
		{
			address[j] = command_line[i];
			j++;
		}
	}
}

// new file (touch?)

// info, etc

void print_info(TAD* a)
{
	int i;
	if(a->arquivo){
        TArq *aux = (TArq*)a->info;
        printf("Criado em: %s    Modificado em: %s\n", aux->dat_criacao, aux->dat_atualiza);
        for (i = 0; i < MAX_NAME_SIZE; i++)	printf(" "); 	// espaços pra deixar mais bonitinho?
        printf("Permissoes: %d", aux->permissoes);
        printf("\n");
	}
	else{
        TDir *aux = (TDir*)a->info;
        printf("Criado em: %s    Modificado em: %s\n", aux->dat_criacao, aux->dat_atualiza);
        for (i = 0; i < MAX_NAME_SIZE; i++)	printf(" "); 	// espaços pra deixar mais bonitinho?
        printf("Permissoes: %d", aux->permissoes);
        printf("    Num. de Arquivos: %d    Num. de Pastas: %d\n", aux->num_arq, aux->num_dir);
	}
}

TAD* busca_filhos (TAD* a, char* c)
{

	for (a = a->filho; a; a = a->irmao)
	{
		if (!strcmp(c,getNome(a)))
		{
			return a;
		}
	}
	return NULL;
}

char **split(char *command_line, int tam_max){
    //retorn nulo se numero de argumentos for maior que tam_max
    //ou se for menor
    //precisa dar free nos retornos
    char **resp = (char**)malloc(sizeof(char*)*(tam_max));
    int i,j,p;
    int len = strlen(command_line);
    for(i=0;i<tam_max;i++){
        int corte = 0;
        p = 0;
        resp[i] = (char*)malloc(sizeof(char)*BUFFER_SIZE);
        while(j<len){
            if(command_line[j]=='\''){
                corte = (corte+1)%2;
            }
            else if(command_line[j]!=' ' || corte){
                resp[i][p] = command_line[j];
                p++;
            }

            else{
                resp[i] = realloc(resp[i],p);
                resp[i][p] = '\0';
                j++;
                break;
            }
            j++;
        }
        if(j==len && i<tam_max){
            printf("ERRO\n");
            free(resp);
            return NULL;
        }
        //resp[i] = elem;
    }
    if(j<len){
        printf("ERRO\n");
        free(resp);
        return NULL;
    }
    return resp;
}

TAD *getLocal(char *str){

}

/*TAD* busca_genu (TAD* a, char *c)
{

	if (!strcmp(c, getNome(a)))
		return a;

    TAD* r,*p;
	for (p=a->filho; p; p=p->irmao)
	{
		r = busca(p,c);
		if (r) return r;
	}

    return NULL;
}*/
