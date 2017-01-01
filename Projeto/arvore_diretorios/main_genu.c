#define BUFFER_SIZE 256
#define MAX_COMMAND_SIZE 256


#include <stdio.h>
#include <string.h>
#include <time.h>
#include "arquivo.h"
#include "diretorio.h"
#include "arvdir.h"
#include "commands.h"

int main()
{

	// inicializa...
	TAD* raiz = exemplo_rosseti("exemplo.txt");
	TAD* cur_dir = raiz;



	printf("Digite seu comando:\n>");
	char command[MAX_COMMAND_SIZE];
	char arg1[BUFFER_SIZE], arg2[BUFFER_SIZE];
	int perm;
	while (1)
	{
		// recebe o comando.
		printf(">");
		print_address(cur_dir);
		printf(": ");
		ler(command);
		// identifica o argumento principal.
		if(!strcmp(command,"ls"))
		{
			ls(cur_dir,0);
		}
		else if(!strcmp(command,"ls+"))
        {
            ls(cur_dir,1);
        }
		else if (!strcmp(command,"cd"))
		{
			ler(arg1);
			cur_dir = cd(cur_dir, arg1);
		}
		else if (!strcmp(command,"mv"))
		{
            ler(arg1);
            ler(arg2);
            mv(cur_dir,arg1,arg2);
		}
		else if (!strcmp(command,"rm"))
		{
            ler(arg1);
            rm(cur_dir,arg1);
		}
		else if (!strcmp(command,"mkdir"))
		{
            ler(arg1);
            ler(arg2);
            perm = atoi(arg2);
            mkdir(cur_dir,arg1,perm);
		}
		else if (!strcmp(command,"touch"))
		{
		    ler(arg1);
		    touch(cur_dir,arg1);
		}

        else if (!strcmp(command,"transform"))
        {
            ler(arg1);
            transformar(getAddress(cur_dir,arg1));
        }

		else if (!strcmp(command,""))
		{
            continue;
		}
		else if(!strcmp(command,"clear")){
            system("cls");
		}
		else if(!strcmp(command,"exit")){
            liberar(raiz);
            break;
		}
		else
		{
			printf("Comando inválido.\n");
		}
	}
    return 0;
}
