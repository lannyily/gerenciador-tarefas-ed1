#ifndef LISTA_DUPLAMENTE_H
#define LISTA_DUPLAMENTE_H
#include "listaEncadeada.h" 

typedef struct TAREFA TAREFA;
typedef struct DataTarefa DataTarefa;
typedef struct TarefasConcluida TarefasConcluida;

typedef struct TarefasOrdenadas{
    TAREFA* tarefa;
    struct TarefasOrdenadas* prox;
    struct TarefasOrdenadas* ant;
}TarefasOrdenadas;

TarefasOrdenadas* transferirTarefas(int tarefaID, char* descricao, int prioridade, int status);
void inserirTarefaOrdenada(TarefasOrdenadas** ordenadas, TAREFA* lista);
void ordenarTarefasDeDataNaListaDupla(DataTarefa* listaData, TarefasOrdenadas** ordenadas);
void imprimirTarefasOrdenadas(TarefasOrdenadas* ordenadas);
void liberarTarefasOrdenadas(TarefasOrdenadas* ordenadas);

#endif 