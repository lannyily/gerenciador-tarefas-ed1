#ifndef FILA_H
#define FILA_H

typedef struct TAREFA TAREFA;
typedef struct DataTarefa DataTarefa;

typedef struct TarefasDoDia{
    TAREFA* inicio;
    TAREFA* fim;
}TarefasDoDia;

int contarTarefasNaFila(TarefasDoDia* fila);
TarefasDoDia* criarFila(void);
void inserirTarefasNaFila(TarefasDoDia* fila, char* decricao, int prioridade, char* status, int id);
void imprimirTarefasDoDia(TarefasDoDia* fila);
void liberarTarefasDoDia(TarefasDoDia* fila);

#endif 