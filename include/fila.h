#ifndef FILA_H
#define FILA_H

typedef struct TAREFA TAREFA;
typedef struct DataTarefa DataTarefa;

typedef struct TarefasDoDia{
    DataTarefa* data;
    int inicio;
    int fim;
    int tamanho;
    int capacidade;
}TarefasDoDia;

void adicionarTarefasNaFila(TarefasDoDia* fila, DataTarefa* tarefasDoDia);

#endif 