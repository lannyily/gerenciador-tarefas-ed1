#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H
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
 * A estrutura armazena a tarefa mais antiga, a mais recente, 
 * o tamanho e a capacidade da lista de tarefas concluídas.
 */
typedef struct TarefasConcluidas {
    TAREFA* tarefaMaisAntiga;   /** Ponteiro para a tarefa mais antiga na lista de tarefas concluídas. */
    TAREFA* tarefaMaisRecente;  /** Ponteiro para a tarefa mais recente na lista de tarefas concluídas. */
    int tamanho;                /** Quantidade de tarefas atualmente armazenadas. */
    int capacidade;             /** Capacidade máxima da lista de tarefas concluídas. */
}TarefasConcluidas;

/**
 * Cria uma nova lista de tarefas concluídas.
 * 
 * Inicializa a estrutura `TarefasConcluidas` com a capacidade fornecida e define
 * os ponteiros de tarefas como `NULL`.
 * 
 * Parâmetros: 
 *      A capacidade máxima da lista de tarefas concluídas.
 * Return:
 *      Ponteiro para a estrutura `TarefasConcluidas` criada.
 */
TarefasConcluidas* criarTC(int capacidade);

/**
 * Adiciona uma tarefa à lista de tarefas concluídas.
 * 
 * Insere uma tarefa na lista de tarefas concluídas, ajustando os ponteiros da lista
 * conforme necessário para manter a ordem de inserção.
 * 
 * Parâmetros:
 *      Ponteiro para a estrutura de tarefas concluídas.
 * Return:
 *      Ponteiro para a tarefa a ser adicionada à lista de tarefas concluídas.
 */
void addTarefaConcluida(TarefasConcluidas* concluidas, TAREFA* lista);

/**
 * Imprime as tarefas concluídas na lista.
 * 
 * Exibe as informações sobre as tarefas armazenadas na lista de tarefas concluídas.
 * 
 * Parâmetros:
 *      Ponteiro para a estrutura de tarefas concluídas a ser impressa.
 */
void imprimirTC(TarefasConcluidas* concluidas);

/**
 * Libera a memória alocada para a lista de tarefas concluídas.
 * 
 * Libera todos os recursos de memória alocados para a estrutura `TarefasConcluidas`,
 * incluindo as tarefas armazenadas nela.
 * 
 * Parâmetros:
 *      Ponteiro para a estrutura de tarefas concluídas que será liberada.
 */
void liberarTC(TarefasConcluidas* concluidas);

#endif 