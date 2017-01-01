#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#define BUFFER_SIZE 256
#define MAX_NAME_SIZE 100
#define SEPARADOR '/'

void print_info(TAD* a);
TAD* busca_filhos (TAD* a, char* c);
void atualiza_data(TAD *a);
void ler(char *str);


// ls
void ls(TAD* cur_dir,int mais_info)
{
	if(mais_info){
        printf("Nome do diretorio atual: %s",getNome(cur_dir));
        print_info(cur_dir);
        printf("\n\n");
	}
	TAD *p;
	int tamNome = 0;
	for (p = cur_dir->filho; p; p = p->irmao)
	{
		if(p->arquivo){
            TArq *aux = (TArq*)p->info;
            printf("%s",aux->nome);
            tamNome = strlen(aux->nome);
		}
		else{
            TDir *aux = (TDir*)p->info;
            printf("/");
            printf("%s",aux->nome);
            tamNome = strlen(aux->nome);
		}
        if(mais_info){
            printf(" ");
            print_info(p);
        }
        printf("\n");
	}
}

//retorna um no dado seu nome
TAD* getAddress(TAD* cur_dir, char* command_line)
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


//cd
TAD *cd(TAD* cur_dir, char* command_line){
    // cd .. para ir um nível acima
    int n = 0;
	if ((command_line[0] == '.') && (command_line[1] == '.'))
	{
		if(cur_dir->pai){
			cur_dir = cur_dir->pai;
            n = 2;
		}

	}
    TAD *org_dir = cur_dir;
    cur_dir = getAddress(cur_dir,&command_line[n]);
    if(!cur_dir){
        printf("Diretorio nao encontrado\n");
        return org_dir;
    }
    if(!cur_dir->arquivo) return cur_dir;
    //nao pode entrar em arquivo
    if(cur_dir->arquivo)
        printf("Operacao invalida\n");
    return org_dir;
}


// mv
void mv(TAD* curr_dir, char* end_org, char* end_dest)
{
    // caso renomear raiz
    if(!strcmp(getNome(curr_dir),end_org)){
        int i, len = strlen(end_dest);
        for(i=0;i<len;i++){
            if(end_dest[i]==SEPARADOR){
                printf("Nao eh possivel utilizar \"%c\" para renomear\n",SEPARADOR);
                return;
            }
        }
        renomear(curr_dir,end_dest);
        atualiza_data(curr_dir);
        return;
    }
    TAD *org = getAddress(curr_dir,end_org);
    TAD *dest = getAddress(curr_dir,end_dest);
    // caso origem invalida
    if(!org){
        printf("Endereco invalido\n");
        return;
    }
    //caso renomear
    if(!dest){
        int i, len = strlen(end_dest);
        for(i=0;i<len;i++){
            if(end_dest[i]==SEPARADOR){
                printf("Nao eh possivel utilizar \"%c\" para renomear\n",SEPARADOR);
                return;
            }
        }
        renomear(org,end_dest);
        atualiza_data(curr_dir);
    }
    else{
        //nao pode pendurar em no arquivo
        if(dest->arquivo){
            printf("Operacao Invalida\n");
            return;
        }
        //verifica se origem é ancestral de destino
        TAD *tmp = dest;
        while (tmp)
        {
            if (tmp == org)
            {
                printf("Pasta de destino eh subpasta da pasta de origem. Operacao invalida.\n");
                return;
            }
            tmp = tmp->pai;
        }
        TAD* com_mesmo_nome = busca_filhos(dest, getNome(org));
        if (com_mesmo_nome)
        {
            printf("Destino ja contem um arquivo com este mesmo nome. Digite 's' se quiser substituir o arquivo no destino, de apenas enter para cancelar.\n");
            char tmp[4];
            fgets(tmp, 4, stdin);
            if (tmp && !strcmp(tmp, "s\n"))
            {
                destruir(com_mesmo_nome,0);
                mover(org, dest);
                atualiza_data(dest);
            }
        }
        else{
            mover(org,dest);
            TDir *x = (TDir*) curr_dir->info;
            if(org->arquivo)
                x->num_arq--;
            else x->num_dir--;
        }
    }
}


// rm
void rm(TAD *curr_dir, char *address){
    //não permite remover a raiz: olhar metodo destruir
    if(!strcmp(getNome(curr_dir),address)){
        atualiza_data(curr_dir);
        destruir(curr_dir,1);
        return;
    }
    TAD *alvo = busca_filhos(curr_dir,address);
    if(alvo){
        atualiza_data(alvo->pai);
        destruir(alvo,0);
    }
    else{
        printf("Arquivo/Diretorio nao encontrado\n");
    }
}


// mkdir
void mkdir(TAD *curr_dir, char* name, int permissao)
{
	TAD *mesmo_nome = busca_filhos(curr_dir, name);
    if(mesmo_nome){
        printf("Diretorio ja existente\n");
        return;
    }
    TAD *ins = cria(name,0,permissao,'n');
    inserir(ins,curr_dir);
    atualiza_data(curr_dir);
}

//touch
void touch (TAD *curr_dir, char* name)
//mesmo principio do mkdir
{
	TAD *mesmo_nome = busca_filhos(curr_dir, name);
    if(mesmo_nome){
        printf("Data atualizada\n");
        atualiza_data(curr_dir);
        return;
    }
    int permissao;
    char tipo;
    char tmp[9];
    ler(tmp);
    permissao = atoi(tmp);
    do{
        ler(tmp);
        if((strcmp("T",tmp)) && (strcmp("B",tmp)))
            printf("Tipo invalido\n");
    }while((strcmp("T",tmp)) && (strcmp("B",tmp)));
    tipo = tmp[0];
    TAD *ins = cria(name,1,permissao,tipo);
    inserir(ins,curr_dir);
    atualiza_data(curr_dir);
}


// info, etc

void print_info(TAD* a)
{
	int i;
	if(a->arquivo){
        TArq *aux = (TArq*)a->info;
        printf("\n\tCriado em: %s\tModificado em: %s\n", aux->dat_criacao, aux->dat_atualiza);
        printf("\tPermissoes: %d", aux->permissoes);
        printf("\tTipo de arq.: %c\t\tTam. arquivo: %d",aux->tipo, aux->tam);
	}
	else{
        TDir *aux = (TDir*)a->info;
        printf("\n\tCriado em: %s\tModificado em: %s\n", aux->dat_criacao, aux->dat_atualiza);
        printf("\tPermissoes: %d", aux->permissoes);
        printf("\tNum. de Arquivos: %d\tNum. de Pastas: %d", aux->num_arq, aux->num_dir);
	}
}

//verifica vizinhancas
TAD* busca_filhos (TAD* a, char* c)
{
    if(!a) return NULL;
	for (a = a->filho; a; a = a->irmao)
	{
		if (!strcmp(c,getNome(a)))
		{
			return a;
		}
	}
	return NULL;
}

//elimina \n na leitura
void ler(char* str)
{
    fgets(str, BUFFER_SIZE, stdin);
    int i = 0;
    while (str[i] != '\n') i++;
    str[i] = '\0';
}

TAD * exemplo_rosseti(char * diretorio)
//todo arranjar um nome melhor
// raiz necessita ser um diretorio
{
	FILE * fp = fopen(diretorio, "r");
	TAD* r;
	char le[255];
	fgets(le, 255, (FILE*)fp);
	char * dir = strtok(le,"/");
	char * nome = strtok(NULL,"/");
	char * pai = strtok(NULL,"/");
	char *tam;
	if (!strcmp(dir, "D")){
		r = cria(nome, 0, 0, 'n');
	}
	while (fgets(le, 255, (FILE*)fp))
	{
		TAD* filho;
		dir = strtok(le,"/");
		nome = strtok(NULL,"/");
		pai = strtok(NULL,"/");
		if (!strcmp(dir, "D")){
			filho = cria(nome, 0, 0, 'n');
		}
		else{
            if (!strcmp(dir, "T")){
                filho = cria(nome, 1, 0, 'T');
            }
            else if (!strcmp(dir, "B")){
                filho = cria(nome, 1, 0, 'B');
            }
            tam = strtok(NULL,"/");
            TArq *info = (TArq*) filho->info;
            info->tam = atoi(tam);
		}
		if(!strcmp(getNome(r),pai)){
            inserir(filho, r);
		}
		else{
            TAD* no_pai = busca(r, pai);
            inserir(filho, no_pai);
		}
	}
	fclose(fp);
	return r;
}

//indica caminho atual
void print_address(TAD *dir)
{
    if (dir)
        if(dir->pai)
            print_address(dir->pai);
    printf("%s/",getNome(dir));
}

void atualiza_data(TAD *a)
{
    if(a){
        if(a->pai){
           atualiza_data(a->pai);
        }
        time_t tempo;
        time(&tempo);
        struct tm *info = localtime(&tempo);
        if(a->arquivo){
            TArq *ar = (TArq*)a->info;
            strftime(ar->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
        }
        else{
            TDir *dir = (TDir*)a->info;
            strftime(dir->dat_atualiza,22,"%d/%m/%Y - %H:%M:%S", info);
        }
    }
}

#endif // COMMANDS_H_INCLUDED
