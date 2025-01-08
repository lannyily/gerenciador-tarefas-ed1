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

void addTarefaConcluida(TarefasConcluidas* concluidas, TAREFA* lista){
    if (concluidas->tarefaMaisAntiga == NULL) {
        // Caso a lista esteja vazia, adiciona a primeira tarefa
        concluidas->tarefaMaisAntiga = lista;
        concluidas->tarefaMaisRecente = lista;
        lista->prox = lista;    
        concluidas->tamanho++;  
        return;
    }

    if(concluidas->tamanho < concluidas->capacidade) {
        // Caso a lista ainda tenha espaço, adiciona a nova tarefa
        lista->prox = concluidas->tarefaMaisAntiga;
        concluidas->tarefaMaisRecente->prox = lista;
        concluidas->tarefaMaisRecente = lista;
        concluidas->tamanho++;
    } 
    
    else {
        // Caso a lista esteja cheia, remove a tarefa mais antiga e adiciona a nova tarefa
        TAREFA* antiga = concluidas->tarefaMaisAntiga;
        concluidas->tarefaMaisAntiga = antiga->prox; 
        concluidas->tarefaMaisRecente->prox = lista; 
        lista->prox = concluidas->tarefaMaisAntiga;  
        concluidas->tarefaMaisRecente = lista;      
        free(antiga);  
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
    } while (atual != inicial);     // Itera pela lista circular até voltar à tarefa inicial

}

void liberarTC(TarefasConcluidas* concluidas) {
    if (concluidas == NULL || concluidas->tarefaMaisAntiga == NULL) {
        free(concluidas);
        return;
    }

    TAREFA* atual = concluidas->tarefaMaisAntiga;
    TAREFA* proximo;

    do {
        proximo = atual->prox;      // Guarda o próximo elemento
        free(atual);
        atual = proximo;
    } while (atual != concluidas->tarefaMaisAntiga);    // Itera pela lista circular até voltar à tarefa inicial

    free(concluidas);
}
