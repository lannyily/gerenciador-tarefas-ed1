#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/listaCircular.h"

TarefasConcluidas* criarTC(int capacidade){
    TarefasConcluidas* concluidas = (TarefasConcluidas*)malloc(sizeof(TarefasConcluidas));
    if (!concluidas){
        exit(1);
    }
    concluidas->tarefaMaisAntiga = NULL;
    concluidas->tarefaMaisRecente = NULL;
    concluidas->tamanho = 0;
    concluidas->capacidade = capacidade;
    return concluidas;
}

void addTarefaConcluida(TarefasConcluidas* concluidas, TAREFA* lista){
    if (concluidas->tarefaMaisAntiga == NULL){
        concluidas->tarefaMaisAntiga = lista;
        concluidas->tarefaMaisRecente = lista;
        lista->prox = lista;
        concluidas->tamanho++;
        return;
    }

    if (concluidas->tamanho < concluidas->capacidade){
        lista->prox = concluidas->tarefaMaisAntiga;
        concluidas->tarefaMaisRecente->prox = lista;
        concluidas->tarefaMaisRecente = lista;
        concluidas->tamanho++;
    }

    TAREFA* antiga = concluidas->tarefaMaisAntiga;
    lista->prox = antiga->prox;
    concluidas->tarefaMaisRecente->prox = lista;
    concluidas->tarefaMaisAntiga = lista->prox;
    concluidas->tarefaMaisRecente = lista;
    free(antiga);
}

void imprimirTC(TarefasConcluidas* concluidas){
    if (concluidas->tarefaMaisAntiga == NULL){
        printf("Nenhuma tarefa concluida!\n");
        return;
    }

    TAREFA* atual = concluidas->tarefaMaisAntiga;
    printf("Tarefas Concluidas (Capacidade: %d):\n", concluidas->capacidade);

    TAREFA* inicial = concluidas->tarefaMaisAntiga;

    do {
        printf(" ID: %d\n Tarefa: %s\n Prioridade: %d\n Status: %d\n", atual->id, atual->descricao, atual->prioridede, atual->status);
        atual = atual->prox;
    } while (atual != inicial);

}

void liberarTC(TarefasConcluidas* concluidas) {
    if (concluidas == NULL || concluidas->tarefaMaisAntiga == NULL) {
        free(concluidas);
        return;
    }

    TAREFA* atual = concluidas->tarefaMaisAntiga;
    TAREFA* proximo;

    do {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    } while (atual != concluidas->tarefaMaisAntiga);

    free(concluidas);
}
