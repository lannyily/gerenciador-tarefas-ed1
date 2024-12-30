#ifndef PILHA_H
#define PILHA_H
#include "listaEncadeada.h"

typedef struct TAREFA TAREFA;
typedef struct DataTarefa DataTarefa;
typedef struct TarefasConcluida TarefasConcluida;
typedef struct TarefasOrdenada TarefasOrdenada;

typedef struct Alteracao{
    TAREFA* primeiro;
}Alteracao;

void pilhaPush(Alteracao* pilha, TAREFA* tarefaOriginal);
TAREFA* pilhaPop(Alteracao* pilha);
DataTarefa* desfazerAlteracao(DataTarefa* listaData, Alteracao* pilha);
TAREFA* desfazerAlteracaoEditar(Alteracao* pilha, DataTarefa* listaData);
void liberarAlteracao(Alteracao* pilha);

#endif