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

void idParaData(int id, char* data) {
    int dia = id / 1000;
    int mes = (id % 1000) / 100;
    sprintf(data, "%02d-%02d-2025", dia, mes);  // Formata a data com o ano de 2025
}

DataTarefa* desfazerAlteracao(DataTarefa* listaData, Alteracao* pilha) { 
    TAREFA* tarefaRestaurada = pilhaPop(pilha);
    if (tarefaRestaurada == NULL) {
        printf("Nenhuma alteração para desfazer!\n");
        return listaData;
    }

    // Extrair a data do ID
    char dataExtraida[11];
    idParaData(tarefaRestaurada->id, dataExtraida);

    // Procurar a data correspondente
    DataTarefa* auxData = listaData;
    DataTarefa* anteriorData = NULL;

    while (auxData != NULL) {
        if (strcmp(auxData->data, dataExtraida) == 0) {
            break; // Encontrou a data
        }
        anteriorData = auxData;
        auxData = auxData->prox;
    }

    // Se a data não existir, criar uma nova
    if (auxData == NULL) {
        printf("Data %s não encontrada! Criando nova data...\n", dataExtraida);
        auxData = (DataTarefa*)malloc(sizeof(DataTarefa));
        if (!auxData) {
            printf("Erro ao alocar memória para nova data!\n");
            free(tarefaRestaurada);
            return listaData;
        }

        strcpy(auxData->data, dataExtraida);
        auxData->tarefas = NULL;
        auxData->cont = 0;
        auxData->prox = NULL;

        // Inserir nova data na lista de datas
        if (anteriorData == NULL) {
            listaData = auxData;
        } else {
            anteriorData->prox = auxData;
        }
    }

    // Verificar se já existe uma tarefa com o mesmo ID
    TAREFA* atual = auxData->tarefas;
    TAREFA* anterior = NULL;

    while (atual != NULL) {
        if (atual->id == tarefaRestaurada->id) {
            printf("Substituindo tarefa existente com ID %d.\n", atual->id);

            // Substituir a tarefa existente
            if (anterior == NULL) {
                auxData->tarefas = tarefaRestaurada;
            } else {
                anterior->prox = tarefaRestaurada;
            }
            tarefaRestaurada->prox = atual->prox;
            free(atual); // Liberar a memória da tarefa antiga
            printf("Tarefa com ID %d substituída na data %s!\n", tarefaRestaurada->id, auxData->data);
            return listaData;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Caso não exista, inserir no início da lista de tarefas
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