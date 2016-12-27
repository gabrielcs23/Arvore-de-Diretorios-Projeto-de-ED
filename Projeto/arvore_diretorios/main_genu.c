#define BUFFER_SIZE 256
#define MAX_COMMAND_SIZE 16


#include <stdio.h>
#include <string.h>
#include "arvdir.c"
#include "commands.c"

int main()
{

	// inicializa...
	TAD* raiz = (TAD*)malloc(sizeOf(TAD));
	TAD* cur_dir = raiz;



	printf("Digite seu comando:\n>");
	char command[MAX_COMMAND_SIZE];
	while (1)
	{
		// recebe o comando.
		printf(">");
		fgets(command, MAX_COMMAND_SIZE, stdin);

		// identifica o argumento principal.
		if(!strcmp(command,"ls"))
		{
			void ls(cur_dir);
		}
		else if (!strcmp(command,"cd"))
		{
			char address[BUFFER_SIZE];
			fgets(address,BUFFER_SIZE,stdin);
			cur_dir = cd(cur_dir, address);
		}
		else if (!strcmp(command,"mv"))
		{

		}
		else if (!strcmp(command,"rm"))
		{

		}
		else if (!strcmp(command,"mkdir"))
		{

		}
		else if (!strcmp(command,""))
		{

		}
		else
		{
			printf("Comando inválido.\n");
		}
	}

}
