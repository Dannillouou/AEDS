/**
 *@title TP1lib.h
 *@brief Definição de todas as funções, estruturas, tipos e constantes usados no programa
 *@author Daniel de Miranda
 *@date 16/07/2021
 */

#pragma once

#ifndef TP1LIB_H
#define TP1LIB_H

//Constantes
#define TAMANHO_MAXIMO_OBSERVACAO  (300 + 1)
#define TAMANHO_MAXIMO_NOME  (80 + 1)

//Estruturas do programa

typedef struct data_s
{
	int dia;
	int mes;
	int ano;
} data_t;

typedef struct consulta_s
{
	data_t data;
	char observacao[TAMANHO_MAXIMO_OBSERVACAO];
} consulta_t;

typedef struct consultaLi_s
{
	consulta_t consulta;
	struct consultaLi_s* proximo;
} consultaLi_t;

typedef struct consultaLi_s* lista_t;

typedef struct prontuario_s
{
	char nome[TAMANHO_MAXIMO_NOME];
	lista_t consultas;
} prontuario_t;

typedef struct prontuarioArv_s
{
	prontuario_t prontuario;
	struct prontuarioArv_s* esq;
	struct prontuarioArv_s* dir;
} prontuarioArv_t;

typedef prontuarioArv_t* arvore_t;


//Funções de manipulação de lista nesse contexto

lista_t* CriaLista();
void LiberaLista(lista_t* lista);
int ListaVazia(lista_t* lista);
int InsereNaListaFinal(lista_t* lista, char* observacao, data_t data);
int RemoveDaListaInicio(lista_t* lista);
int RemoveDaListaFinal(lista_t* lista);
void MostraLista(lista_t* lista);


//Funções de manipulação de árvore nesse contexto

arvore_t* CriaArvore();
void LiberaArvore(arvore_t* arvore);
int InsereNaArvore(arvore_t* arvore, prontuario_t* prontuario);
int RemoveDaArvore(arvore_t* arvore, char* nome);
int ConsultaArvore(arvore_t* arvore, char* nome);
int AlturaArvore(arvore_t* arvore);
int ArvoreVazia(arvore_t* arvore);

//funções do programa
int ConsultaPaciente(arvore_t* arvore);
int ConsultaData(arvore_t* arvore);
int InsereConsulta(arvore_t*);
int RemoveProntuario(arvore_t* arvore);
void PercorrePreOrdemData(arvore_t*, data_t data);

//Outras funções
void ImprimeMenu();
int DataValida(data_t data);

#endif