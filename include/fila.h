#ifndef FILA_H
#define FILA_H

typedef struct TAREFA TAREFA;
typedef struct DataTarefa DataTarefa;

typedef struct TarefasDoDia{
    TAREFA* inicio;
    TAREFA* fim;
}TarefasDoDia;

TarefasDoDia* criarFila(void);
void inserirTarefasNaFila(TarefasDoDia* fila, char* decricao, int prioridade, char* status, int id);

#endif 