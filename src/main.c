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

                    if (verificarData(data)){
                        break;
                    } else{
                        printf("Entrada invalida! Tente novamente!\n");
                    }
                }

                while (1) {
                    printf("A Tarefa: ");
                    scanf(" %[^\n]", descricao); 

                    if (strlen(descricao) > 300) {
                        printf("A descricao não pode ter mais de 300 caracteres! Tente novamente!\n");
                    } else {
                        break;  
                    }
                }

                while (1)
                {
                    printf("Nivel de prioridade (1 - Alta | 2 - Media | 3 - Baixa): ");
                    scanf("%d", &prioridade);

                    if (prioridade < 1 || prioridade > 3) {
                        printf("Nivel de prioridade invalido! Tente novamente!\n");
                    } else {
                        break;
                    }
                }

                inserirTarefaData(&lista, data, descricao, prioridade, "PENDENTE");

                inserirTarefaData(&lista, "05-01-2025", "Planejar Roteiro de Viagem para o Fim de Ano", 1, "PENDENTE");
                inserirTarefaData(&lista, "05-01-2025", "Estudar Conceitos Avancados de C", 2, "PENDENTE");
                inserirTarefaData(&lista, "06-01-2025", "Estudar Programacao em C", 1, "PENDENTE");
                inserirTarefaData(&lista, "06-01-2025", "Revisar Notas das Aulas da Semana", 1, "PENDENTE");
                inserirTarefaData(&lista, "06-01-2025", "Comprar Material Escolar e de Escritorio", 3, "PENDENTE");
                inserirTarefaData(&lista, "07-01-2025", "Planejar Cronograma de Estudos", 2, "PENDENTE");
                inserirTarefaData(&lista, "07-01-2025", "Estudar Haskell para Desenvolvimento Funcional", 3, "PENDENTE");
                inserirTarefaData(&lista, "08-01-2025", "Organizar Agenda do Trabalho", 1, "PENDENTE");
                inserirTarefaData(&lista, "08-01-2025", "Comprar Material para o Escritorio", 2, "PENDENTE");
                inserirTarefaData(&lista, "09-01-2025", "Planejar Objetivos do Primeiro Trimestre", 1, "PENDENTE");
                inserirTarefaData(&lista, "09-01-2025", "Revisar Notas e Atualizar Arquivos", 2, "PENDENTE");
                inserirTarefaData(&lista, "10-01-2025", "Estudar Fundamentos de Haskell", 1, "PENDENTE");
                inserirTarefaData(&lista, "10-01-2025", "Organizar Agenda Pessoal e Profissional", 1, "PENDENTE");
                inserirTarefaData(&lista, "10-01-2025", "Estudar Programacao Orientada a Objetos", 1, "PENDENTE");
                inserirTarefaData(&lista, "10-01-2025", "Planejar Cronograma de Estudos Semanais", 2, "PENDENTE");
                inserirTarefaData(&lista, "10-01-2025", "Revisar Topicos para a Reuniao Semanal", 1, "PENDENTE");
                inserirTarefaData(&lista, "10-01-2025", "Estudar Haskell para Analise de Dados", 3, "PENDENTE");
                inserirTarefaData(&lista, "11-01-2025", "Estudar Programacao Orientada a Objetos", 1, "PENDENTE");
                inserirTarefaData(&lista, "11-01-2025", "Planejar Cronograma de Estudos Semanais", 2, "PENDENTE");
                inserirTarefaData(&lista, "12-01-2025", "Revisar Topicos para a Reuniao Semanal", 1, "PENDENTE");
                inserirTarefaData(&lista, "12-01-2025", "Estudar Haskell para Analise de Dados", 3, "PENDENTE");
                inserirTarefaData(&lista, "13-01-2025", "Planejar Orcamento Familiar do Mes", 1, "PENDENTE");
                inserirTarefaData(&lista, "13-01-2025", "Revisar Documentos Importantes", 2, "PENDENTE");
                inserirTarefaData(&lista, "14-01-2025", "Comprar Material Escolar e de Escritorio", 3, "PENDENTE");
                inserirTarefaData(&lista, "03-01-2025", "Estudar Haskell para Fundamentos Avancados", 1, "PENDENTE");
                inserirTarefaData(&lista, "03-01-2025", "Planejar Objetivos de Longo Prazo", 1, "PENDENTE");
                inserirTarefaData(&lista, "04-01-2025", "Estudar Logica para Programacao em C", 2, "PENDENTE");
                inserirTarefaData(&lista, "04-01-2025", "Revisar Notas e Atualizar Projetos", 1, "PENDENTE");
                inserirTarefaData(&lista, "04-01-2025", "Comprar Livros para Estudos Avancados", 3, "PENDENTE");

                inserirTarefaData(&lista, "01-02-2025", "Estudar Logica para Programacao em C", 1, "PENDENTE");
                inserirTarefaData(&lista, "01-02-2025", "Planejar Cronograma de Viagem de Carnaval", 3, "PENDENTE");
                inserirTarefaData(&lista, "02-02-2025", "Comprar Itens para Organizacao da Casa", 2, "PENDENTE");
                inserirTarefaData(&lista, "02-02-2025", "Organizar Atividades do Mes de Fevereiro", 1, "PENDENTE");
                inserirTarefaData(&lista, "03-02-2025", "Estudar Haskell para Analise de Dados", 3, "PENDENTE");
                inserirTarefaData(&lista, "03-02-2025", "Revisar Palestra para Apresentacao", 2, "PENDENTE");
                inserirTarefaData(&lista, "04-02-2025", "Planejar Prazos de Entregas no Trabalho", 1, "PENDENTE");
                inserirTarefaData(&lista, "04-02-2025", "Comprar Livros para Estudos Avancados", 3, "PENDENTE");
                inserirTarefaData(&lista, "05-02-2025", "Estudar Algoritmos Recursivos em C", 2, "PENDENTE");
                inserirTarefaData(&lista, "05-02-2025", "Organizar Documentos Pessoais", 1, "PENDENTE");
                inserirTarefaData(&lista, "06-02-2025", "Planejar Investimentos a Curto Prazo", 3, "PENDENTE");
                inserirTarefaData(&lista, "06-02-2025", "Revisar Codigo de Projetos Anteriores", 2, "PENDENTE");
                inserirTarefaData(&lista, "07-02-2025", "Estudar Novas Funcionalidades de Haskell", 1, "PENDENTE");
                inserirTarefaData(&lista, "07-02-2025", "Planejar Roteiro de Atividades Familiares", 3, "PENDENTE");
                inserirTarefaData(&lista, "08-02-2025", "Organizar Checklist para Proxima Semana", 2, "PENDENTE");
                inserirTarefaData(&lista, "08-02-2025", "Planejar Jornada de Estudos Intensiva", 1, "PENDENTE");

                inserirTarefaData(&lista, "01-03-2025", "Planejar Projeto de Desenvolvimento Pessoal", 1, "PENDENTE");
                inserirTarefaData(&lista, "01-03-2025", "Estudar Estruturas Condicionais em C", 3, "PENDENTE");
                inserirTarefaData(&lista, "02-03-2025", "Revisar Leituras de Livros Tecnicos", 2, "PENDENTE");
                inserirTarefaData(&lista, "02-03-2025", "Planejar Financas para o Mes", 1, "PENDENTE");
                inserirTarefaData(&lista, "03-03-2025", "Comprar Material para Estudos Remotos", 3, "PENDENTE");
                inserirTarefaData(&lista, "03-03-2025", "Organizar Tarefas de Casa e Trabalho", 2, "PENDENTE");
                inserirTarefaData(&lista, "04-03-2025", "Estudar Haskell para Resolucao de Problemas", 1, "PENDENTE");
                inserirTarefaData(&lista, "04-03-2025", "Planejar Viagem de Descanso com Familia", 3, "PENDENTE");
                inserirTarefaData(&lista, "05-03-2025", "Estudar Funcoes Lambda em C", 2, "PENDENTE");
                inserirTarefaData(&lista, "05-03-2025", "Revisar Progresso das Metas do Ano", 1, "PENDENTE");
                inserirTarefaData(&lista, "06-03-2025", "Planejar Investimentos a Curto Prazo", 1, "PENDENTE");
                inserirTarefaData(&lista, "06-03-2025", "Comprar Suprimentos para o Escritorio", 2, "PENDENTE");

                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                carregartarefasDoDia(lista, &fila);
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
                
                printf("Informe o id da tarefa que deseja remover: ");
                scanf("%d", &idBusca);

                lista = removerTarefaData(lista, &pilha, idBusca);

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
            case 5: { 
                imprimirTC(historico);
                break;
            }
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

                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                imprimirTarefasPorData(lista);
                printf("Informe o ID da tarefa a ser editada: ");
                scanf("%d", &idEditar);

                buscarTarefa(lista, &pilha, idEditar);

                break;
            }
            case 8:
                desfazerAlteracao(lista, &pilha);
                break;
            case 9: { 
                if (contarTarefasNaFila(&fila) > 0){ 
                    imprimirTarefasDoDia(&fila);
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