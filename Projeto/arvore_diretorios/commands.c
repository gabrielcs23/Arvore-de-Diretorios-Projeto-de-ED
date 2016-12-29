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

TAD* getAddress(TAD* cur_dir, char* command_line)	// bugres: "cd //////////filho1/filho1filho1" funciona.
{
	char address[MAX_NAME_SIZE];
	int i = -1, j = 0;

	while ((i==-1) || ((command_line[i] != '\n') && (command_line[i] != '\0')))
	{
        i++;
		if (command_line[i] == SEPARADOR || command_line[i] == '\0' || command_line[i] == '\n')
		{
			if (j > 0) // se 'address' não for vazia
			{
				address[j] = '\0';

				TAD* new_dir = busca_filhos(cur_dir, address);
				if (new_dir) // se encontrar o endereço, continua até o final do comando
					cur_dir = new_dir;
				else // se não encontrar o endereço, cancela o comando
					return NULL;

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

TAD *cd(TAD* cur_dir, char* command_line){
    // cd .. para ir um nível acima
	if ((command_line[0] == '.') && (command_line[1] == '.'))
	{
		if(cur_dir->pai)
			cur_dir = cur_dir->pai;
		return cur_dir;
	}
    TAD *org_dir = cur_dir;
    cur_dir = getAddress(cur_dir,command_line);
    if(cur_dir) return cur_dir;
    return org_dir;
}

// mv

/*void mv(TAD* curr_dir, char* end_org, char* end_dest)
{
	// fazer um "getxxxxx()" baseado no formato do cd e no diretorio atual. usar aqui e no cd...
    TAD *org = getAddress(curr_dir,end_org);
    TAD *dest = getAddress(curr_dir,end_dest);
    if(!org){
        printf("Endereço invalido\n");
        return;
    }
    if(!dest){
        int i, len = strlen(end_dest);
        for(i=0;i<len;i++){
            if(end_dest[i]==SEPARADOR){
                printf("Não é possivel utilizar \"%c\" para renomear\n",SEPARADOR);
                return;
            }
        }
        renomear(curr_dir,end_dest);
    }
    else if()

}*/

// rename
/*void renameM(TAD *a, char* command_line)
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
}*/

// rm
void rmOld(TAD *a, char* command_line){
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

void rm(TAD *curr_dir, char *address){
    TAD *alvo = busca_filhos(curr_dir,address);
    if(alvo){
        destruir(alvo);
    }
    else{
        printf("Arquivo/Diretorio não encontrado\n");
    }
}

// mkdir
void mkdir(TAD *curr_dir, char* name, int permissao)
//seria interessante pensar em colocar argumentos para criar o diretório com permissões escolhidas pelo usuário
{
	TAD *mesmo_nome = busca_filhos(curr_dir, name);
    if(mesmo_nome){
        printf("Diretorio ja existente\n");
        return;
    }
    TAD *ins = cria(name,0,permissao,'n');
    inserir(ins,curr_dir);
}

void touch (TAD *curr_dir, char* name)
//mesma coisa do mkdir, pensar em argumentos para tipo e permissão
{
	TAD *mesmo_nome = busca_filhos(curr_dir, name);
    if(mesmo_nome){
        time_t tempo;
        time(&tempo);
        struct tm *info = localtime(&tempo);
        TArq *ar = (TArq*) mesmo_nome->info;
        strftime(ar->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
        return;
    }
    int permissao;
    char tipo;
    scanf("%d\n",&permissao);
    scanf("%c\n",&tipo);
    TAD *ins = cria(name,1,permissao,tipo);
    inserir(ins,curr_dir);
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

/*void split(char *command_line,char *resp[],int tam_max){
    int i=0,j;
    char *temp;
    char aux[strlen(command_line)];
    //for(i=0;command_line[i]!='\0';i++){
      //  if(command_line[i]=='\'') break;
        //else temp[i] = command_line[i];
    //}
    temp = strtok(command_line,"'");
    while( temp!= NULL )
    {
      resp[i] = temp;
      temp = strtok(NULL, "'");
      i++;
    }
}
*/
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
