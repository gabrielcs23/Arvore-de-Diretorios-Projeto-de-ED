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
void renameM(TAD *a, char* command_line)
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
				if(!a->pai)
				{
					TDir *mod = (TDir*) a->info;
					mod->nome = address;
				}
				TAD *mesmo_nome = busca_filhos(a->pai,address);
				if(mesmo_nome)
				{
					//podemos sobrescrever neste caso
					//ou até mesmo colocar um scanf e perguntar se o usuario quer sobrescrever
					//ou deixar de fazer a operação
					printf("Diretorio ou arquivo ja existente");
					return;
				}
				if(a->arquivo)
				{
					TArq *mod = (TArq*) a->info;
					mod->nome = address;
				}
				else
				{
					TDir *mod = (TDir*) a->info;
					mod->nome = address;
				}

			}
		}
		else
		{
			address[j] = command_line[i];
			j++;
		}
	}
}

// rm
void rm(TAD *a, char* command_line){
    char address[MAX_NAME_SIZE];
    int i = 2, j = 0;
    while((command_line[i] != '\n') || (command_line[i] != '\0')){
        i++;
        if(command_line[i] != '\0'){
            address[j] = command_line[i];
            j++;
        }
        else{
            if(j>0){ // se 'address' não for vazia
                address[j] = '\0';
                TAD *alvo = busca_filhos(a,address);
                if(alvo){
                    destruir(alvo);
                    return;
                }
                else{
                    printf("Arquivo/Diretorio não encontrado\n");
                    return;
                }
            }
            else{
                printf("Querido\n");
            }
        }
    }
}

// mkdir
void mkdir(TAD *a, char* command_line)
//seria interessante pensar em colocar argumentos para criar o diretório com permissões escolhidas pelo usuário
//se o split funcionasse corretamente com delimitadores passados para a função, isso seria trivial
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
				TAD *mesmo_nome = busca_filhos(a, address);
				if(mesmo_nome){
					printf("Diretorio ja existente\n");
					return;
				}
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

void touch (TAD *a, char* command_line)
//mesma coisa do mkdir, pensar em argumentos para tipo e permissão
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
				TAD *mesmo_nome = busca_filhos(a, address);
				if(mesmo_nome){
					printf("Diretorio ja existente\n");
					return;
				}
				TAD *ins = cria(address,1,0,'T');
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

void split(char *command_line,char *resp[],int tam_max){
    int i=0,j;
    char *temp;
    char aux[strlen(command_line)];
    /*for(i=0;command_line[i]!='\0';i++){
        if(command_line[i]=='\'') break;
        else temp[i] = command_line[i];
    }*/
    temp = strtok(command_line,"'");
    while( temp!= NULL )
    {
      resp[i] = temp;
      temp = strtok(NULL, "'");
      i++;
    }
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
