#ifndef PILHA_H
#define PILHA_H
#include "listaEncadeada.h"

/**
 * Estrutura que representa uma tarefa.
 * 
 * Detalhes internos da tarefa, como descrição, prioridade, 
 * status e id são armazenados aqui. Esta estrutura não está
 * completamente definida neste arquivo.
 */
typedef struct TAREFA TAREFA;

/**
 * Estrutura que representa a data de uma tarefa.
 * 
 * Detalhes internos sobre a data da tarefa, como ano, mês, 
 * dia, etc. são armazenados aqui. Esta estrutura não está
 * completamente definida neste arquivo. 
 */
typedef struct DataTarefa DataTarefa;

/**
 * Estrutura que representa as tarefas concluídas.
 * 
 * A estrutura mantém o controle das tarefas mais antigas e 
 * mais recentes, além do tamanho e da capacidade da lista.
 * Esta estrutura não está completamente definida neste 
 * arquivo.
 */
typedef struct TarefasConcluida TarefasConcluida;

/**
 * Estrutura que representa as tarefas ordenadas.
 * 
 * A estrutura mantém o controle das tarefas ordenadas em 
 * uma lista duplamente encadeada. Esta estrutura não está
 * completamente definida neste arquivo.
 */
typedef struct TarefasOrdenadas TarefasOrdenadas;

/**
 * Estrutura que representa uma pilha de alterações.
 * 
 * A estrutura pilha armazena as tarefas de forma que a última tarefa
 * inserida é a primeira a ser removida.
 */
typedef struct Alteracao{
    TAREFA* primeiro;   /** Ponteiro para o primeiro elemento da pilha. */
}Alteracao;

/**
 * Empilha uma tarefa na pilha de alterações.
 * 
 * A função adiciona uma tarefa no topo da pilha.
 * 
 * Parâmetros: 
 *      Ponteiro para a pilha onde a tarefa será empilhada.
 *      Ponteiro para a tarefa a ser empilhada.
 */
void pilhaPush(Alteracao* pilha, TAREFA* tarefaOriginal);

/**
 * Desempilha uma tarefa da pilha de alterações.
 * 
 * A função remove e retorna a tarefa do topo da pilha.
 * 
 * Parâmetros:
 *      Ponteiro para a pilha de onde a tarefa será removida.
 * Return:
 *      Ponteiro para a tarefa removida da pilha.
 */
TAREFA* pilhaPop(Alteracao* pilha);

/**
 * Converte um ID de tarefa para uma data associada.
 * 
 * A função converte o ID de uma tarefa para uma data no formato de string.
 * Vai ser usado na função desfazer alteração para localizar a data da 
 * tarefa.
 * 
 * Parâmetros:
 *      ID da tarefa que será convertido.
 *      Ponteiro para o buffer onde a data será armazenada.
 */
void idParaData(int id, char* data);

/**
 * Desfaz a última alteração realizada na lista de tarefas.
 * 
 * A função desfaz a última alteração feita em uma tarefa, restaurando o estado anterior.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas, onde a alteração será desfeita.
 *      Ponteiro para a pilha contendo as alterações a serem desfeitas.
 * Return:
 *      Ponteiro para a lista de tarefas atualizada após desfazer a alteração.
 */
DataTarefa* desfazerAlteracao(DataTarefa* listaData, Alteracao* pilha);

/**
 * Libera a memória da pilha de alterações.
 * 
 * A função libera todos os recursos de memória alocados para a pilha de alterações.
 * 
 * Parâmetros:
 *      Ponteiro para a pilha que será liberada.
 */
void liberarAlteracao(Alteracao* pilha);

#endif