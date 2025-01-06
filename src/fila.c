#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/fila.h"
#include "../include/listaEncadeada.h"

int contarTarefasNaFila(TarefasDoDia* fila) {
    TAREFA* atual = fila->inicio;   // Começa no início da fila
    int count = 0;
    while (atual != NULL) {         // Conta os nós da fila
        count++;
        atual = atual->prox;
    }
    return count;                   // Retorna a quantidade de tarefas
}

TarefasDoDia* criarFila(void){
    TarefasDoDia* fila = (TarefasDoDia*)malloc(sizeof(TarefasDoDia));   // Aloca memória para a fila
    fila->inicio = NULL;                                                // Inicializa a fila com o início vazio
    fila->fim = NULL;                                                   // Inicializa a fila com o fim vazio
    return fila;                                                        // Retorna o ponteiro para a fila criada
}

void inserirTarefasNaFila(TarefasDoDia* fila, char* decricao, int prioridade, char* status, int id){
    TAREFA* nova = (TAREFA*)malloc(sizeof(TAREFA));     // Aloca memória para a nova tarefa
    nova->id = id;                                      // Define o ID da tarefa
    strcpy(nova->descricao, decricao);                  // Copia a descrição
    nova->prioridade = prioridade;                      // Define a prioridade
    strcpy(nova->status, status);                       // Define o status
    nova->prox = NULL;                                  // Inicializa o ponteiro para a próxima tarefa como NULL

    if (fila->inicio == NULL) { 
        fila->inicio = nova;                            // A nova tarefa se torna a primeira da fila
    } else {
        fila->fim->prox = nova;                         // Se não estiver vazia, adiciona a tarefa no fim
    }
    fila->fim = nova;                                   // Atualiza o ponteiro para o fim da fila
}

void imprimirTarefasDoDia(TarefasDoDia* fila){
    if(fila == NULL) return;                                    // Verifica se a fila é NULL

    printf("--------------- TAREFAS DO DIA ---------------\n");
    TAREFA* atual = fila->inicio;                               // Começa no início da fila
    while (atual != NULL) {                                     // Enquanto houver tarefas na fila
        printf("ID: %d\n", atual->id);
        printf("Tarefa: %s\n", atual->descricao);
        printf("Prioridade: %d\n", atual->prioridade);
        printf("Status: %s\n", atual->status);
        printf("----------------------------------------------\n");
        atual = atual->prox;                                    // Move para a próxima tarefa
    }
}

void liberarTarefasDoDia(TarefasDoDia* fila){
    TAREFA* aux = fila->inicio;                 // Ponteiro auxiliar para percorrer a fila
    while (aux != NULL){
        TAREFA* temp = aux->prox;               // Armazena o próximo elemento da fila
        free(aux);
        aux = temp;                             // Avança para o próximo elemento
    }
    free(fila);                                 // Libera a memória da própria fila
}
