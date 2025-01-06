#ifndef FILA_H
#define FILA_H

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
 * Estrutura que representa uma fila de tarefas do dia.
 * 
 * Esta estrutura mantém o início e o fim de uma fila de tarefas.
 */
typedef struct TarefasDoDia{
    TAREFA* inicio; /** Ponteiro para o início da fila de tarefas. */
    TAREFA* fim;    /** Ponteiro para o final da fila de tarefas. */ 
}TarefasDoDia;

/**
 * Conta o número de tarefas na fila.
 * 
 * Esta função retorna a quantidade de tarefas presentes na fila de tarefas do dia.
 *
 * Parâmetros: 
 *      Ponteiro para a fila de tarefas.
 * Return: 
 *      O número de tarefas na fila.
 */
int contarTarefasNaFila(TarefasDoDia* fila);

/**
 * Cria uma nova fila de tarefas do dia.
 * 
 * Esta função aloca memória para uma nova fila de tarefas e inicializa seus ponteiros.
 * 
 * Return: 
 *      Ponteiro para a fila de tarefas recém-criada.
 */
TarefasDoDia* criarFila(void);

/**
 * Insere uma nova tarefa na fila.
 * 
 * Esta função adiciona uma tarefa à fila, com base nos parâmetros fornecidos.
 * 
 * Parâmetros: 
 *      Ponteiro para a fila de tarefas.
 *      Descrição da tarefa a ser inserida.
 *      Prioridade da tarefa (valor inteiro).
 *      Status atual da tarefa.
 *      Identificador único para a tarefa.
 */
void inserirTarefasNaFila(TarefasDoDia* fila, char* decricao, int prioridade, char* status, int id);

/**
 * Imprime todas as tarefas do dia.
 * 
 * Esta função imprime as informações de todas as tarefas presentes na fila.
 * 
 * Parâmetros: 
 *      Ponteiro para a fila de tarefas.
 */
void imprimirTarefasDoDia(TarefasDoDia* fila);

/**
 * Libera a memória alocada para a fila de tarefas.
 * 
 * Esta função libera a memória associada à fila de tarefas do dia, 
 * incluindo todas as tarefas nela armazenadas.
 * 
 * Parâmetros:
 *      Ponteiro para a fila de tarefas.
 */
void liberarTarefasDoDia(TarefasDoDia* fila);

#endif 