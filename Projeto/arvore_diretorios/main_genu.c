#define BUFFER_SIZE 256
#define MAX_COMMAND_SIZE 16


#include <stdio.h>
#include <string.h>
#include "arvdir.c"
#include "commands.h"

int main()
{

	// inicializa...
	TAD* raiz = (TAD*)malloc(sizeof(TAD));
	TAD* cur_dir = raiz;



	printf("Digite seu comando:\n>");
	char command[MAX_COMMAND_SIZE];
	while (1)
	{
		// recebe o comando.
		printf(">");
		fgets(command, MAX_COMMAND_SIZE, stdin); //ta pegando \n tb
		// identifica o argumento principal.
		if(!strcmp(command,"ls\n"))
		{
			ls(cur_dir);
		}
		else if (!strcmp(command,"cd\n"))
		{
			char address[BUFFER_SIZE];
			fgets(address,BUFFER_SIZE,stdin);
			cur_dir = cd(cur_dir, address);
		}
		else if (!strcmp(command,"mv\n"))
		{

		}
		else if (!strcmp(command,"rm\n"))
		{

		}
		else if (!strcmp(command,"mkdir\n"))
		{

		}
		else if (!strcmp(command,"\n"))
		{

		}
		else
		{
			printf("Comando inválido.\n");
		}
	}

}
