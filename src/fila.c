#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/fila.h"
#include "../include/listaEncadeada.h"

int contarTarefasNaFila(TarefasDoDia* fila) {
    TAREFA* atual = fila->inicio;
    int count = 0;
    while (atual != NULL) {
        count++;
        atual = atual->prox;
    }
    return count;
}

TarefasDoDia* criarFila(void){
    TarefasDoDia* fila = (TarefasDoDia*)malloc(sizeof(TarefasDoDia));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void inserirTarefasNaFila(TarefasDoDia* fila, char* decricao, int prioridade, char* status, int id){
    TAREFA* nova = (TAREFA*)malloc(sizeof(TAREFA));
    nova->id = id;
    strcpy(nova->descricao, decricao);
    nova->prioridade = prioridade;
    strcpy(nova->status, status);
    nova->prox = NULL;

    if (fila->inicio == NULL) { 
        fila->inicio = nova;
    } else {
        fila->fim->prox = nova;
    }
    fila->fim = nova;
}

void imprimirTarefasDoDia(TarefasDoDia* fila){
    if(fila == NULL) return;

    printf("--------------- TAREFAS DO DIA ---------------\n");
    TAREFA* atual = fila->inicio;
    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Tarefa: %s\n", atual->descricao);
        printf("Prioridade: %d\n", atual->prioridade);
        printf("Status: %s\n", atual->status);
        printf("----------------------------------------------\n");
        atual = atual->prox;
    }
}

void liberarTarefasDoDia(TarefasDoDia* fila){
    TAREFA* aux = fila->inicio;
    while (aux != NULL){
        TAREFA* temp = aux->prox;
        free(aux);
        aux = temp;
    }
    free(fila);
}
