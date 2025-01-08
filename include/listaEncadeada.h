#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

/**
 * Estrutura que representa as tarefas concluídas.
 * 
 * A estrutura mantém o controle das tarefas mais antigas e 
 * mais recentes, além do tamanho e da capacidade da lista.
 *
 */
typedef struct TarefasConcluidas TarefasConcluidas;

/**
 * Estrutura que representa as tarefas ordenadas.
 * 
 * A estrutura mantém o controle das tarefas ordenadas em 
 * uma lista duplamente encadeada. 
 */
typedef struct TarefasOrdenadas TarefasOrdenadas;

/**
 * Estrutura que representa uma pilha de alterações.
 * 
 * A estrutura pilha armazena as tarefas de forma que a última tarefa
 * inserida é a primeira a ser removida. 
 */
typedef struct Alteracao Alteracao;

/**
 * Estrutura que representa as tarefas do dia.
 * 
 * A estrutura armazena informações sobre as tarefas do dia atual.
 * 
 */
typedef struct TarefasDoDia TarefasDoDia;

/**
 * Estrutura que representa uma tarefa.
 * 
 * A estrutura contém os detalhes da tarefa, como id, descrição, prioridade, 
 * status e o ponteiro para a próxima tarefa na lista.
 */
typedef struct TAREFA{
    int id;                 /** ID da tarefa. */
    char descricao[301];    /** Descrição da tarefa. */
    int prioridade;         /** Prioridade da tarefa (1 - Alta, 2 - Média, 3 - Baixa). */
    char status[20];        /** Status da tarefa (PENDENTE ou CONCLUIDA). */
    struct TAREFA* prox;    /** Ponteiro para a próxima tarefa. */
}TAREFA;

/**
 * Estrutura que representa a data de uma tarefa.
 * 
 * A estrutura contém a data, o contador de tarefas e o ponteiro para 
 * a lista de tarefas associadas a essa data.
 */
typedef struct DataTarefa{
    char data[20];              /** Data da tarefa no formato 'dd/mm/aaaa'. */     
    int cont;                   /** Contador de tarefas para a data. */
    TAREFA* tarefas;            /** Lista de tarefas associadas a essa data. */
    struct DataTarefa* prox;    /** Ponteiro para o próximo elemento da lista. */
}DataTarefa;

/**
 * Remove uma tarefa de uma lista de tarefas de uma data específica.
 * 
 * A função remove a tarefa com o ID especificado da lista de tarefas de uma data.
 * Essa função é usada na função de transferir uma tarefa para outra data, ela é 
 * usada remover a tarefa da data antiga, para a tarefa não ficar duplicada.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas associadas a uma data.
 *      ID da tarefa a ser removida.
 * Return:
 *      Ponteiro para a tarefa removida ou NULL se não encontrada.
 */
TAREFA* removerTarefaDeData(DataTarefa** listaData, int idTarefa);

/**
 * Adiciona uma tarefa a uma lista de tarefas de uma data específica.
 * 
 * A função insere uma tarefa na lista de tarefas associadas a uma data.
 * Essa função é usada na função de transferir uma tarefa para outra data,
 * ela pega a tarefa que foi removida na função 'removerTarefaDeData' e 
 * adiciona na nova data.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas associadas a uma data.
 *      Ponteiro para a tarefa a ser adicionada.
 *      Data para a qual a tarefa será adicionada.
 */
void adicionarTarefaEmData(DataTarefa** listaData, TAREFA* tarefa, char* novaData);

/**
 * Transfere uma tarefa de uma data para outra.
 * 
 * A função transfere a tarefa com o ID especificado de uma data para outra.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas associadas à data original.
 *      ID da tarefa a ser transferida.
 *      Nova data para a tarefa.
 */
void transferirTarefaParaOutraData(DataTarefa** listaData, int idTarefa, char* novaData);

/**
 * Imprime as tarefas vencidas.
 * 
 * A função imprime as tarefas que já passaram da data atual.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas vencidas.
 */
void imprimirTarefasVencidas(DataTarefa* listaPendentesVencidas);

/**
 * Compara duas datas no formato 'dd/mm/aaaa'.
 * 
 * A função compara duas datas, a comparação segue a hierarquia 
 * dos componentes da data: Primeiro, os anos são comparados. 
 * Se forem diferentes, a diferença entre os anos é retornada.
 * Se os anos forem iguais, os meses são comparados. Se forem 
 * diferentes, a diferença entre os meses é retornada. Se os meses 
 * também forem iguais, os dias são comparados, e a diferença 
 * entre os dias é retornada. Essa função é usada na ordenação
 * por data usando Selection Sort e na função de mover datas
 * vencidas para outra lista.
 * 
 * Parâmetros:
 *      Primeira data a ser comparada.
 *      Segunda data a ser comparada.
 * Return:
 *      Diferença entre o dia, mes ou ano, dependedo a condição.
 */
int compararDatas(char* data1, char* data2);

/**
 * Ordena a lista de tarefas de uma data usando o algoritmo Selection Sort.
 * 
 * A função organiza as tarefas de uma data em ordem crescente.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas que será ordenada.
 */
void selectionSort(DataTarefa* listaData);

/**
 * Move as tarefas vencidas para uma lista separada.
 * 
 * A função move as tarefas que já venceram para uma lista de tarefas vencidas.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas associadas a uma data.
 *      Ponteiro para a lista onde as tarefas vencidas serão movidas.
 */
void moverTarefasVencidas(DataTarefa** listaData, DataTarefa** listaPendentesVencidas);

/**
 * Compara duas strings.
 * 
 * A função compara duas strings, retornando 0 se forem iguais e um valor diferente de 
 * 0 caso contrário. Essa função é usanda na pesquisa de tarefa pelo nome.
 * 
 * Parâmetros:
 *      Nome a ser comparado.
 *      Nome para a comparação.
 * Return:
 *      0 se as strings forem iguais, valor diferente de 0 caso contrário.
 */
int comparaString(char* nomeBusca, char* nome);

/**
 * Busca uma tarefa pelo nome na lista de tarefas.
 * 
 * A função procura uma tarefa pelo nome especificado e mostra a tarefa
 * para o usuário caso ela seja encontrada.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas.
 *      Nome da tarefa a ser buscada.
 */
void buscarTarefaNome(DataTarefa* listaData, char* nomeBusca);

/**
 * Obtém a data atual no formato 'dd/mm/aaaa'.
 * 
 * A função preenche o parâmetro `dataHoje` com a data atual. Essa função
 * é usada para decobrir a data de hoje para carregar as terefas do dia.
 * 
 * Parâmetros:
 *      Ponteiro para o buffer onde a data será armazenada.
 */
void dataAtual(char* dataHoje);


/**
 * Carrega as tarefas do dia para uma fila.
 * 
 * A função transfere as tarefas do dia para a estrutura de fila `TarefasDoDia`.
 * Essa fução usa a estrutura TarefasOrdenadas para ordena-las por ordem de prioridade
 * usando o Bubble Sort.
 * 
 * Parâmetros:
 *      Lista de tarefas por data.
 *      Fila onde as tarefas serão armazenadas.
 */
void carregartarefasDoDia(DataTarefa* listaData, TarefasDoDia* fila);

/**
 * Calcula o ID de uma tarefa a partir da data e contador.
 * 
 * A função gera um ID único para cada tarefa com base na data e contador.
 * 
 * Parâmetros:
 *      Data da tarefa.
 *      Contador para a tarefa.
 * Return:
 *      ID calculado da tarefa.
 */
int calcularId(char* data, int cont);

/**
 * Cria uma nova tarefa.
 * 
 * A função cria uma tarefa com os dados fornecidos.
 * 
 * Parâmetros:
 *      Descrição da tarefa.
 *      Prioridade da tarefa.
 *      Status da tarefa.
 *      ID único da tarefa.
 * Return:
 *      Ponteiro para a nova tarefa criada.
 */
TAREFA* criarTarefa(char* decricao, int prioridade, char* status, int id);

/**
 * Cria uma nova estrutura DataTarefa.
 * 
 * A função cria uma nova data de tarefa com base na data fornecida.
 * 
 * Parâmetros:
 *      Data associada à tarefa.
 * Return:
 *      Ponteiro para a nova estrutura DataTarefa.
 */
DataTarefa* criarDataTarefa(char* data);

/**
 * Insere uma tarefa na lista de tarefas.
 * 
 * A função insere uma tarefa na lista de tarefas com os dados fornecidos.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas.
 *      ID da tarefa a ser inserida.
 *      Status da tarefa.
 *      Descrição da tarefa.
 *      Prioridade da tarefa.
 */
void inserirTarefa(TAREFA** lista, int id, char* status, char* descricao, int prioridade);

/**
 * Insere uma tarefa em uma data específica.
 * 
 * A função insere uma tarefa na lista de tarefas associada a uma data específica.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas por data.
 *      Data associada à tarefa.
 *      Descrição da tarefa.
 *      Prioridade da tarefa.
 *      Status da tarefa.
 */
void inserirTarefaData(DataTarefa** listaData, char* data, char* descricao, int prioridade, char* status);

/**
 * Remove uma tarefa da lista de tarefas.
 * 
 * A função remove uma tarefa da lista de tarefas e também lida com a pilha de alterações.
 * 
 * Parâmetros:
 *      Lista de tarefas.
 *      Pilha de alterações.
 *      ID da tarefa a ser removida.
 * Return:
 *      Ponteiro para a nova lista de tarefas.
 */
TAREFA* removerTarefa(TAREFA* lista, Alteracao* pilha, int idBusca);

/**
 * Calcula o tamanho de uma lista de tarefas.
 * 
 * A função percorre a lista de tarefas e retorna o número de elementos presentes.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas.
 * Return:
 *      O número de tarefas na lista.
 */
int listaTamanho(TAREFA* lista);

/**
 * Remove uma tarefa de uma lista de tarefas de uma data específica.
 * 
 * A função remove uma tarefa de uma data específica e também lida com a pilha de alterações.
 * 
 * Parâmetros:
 *      Lista de tarefas de uma data.
 *      Pilha de alterações.
 *      ID da tarefa a ser removida.
 * Return:
 *      Ponteiro para a nova lista de tarefas de data.
 */
DataTarefa* removerTarefaData(DataTarefa* listaData, Alteracao* pilha, int idBusca);

/**
 * Edita uma tarefa.
 * 
 * A função permite editar uma tarefa existente.
 * 
 * Parâmetros:
 *      Ponteiro para a tarefa a ser editada.
 *      Descrição antiga da tarefa.
 */
void editarTarefa(TAREFA* tarefa, char* descricaoAtual);

/**
 * Busca uma tarefa pelo ID na lista de tarefas.
 * 
 * A função procura uma tarefa com o ID especificado.
 * 
 * Parâmetros:
 *      Lista de tarefas por data.
 *      Pilha de alterações.
 *      ID da tarefa a ser buscada.
 */
void buscarTarefa(DataTarefa* listaData, Alteracao* pilha, int idbusca);

/**
 * Conclui uma tarefa.
 * 
 * A função marca o status uma tarefa como concluída.
 * 
 * Parâmetros:
 *      Lista de tarefas por data.
 *      Lista de tarefas concluídas.
 *      ID da tarefa a ser concluída.
 */
void concluirTarefa(DataTarefa** listaData, TarefasConcluidas* concluidas, int id);

/**
 * Imprime as tarefas por data.
 * 
 * A função imprime todas as tarefas de uma lista associada a uma data.
 * 
 * Parâmetros:
 *      Lista de tarefas por data.
 */
void imprimirTarefasPorData(DataTarefa* lista);

/**
 * Libera a memória de uma lista de tarefas.
 * 
 * A função libera a memória alocada para uma lista de tarefas.
 * 
 * Parâmetros:
 *      Lista de tarefas a ser liberada.
 */
void liberarTarefas(TAREFA* lista);

/**
 * Libera a memória de uma lista de tarefas por data.
 * 
 * A função libera a memória alocada para uma lista encadeada de tarefas 
 * associadas a datas.
 * 
 * Parâmetros:
 *      Ponteiro para a lista de tarefas por data que será liberada.
 */
void liberarTarefaData(DataTarefa* lista);

/**
 * Verifica a validade de uma data no formato 'dd/mm/aaaa'.
 * 
 * A função valida se a data fornecida segue o formato esperado e é uma data válida.
 * 
 * Parâmetros:
 *      Ponteiro para a string contendo a data a ser verificada.
 * Return:
 *  1 se a data for válida, 0 caso contrário.
 */
int verificarData(char* data);

#endif