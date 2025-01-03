#ifndef LISTA_DUPLAMENTE_H
#define LISTA_DUPLAMENTE_H
#include "listaEncadeada.h" 

typedef struct TAREFA TAREFA;
typedef struct DataTarefa DataTarefa;
typedef struct TarefasConcluida TarefasConcluida;
typedef struct TarefasOrdenadas TarefasOrdenadas;

typedef struct TarefasOrdenadas{
    TAREFA* tarefa;
    struct TarefasOrdenadas* prox;
    struct TarefasOrdenadas* ant;
}TarefasOrdenadas;

TarefasOrdenadas* meio(TarefasOrdenadas* inicio, TarefasOrdenadas* fim);
int buscaBinaria(TarefasOrdenadas* ordenadas, int idBusca);
TarefasOrdenadas* concatenar(TarefasOrdenadas* menor, TarefasOrdenadas* pivo, TarefasOrdenadas* maior);
TarefasOrdenadas* particionar(TarefasOrdenadas* ordenadas, TarefasOrdenadas** menor, TarefasOrdenadas** maior);
TarefasOrdenadas* quickSort(TarefasOrdenadas* ordenadas);
TarefasOrdenadas* mesclar(TarefasOrdenadas* lista1, TarefasOrdenadas* lista2);
TarefasOrdenadas* dividir(TarefasOrdenadas* ordenadas);
TarefasOrdenadas* mergeSort(TarefasOrdenadas* ordenadas);
void insertionSort(TarefasOrdenadas** todasTarefasOrdenadas);
void transferirTodasTarefas(DataTarefa* lista, TarefasOrdenadas** todasTarefasOrdenadas);
void bubblesort(TarefasOrdenadas* ordenadas);
TarefasOrdenadas* transferirTarefas(int tarefaID, char* descricao, int prioridade, char* status);
void inserirTarefasOrdenadas(DataTarefa* listaData, TarefasOrdenadas** ordenadas);
void imprimirTarefasOrdenadas(TarefasOrdenadas* ordenadas);
void liberarTarefasOrdenadas(TarefasOrdenadas* ordenadas);

#endif 