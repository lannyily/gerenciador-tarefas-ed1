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
    // --- Declaração de variáveis principais do sistema ---
    DataTarefa* lista = NULL;                       // Lista encadeada para tarefas pendentes
    DataTarefa* listaPendentesVencidas = NULL;      // Lista encadeada para tarefas pendentes e vencidas
    TarefasConcluidas* historico = criarTC(10);     // Lista encadeada circular para o histórico de tarefas concluídas
    TarefasOrdenadas* todasTarefasOrdenadas = NULL; // Lista duplamente encadeada para ordenação de tarefas
    Alteracao pilha = {NULL};                       // Pilha para desfazer operações (remoção e edição)
    TarefasDoDia fila = {NULL, NULL};               // Fila para tarefas do dia de hoje
    int op;     // Opção do menu

    do {
        // --- Exibe o menu principal ---
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

        // --- Processa a escolha do usuário ---
        switch (op) {
            case 1: {
                // --- Adicionar uma nova tarefa ---
                char data[20];          // Data no formato dd-mm-aaaa
                char descricao[300];    // Descrição da tarefa
                int prioridade;         // Nível de prioridade (1- Alta, 2- Média, 3- Baixa)

                // --- Solicita a data e valida o formato --- 
                while(1){
                    printf("Informe a data (no formato dd-mm-yyyy): ");
                    scanf("%10s", data);

                    if (verificarData(data)){
                        break;
                    } else{
                        printf("Entrada invalida! Tente novamente!\n");
                    }
                }

                // --- Solicita e valida a descrição ---
                while (1) {
                    printf("A Tarefa: ");
                    scanf(" %[^\n]", descricao); 

                    if (strlen(descricao) > 300) {
                        printf("A descricao não pode ter mais de 300 caracteres! Tente novamente!\n");
                    } else {
                        break;  
                    }
                }

                 // --- Solicita e valida o nível de prioridade ---
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

                // --- Insere a nova tarefa na lista de pendentes ---
                inserirTarefaData(&lista, data, descricao, prioridade, "PENDENTE");

                // --- Exemplo de tarefas predefinidas para testes ---
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

                moverTarefasVencidas(&lista, &listaPendentesVencidas);  // Atualiza as tarefas vencidas 
                carregartarefasDoDia(lista, &fila);                     // Transfere tarefas do dia
                break;
            }
            case 2:
                 // --- Imprime todas as tarefas pendentes organizadas por data ---
                printf("------------------ TAREFAS ------------------\n");
                
                moverTarefasVencidas(&lista, &listaPendentesVencidas);  // Atualiza as tarefas vencidas 
                imprimirTarefasPorData(lista);                          // Imprime todas as tarefas pendentes 
                break;
            case 3: {
                // --- Remove uma tarefa da lista por ID ---
                moverTarefasVencidas(&lista, &listaPendentesVencidas);  // Atualiza as tarefas vencidas 
                imprimirTarefasPorData(lista);                          // Imprime todas as tarefas pendentes

                int idBusca; // ID da busca para a remoção
                
                printf("Informe o id da tarefa que deseja remover: ");
                scanf("%d", &idBusca);

                lista = removerTarefaData(lista, &pilha, idBusca);      // Remover a tarefa

                break;
            }
            case 4: { 
                // --- Marca uma tarefa como concluída ---
                int idConcluida;    // ID da busca para concluir a tarefa

                imprimirTarefasPorData(lista);      // Imprime todas as tarefas pendentes
                printf("Informe o ID da tarefa: ");
                scanf("%d", &idConcluida);
                concluirTarefa(&lista, historico, idConcluida); // Concluir a tarefa
                break;
            }
            case 5: { 
                // --- Imprime o histórico de tarefas concluída ---
                imprimirTC(historico);      // Imprime as tarefas concluidas
                break;
            }
            case 6: { 
                // --- Opções para ordenar todas as tarefas ---
                int opcao6;

                moverTarefasVencidas(&lista, &listaPendentesVencidas);      // Atualiza as tarefas vencidas
                transferirTodasTarefas(lista, &todasTarefasOrdenadas);      // Transfere todas as tarefas para a lista duplamente encadeada
                
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
                            // --- Ordena por ID (Insertion Sort) ---
                            insertionSort(&todasTarefasOrdenadas);
                            imprimirTarefasOrdenadas(todasTarefasOrdenadas);
                            break;
                        case 2:
                            // --- Ordena por prioridade crescente (MergeSort) ---
                            mergeSort(todasTarefasOrdenadas);
                            imprimirTarefasOrdenadas(todasTarefasOrdenadas);
                            break;
                        case 3:
                            // --- Ordena por prioridade decrescente (QuickSort) ---
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
                // --- Editar uma tarefa existente ---
                int idEditar;

                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                imprimirTarefasPorData(lista);
                printf("Informe o ID da tarefa a ser editada: ");
                scanf("%d", &idEditar);

                buscarTarefa(lista, &pilha, idEditar); // Buscar e editar a tarefa 

                break;
            }
            case 8:
                // --- Desfaz a última operação realizada utilizando a pilha ---
                desfazerAlteracao(lista, &pilha);
                break;
            case 9: { 
                // --- Imprime as tarefas agendadas para o dia atual ---
                if (contarTarefasNaFila(&fila) > 0){ 
                    imprimirTarefasDoDia(&fila);
                } else {
                    printf("Nenhuma tarefa para hoje!\n");
                }
                break;
            }
            case 10: { 
                // --- Pesquisa uma tarefa pelo nome (nome completo) ---
                char buscarTarefa[300];
                printf("Digite a tarefa: ");
                scanf(" %[^\n]", buscarTarefa);

                buscarTarefaNome(lista, buscarTarefa);  // Realiza a busca por nome na lista de tarefas
                break;
            }
            case 11: {
                // --- Busca uma tarefa específica pelo ID usando busca binária ---
                int chave;

                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                transferirTodasTarefas(lista, &todasTarefasOrdenadas);
                insertionSort(&todasTarefasOrdenadas);                  // Ordena a lista de tarefas para busca binária
                imprimirTarefasOrdenadas(todasTarefasOrdenadas);        // Imprime a lista ordenada
                
                printf("Digite o ID que deseja buscar: ");
                scanf("%d", &chave);

                // Realiza a busca binária e informa o resultado
                if (buscaBinaria(todasTarefasOrdenadas, chave)){
                    printf("Tarefa encontrada!\n");
                } else {
                    printf("Tarefa nao encontrada!\n");
                }

                break;
            }
            case 12:
                // --- Imprime a lista de tarefas vencidas --- 
                moverTarefasVencidas(&lista, &listaPendentesVencidas);
                imprimirTarefasVencidas(listaPendentesVencidas);
                break;
            case 13: {
                // --- Transfere uma tarefa para uma nova data ---
                int idTarefa;
                char novaData[20];

                printf("Digite o ID da tarefa que deseja transferir: ");
                scanf("%d", &idTarefa);

                printf("Digite a nova data (dd-mm-aaaa): ");
                scanf("%s", novaData);

                transferirTarefaParaOutraData(&lista, idTarefa, novaData);  // Realiza a transferência da tarefa para a nova data
                break;
            }
            case 0:
                // --- Finaliza o programa e libera todos os recursos alocados dinamicamente ---
                printf("Saindo do programa...\n");
                liberarTarefaData(lista);
                liberarTC(historico);
                liberarTarefasOrdenadas(todasTarefasOrdenadas);
                liberarAlteracao(&pilha);
                liberarTarefasDoDia(&fila);
                exit(0);    // Encerra o programa
                break;
            default:
                // --- Caso o usuário insira uma opção inválida ---
                printf("Opcao invalida, tente novamente!\n");
        }
    } while (op != 0);

    return 0;
}