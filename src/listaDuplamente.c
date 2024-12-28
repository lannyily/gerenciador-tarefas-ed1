#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/listaDuplamente.h"
#include "../include/listaEncadeada.h"

TarefasOrdenadas* transferirTarefas(int tarefaID, char* descricao, int prioridade, int status) {
    TarefasOrdenadas* novaTarefa = (TarefasOrdenadas*)malloc(sizeof(TarefasOrdenadas));
    novaTarefa->tarefa = (TAREFA*)malloc(sizeof(TAREFA));
    novaTarefa->tarefa->id = tarefaID;
    strcpy(novaTarefa->tarefa->descricao, descricao);
    novaTarefa->tarefa->prioridade = prioridade;
    novaTarefa->tarefa->status = status;
    novaTarefa->prox = NULL;
    novaTarefa->ant = NULL;
    return novaTarefa;
}

void inserirTarefaOrdenada(TarefasOrdenadas** ordenadas, TAREFA* tarefa) {
    TarefasOrdenadas* novaTarefa = transferirTarefas(tarefa->id, tarefa->descricao, tarefa->prioridade, tarefa->status);

    if (*ordenadas == NULL || (*ordenadas)->tarefa->prioridade > novaTarefa->tarefa->prioridade) {
        novaTarefa->prox = *ordenadas;
        if (*ordenadas != NULL) {
            (*ordenadas)->ant = novaTarefa;
        }
        *ordenadas = novaTarefa;
        return;
    }

    TarefasOrdenadas* atual = *ordenadas;
    while (atual->prox != NULL && atual->prox->tarefa->prioridade <= novaTarefa->tarefa->prioridade) {
        atual = atual->prox;
    }

    novaTarefa->prox = atual->prox;
    if (atual->prox != NULL) {
        atual->prox->ant = novaTarefa;
    }
    atual->prox = novaTarefa;
    novaTarefa->ant = atual;
}

void ordenarTarefasDeDataNaListaDupla(DataTarefa* listaData, TarefasOrdenadas** ordenadas) {
    DataTarefa* dataAtual = listaData;
    while (dataAtual != NULL) {
        TAREFA* tarefaAtual = dataAtual->tarefas;
        while (tarefaAtual != NULL) {
            inserirTarefaOrdenada(ordenadas, tarefaAtual);
            tarefaAtual = tarefaAtual->prox;
        }
        dataAtual = dataAtual->prox;
    }
}

void imprimirTarefasOrdenadas(TarefasOrdenadas* ordenadas) {
    TarefasOrdenadas* atual = ordenadas;
    while (atual != NULL) {
        printf("ID: %d\nTarefa: %s\nPrioridade: %d\nStatus: %d\n\n",
               atual->tarefa->id, atual->tarefa->descricao, atual->tarefa->prioridade, atual->tarefa->status);
        atual = atual->prox;
    }
}

void liberarTarefasOrdenadas(TarefasOrdenadas* ordenadas) {
    TarefasOrdenadas* atual = ordenadas;
    while (atual != NULL) {
        TarefasOrdenadas* temp = atual;
        atual = atual->prox;
        free(temp);         
    }
}