#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pilha.h"

void pilhaPush(Alteracao* pilha, TAREFA* tarefaOriginal){
    TAREFA* novaTarefa = (TAREFA*)malloc(sizeof(TAREFA));

    if (novaTarefa == NULL) return;

    *novaTarefa = *tarefaOriginal;
    novaTarefa->prox = pilha->primeiro;
    pilha->primeiro = novaTarefa;
}

TAREFA* pilhaPop(Alteracao* pilha){
    if (pilha->primeiro == NULL) return NULL;

    TAREFA* topo = pilha->primeiro;
    pilha->primeiro = topo->prox;
    return topo;
}

void desfazerAlteracao(Alteracao* pilha, DataTarefa* listaData){
    TAREFA* desfazer = pilhaPop(pilha);

    if (desfazer == NULL) return;

    DataTarefa* atual = listaData;
    while (atual != NULL){
        if (strcmp(atual->data, desfazer->status) == 0){
            desfazer->prox = atual->tarefas;
            atual->tarefas = desfazer;
            printf("Alteracao desfeita para a tarefa ID %d.\n", desfazer->id);
            return;
        }
        atual = atual->prox;
    }
    printf("Data nao encontrada! Nao foi possivel desfazer a alteracao!\n");
    free(desfazer);
}