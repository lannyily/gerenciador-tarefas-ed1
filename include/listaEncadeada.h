#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

typedef struct TarefasConcluidas TarefasConcluidas;

typedef struct TAREFA{
    int id;
    char descricao[300];
    int prioridede; // 1 - Alta, 2 - Média e 3 - Baixa
    int status; // 1 - Não Concluida e 0 - Concluida
    struct TAREFA* prox;
}TAREFA;

typedef struct DataTarefa{
    char data[20];
    int cont;
    TAREFA* tarefas;
    struct DataTarefa* prox;
}DataTarefa;

int calcularId(char* data, int cont);
TAREFA* criarTarefa(char* decricao, int prioridade, int status, int id);
DataTarefa* criarDataTarefa(char* data);
void inserirTarefa(TAREFA** lista, int id, int status, char* descricao, int prioridade);
void inserirTarefaData(DataTarefa** listaData, char* data, char* descricao, int prioridade, int status);
TAREFA* removerTarefa(TAREFA* lista, int idBusca);
DataTarefa* removerTarefaData(DataTarefa* listaData, int idBusca);
void concluirTarefa(DataTarefa** listaData, TarefasConcluidas* concluidas, int id);
void imprimirTarefasPorData(DataTarefa* lista);
void liberarTarefas(TAREFA* lista);
void liberarTarefaData(DataTarefa* lista);
int verificarData(char* data);

#endif