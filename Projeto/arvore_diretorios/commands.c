#define BUFFER_SIZE 256
#define MAX_NAME_SIZE 100
#define SEPARADOR '/'

#include <stdio.h>

typedef struct arvdir
{
	int tipo;
	struct arvdir *pai, *filho, *prox_irmao;
	void * info;
} TAD;

// ls

void ls(TAD* cur_dir)
{
	for (TAD* p = cur_dir->filho; p; p->irmao)
	{
		printf(p->info->nome);
		
		// espaços pra deixar mais bonitinho:
		for (int i = strlen(p->info->nome); i < MAX_NAME_SIZE; i++)
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

// new file (touch?)

// info, etc

void print_info(TAD* a)
{
	printf("Criado em: %s    Modificado em: %s\n", a->info->dat_criacao, a->info->dat_atualiza);
	for (int i = 0; i < MAX_NAME_SIZE; i++)	printf(" "); 	// espaços pra deixar mais bonitinho?
	printf("Permissoes: %d", a->info->permissoes);
	if (a->arquivo)
	{
		printf("\n")
	}
	else
	{
		printf("    Num. de Arquivos: %d    Num. de Pastas: %d\n", a->info->num_arq, a->info->num_dir);
	}
}

TAD* busca_filhos (TAD* a, char* c)
{
	for (TAD* a = a->filho; a; a = a->irmao)
	{
		if (!strcmp(c, a->info->nome))
		{
			return a;
		}
	}
	return NULL;
}

TAD* busca_genu (TAD* a, char *c)
{
    
	if (!strcmp(c, a->info->nome))
		return a;
	
    TAD* r;
	for (TAD* p=a->filho; p; p=p->irmao)
	{
		r = busca(p,c);
		if (r) return r;
	}
	
    return NULL;
}




















