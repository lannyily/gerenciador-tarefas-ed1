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
    DataTarefa* listaPendentesVencidas = NULL;
    TarefasConcluidas* historico = criarTC(10);
    TarefasOrdenadas* todasTarefasOrdenadas = NULL;
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
        printf(" 6 - Opcoes de ordencao de todas as tarefas\n");
        printf(" 7 - Editar tarefa\n");
        printf(" 8 - Desfazer a ultima operacao\n");
        printf(" 9 - Tarefas do dia\n");
        printf("10 - Pesquisar tarefa (String)\n");
        printf("11 - Pesquisar tarefa (Busca binaria)\n");
        printf("12 - Imprimir tarefas pendentes vencidas\n");
        printf("13 - Transferir tarefa pra outra data\n");
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

                while(1){
                    printf("Informe a data (no formato dd-mm-yyyy): ");
                    scanf("%10s", data);

                    if (!verificarData(data)){
                        break;
                    } else{
                        printf("Entrada invalida! Tente novamente!\n");
                    }
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

                inserirTarefaData(&lista, "01-11-2025", "Estudar C", 1, "PENDENTE");
                inserirTarefaData(&lista, "01-10-2025", "Estudar C", 1, "PENDENTE");
                inserirTarefaData(&lista, "21-02-2025", "Revisar Notas", 2, "PENDENTE");
                inserirTarefaData(&lista, "22-02-2025", "Comprar Material", 3, "PENDENTE");
                inserirTarefaData(&lista, "03-02-2025", "Comprar Material", 3, "PENDENTE");
                inserirTarefaData(&lista, "03-01-2025", "Planejar Viagem", 1, "PENDENTE");
                inserirTarefaData(&lista, "28-01-2025", "Planejar Viagem", 1, "PENDENTE");

                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                break;
            }
            case 2:
                printf("------------------ TAREFAS ------------------\n");
                
                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                imprimirTarefasPorData(lista);
                break;
            case 3: {
                moverTarefasVencidas(&lista, &listaPendentesVencidas);
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
            case 6: { 
                int opcao6;

                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                transferirTodasTarefas(lista, &todasTarefasOrdenadas);
                
                do{
                    printf("------------- TIPOS DE ORDENACAO -------------\n");
                    printf("1 - Ordenar por ID\n");
                    printf("2 - Ordenar por prioridade crescente\n");
                    printf("3 - Ordenar por prioridade decrescente\n");
                    printf("0 - Voltar\n");
                    printf("----------------------------------------------\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcao6);
                    printf("\n");

                    switch (opcao6){
                        case 1:
                            insertionSort(&todasTarefasOrdenadas);
                            imprimirTarefasOrdenadas(todasTarefasOrdenadas);
                            break;
                        case 2:
                            mergeSort(todasTarefasOrdenadas);
                            imprimirTarefasOrdenadas(todasTarefasOrdenadas);
                            break;
                        case 3:
                            todasTarefasOrdenadas = quickSort(todasTarefasOrdenadas);
                            imprimirTarefasOrdenadas(todasTarefasOrdenadas);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida, tente novamente!\n");
                    }
                } while (opcao6 != 0);
                
                break;
            }
            case 7: { 
                int idEditar;
                char voltar7[10];

                moverTarefasVencidas(&lista, &listaPendentesVencidas);
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
                
                carregartarefasDoDia(lista, &fila);

                if (contarTarefasNaFila(&fila) > 0){ 
                    imprimirTarefasDoDia(&fila);

                    while (1) {
                        printf("Deseja concluir alguma tarefa? [S/N]: ");
                        scanf("%s", opcao);

                        if (opcao[0] == 'S' || opcao[0] == 's') {
                            printf("Digite o ID da tarefa: ");
                            scanf("%d", &concluirID);
                            concluirTarefa(&lista, historico, concluirID);
                            break;
                        } else if (opcao[0] == 'N' || opcao[0] == 'n') {
                            break;
                        } else {
                            printf("Entrada inválida! Tente novamente!\n");
                        }
                    }
                } else {
                    printf("Nenhuma tarefa para hoje!\n");
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
            case 11: {
                int chave;

                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                transferirTodasTarefas(lista, &todasTarefasOrdenadas);
                insertionSort(&todasTarefasOrdenadas);
                imprimirTarefasOrdenadas(todasTarefasOrdenadas);
                
                printf("Digite o ID que deseja buscar: ");
                scanf("%d", &chave);

                if (buscaBinaria(todasTarefasOrdenadas, chave)){
                    printf("Tarefa encontrada!\n");
                } else {
                    printf("Tarefa nao encontrada!\n");
                }

                break;
            }
            case 12:
                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                imprimirTarefasVencidas(listaPendentesVencidas);
                break;
            case 13: {
                int idTarefa;
                char novaData[20];

                printf("Digite o ID da tarefa que deseja transferir: ");
                scanf("%d", &idTarefa);

                printf("Digite a nova data (dd-mm-aaaa): ");
                scanf("%s", novaData);

                transferirTarefaParaOutraData(&lista, idTarefa, novaData);
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                liberarTarefaData(lista);
                liberarTC(historico);
                liberarTarefasOrdenadas(todasTarefasOrdenadas);
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