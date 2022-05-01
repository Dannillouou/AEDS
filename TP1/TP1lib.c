/**
 *@title TP1lib.c
 *@brief Implementações de todas as funções usadas no programa
 *@author Daniel de Miranda
 *@date 18/07/2021
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h> //Para usar a função Sleep
#include"TP1lib.h"
#include"erros.h"

//Funções para listas
lista_t* CriaLista()
{
    lista_t* lista = (lista_t*)malloc(sizeof(lista_t));
    if (lista != NULL) *lista = NULL;
    return lista;
}

void LiberaLista(lista_t* lista)
{
    if (lista == NULL)
        return;

    consultaLi_t* aux;
    while (*lista != NULL)
    {
        aux = *lista;
        *lista = (*lista)->proximo;
        free(aux);
    }
    free(lista);
}

int ListaVazia(lista_t* lista)
{
    return (lista == NULL || *lista == NULL);
}

int InsereNaListaFinal(lista_t* lista, char* observacao, data_t data)
{
    if (lista == NULL) return 1;

    consultaLi_t* elem = (consultaLi_t*)malloc(sizeof(consultaLi_t));

    if (elem == NULL) return 1;

    strcpy(elem->consulta.observacao, observacao);

    elem->consulta.data.dia = data.dia;
    elem->consulta.data.mes = data.mes;
    elem->consulta.data.ano = data.ano;

    elem->proximo = NULL;

    if (*lista == NULL)
    {
        *lista = elem;
    }
    else
    {
        consultaLi_t* aux = *lista;
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux->proximo = elem;

    }

    return 0;
}

void MostraLista(lista_t* lista)
{
    if (ListaVazia(lista)) return;

    consultaLi_t* elem = *lista;
    int posicao = 1;

    printf("----------------------------------------------------------------");
    while (elem != NULL)
    {
        printf("\nconsulta %d: %d/", posicao, elem->consulta.data.dia);
        printf("%d/", elem->consulta.data.mes);
        printf("%d\n", elem->consulta.data.ano);
        printf("Observacao: %s\n", elem->consulta.observacao);
        Sleep(1000);
        elem = elem->proximo;
        posicao++;
    }
    printf("----------------------------------------------------------------\n");
}


//Funções para árvores
arvore_t* CriaArvore()
{
    arvore_t* raiz = malloc(sizeof(arvore_t));
    if (raiz != NULL) *raiz = NULL;
    return raiz;
}

void LiberaNo(prontuarioArv_t* no)
{
    if (no == NULL) return;

    LiberaLista(no->prontuario.consultas);
    LiberaNo(no->esq);
    LiberaNo(no->dir);
    free(no);
    no = NULL;
}

void LiberaArvore(arvore_t* arvore)
{
    if (arvore == NULL) return;
    LiberaNo((*arvore));
    free(arvore);
}

int InsereNaArvore(arvore_t* arvore, prontuario_t* prontuario)
{
    if (arvore == NULL)
        return 1;
    prontuarioArv_t* novo = malloc(sizeof(prontuarioArv_t));
    if (novo == NULL)
        return 1;

    strcpy(novo->prontuario.nome, prontuario->nome);
    novo->prontuario.consultas = prontuario->consultas;
    novo->dir = NULL;
    novo->esq = NULL;

    if (*arvore == NULL)
    {
        *arvore = novo;
        return 0;
    }

    prontuarioArv_t* atual = *arvore;
    prontuarioArv_t* pai = NULL;

    while (atual != NULL)
    {
        pai = atual;
        if (strcmp(atual->prontuario.nome, novo->prontuario.nome) == 0)
        {
            free(novo);
            return 1; //elemento já existe
        }

        if (strcmp(novo->prontuario.nome, atual->prontuario.nome))
            atual = atual->dir;
        else atual = atual->esq;
    }

    if (strcmp(novo->prontuario.nome, pai->prontuario.nome)) pai->dir = novo;
    else pai->esq = novo;
    return 0;
}

prontuarioArv_t* RemoveNo(prontuarioArv_t* no)
{
    prontuarioArv_t* n1, * n2;
    if (no->esq == NULL)
    {
        n2 = no->dir;
        free(no);
        return n2;
    }
    n1 = no;
    n2 = no->esq;
    while (n2->dir != NULL)
    {
        n1 = n2;
        n2 = n2->dir;
    }
    if (n1 != no)
    {
        n1->dir = n2->esq;
        n2->esq = no->esq;
    }
    n2->dir = no->dir;
    LiberaLista(no->prontuario.consultas);
    free(no);
    return n2;
}

int RemoveDaArvore(arvore_t* arvore, char* nome)
{
    if (arvore == NULL) return 1;
    
    prontuarioArv_t* pai = NULL, * atual = *arvore;

    while (atual != NULL)
    {
        if (strcmp(nome, atual->prontuario.nome) == 0)
        {
            if (atual == *arvore) *arvore = RemoveNo(atual);
            else
            {
                if (pai->dir == atual) pai->dir = RemoveNo(atual);
                else pai->esq = RemoveNo(atual);
            }
            return 0;
        }
        pai = atual;
        if (strcmp(nome, atual->prontuario.nome) > 0) atual = atual->dir;
        else atual = atual->esq;
    }
    return 1;
}

int ArvoreVazia(arvore_t* arvore)
{
    if (arvore == NULL) return 1;
    if (*arvore == NULL) return 1;
    return 0;
}

//Funções auxiliares e do programa
int ConsultaPaciente(arvore_t* arvore)
{
    char lixo;
    
    if (ArvoreVazia(arvore)) {
        fprintf(stderr, "Nenhum prontuario encontrado, nada para ver aqui");
        return 0;
    }

    char nome[TAMANHO_MAXIMO_NOME];

    (void)scanf("%c", &lixo);
    printf("Digite o nome do paciente: ");
    fgets(nome, TAMANHO_MAXIMO_NOME, stdin);
    
    size_t len = strlen(nome);
    if (nome[len - 1] == '\n') nome[--len] = 0;

    prontuarioArv_t* atual = *arvore;
    prontuarioArv_t* pai = NULL;

    if (atual == NULL) return 0;

    while (atual != NULL) {
        if (strcmp(nome, atual->prontuario.nome) == 0) 
        {
            if(atual == *arvore) MostraLista(&(atual->prontuario.consultas));
            else
            {
                if (pai->dir == atual) MostraLista(&((*pai).dir->prontuario.consultas));
                else MostraLista(&((*pai).esq->prontuario.consultas));
            }
            return 1;
        }
        
        pai = atual;
        if (strcmp(atual->prontuario.nome, nome) > 0) atual = atual->dir;
        else atual = atual->esq;
    }

    printf("Nome nao encontrado");
    return 0;
}

int ConsultaData(arvore_t* arvore)
{
    if (ArvoreVazia(arvore))
    {
        fprintf(stderr, "Nenhum prontuario, nada para ver aqui");
        return 0;
    }

    data_t dataProcurada;

    printf("Entre a data (DD/MM/AAAA): ");
    (void)scanf("%d/%d/%d", &dataProcurada.dia, &dataProcurada.mes, &dataProcurada.ano);

    if (DataValida(dataProcurada) == 0)
    {
        fprintf(stderr, "data invalida");
        return 0;
    }

    //Percorrer toda a árvore como na função Consulta Paciente

    printf("\nConsultas no dia:\n\n");
    PercorrePreOrdemData(arvore, dataProcurada);

    return 1;
}

int InsereConsulta(arvore_t* arvore)
{
    char nome[TAMANHO_MAXIMO_NOME], observacao[TAMANHO_MAXIMO_OBSERVACAO], lixo;
    data_t dataConsulta;

    printf("Entre a data da consulta(DD/MM/AAAA): ");
    (void)scanf("%d/%d/%d", &dataConsulta.dia, &dataConsulta.mes, &dataConsulta.ano);

    if (DataValida(dataConsulta) == 0)
    {
        fprintf(stderr, "Data invalida");
        return 1;
    }

    printf("Entre o nome do paciente: ");
    (void)scanf("%c", &lixo);
    fgets(nome, TAMANHO_MAXIMO_NOME, stdin);
    size_t len = strlen(nome);
    if (nome[len - 1] == '\n') nome[--len] = 0;

    printf("Entre a observacao sobre a consulta:\n");
    fgets(observacao, TAMANHO_MAXIMO_OBSERVACAO, stdin);
    len = strlen(observacao);
    if (observacao[len - 1] == '\n') observacao[--len] = 0;

    prontuarioArv_t* atual = *arvore;

    while (atual != NULL) {
        if (strcmp(nome, atual->prontuario.nome) == 0) 
        {
            InsereNaListaFinal(&(atual->prontuario.consultas), observacao, dataConsulta);
        }
        if (strcmp(nome, atual->prontuario.nome) > 0) atual = atual->dir;
        else atual = atual->esq;
    }
    
    //Não achou o nome, então o cria prontuario
    prontuario_t* prontuarioNovo = malloc(sizeof(prontuario_t));

    if (prontuarioNovo == NULL)
    {
        fprintf(stderr, "falha ao criar prontuario");
        return 1;
    }

    lista_t* Lista = CriaLista();

    strcpy(prontuarioNovo->nome, nome);//possivel erro
    
    InsereNaListaFinal(Lista, observacao, dataConsulta);

    prontuarioNovo->consultas = *Lista;

    InsereNaArvore(arvore, prontuarioNovo);

    return 0;
}

int RemoveProntuario(arvore_t* arvore)
{
    char nome[TAMANHO_MAXIMO_NOME], lixo;
    
    if (ArvoreVazia(arvore))
    {
        fprintf(stderr, "Arvore vazia, nada para remover");
        return ERRO;
    }

    printf("Insira o nome que deseja remover:\n");
    (void)scanf("%c", &lixo);
    fgets(nome, TAMANHO_MAXIMO_NOME, stdin);
    size_t len = strlen(nome);
    if (nome[len - 1] == '\n') nome[--len] = 0;
    
    prontuarioArv_t* atual = *arvore;
    prontuarioArv_t* pai = NULL;    

    while (atual != NULL) 
    {
        if (strcmp(atual->prontuario.nome, nome) == 0)
        {
            if (atual == *arvore) *arvore = RemoveNo(atual);
            else
            {
                if (pai->dir == atual) pai->dir = RemoveNo(atual);
                else pai->esq = RemoveNo(atual);
            }
            return SUCESSO;
        }
        pai = atual;
        if (strcmp(atual->prontuario.nome, nome) > 0) atual = atual->esq;
        else atual = atual->dir;
    }

    printf("Nome nao encontrado");
    return ERRO;
}

void PercorrePreOrdemData(arvore_t* raiz, data_t data)
{
    if (ArvoreVazia(raiz)) return;

    lista_t lista = ((*raiz)->prontuario.consultas);

    if (*raiz != NULL)
    {

        while (lista != NULL)
        {
            if (lista->consulta.data.dia == data.dia && lista->consulta.data.mes == data.mes && lista->consulta.data.ano == data.ano)
            {
                //printf("%s", &((*raiz)->prontuario.nome));
                puts((*raiz)->prontuario.nome);
            }
            lista = lista->proximo;
        }

        PercorrePreOrdemData(&((*raiz)->esq), data);
        PercorrePreOrdemData(&((*raiz)->dir), data);
    }
}

void ImprimeMenu()
{
    printf("\n\n\nDigite a opcao desejada");
    Sleep(400);
    printf("\n+---------------------+");
    Sleep(100);
    printf("\n|1.Consultar paciente |");
    Sleep(100);
    printf("\n|2.Consultar data     |");
    Sleep(100);
    printf("\n|3.Inserir consulta   |");
    Sleep(100);
    printf("\n|4.Remover prontuario |");
    Sleep(100);
    printf("\n|0.Encerrar Programa  |");
    printf("\n+---------------------+\n");
}

int DataValida(data_t data)
{
    if ((data.ano > 1900) && (data.mes > 0 && data.mes < 13))
    {
        if (data.mes == 1 || data.mes == 3 || data.mes == 5 || data.mes == 7 || data.mes == 8 || data.mes == 10 || data.mes == 12)
        {
            if (data.dia > 0 && data.dia < 32) return 1;
            else return 0;
        }
        if (data.mes == 4 || data.mes == 6 || data.mes == 9 || data.mes == 11)
        {
            if (data.dia > 0 && data.dia < 31) return 1;
            else return 0;
        }
        else
        {
            if (data.dia > 0 && data.dia < 29) return 1;
            else return 0;
        }
    }
    else return 0;
}