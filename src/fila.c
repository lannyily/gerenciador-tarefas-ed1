#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/fila.h"

void adicionarTarefasNaFila(TarefasDoDia* fila, DataTarefa* tarefasDoDia) {
    if (tarefasDoDia == NULL || tarefasDoDia->tarefas == NULL) {
        printf("Nenhuma tarefa encontrada para o dia.\n");
        return;
    }

    TAREFA* tarefaAtual = tarefasDoDia->tarefas;
    while (tarefaAtual != NULL) {
        enfileirar(fila, tarefaAtual);
        tarefaAtual = tarefaAtual->prox;
    }
    printf("Tarefas do dia %s adicionadas na fila.\n", tarefasDoDia->data);
}

void carregarTarefasDoDia(DataTarefa* listaData, TarefasDoDia* fila) {
    char dataAtual[10];
    obterDataAtual(dataAtual, sizeof(dataAtual));

    printf("Data atual: %s\n", dataAtual);

    DataTarefa* tarefasDoDia = encontrarTarefasDoDia(listaData, dataAtual);
    if (tarefasDoDia != NULL) {
        adicionarTarefasNaFila(fila, tarefasDoDia);
    } else {
        printf("Nenhuma tarefa encontrada para a data %s.\n", dataAtual);
    }
}