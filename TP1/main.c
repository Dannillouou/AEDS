
//Função principal

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h> //Para usar a função Sleep
#include"erros.h"
#include"Tp1lib.h"


int main(int argc, char** argv)
{
	arvore_t* Arvore = CriaArvore();

	int escolha = 0;
	//char lixoChar;
	
	printf("\n+----------------------+");
	printf("\n|    Bem vindo ao      |");
	printf("\n|  Trabalho de AEDS    |");
	printf("\n|  Primeiro Trimestre  |");
	printf("\n+----------------------+\n");
	do
	{
		ImprimeMenu();
		(void)scanf("%d", &escolha);

		switch (escolha)
		{
			case 0:
				system("cls");
				printf("\n\nEncerrando programa...\n");
				Sleep(500);
			break;
			case 1:
				system("cls");
				printf("\n\nConsultando paciente pedido...\n\n");
				Sleep(250);
				ConsultaPaciente(Arvore);
				printf("\nProcedimento concluido\n");
				Sleep(300);
				system("pause");
				system("cls");
			break;
			case 2:
				system("cls");
				printf("\n\nConsultando Data...\n");
				Sleep(250);
				ConsultaData(Arvore);
				printf("\nProcedimento concluido\n");
				Sleep(300);
				system("pause");
				system("cls");
			break;
			case 3:
				system("cls");
				printf("\n\nInserindo consulta...\n");
				Sleep(250);
				InsereConsulta(Arvore);
				printf("\nProcedimento concluido\n");
				Sleep(300);
				system("pause");
				system("cls");
			break;
			case 4:
				system("cls");
				printf("\nRemovendo prontuario...\n");
				Sleep(250);
				RemoveProntuario(Arvore);
				printf("\nProcedimento concluido\n");
				Sleep(300);
				system("pause");
				system("cls");
			break;
			default:
				system("cls");
				printf("\nValor invalido\n");
			break;

		}
	} while (escolha != 0);

	//Liberações
	LiberaArvore(Arvore);

	return SUCESSO;
}