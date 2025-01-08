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

    TAREFA* topo = pilha->primeiro;     // Armazena o topo da pilha  
    pilha->primeiro = topo->prox;       // Atualiza o topo da pilha para o próximo nó
    return topo;
}

void idParaData(int id, char* data){
    int dia = id / 1000;                        // Extrai o dia do ID
    int mes = (id % 1000) / 100;                // Extrai o mês do ID
    sprintf(data, "%02d-%02d-2025", dia, mes);  // Formata a data como string
}

DataTarefa* desfazerAlteracao(DataTarefa* listaData, Alteracao* pilha) { 
    TAREFA* tarefaRestaurada = pilhaPop(pilha);         // Remove a última tarefa da pilha
    if (tarefaRestaurada == NULL) {
        printf("Nenhuma alteracao para desfazer!\n");
        return listaData;                               // Se a pilha estiver vazia, não há o que desfazer
    }

    char dataExtraida[11];
    idParaData(tarefaRestaurada->id, dataExtraida);     // Converte o ID para data

    DataTarefa* auxData = listaData;
    DataTarefa* anteriorData = NULL;

    // Procura pela data correspondente na lista de datas
    while (auxData != NULL) {
        if (strcmp(auxData->data, dataExtraida) == 0) {
            break;                                      // Se a data for encontrada, sai do loop
        }
        anteriorData = auxData;
        auxData = auxData->prox;
    }

    // Se a data não foi encontrada, cria uma nova data
    if (auxData == NULL) {
        printf("Data %s nao encontrada! Criando nova data...\n", dataExtraida);
        auxData = (DataTarefa*)malloc(sizeof(DataTarefa));
        if (!auxData) {
            free(tarefaRestaurada);                     // Libera a memória da tarefa restaurada
            return listaData;
        }

        strcpy(auxData->data, dataExtraida);            // Atribui a data à nova data
        auxData->tarefas = NULL;
        auxData->cont = 0;
        auxData->prox = NULL;

        if (anteriorData == NULL) {
            listaData = auxData;                       
        } else {
            anteriorData->prox = auxData;               
        }
    }

    TAREFA* atual = auxData->tarefas;                   // Inicia a busca pela tarefa na data 
    TAREFA* anterior = NULL;

    // Procura pela tarefa com o mesmo ID da tarefa restaurada
    while (atual != NULL) 
    {
        if (atual->id == tarefaRestaurada->id) {
            printf("Substituindo tarefa existente com ID %d.\n", atual->id);

            // Substitui a tarefa existente pela restaurada
            if (anterior == NULL) {
                auxData->tarefas = tarefaRestaurada;
            } else {
                anterior->prox = tarefaRestaurada;
            }
            tarefaRestaurada->prox = atual->prox;
            free(atual); 
            printf("Tarefa com ID %d substituída na data %s!\n", tarefaRestaurada->id, auxData->data);
            return listaData;                           // Retorna a lista com a tarefa substituída
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Caso a tarefa não tenha sido encontrada, insere a tarefa restaurada no início da lista de tarefas
    tarefaRestaurada->prox = auxData->tarefas;
    auxData->tarefas = tarefaRestaurada;
    auxData->cont++;
    printf("Tarefa com ID %d restaurada na data %s!\n", tarefaRestaurada->id, auxData->data);

    return listaData;           // Retorna a lista com a tarefa restaurada
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