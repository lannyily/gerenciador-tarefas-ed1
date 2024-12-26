#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

typedef struct TarefaConcluida {
    int id;
    char descricao[300];
    struct TarefaConcluida* prox;
}TarefaConcluida;

typedef struct LC {
    TarefaConcluida* tarefaMaisAntiga;
    TarefaConcluida* tarefaMaisRecente;
    int tamanho;
    int capacidade;
}LC;

#endif 
