#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../include/listaEncadeada.h"
#include "../include/listaCircular.h"
#include "../include/pilha.h"
#include "listaCircular.c"
#include "../include/fila.h"
#include "../include/listaDuplamente.h"

TAREFA* removerTarefaDeData(DataTarefa** listaData, int idTarefa) {
    DataTarefa* atual = *listaData;
    DataTarefa* anterior = NULL;

    while (atual != NULL) 
    {
        TAREFA* tarefaAtual = atual->tarefas;
        TAREFA* tarefaAnterior = NULL;

        while (tarefaAtual != NULL) {
            // Encontra a tarefa com o ID especificado
            if (tarefaAtual->id == idTarefa){
               
                // Remove a tarefa da lista de tarefas da data
                if (tarefaAnterior == NULL) {
                    atual->tarefas = tarefaAtual->prox;
                } else {
                    tarefaAnterior->prox = tarefaAtual->prox;
                }
                atual->cont--;              // Decrementa o contador de tarefas da data

                // Se não houver mais tarefas para essa data, remove a data da lista
                if (atual->cont == 0) {
                    if (anterior == NULL) {
                        *listaData = atual->prox;
                    }
                     else {
                        anterior->prox = atual->prox;
                    }
                    free(atual);            
                }
                return tarefaAtual;       
            }
            tarefaAnterior = tarefaAtual;
            tarefaAtual = tarefaAtual->prox;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return NULL;                            
}


void adicionarTarefaEmData(DataTarefa** listaData, TAREFA* tarefa, char* novaData){
    DataTarefa* atual = *listaData;

    // Procura se a data já existe na lista
    while (atual != NULL){
        if (strcmp(atual->data, novaData) == 0) {
            break;
        }
        atual = atual->prox;
    }

    // Se a data não for encontrada, cria uma nova entrada para a data
    if(atual == NULL){
        atual = (DataTarefa*)malloc(sizeof(DataTarefa));
        strcpy(atual->data, novaData);
        atual->cont = 0;
        atual->tarefas = NULL;
        atual->prox = *listaData;
        *listaData = atual;
    }
    // Adiciona a tarefa na lista de tarefas da data
    tarefa->prox = atual->tarefas;
    atual->tarefas = tarefa;
    atual->cont++;
}

void transferirTarefaParaOutraData(DataTarefa** listaData, int idTarefa, char* novaData) {
    TAREFA* tarefaRemovida = removerTarefaDeData(listaData, idTarefa);      // Remove a tarefa da data original

    if (tarefaRemovida == NULL){
        printf("Tarefa com ID %d não encontrada.\n", idTarefa);
        return;
    }

    adicionarTarefaEmData(listaData, tarefaRemovida, novaData);              // Adiciona a tarefa na nova data

    printf("Tarefa com ID %d transferida para a data %s.\n", idTarefa, novaData);
}

void imprimirTarefasVencidas(DataTarefa* listaPendentesVencidas){
    if (listaPendentesVencidas == NULL){
        printf("Nao tem tarefas vencidas!\n\n");
        return;
    } 

    DataTarefa* atual = listaPendentesVencidas;
    printf("-------------- TAREFAS VENCIDAS --------------\n");

    // Percorre a lista de datas e imprime as tarefas vencidas
    while (atual != NULL) {
        printf("----------------------------------------------\n");
        printf("Data: %s\n", atual->data);
        printf("----------------------------------------------\n");
        TAREFA* tarefaAtual = atual->tarefas;

        // Imprime todas as tarefas da data
        while (tarefaAtual != NULL) {
            printf("ID: %d\nTarefa: %s\nPrioridade: %d\nStatus: %s\n\n",
                tarefaAtual->id, tarefaAtual->descricao, tarefaAtual->prioridade, tarefaAtual->status);
            tarefaAtual = tarefaAtual->prox;
        }
        printf("----------------------------------------------\n\n");
        atual = atual->prox;
    }
}

int compararDatas(char* data1, char* data2) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    // Converte as datas para inteiros (dia, mês e ano)
    sscanf(data1, "%d-%d-%d", &dia1, &mes1, &ano1); 
    sscanf(data2, "%d-%d-%d", &dia2, &mes2, &ano2); 

    // Compara as datas primeiro pelo ano, depois pelo mês e finalmente pelo dia
    if (ano1 != ano2) {
        return ano1 - ano2;     // Retorna a diferença de anos
    } else if (mes1 != mes2) {
        return mes1 - mes2;     // Retorna a diferença de meses
    } else{
        return dia1 - dia2;     // Retorna a diferença de dias
    }
}

void selectionSort(DataTarefa* listaData) {
    DataTarefa *noAtual, *noComparador, *noMinimo;
    char tempData[11]; 
    TAREFA* tempTarefas;

    // Percorre a lista de data
    for (noAtual = listaData; noAtual != NULL; noAtual = noAtual->prox) {
        noMinimo = noAtual;

        // Compara a data atual com as demais para encontrar a data mínima
        for (noComparador = noAtual->prox; noComparador != NULL; noComparador = noComparador->prox){
            
            if (compararDatas(noComparador->data, noMinimo->data) < 0) {
                noMinimo = noComparador;
            }
        }

        // Se o nó mínimo for diferente do nó atual, troca as datas e as listas de tarefas
        if(noMinimo != noAtual) {
            strcpy(tempData, noAtual->data);
            strcpy(noAtual->data, noMinimo->data);
            strcpy(noMinimo->data, tempData);

            tempTarefas = noAtual->tarefas;
            noAtual->tarefas = noMinimo->tarefas;
            noMinimo->tarefas = tempTarefas;
        }
    }
}


void moverTarefasVencidas(DataTarefa** listaData, DataTarefa** listaPendentesVencidas){
    char dataHoje[11];
    dataAtual(dataHoje);

    DataTarefa* atual = *listaData;
    DataTarefa* anterior = NULL;

    while (atual != NULL) {
        if (compararDatas(atual->data, dataHoje) < 0){  // Se a data da tarefa for anterior a data atual
            DataTarefa* vencida = atual;                // Marca a data vencida para mover para a lista de vencidas

            if(anterior == NULL) {                      // Caso a data vencida seja a primeira na lista
                *listaData = atual->prox;
            } 
            else{
                anterior->prox = atual->prox;           // Remove a data vencida da lista
            }

            atual = atual->prox; 
            vencida->prox = *listaPendentesVencidas;    // Coloca a data vencida no início da lista de vencidas
            *listaPendentesVencidas = vencida;          // Atualiza a lista de vencidas

        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}

int comparaString(char* nomeBusca, char* nome){
    if(*nomeBusca != 0){                                                    
        if (*nome == 0) return 0;                                           
        if (*nomeBusca == *nome) return comparaString(++nomeBusca, ++nome); 
        return 0;                                                           
    } else {
        return (*nome == 0);                                                
    }
}

void buscarTarefaNome(DataTarefa* listaData, char* nomeBusca){
    while(listaData != NULL){
        TAREFA* tarefa = listaData->tarefas;
        while (tarefa != NULL){
            if(comparaString(nomeBusca, tarefa->descricao)){    
                printf("Tarefa encontrada!\n");
                printf("ID: %d\n", tarefa->id);
                printf("Tarefa: %s\n", tarefa->descricao);
                printf("Prioridade: %d\n", tarefa->prioridade);
                printf("Status: %s\n", tarefa->status);
                return;
            }
            tarefa = tarefa->prox;
        }
        listaData = listaData->prox;
    }
    printf("Tarefa '%s' nao encontrada!\n", nomeBusca);
}

void dataAtual(char* dataHoje){
    time_t tempo = time(NULL);          // Obtém o tempo atual
    struct tm tm = *localtime(&tempo);  // Converte para tm
    sprintf(dataHoje, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);  // Formata a data.
}

void carregartarefasDoDia(DataTarefa* listaData, TarefasDoDia* fila) {
    char dataHoje[11];
    dataAtual(dataHoje);

    DataTarefa* aux = listaData;
    TarefasOrdenadas* listaOrdenada = NULL;

    while (aux != NULL) {
        if (strcmp(aux->data, dataHoje) == 0) {     // Se a data da entrada for igual à data atual
            TAREFA* tarefa = aux->tarefas;

            while (tarefa != NULL) {
                TarefasOrdenadas* novaTarefa = transferirTarefas(tarefa->id, tarefa->descricao, tarefa->prioridade, tarefa->status);

                if (listaOrdenada == NULL) {
                    listaOrdenada = novaTarefa;             // Se não houver lista ordenada, insere a nova tarefa como a primeira
                } else {
                    TarefasOrdenadas* temp = listaOrdenada;
                    while (temp->prox != NULL) {             // insere no final da lista ordenada
                        temp = temp->prox;
                    }
                    temp->prox = novaTarefa;
                    novaTarefa->ant = temp;
                }

                tarefa = tarefa->prox;
            }

            bubblesort(listaOrdenada);                      // Ordena a lista de tarefas pela prioridade

            TarefasOrdenadas* ordenadaAtual = listaOrdenada;
            // Insere todas as tarefas ordenadas na fila
            while (ordenadaAtual != NULL) {
                inserirTarefasNaFila(fila, ordenadaAtual->tarefa->descricao, 
                    ordenadaAtual->tarefa->prioridade, ordenadaAtual->tarefa->status, ordenadaAtual->tarefa->id);
                ordenadaAtual = ordenadaAtual->prox;
            }

             // Libera a memória das tarefas ordenadas
            TarefasOrdenadas* temp = listaOrdenada;
            while (temp != NULL) {
                TarefasOrdenadas* prox = temp->prox;
                free(temp->tarefa);
                free(temp);
                temp = prox;
            }
            return; 
        }
        aux = aux->prox;
    }
}

int calcularId(char* data, int cont){
    int dia, mes, ano;
    sscanf(data, "%d-%d-%d", &dia, &mes, &ano);     // Extrai o dia, mês e ano da data
    return (dia * 1000) + (mes * 100) + cont;       // Gera um ID único
}

TAREFA* criarTarefa(char* decricao, int prioridade, char* status, int id){
    TAREFA* novaTarefa = (TAREFA*)malloc(sizeof(TAREFA));
    if (!novaTarefa){
        exit(1);       
    }
    novaTarefa->id = id;
    // Preenche os dados da tarefa
    strcpy(novaTarefa->status, status);
    strcpy(novaTarefa->descricao, decricao);
    novaTarefa->prioridade = prioridade;
    novaTarefa->prox = NULL;
    return novaTarefa;
}

DataTarefa* criarDataTarefa(char* data){
    DataTarefa* novaData = (DataTarefa*)malloc(sizeof(DataTarefa));
    if (!novaData){
        exit(1);        
    }
     // Preenche o campo da data.
    strcpy(novaData->data, data);
    novaData->cont = 0;
    novaData->tarefas = NULL;
    novaData->prox = NULL;
    return novaData;
}

void inserirTarefa(TAREFA** lista, int id, char* status, char* descricao, int prioridade){
    TAREFA* novaTarefa = criarTarefa(descricao, prioridade, status, id);
    
    if (*lista == NULL){
        *lista = novaTarefa;
    } else {
        TAREFA* temp = *lista;
        
        while (temp->prox != NULL){
            temp = temp->prox;
        }
        temp->prox = novaTarefa;        
    }
}

void inserirTarefaData(DataTarefa** listaData, char* data, char* descricao, int prioridade, char* status){
    DataTarefa* aux = *listaData;

    // Busca pela data correspondente na lista de datas
    while (aux != NULL && strcmp(aux->data, data) != 0){
        aux = aux->prox;
    }

    // Se a data não for encontrada, cria uma nova entrada de data
    if (aux == NULL){
        DataTarefa* novaData = criarDataTarefa(data);
        novaData->prox = *listaData;
        *listaData = novaData;
        aux = novaData;
    }

    aux->cont++;
    int id = calcularId(data, aux->cont);

    // Insere a tarefa na lista de tarefas da data
    inserirTarefa(&(aux->tarefas), id, status, descricao, prioridade);

    printf("Tarefa adicionada com sucesso na data %s!\n", data);
}

TAREFA* removerTarefa(TAREFA* lista, Alteracao* pilha, int idBusca) {
    TAREFA* ant = NULL;
    TAREFA* aux = lista;

    while (aux != NULL) {
        if (aux->id == idBusca){
            // Coloca a tarefa na pilha para possível desfazer a remoção
            pilhaPush(pilha, aux);

            if (ant == NULL) { 
                lista = aux->prox;
            } else {
                ant->prox = aux->prox;
            }
            printf("Tarefa com ID %d removida com sucesso!\n", aux->id);
            free(aux); 
            return lista; 
        }

        ant = aux;
        aux = aux->prox;
    }
    return lista;   
}

int listaTamanho(TAREFA* lista) {
    int contador = 0;
    TAREFA* aux = lista;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

DataTarefa* removerTarefaData(DataTarefa* listaData, Alteracao* pilha, int idBusca) {
    DataTarefa* auxData = listaData;
    DataTarefa* antData = NULL;
    int tarefaEncontrada = 0; 

    while (auxData != NULL) {
        int tamanhoAnterior = listaTamanho(auxData->tarefas);               
        auxData->tarefas = removerTarefa(auxData->tarefas, pilha, idBusca); 
        int tamanhoAtual = listaTamanho(auxData->tarefas);                  

         // Se o tamanho mudou a tarefa foi removida
        if (tamanhoAnterior != tamanhoAtual) {
            tarefaEncontrada = 1; 
        }

        // Se a lista de tarefas da data ficou vazia remove a data.
        if (auxData->tarefas == NULL) {
            if (antData == NULL) {
                listaData = auxData->prox;
            } else {
                antData->prox = auxData->prox;
            }
            DataTarefa* temp = auxData;
            auxData = auxData->prox;
            free(temp);
            printf("Data removida!\n");
        } else {
            antData = auxData;
            auxData = auxData->prox;
        }
    }
    if (!tarefaEncontrada) {
        printf("Tarefa com ID %d nao encontrada em nenhuma data!\n", idBusca);
    }

    return listaData;
}

void editarTarefa(TAREFA* tarefa, char* descricaoAtual) {
    printf("------------- EDITANDO TAREFA %d -------------\n", tarefa->id);

    char novaDescricao[301];

    printf("Digite o novo nome (ou pressione Enter para manter): ");
   
    fflush(stdin);  
    fgets(novaDescricao, sizeof(novaDescricao), stdin);

    size_t len = strlen(novaDescricao);
    if (len > 0 && novaDescricao[len - 1] == '\n') {
        novaDescricao[len - 1] = '\0';
    }

    if (strlen(novaDescricao) > 0) {
        strcpy(descricaoAtual, novaDescricao);
    }

    int novaPrioridade;
    while (1) {
        printf("Digite a nova prioridade (1 - Alta, 2 - Media, 3 - Baixa, ou 0 para manter): ");
        if (scanf("%d", &novaPrioridade) == 1) {
            getchar(); 
            if (novaPrioridade >= 1 && novaPrioridade <= 3) {
                tarefa->prioridade = novaPrioridade;
                break;  
            } else if (novaPrioridade == 0) {
                break; 
            } else {
                printf("Prioridade invalida! Digite um valor entre 1 e 3.\n");
            }
        } else {
            printf("Entrada invalida! Tente novamente.\n");
            getchar();  
        }
    }

    printf("Tarefa editada com sucesso!\n");
}

void buscarTarefa(DataTarefa* listaData, Alteracao* pilha, int idbusca){
    while (listaData != NULL) {
        TAREFA* tarefa = listaData->tarefas;
        while (tarefa != NULL) {
            if (tarefa->id == idbusca){         
                pilhaPush(pilha, tarefa);       // Adiciona a tarefa à pilha para possível desfazer
 
                printf("Tarefa encontrada!\n\n");
                printf("ID: %d\n", tarefa->id);
                printf("Tarefa: %s\n", tarefa->descricao);
                printf("Prioridade: %d\n", tarefa->prioridade);
                printf("Status: %s\n", tarefa->status);

                editarTarefa(tarefa, tarefa->descricao);

                return;
            }
            tarefa = tarefa->prox;
        }
        listaData = listaData->prox;
    }
    printf("Tarefa com ID %d nao encontrada!\n", idbusca);
}

void concluirTarefa(DataTarefa** listaData, TarefasConcluidas* concluidas, int id) {
    DataTarefa* atual = *listaData;
    DataTarefa* anteriorData = NULL;

    while (atual != NULL) {
        TAREFA* tarefa = atual->tarefas;
        TAREFA* anteriorTarefa = NULL;

        while (tarefa != NULL) {
            // Se encontrar a tarefa com o ID 
            if (tarefa->id == id) {
                strcpy(tarefa->status, "CONCLUIDA");  
                printf("Tarefa ID %d foi marcada como CONCLUIDA!\n", id);

                // Remove a tarefa da lista de tarefas
                if (anteriorTarefa == NULL) {
                    atual->tarefas = tarefa->prox;  
                } else {
                    anteriorTarefa->prox = tarefa->prox;  
                }

                // Adiciona a tarefa concluída à lista de tarefas concluídas
                addTarefaConcluida(concluidas, tarefa);

                if (atual->tarefas == NULL) {
                    printf("Todas as tarefas da data %s foram concluidas! Removendo a data...\n", atual->data);
                    if (anteriorData == NULL) {
                        *listaData = atual->prox;  
                    } else {
                        anteriorData->prox = atual->prox;  
                    }
                    free(atual);
                }
                return; 
            }
            anteriorTarefa = tarefa;
            tarefa = tarefa->prox;
        }
        anteriorData = atual;
        atual = atual->prox;
    }
    printf("Tarefa com ID %d nao encontrada!\n", id);
}

void imprimirTarefasPorData(DataTarefa* lista){
    if (lista == NULL){
        return;
    }

    selectionSort(lista);
    DataTarefa* auxData = lista;
    
    while (auxData != NULL){
        printf("---------------------------------------------\n");
        printf("Data: %s\n", auxData->data);
        printf("---------------------------------------------\n");
        TAREFA* auxTarefa = auxData->tarefas;
        while (auxTarefa != NULL){
            printf(" ID: %d\n Tarefa: %s\n Prioridade: %d\n Status: %s\n", 
                auxTarefa->id, auxTarefa->descricao, auxTarefa->prioridade, auxTarefa->status);
            printf("---------------------------------------------\n");
            auxTarefa = auxTarefa->prox;
        }
        auxData = auxData->prox;
        printf("\n");
    }
}

void liberarTarefas(TAREFA* lista){
    if (lista){
        liberarTarefas(lista->prox);
        free(lista);
    }
}

void liberarTarefaData(DataTarefa* lista){
    if (lista){
        liberarTarefaData(lista->prox);
        free(lista);
    }
}

int verificarData(char* data) {
     // Verifica se o comprimento da data é 10 e se está no formato "DD-MM-AAAA"
    if (strlen(data) != 10) {
        // Retorna 0 se a data não tiver o comprimento esperado
        return 0; 
    }

    // Verifica se a data contém apenas números e os caracteres '-' nas posições certas
    if (!isdigit(data[0]) || !isdigit(data[1]) || data[2] != '-' ||
        !isdigit(data[3]) || !isdigit(data[4]) || data[5] != '-' ||
        !isdigit(data[6]) || !isdigit(data[7]) || !isdigit(data[8]) || !isdigit(data[9])) {
        // Retorna 0 se a data não for válida
        return 0;
    }

    // Converte os valores da data para inteiros
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = atoi(data + 6);

    // Converte os valores da data para inteiros
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;

    // Array com o número de dias de cada mês
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verifica se o ano é bissexto e ajusta o número de dias de fevereiro
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasNoMes[1] = 29;
    }
    // Verifica se o dia é válido para o mês especificado
    if (dia > diasNoMes[mes - 1]) return 0;

    // Retorna 1 se a data for válida
    return 1;
}