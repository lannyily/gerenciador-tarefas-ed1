#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/listaEncadeada.h"
#include "listaEncadeada.c"
#include "../include/listaCircular.h"
#include "../include/listaDuplamente.h"
#include "listaDuplamente.c"
#include "../include/pilha.h"
#include "pilha.c"
#include "../include/fila.h"
#include "fila.c"

int main() {
    DataTarefa* lista = NULL;
    TarefasConcluidas* historico = criarTC(10);
    TarefasOrdenadas* listaOrdenada = NULL;
    Alteracao pilha = {NULL};
    TarefasDoDia fila = {NULL, NULL};
    int op;

    do {
        printf("-------------------- MENU --------------------\n");
        printf(" 1 - Adicionar tarefa\n");
        printf(" 2 - Imprimir todas as tarefas\n");
        printf(" 3 - Remover tarefa\n");
        printf(" 4 - Concluir uma tarefa\n");
        printf(" 5 - Historico de tarefas concluidas\n");
        printf(" 6 - Imprimir tarefas ordenadas\n");
        printf(" 7 - Editar tarefa\n");
        printf(" 8 - Desfazer a ultima operacao\n");
        printf(" 9 - Tarefas do dia\n");
        printf("10 - Pesquisar tarefa\n");
        printf(" 0 - SAIR\n");
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

                inserirTarefaData(&lista, data, descricao, prioridade, "PENDENTE");
                
                break;
            }
            case 2:
                printf("------------------ TAREFAS ------------------\n");
                
                imprimirTarefasPorData(lista);
                break;
            case 3: {
                inserirTarefaData(&lista, "21-02-2025", "Estudar C", 1, "PENDENTE");
                inserirTarefaData(&lista, "21-02-2025", "Revisar Notas", 2, "PENDENTE");
                inserirTarefaData(&lista, "22-02-2025", "Comprar Material", 3, "PENDENTE");
                inserirTarefaData(&lista, "22-02-2025", "Planejar Viagem", 1, "PENDENTE");
                
                imprimirTarefasPorData(lista);

                int idBusca;
                char voltar3[10];
                printf("Informe o id da tarefa que deseja remover: ");
                scanf("%d", &idBusca);

                lista = removerTarefaData(lista, &pilha, idBusca);

                while (1){
                    printf("Deseja desfazer essa operacao? [S/N]: ");
                    scanf("%s", voltar3);

                    if(voltar3[0] == 'S' || voltar3[0] == 's') {
                        desfazerAlteracao(lista, &pilha);
                        break; 
                    } else if (voltar3[0] == 'N' || voltar3[0] == 'n'){
                        break; 
                    } else {
                        printf("Entrada invalida! Tente novamente!\n");
                    }
                }
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
            case 7: { 
                inserirTarefaData(&lista, "21-02-2025", "Estudar C", 1, "PENDENTE");
                inserirTarefaData(&lista, "21-02-2025", "Revisar Notas", 2, "PENDENTE");
                inserirTarefaData(&lista, "22-02-2025", "Comprar Material", 3, "PENDENTE");
                inserirTarefaData(&lista, "22-02-2025", "Planejar Viagem", 1, "PENDENTE");
                int idEditar;
                char voltar7[10];

                imprimirTarefasPorData(lista);
                printf("Informe o ID da tarefa a ser editada: ");
                scanf("%d", &idEditar);

                buscarTarefa(lista, &pilha, idEditar);

                while(1){
                    printf("Deseja desfazer essa operacao? [S/N]: ");
                    scanf("%s", voltar7);

                    if (voltar7[0] == 'S' || voltar7[0] == 's'){
                        desfazerAlteracao(lista, &pilha);
                        break;
                    } else if (voltar7[0] == 'N' || voltar7[0] == 'n'){
                        break;
                    } else {
                        printf("Entrada invalida! Tente novamente!\n");
                    }
                }
                break;
            }
            case 8:
                desfazerAlteracao(lista, &pilha);
                break;
            case 9: { 
                char opcao[10];
                int concluirID;

                inserirTarefaData(&lista, "21-02-2025", "Estudar C", 1, "PENDENTE");
                inserirTarefaData(&lista, "21-02-2025", "Revisar Notas", 2, "PENDENTE");
                inserirTarefaData(&lista, "22-02-2025", "Comprar Material", 3, "PENDENTE");
                inserirTarefaData(&lista, "30-12-2024", "Planejar Viagem", 1, "PENDENTE");
                inserirTarefaData(&lista, "30-12-2024", "Estudar C", 1, "PENDENTE");
                inserirTarefaData(&lista, "30-12-2024", "Revisar Notas", 2, "PENDENTE");
                inserirTarefaData(&lista, "30-12-2024", "Comprar Material", 3, "PENDENTE");
                inserirTarefaData(&lista, "30-12-2024", "Planejar Viagem", 1, "PENDENTE");
                carregartarefasDoDia(lista, &fila);
                imprimirTarefasDoDia(&fila);

                while(1) {
                    printf("Deseja concluir alguma tarefa? [S/N]: ");
                    scanf("%s", opcao);

                    if(opcao[0] == 'S' || opcao[0] == 's'){
                        printf("Digite o ID da tarefa: ");
                        scanf("%d", &concluirID);
                        concluirTarefa(&lista, historico, concluirID);
                        break;
                    } else if (opcao[0] == 'N' || opcao[0] == 'n') {
                        break;
                    } else{
                        printf("Entrada invalida! Tente novamente!\n");
                    }
                }
                break;
            }
            case 10: { 
                char buscarTarefa[300];
                printf("Digite a tarefa: ");
                scanf(" %[^\n]", buscarTarefa);

                buscarTarefaNome(lista, buscarTarefa);
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                liberarTarefaData(lista);
                liberarTC(historico);
                liberarTarefasOrdenadas(listaOrdenada);
                liberarAlteracao(&pilha);
                liberarTarefasDoDia(&fila);
                exit(0); 
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
        }
    } while (op != 0);

    return 0;
}