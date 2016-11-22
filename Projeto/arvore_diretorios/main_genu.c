


#define BUFFER_SIZE 256
#define MAX_COMMAND_SIZE 16


#include <sdtio.h>
#include <string.h>
#include "arvdir.c"
#include "commands.c"

int main()
{
	
	// inicializa...
	TAD* raiz = (TAD*)malloc(sizeOf(TAD));
	TAD* cur_dir = raiz;
	
	
	
	printf("Digite seu comando:\n>");
	char command_line[BUFFER_SIZE];
	while (1)
	{
		// recebe o comando.
		printf(">");
		fgets(command_line, BUFFER_SIZE, stdin);
		
		// separa o argumento principal.
		char command[MAX_COMMAND_SIZE];
		int i;
		for (i = 0; i < MAX_COMMAND_SIZE; i++)
		{
			if (command_line[i] != ' ' 
					&& command_line[i] != '\n'
					&& command_line[i] != '\0')
				{
					command[i] = command_line[i];
				}
		}
		command[i] = '\0';
		
		// identifica o argumento principal.
		if(!strcmp(command,"ls"))
		{
			void ls(cur_dir);
		}
		else if (!strcmp(command,"cd"))
		{
			cur_dir = cd(cur_dir, command_line);
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