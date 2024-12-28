#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/listaEncadeada.h"
#include "../include/listaCircular.h"
#include "listaCircular.c"

int calcularId(char* data, int cont){
    int dia, mes, ano;
    sscanf(data, "%d-%d-%d", &dia, &mes, &ano);
    return (dia * 1000) + (mes * 100) + cont;
}

TAREFA* criarTarefa(char* decricao, int prioridade, int status, int id){
    TAREFA* novaTarefa = (TAREFA*)malloc(sizeof(TAREFA));
    if (!novaTarefa){
        exit(1);
    }
    novaTarefa->id = id;
    novaTarefa->status = status;
    strcpy(novaTarefa->descricao, decricao);
    novaTarefa->prioridade = prioridade;
    novaTarefa->prox = NULL;
    return novaTarefa;
}

DataTarefa* criarDataTarefa(char* data){
    DataTarefa* novaData = (DataTarefa*)malloc(sizeof(DataTarefa));
    if (!novaData){
        exit(1);
    }
    strcpy(novaData->data, data);
    novaData->cont = 0;
    novaData->tarefas = NULL;
    novaData->prox = NULL;
    return novaData;
}

void inserirTarefa(TAREFA** lista, int id, int status, char* descricao, int prioridade){
    TAREFA* novaTarefa = criarTarefa(descricao, prioridade, status, id);
    if (*lista == NULL){
        *lista = novaTarefa;
    } else {
        TAREFA* temp = *lista;
        while (temp->prox != NULL){
            temp = temp->prox;
        }
        temp->prox = novaTarefa;
    }
}

void inserirTarefaData(DataTarefa** listaData, char* data, char* descricao, int prioridade, int status){
    DataTarefa* aux = *listaData;

    while (aux != NULL && strcmp(aux->data, data) != 0){
        aux = aux->prox;
    }

    if (aux == NULL){
        DataTarefa* novaData = criarDataTarefa(data);
        novaData->prox = *listaData;
        *listaData = novaData;
        aux = novaData;
    }

    aux->cont++;
    int id = calcularId(data, aux->cont);

    inserirTarefa(&(aux->tarefas), id, status, descricao, prioridade);
}

TAREFA* removerTarefa(TAREFA* lista, int idBusca) {
    TAREFA* ant = NULL;
    TAREFA* aux = lista;

    while (aux != NULL && aux->id != idBusca) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {  
        printf("Tarefa com ID %d nao encontrada.\n", idBusca);
        return lista;
    }

    if (ant == NULL) {  
        lista = aux->prox;
    } else {  
        ant->prox = aux->prox;
    }

    printf("Tarefa com ID %d removida com sucesso.\n", aux->id);
    free(aux);  

    return lista;
}

DataTarefa* removerTarefaData(DataTarefa* listaData, int idBusca) {
    DataTarefa* auxData = listaData;
    DataTarefa* antData = NULL;

    while (auxData != NULL) {
        auxData->tarefas = removerTarefa(auxData->tarefas, idBusca);

        if (auxData->tarefas == NULL) {
            if (antData == NULL) {
                listaData = auxData->prox;
            } else {
                antData->prox = auxData->prox;
            }
            DataTarefa* temp = auxData;
            auxData = auxData->prox;
            free(temp); 
            printf("Data removida.\n");
        } else {
            antData = auxData;
            auxData = auxData->prox;
        }
    }

    return listaData;
}

void concluirTarefa(DataTarefa** listaData, TarefasConcluidas* concluidas, int id) {
    DataTarefa* atual = *listaData;
    DataTarefa* anteriorData = NULL;

    while (atual != NULL) {
        TAREFA* tarefa = atual->tarefas;
        TAREFA* anteriorTarefa = NULL;

        while (tarefa != NULL) {
            if (tarefa->id == id) {
                tarefa->status = 0;  
                printf("Tarefa ID %d foi marcada como CONCLUIDA!\n", id);

                if (anteriorTarefa == NULL) {
                    atual->tarefas = tarefa->prox;  
                } else {
                    anteriorTarefa->prox = tarefa->prox;  
                }

                addTarefaConcluida(concluidas, tarefa);

                if (atual->tarefas == NULL) {
                    printf("Todas as tarefas da data %s foram concluidas. Removendo a data...\n", atual->data);
                    if (anteriorData == NULL) {
                        *listaData = atual->prox;  
                    } else {
                        anteriorData->prox = atual->prox;  
                    }
                    free(atual);
                }
                return; 
            }
            anteriorTarefa = tarefa;
            tarefa = tarefa->prox;
        }
        anteriorData = atual;
        atual = atual->prox;
    }
    printf("Tarefa com ID %d nao encontrada!\n", id);
}

void imprimirTarefasPorData(DataTarefa* lista){
    if (lista == NULL){
        return;
    }

    DataTarefa* auxData = lista;
    while (auxData != NULL){
        printf("---------------------------------------------\n");
        printf("Data: %s\n", auxData->data);
        printf("---------------------------------------------\n");
        TAREFA* auxTarefa = auxData->tarefas;
        while (auxTarefa != NULL){
            printf(" ID: %d\n Tarefa: %s\n Prioridade: %d\n Status: %d\n", auxTarefa->id, auxTarefa->descricao, auxTarefa->prioridade, auxTarefa->status);
            printf("---------------------------------------------\n");
            auxTarefa = auxTarefa->prox;
        }
        auxData = auxData->prox;
        printf("\n");
    }
}

void liberarTarefas(TAREFA* lista){
    if (lista){
        liberarTarefas(lista->prox);
        free(lista);
    }
}

void liberarTarefaData(DataTarefa* lista){
    if (lista){
        liberarTarefaData(lista->prox);
        free(lista);
    }
}

int verificarData(char* data) {
    if (strlen(data) != 10) {
        return 0; 
    }

    // Verifica o formato dd-mm-yyyy
    if (!isdigit(data[0]) || !isdigit(data[1]) || data[2] != '-' ||
        !isdigit(data[3]) || !isdigit(data[4]) || data[5] != '-' ||
        !isdigit(data[6]) || !isdigit(data[7]) || !isdigit(data[8]) || !isdigit(data[9])) {
        return 0;
    }

    // Converte partes da data para números inteiros
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = atoi(data + 6);

    // Verifica os limites de dia, mês e ano
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;

    // Verifica dias válidos para cada mês
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta para anos bissextos
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasNoMes[1] = 29;
    }

    if (dia > diasNoMes[mes - 1]) return 0;

    return 1;
}