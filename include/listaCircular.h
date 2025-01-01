#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H
#include "listaEncadeada.h" 

typedef struct TAREFA TAREFA;
typedef struct DataTarefa DataTarefa;
typedef struct TarefasOrdenadas TarefasOrdenadas;

typedef struct TarefasConcluidas {
    TAREFA* tarefaMaisAntiga;
    TAREFA* tarefaMaisRecente;
    int tamanho;
    int capacidade;
}TarefasConcluidas;

TarefasConcluidas* criarTC(int capacidade);
void addTarefaConcluida(TarefasConcluidas* concluidas, TAREFA* lista);
void imprimirTC(TarefasConcluidas* concluidas);
void liberarTC(TarefasConcluidas* concluidas);

#endif 