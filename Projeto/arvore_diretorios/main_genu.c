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
            //para funcionar em Windows e Linux tb
            #ifdef WINDOWS
                system("cls");
            #else
                system ("clear");
            #endif
		}
		else if(!strcmp(command,"exit")){
            liberar(raiz);
            break;
		}
		else if(!strcmp(command,"help")){
			printf("Lista de comandos:\n\thelp: Mostra os comandos disponiveis.\n");
			printf("\tls: Mostra arquivos e diretorios do diretorio atual.\n");
			printf("\tls+: Mostra arquivos e diretorios do diretório atual com informacoes detalhadas.\n");
			printf("\tcd: Troca de diretorio. Usa um argumento apos o comando.\n\t\t- .. Sobe um nivel de diretorio.\n");
			printf("\t\t- <nome_filho> Vai para o subdiretorio com o nome especificado. Pode ser escrito ");
			printf("com separadores para alcancar descendetes mais distantes.\n");
			printf("\tmv: Move um filho deste diretorio para outro. Primeiro argumento filho, segundo argumento destino.");
			printf(" Se o destino nao existir, renomeia o filho com o nome passado como destino.\n");
			printf("\trm: Remove um filho deste diretorio com o nome passado no argumento.\n");
			printf("\tmkdir: Cria um novo diretorio filho do atual com o nome especificado no primeiro argumento");
			printf(" e a permissao no segundo argumento.\n");
			printf("\ttouch: Muda a data de atualizacao do arquivo com o nome passado no argumento e, se ele nao existir,");
			printf(" cria um novo arquivo e recebe mais dois argumentos, um de permissao e outro de tipo de arquivo (T ou B).\n");
			printf("\ttransform: Transforma um arquivo passado como argumento em diretorio e vice versa.");
			printf(" Recebe ainda um argumento de tipo (T ou B) se for transformado para arquivo.\n");
			printf("\tclear: Limpa o texto da tela.\n\texit: Termina a execucao do programa.\n");
		}
		else
		{
			printf("Comando inválido.\n");
		}
	}
    return 0;
}
