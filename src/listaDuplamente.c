#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/listaDuplamente.h"
#include "../include/listaEncadeada.h"

TarefasOrdenadas* meio(TarefasOrdenadas* inicio, TarefasOrdenadas* fim){
    if (inicio == NULL) return NULL;

    if (inicio == fim) return inicio;

    TarefasOrdenadas* lento = inicio;
    TarefasOrdenadas* rapido = inicio->prox;

    while(rapido != fim){
        rapido = rapido->prox;
        lento = lento->prox;
        if (rapido != fim){
            rapido = rapido->prox;
        }
    }
    return lento;
}

int buscaBinaria(TarefasOrdenadas* ordenadas, int idBusca){
    TarefasOrdenadas* inicio = ordenadas;
    TarefasOrdenadas* fim = NULL;

    while(1){
        TarefasOrdenadas* meioLista = meio(inicio, fim);

        if (meioLista == NULL) return 0;

        if (meioLista->tarefa->id == idBusca) {
            printf("\n----------------- TAREFA %d -----------------\n", idBusca);
            printf("ID: %d\nTarefa: %s\nPrioridade: %d\nStatus: %s\n\n",
                meioLista->tarefa->id, meioLista->tarefa->descricao, meioLista->tarefa->prioridade, meioLista->tarefa->status);
            return 1;
        } else if (inicio == fim){
            break;
        } else if (meioLista->tarefa->id < idBusca){
            inicio = meioLista->prox;
        } else if (meioLista->tarefa->id > idBusca){
            fim = meioLista;
        }
    }
    return 0;
}

TarefasOrdenadas* concatenar(TarefasOrdenadas* menor, TarefasOrdenadas* pivo, TarefasOrdenadas* maior) {
    TarefasOrdenadas* resultado = menor;

    if (resultado != NULL) {
        TarefasOrdenadas* atual = resultado;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = pivo;
        pivo->ant = atual;
    } else {
        resultado = pivo;
    }

    // Conecta o pivo à lista "maior"
    pivo->prox = maior;
    if (maior != NULL) {
        maior->ant = pivo;
    }
    
    return resultado;
}

TarefasOrdenadas* particionar(TarefasOrdenadas* ordenadas, TarefasOrdenadas** menor, TarefasOrdenadas** maior) {
    TarefasOrdenadas* pivo = ordenadas;
    TarefasOrdenadas* atual = ordenadas->prox;

    *menor = NULL;
    *maior = NULL;

    while (atual != NULL) {
        TarefasOrdenadas* proxima = atual->prox;
        atual->ant = NULL; // Limpa o ponteiro "ant"
        if (atual->tarefa->prioridade >= pivo->tarefa->prioridade) {
            // Adiciona ao início da lista "menor"
            atual->prox = *menor;
            if (*menor != NULL) {
                (*menor)->ant = atual;
            }
            *menor = atual;
        } else {
            // Adiciona ao início da lista "maior"
            atual->prox = *maior;
            if (*maior != NULL) {
                (*maior)->ant = atual;
            }
            *maior = atual;
        }
        atual = proxima;
    }

    pivo->prox = NULL;
    pivo->ant = NULL;

    return pivo;
}

TarefasOrdenadas* quickSort(TarefasOrdenadas* ordenadas) {
    if (ordenadas == NULL || ordenadas->prox == NULL) {
        return ordenadas;
    }

    TarefasOrdenadas *menor, *maior;
    TarefasOrdenadas* pivo = particionar(ordenadas, &menor, &maior);

    menor = quickSort(menor);
    maior = quickSort(maior);
    
    return concatenar(menor, pivo, maior);
}

TarefasOrdenadas* mesclar(TarefasOrdenadas* lista1, TarefasOrdenadas* lista2) {
    TarefasOrdenadas* resultado = NULL;

    if (lista1 == NULL) return lista2;
    if (lista2 == NULL) return lista1;

    if (lista1->tarefa->prioridade <= lista2->tarefa->prioridade) {
        resultado = lista1;
        resultado->prox = mesclar(lista1->prox, lista2);
        if (resultado->prox != NULL) {
            resultado->prox->ant = resultado;
        }
    } else {
        resultado = lista2;
        resultado->prox = mesclar(lista1, lista2->prox);
        if (resultado->prox != NULL) {
            resultado->prox->ant = resultado;
        }
    }
    return resultado;
}

TarefasOrdenadas* dividir(TarefasOrdenadas* ordenadas) {
    TarefasOrdenadas* meio = ordenadas;
    TarefasOrdenadas* fim = ordenadas;

    while (fim != NULL && fim->prox != NULL) {
        fim = fim->prox->prox; 
        if (fim != NULL) {
            meio = meio->prox; 
        }
    }

    TarefasOrdenadas* segundaMetade = meio->prox;
    if (segundaMetade != NULL) {
        segundaMetade->ant = NULL; 
    }
    meio->prox = NULL; 

    return segundaMetade;
}

TarefasOrdenadas* mergeSort(TarefasOrdenadas* ordenadas) {
    if (ordenadas == NULL || ordenadas->prox == NULL)  return ordenadas; 
    
    TarefasOrdenadas* segundaMetade = dividir(ordenadas);

    ordenadas = mergeSort(ordenadas);
    segundaMetade = mergeSort(segundaMetade);

    return mesclar(ordenadas, segundaMetade);
}

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

void transferirTodasTarefas(DataTarefa* lista, TarefasOrdenadas** todasTarefasOrdenadas) {
    DataTarefa* dataAtual = lista;

    while (dataAtual != NULL) {
        TAREFA* tarefaAtual = dataAtual->tarefas;

        while (tarefaAtual != NULL) {
            TarefasOrdenadas* novaTarefa = transferirTarefas(tarefaAtual->id, tarefaAtual->descricao, tarefaAtual->prioridade, tarefaAtual->status);

            if (*todasTarefasOrdenadas == NULL) {
                *todasTarefasOrdenadas = novaTarefa;
            } else {
                TarefasOrdenadas* temp = *todasTarefasOrdenadas;

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