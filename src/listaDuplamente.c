#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/listaDuplamente.h"
#include "../include/listaEncadeada.h"


/* 
TarefasOrdenadas* mesclar(TarefasOrdenadas* lista1, TarefasOrdenadas* lista2){
    TarefasOrdenadas* resultado = NULL;

    if(lista1 == NULL) return lista2;
    if(lista2 == NULL) return lista1;

    if(lista1->tarefa->id <= lista2->tarefa->id){
        resultado = lista1;
        resultado->prox = mesclar(lista1->prox, lista2);
    } else {
        resultado = lista2;
        resultado->prox = mesclar(lista1, lista2->prox);
    }
    return resultado;
}

TarefasOrdenadas* dividir(TarefasOrdenadas* ordenadas){
    TarefasOrdenadas* meio = ordenadas;
    TarefasOrdenadas* fim = ordenadas;

    while(fim != NULL && fim->prox != NULL){
        fim = fim->prox->prox;
        meio = meio->prox;
    }

    TarefasOrdenadas segundaMetade = meio->prox;
    meio->prox = NULL;
    return segundaMetade;
}

TarefasOrdenadas* mergeSort(TarefasOrdenadas* ordenadas){
    if (ordenadas == NULL || ordenadas->prox == NULL) return ordenadas;

    TarefasOrdenadas* segundaMetade = dividir(ordenadas);

    ordenadas = mergeSort(ordenadas);
    segundaMetade = mergeSort(segundaMetade);

    return mesclar(ordenadas, segundaMetade);
}
*/

void insertionSort(TarefasOrdenadas** todasTarefasOrdenadas){
    if (*todasTarefasOrdenadas == NULL) return;

    TarefasOrdenadas* atual = *todasTarefasOrdenadas;
    TarefasOrdenadas* ordenar = NULL;

    while(atual != NULL) {
        TarefasOrdenadas* proximo = atual->prox;
        atual->ant = atual->prox = NULL;

        if(ordenar == NULL || ordenar->tarefa->id >= atual->tarefa->id) {
            atual->prox = ordenar;
            if (ordenar != NULL){
                ordenar->ant = atual;
            }
            ordenar = atual;
        } else{
            TarefasOrdenadas* temp = ordenar;
            while(temp->prox != NULL && temp->prox->tarefa->id < atual->tarefa->id){
                temp = temp->prox;
            }

            atual->prox = temp->prox;
            if (temp->prox != NULL){
                temp->prox->ant = atual;
            }
            temp->prox = atual;
            atual->ant = temp;
        }
        atual = proximo;
    }
    *todasTarefasOrdenadas = ordenar;
}

void transferirTodasTarefas(TAREFA* lista, TarefasOrdenadas** todasTarefasOrdenadas) {
    TAREFA* tarefaAtual = lista;

    while (tarefaAtual != NULL) {
        TarefasOrdenadas* novaTarefa = transferirTarefas(tarefaAtual->id, tarefaAtual->descricao, tarefaAtual->prioridade, tarefaAtual->status);

        if (*todasTarefasOrdenadas == NULL) {
            *todasTarefasOrdenadas = novaTarefa;
        } else {
            TarefasOrdenadas* temp = *todasTarefasOrdenadas;
            while(temp->prox != NULL) {
                temp = temp->prox;
            }
            temp->prox = novaTarefa;
            novaTarefa->ant = temp;
        }
        tarefaAtual = tarefaAtual->prox;
    }
}

void bubblesort(TarefasOrdenadas* ordenadas) {
    int troca;
    TarefasOrdenadas *noAtual, *noProximo;
    troca = 1;

    while (troca) {
        troca = 0;
        noAtual = ordenadas;

        while (noAtual != NULL && noAtual->prox != NULL) {
            noProximo = noAtual->prox;

            if (noAtual->tarefa->prioridade > noProximo->tarefa->prioridade) {
                TAREFA tempTarefa = *(noAtual->tarefa);
                *(noAtual->tarefa) = *(noProximo->tarefa);
                *(noProximo->tarefa) = tempTarefa;

                troca = 1;
            }
            noAtual = noAtual->prox;
        }
    }
}

TarefasOrdenadas* transferirTarefas(int tarefaID, char* descricao, int prioridade, char* status) {
    TarefasOrdenadas* novaTarefa = (TarefasOrdenadas*)malloc(sizeof(TarefasOrdenadas));
    novaTarefa->tarefa = (TAREFA*)malloc(sizeof(TAREFA));
    novaTarefa->tarefa->id = tarefaID;
    strcpy(novaTarefa->tarefa->descricao, descricao);
    novaTarefa->tarefa->prioridade = prioridade;
    strcpy(novaTarefa->tarefa->status, status);
    novaTarefa->prox = NULL;
    novaTarefa->ant = NULL;
    return novaTarefa;
}

void inserirTarefasOrdenadas(DataTarefa* listaData, TarefasOrdenadas** ordenadas) {
    DataTarefa* dataAtual = listaData;

    while (dataAtual != NULL) {
        TAREFA* tarefaAtual = dataAtual->tarefas;
        while (tarefaAtual != NULL) {
            TarefasOrdenadas* novaTarefa = transferirTarefas(tarefaAtual->id, tarefaAtual->descricao, tarefaAtual->prioridade, tarefaAtual->status);

            if (*ordenadas == NULL) {
                *ordenadas = novaTarefa;
            } else {
                TarefasOrdenadas* temp = *ordenadas;
                while (temp->prox != NULL) {
                    temp = temp->prox;
                }
                temp->prox = novaTarefa;
                novaTarefa->ant = temp;
            }
            tarefaAtual = tarefaAtual->prox;
        }
        dataAtual = dataAtual->prox;
    }
}

void imprimirTarefasOrdenadas(TarefasOrdenadas* ordenadas) {
    TarefasOrdenadas* atual = ordenadas;
    while (atual != NULL) {
        printf("ID: %d\nTarefa: %s\nPrioridade: %d\nStatus: %s\n\n",
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