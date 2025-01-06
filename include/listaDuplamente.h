#ifndef LISTA_DUPLAMENTE_H
#define LISTA_DUPLAMENTE_H
#include "listaEncadeada.h" 

/**
 * Estrutura que representa uma tarefa.
 * 
 * Detalhes internos da tarefa, como descrição, prioridade, 
 * status e id são armazenados aqui. 
 * 
 */
typedef struct TAREFA TAREFA;

/**
 * Estrutura que representa a data de uma tarefa.
 * 
 * Detalhes internos sobre a data da tarefa, como ano, mês, 
 * dia, etc. são armazenados aqui. 
 * 
 */
typedef struct DataTarefa DataTarefa;

/**
 * Estrutura que representa as tarefas concluídas.
 * 
 * A estrutura mantém o controle das tarefas mais antigas e 
 * mais recentes, além do tamanho e da capacidade da lista.
 * 
 */
typedef struct TarefasConcluida TarefasConcluida;

/**
 * Estrutura que representa as tarefas ordenadas.
 * 
 * A estrutura armazena as tarefas em uma lista duplamente encadeada,
 * com ponteiros para as tarefas anterior e próxima.
 */
typedef struct TarefasOrdenadas{
    TAREFA* tarefa;                 /** Ponteiro para a tarefa armazenada. */
    struct TarefasOrdenadas* prox;  /** Ponteiro para o próximo nó da lista. */
    struct TarefasOrdenadas* ant;   /** Ponteiro para o nó anterior na lista. */
}TarefasOrdenadas;

/**
 * Encontra o meio de uma lista de tarefas ordenadas.
 * 
 * A função encontra o meio da lista de tarefas ordenadas, retornando o nó 
 * central. Essa função é usada na Busca Binária.
 * 
 * Parâmetros:
 *      Ponteiro para o início da lista.
 *      Ponteiro para o fim da lista.
 * Return:
 *      Ponteiro para o nó do meio da lista.
 */
TarefasOrdenadas* meio(TarefasOrdenadas* inicio, TarefasOrdenadas* fim);

/**
 * Realiza uma busca binária em uma lista de tarefas ordenadas.
 * 
 * A função realiza a busca de uma tarefa com base no ID fornecido.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas ordenadas.
 *      ID da tarefa a ser buscada.
 * Return:
 *      0 se tarefa encontrada ou -1 se não encontrada.
 */
int buscaBinaria(TarefasOrdenadas* ordenadas, int idBusca);

/**
 * Concatena três listas de tarefas ordenadas.
 * 
 * A função concatena uma lista menor, uma lista pivô e uma lista maior.
 * Essa função é usada na ordenação por QuickSort.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas menores.
 *      Ponteiro para a lista de tarefas pivô.
 *      Ponteiro para a lista de tarefas maiores.
 * Return:
 *      O resultado da concatenação.
 */
TarefasOrdenadas* concatenar(TarefasOrdenadas* menor, TarefasOrdenadas* pivo, TarefasOrdenadas* maior);

/**
 * Particiona uma lista de tarefas ordenadas em duas partes.
 * 
 * A função particiona uma lista em duas partes menores e maiores.
 * Essa função é usada na ordenação por QuickSort.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas ordenadas a ser particionada.
 *      Ponteiro para a lista de tarefas menores.
 *      Ponteiro para a lista de tarefas maiores.
 * Return:
 *      Ponteiro para o nó pivô após particionamento.
 */
TarefasOrdenadas* particionar(TarefasOrdenadas* ordenadas, TarefasOrdenadas** menor, TarefasOrdenadas** maior);

/**
 * Realiza o algoritmo de ordenação QuickSort em uma lista de tarefas.
 * 
 * A função ordena a lista de tarefas utilizando o algoritmo QuickSort.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas ordenadas.
 * Return:
 *      A função concatenar para finalizar a ordenação.
 */
TarefasOrdenadas* quickSort(TarefasOrdenadas* ordenadas);

/**
 * Mescla duas listas de tarefas ordenadas.
 * 
 * A função mescla duas listas de tarefas ordenadas em uma única lista.
 * Essa função é usada na ordenação por MergeSort.
 * 
 * Parâmetros:
 *      Ponteiro para a primeira lista de tarefas ordenadas.
 *      Ponteiro para a segunda lista de tarefas ordenadas.
 * Return:
 *      O resultado da mesclagem das listas.
 */
TarefasOrdenadas* mesclar(TarefasOrdenadas* lista1, TarefasOrdenadas* lista2);

/**
 * Divide uma lista de tarefas ordenadas em duas partes.
 * 
 * A função divide uma lista de tarefas ordenadas em duas listas menores.
 * Essa função é usada na ordenação por MergeSort.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas ordenadas.
 * Return:
 *      A segunda metade da partição da lista.
 */
TarefasOrdenadas* dividir(TarefasOrdenadas* ordenadas);

/**
 * Realiza o algoritmo de ordenação MergeSort em uma lista de tarefas.
 * 
 * A função ordena a lista de tarefas utilizando o algoritmo MergeSort.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas ordenadas.
 * Return:
 *      A função mesclar para finalizar a ordenação.
 */
TarefasOrdenadas* mergeSort(TarefasOrdenadas* ordenadas);

/**
 * Realiza a ordenação Insertion Sort em uma lista de tarefas.
 * 
 * A função ordena a lista de tarefas utilizando o algoritmo Insertion Sort.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de todas as tarefas ordenadas.
 */
void insertionSort(TarefasOrdenadas** todasTarefasOrdenadas);

/**
 * Transfere todas as tarefas de uma lista de DataTarefa para uma lista de 
 * TarefasOrdenadas.
 * 
 * A função transfere todas as tarefas de uma lista de DataTarefa para a lista 
 * de TarefasOrdenadas.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas.
 */
void transferirTodasTarefas(DataTarefa* lista, TarefasOrdenadas** todasTarefasOrdenadas);

/**
 * Realiza a ordenação Bubble Sort em uma lista de tarefas.
 * 
 * A função ordena a lista de tarefas utilizando o algoritmo Bubble Sort.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas ordenadas.
 */
void bubblesort(TarefasOrdenadas* ordenadas);

/**
 * Cria e transfere uma tarefa para a lista de tarefas ordenadas.
 * 
 * A função cria uma nova tarefa e a transfere para a lista de tarefas ordenadas.
 * 
 * Parâmetros:
 *      ID da tarefa.
 *      Descrição da tarefa.
 *      Prioridade da tarefa.
 *      Status da tarefa.
 * Return:
 *      Ponteiro para a nova tarefa criada.
 */
TarefasOrdenadas* transferirTarefas(int tarefaID, char* descricao, int prioridade, char* status);

/**
 * Insere tarefas ordenadas a partir de uma lista de DataTarefa.
 * 
 * A função insere tarefas na lista de tarefas ordenadas, a partir da 
 * lista de DataTarefa.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas com as datas.
 *      Ponteiro para a lista de tarefas ordenadas.
 */
void inserirTarefasOrdenadas(DataTarefa* listaData, TarefasOrdenadas** ordenadas);

/**
 * Imprime as tarefas ordenadas.
 * 
 * Exibe as informações sobre as tarefas ordenadas na lista.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas ordenadas a ser impressa.
 */
void imprimirTarefasOrdenadas(TarefasOrdenadas* ordenadas);

/**
 * Libera a memória alocada para a lista de tarefas ordenadas.
 * 
 * Libera todos os recursos de memória alocados para a lista de tarefas ordenadas.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas ordenadas que será liberada.
 */
void liberarTarefasOrdenadas(TarefasOrdenadas* ordenadas);

#endif 