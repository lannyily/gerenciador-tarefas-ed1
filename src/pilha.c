#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/pilha.h"
#include "../include/listaEncadeada.h"

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

DataTarefa* desfazerAlteracao(DataTarefa* listaData, Alteracao* pilha) { 
    TAREFA* tarefaRestaurada = pilhaPop(pilha);
    if (tarefaRestaurada == NULL) {
        printf("Nenhuma alteracao para desfazer!\n");
        return listaData;
    }

    int idDataTarefa = tarefaRestaurada->id / 1000;

    DataTarefa* auxData = listaData;
    while (auxData != NULL) {
        int idDataAtual = calcularId(auxData->data, 0) / 1000;
        if (idDataAtual == idDataTarefa) {
            break;
        }
        auxData = auxData->prox;
    }

    if (auxData == NULL) {
        printf("Data do ID %d nao encontrada!\n", tarefaRestaurada->id);
        free(tarefaRestaurada); 
        return listaData;
    }

    TAREFA* anterior = NULL;
    TAREFA* atual = auxData->tarefas;

    while (atual != NULL) {
        if (atual->id == tarefaRestaurada->id) {
            if (anterior == NULL) {
                auxData->tarefas = tarefaRestaurada;
            } else {
                anterior->prox = tarefaRestaurada;
            }
            tarefaRestaurada->prox = atual->prox;
            free(atual); 
            printf("Tarefa ID %d foi restaurada na data %s!\n", tarefaRestaurada->id, auxData->data);
            return listaData;
        }
        anterior = atual;
        atual = atual->prox;
    }

    tarefaRestaurada->prox = auxData->tarefas;
    auxData->tarefas = tarefaRestaurada;
    auxData->cont++;
    printf("Tarefa com ID %d restaurada na data %s!\n", tarefaRestaurada->id, auxData->data);

    return listaData;
}

void liberarAlteracao(Alteracao* pilha) {
    TAREFA* q = pilha->primeiro;
    while (q != NULL) {
        TAREFA* temp = q->prox;
        free(q);
        q = temp;
    }
    free(pilha);
}