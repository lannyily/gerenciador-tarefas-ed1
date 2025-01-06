#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

void addTarefaConcluida(TarefasConcluidas* concluidas, TAREFA* lista) {
    if (concluidas->tarefaMaisAntiga == NULL) {
        // Primeira tarefa a ser adicionada
        concluidas->tarefaMaisAntiga = lista;
        concluidas->tarefaMaisRecente = lista;
        lista->prox = lista; // Lista circular
        concluidas->tamanho++;
        return;
    }

    if (concluidas->tamanho < concluidas->capacidade) {
        // Adiciona ao final da lista circular
        lista->prox = concluidas->tarefaMaisAntiga;
        concluidas->tarefaMaisRecente->prox = lista;
        concluidas->tarefaMaisRecente = lista;
        concluidas->tamanho++;
    } else {
        // Substitui a tarefa mais antiga
        TAREFA* antiga = concluidas->tarefaMaisAntiga;
        concluidas->tarefaMaisAntiga = antiga->prox; // Atualiza a mais antiga
        concluidas->tarefaMaisRecente->prox = lista; // Conecta a nova ao final
        lista->prox = concluidas->tarefaMaisAntiga;  // Conecta a nova ao início
        concluidas->tarefaMaisRecente = lista;      // Atualiza a mais recente
        free(antiga); // Libera memória da tarefa mais antiga
    }
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
        printf(" ID: %d\n Tarefa: %s\n Prioridade: %d\n Status: %s\n\n", 
            atual->id, atual->descricao, atual->prioridade, atual->status);
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
