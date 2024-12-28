#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/listaEncadeada.h"
#include "listaEncadeada.c"
#include "../include/listaCircular.h"
#include "../include/listaDuplamente.h"
#include "listaDuplamente.c"
// #include "../include/fila.h"
// #include "../include/pilha.h"

int main() {
    DataTarefa* lista = NULL;
    TarefasConcluidas* historico = criarTC(10);
    TarefasOrdenadas* listaOrdenada = NULL;
    int op;

    do {
        printf("-------------------- MENU --------------------\n");
        printf("1 - Adicionar tarefa\n");
        printf("2 - Imprimir tarefas\n");
        printf("3 - Remover tarefa\n");
        printf("4 - Concluir uma tarefa\n");
        printf("5 - Historico de tarefas concluidas\n");
        printf("6 - Imprimir tarefas ordenadas\n");
        printf("0 - SAIR\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);
        printf("\n");

        switch (op) {
            case 1: {
                char data[20];
                char descricao[300];
                int prioridade;

                printf("Informe a data (no formato dd-mm-yyyy): ");
                scanf("%10s", data);

                if (!verificarData(data)) {
                    printf("Erro: Data invalida ou em formato incorreto.\n");
                    return 1;
                }

                printf("A Tarefa: ");
                scanf(" %[^\n]", descricao);  // Permite leitura de strings com espaços

                printf("Nivel de prioridade (1 - Alta | 2 - Media | 3 - Baixa): ");
                scanf("%d", &prioridade);

                if (prioridade < 1 || prioridade > 3) {
                    printf("Erro: Nivel de prioridade invalido.\n");
                    return 1;
                }

                inserirTarefaData(&lista, data, descricao, prioridade, 1);

                inserirTarefaData(&lista, "21-02-2025", "Estudar C", 1, 1);
                inserirTarefaData(&lista, "21-02-2025", "Revisar Notas", 2, 1);
                inserirTarefaData(&lista, "22-02-2025", "Comprar Material", 3, 1);
                inserirTarefaData(&lista, "22-02-2025", "Planejar Viagem", 1, 1);
                
                break;
            }
            case 2:
                printf("------------------ TAREFAS ------------------\n");
                
                imprimirTarefasPorData(lista);
                break;
            case 3: {
                imprimirTarefasPorData(lista);

                int idBusca;
                printf("Informe o id da tarefa que deseja remover: ");
                scanf("%d", &idBusca);

                lista = removerTarefaData(lista, idBusca);

                break;
            }
            case 4: { 
                int idConcluida;

                imprimirTarefasPorData(lista);
                printf("Informe o ID da tarefa: ");
                scanf("%d", &idConcluida);
                concluirTarefa(&lista, historico, idConcluida);;
                break;
            }
            case 5:
                imprimirTC(historico);
                break;
            case 6:
                ordenarTarefasDeDataNaListaDupla(lista, &listaOrdenada);
                imprimirTarefasOrdenadas(listaOrdenada);
                break;
            case 0:
                printf("Saindo do programa...\n");
                liberarTarefaData(lista);
                liberarTC(historico);
                liberarTarefasOrdenadas(listaOrdenada);
                exit(0); 
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
        }
    } while (op != 0);

    return 0;
}