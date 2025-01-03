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

    while (atual != NULL) {
        TAREFA* tarefaAtual = atual->tarefas;
        TAREFA* tarefaAnterior = NULL;

        while (tarefaAtual != NULL) {
            if (tarefaAtual->id == idTarefa) {
                // Remove a tarefa encontrada
                if (tarefaAnterior == NULL) {
                    atual->tarefas = tarefaAtual->prox;
                } else {
                    tarefaAnterior->prox = tarefaAtual->prox;
                }
                atual->cont--;

                // Verifica se a data ficou vazia e a remove
                if (atual->cont == 0) {
                    if (anterior == NULL) {
                        *listaData = atual->prox;
                    } else {
                        anterior->prox = atual->prox;
                    }
                    free(atual);
                }
                return tarefaAtual; // Retorna a tarefa removida
            }
            tarefaAnterior = tarefaAtual;
            tarefaAtual = tarefaAtual->prox;
        }
        anterior = atual;
        atual = atual->prox;
    }

    return NULL; // Retorna NULL se a tarefa não foi encontrada
}

void adicionarTarefaEmData(DataTarefa** listaData, TAREFA* tarefa, const char* novaData) {
    DataTarefa* atual = *listaData;

    // Procura pela data
    while (atual != NULL) {
        if (strcmp(atual->data, novaData) == 0) {
            break;
        }
        atual = atual->prox;
    }

    // Cria a data se ela não existir
    if (atual == NULL) {
        atual = (DataTarefa*)malloc(sizeof(DataTarefa));
        strcpy(atual->data, novaData);
        atual->cont = 0;
        atual->tarefas = NULL;
        atual->prox = *listaData;
        *listaData = atual;
    }

    // Adiciona a tarefa à lista de tarefas da data
    tarefa->prox = atual->tarefas;
    atual->tarefas = tarefa;
    atual->cont++;
}

void transferirTarefaParaOutraData(DataTarefa** listaData, int idTarefa, char* novaData) {
    // Remove a tarefa da data original
    TAREFA* tarefaRemovida = removerTarefaDeData(listaData, idTarefa);

    if (tarefaRemovida == NULL) {
        printf("Tarefa com ID %d não encontrada.\n", idTarefa);
        return;
    }

    // Adiciona a tarefa à nova data
    adicionarTarefaEmData(listaData, tarefaRemovida, novaData);

    printf("Tarefa com ID %d transferida para a data %s.\n", idTarefa, novaData);
}

void imprimirTarefasVencidas(DataTarefa* listaPendentesVencidas) {
    if (listaPendentesVencidas == NULL){
        printf("Nao tem tarefas vencidas!\n\n");
        return;
    } 

    DataTarefa* atual = listaPendentesVencidas;
    printf("-------------- TAREFAS VENCIDAS --------------\n");

    while (atual != NULL) {
        printf("----------------------------------------------\n");
        printf("Data: %s\n", atual->data);
        printf("----------------------------------------------\n");
        TAREFA* tarefaAtual = atual->tarefas;

        while (tarefaAtual != NULL) {
            printf("ID: %d\nTarefa: %s\nPrioridade: %d\nStatus: %s\n\n",
                tarefaAtual->id, tarefaAtual->descricao, tarefaAtual->prioridade, tarefaAtual->status);
            tarefaAtual = tarefaAtual->prox;
        }
        printf("----------------------------------------------\n\n");
        atual = atual->prox;
    }
}

int compararDatas(const char* data1, const char* data2) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    sscanf(data1, "%d-%d-%d", &dia1, &mes1, &ano1); // Extrai dia, mês e ano de data1
    sscanf(data2, "%d-%d-%d", &dia2, &mes2, &ano2); // Extrai dia, mês e ano de data2

    if (ano1 != ano2) {
        return ano1 - ano2; // Compara os anos
    } else if (mes1 != mes2) {
        return mes1 - mes2; // Compara os meses
    } else {
        return dia1 - dia2; // Compara os dias
    }
}

void selectionSort(DataTarefa* listaData) {
    DataTarefa *noAtual, *noComparador, *noMinimo;
    char tempData[11]; // Buffer temporário para troca de datas
    TAREFA* tempTarefas; // Buffer temporário para troca de listas de tarefas

    for (noAtual = listaData; noAtual != NULL; noAtual = noAtual->prox) {
        noMinimo = noAtual;

        for (noComparador = noAtual->prox; noComparador != NULL; noComparador = noComparador->prox) {
            // Usa compararDatas para determinar a menor data
            if (compararDatas(noComparador->data, noMinimo->data) < 0) {
                noMinimo = noComparador;
            }
        }

        // Realiza a troca se necessário
        if (noMinimo != noAtual) {
            // Troca as datas
            strcpy(tempData, noAtual->data);
            strcpy(noAtual->data, noMinimo->data);
            strcpy(noMinimo->data, tempData);

            // Troca as listas de tarefas associadas
            tempTarefas = noAtual->tarefas;
            noAtual->tarefas = noMinimo->tarefas;
            noMinimo->tarefas = tempTarefas;
        }
    }
}


void moverTarefasVencidas(DataTarefa** listaData, DataTarefa** listaPendentesVencidas) {
    char dataHoje[11];
    dataAtual(dataHoje);

    DataTarefa* atual = *listaData;
    DataTarefa* anterior = NULL;

    while (atual != NULL) {
        if (compararDatas(atual->data, dataHoje) < 0) { // Data da tarefa é anterior à data atual
            DataTarefa* vencida = atual;

            // Remove o nó da lista original
            if (anterior == NULL) {
                *listaData = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            atual = atual->prox; // Atualiza o ponteiro atual antes de realocar

            // Insere na lista de pendentes vencidas
            vencida->prox = *listaPendentesVencidas;
            *listaPendentesVencidas = vencida;

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
    time_t tempo = time(NULL);
    struct tm tm = *localtime(&tempo);
    sprintf(dataHoje, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void carregartarefasDoDia(DataTarefa* listaData, TarefasDoDia* fila) {
    char dataHoje[11];
    dataAtual(dataHoje);

    printf("\nTarefas para o dia %s:\n", dataHoje);

    DataTarefa* aux = listaData;
    TarefasOrdenadas* listaOrdenada = NULL;

    while (aux != NULL) {
        if (strcmp(aux->data, dataHoje) == 0) {
            TAREFA* tarefa = aux->tarefas;

            while (tarefa != NULL) {
                TarefasOrdenadas* novaTarefa = transferirTarefas(tarefa->id, tarefa->descricao, tarefa->prioridade, tarefa->status);

                if (listaOrdenada == NULL) {
                    listaOrdenada = novaTarefa;
                } else {
                    TarefasOrdenadas* temp = listaOrdenada;
                    while (temp->prox != NULL) {
                        temp = temp->prox;
                    }
                    temp->prox = novaTarefa;
                    novaTarefa->ant = temp;
                }

                tarefa = tarefa->prox;
            }

            bubblesort(listaOrdenada);

            TarefasOrdenadas* ordenadaAtual = listaOrdenada;
            while (ordenadaAtual != NULL) {
                inserirTarefasNaFila(fila, ordenadaAtual->tarefa->descricao, 
                    ordenadaAtual->tarefa->prioridade, ordenadaAtual->tarefa->status, ordenadaAtual->tarefa->id);
                ordenadaAtual = ordenadaAtual->prox;
            }

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
    sscanf(data, "%d-%d-%d", &dia, &mes, &ano);
    return (dia * 1000) + (mes * 100) + cont;
}

TAREFA* criarTarefa(char* decricao, int prioridade, char* status, int id){
    TAREFA* novaTarefa = (TAREFA*)malloc(sizeof(TAREFA));
    if (!novaTarefa){
        exit(1);
    }
    novaTarefa->id = id;
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

    while (aux != NULL && strcmp(aux->data, data) != 0){
        aux = aux->prox;
    }

    if (aux == NULL){
        DataTarefa* novaData = criarDataTarefa(data);
        novaData->prox = *listaData;
        *listaData = novaData;
        aux = novaData;
    }

    aux->cont++;
    int id = calcularId(data, aux->cont);

    inserirTarefa(&(aux->tarefas), id, status, descricao, prioridade);

    printf("Tarefa adicionada com sucesso na data %s!\n", data);
}

TAREFA* removerTarefa(TAREFA* lista, Alteracao* pilha, int idBusca) {
    TAREFA* ant = NULL;
    TAREFA* aux = lista;
    
    while (aux != NULL && aux->id != idBusca){
        ant = aux;
        aux = aux->prox;
    }
    if (aux == NULL) {  
        printf("Tarefa com ID %d nao encontrada!\n", idBusca);
        return lista;
    }

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

DataTarefa* removerTarefaData(DataTarefa* listaData, Alteracao* pilha, int idBusca) {
    DataTarefa* auxData = listaData;
    DataTarefa* antData = NULL;

    while (auxData != NULL) {
        auxData->tarefas = removerTarefa(auxData->tarefas, pilha, idBusca);
       
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

    return listaData;
}

void editarTarefa(TAREFA* tarefa) {
    printf("------------- EDITANDO TAREFA %d -------------\n", tarefa->id);

    printf("Digite o novo nome (ou pressione Enter para manter): ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char novaDescricao[300];
    if (fgets(novaDescricao, sizeof(novaDescricao), stdin) != NULL) {
        novaDescricao[strcspn(novaDescricao, "\n")] = 0; 
        
        if (strlen(novaDescricao) > 0) {
            strcpy(tarefa->descricao, novaDescricao);
        }
    }

    printf("Digite a nova prioridade (1 - Alta, 2 - Media, 3 - Baixa, ou 0 para manter): ");
    int novaPrioridade;
    scanf("%d", &novaPrioridade);
    getchar();  
    if (novaPrioridade >= 1 && novaPrioridade <= 3) {
        tarefa->prioridade = novaPrioridade;
    }
    printf("Tarefa editada com sucesso!\n");
}

void buscarTarefa(DataTarefa* listaData, Alteracao* pilha, int idbusca){
    while (listaData != NULL) {
        TAREFA* tarefa = listaData->tarefas;
        while (tarefa != NULL) {
            if (tarefa->id == idbusca){
                pilhaPush(pilha, tarefa);  

                printf("Tarefa encontrada!\n\n");
                printf("ID: %d\n", tarefa->id);
                printf("Tarefa: %s\n", tarefa->descricao);
                printf("Prioridade: %d\n", tarefa->prioridade);
                printf("Status: %s\n", tarefa->status);

                editarTarefa(tarefa);

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
            if (tarefa->id == id) {
                strcpy(tarefa->status, "CONCLUIDA");  
                printf("Tarefa ID %d foi marcada como CONCLUIDA!\n", id);

                if (anteriorTarefa == NULL) {
                    atual->tarefas = tarefa->prox;  
                } else {
                    anteriorTarefa->prox = tarefa->prox;  
                }

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
    if (strlen(data) != 10) {
        return 0; 
    }

    // Verifica o formato dd-mm-yyyy
    if (!isdigit(data[0]) || !isdigit(data[1]) || data[2] != '-' ||
        !isdigit(data[3]) || !isdigit(data[4]) || data[5] != '-' ||
        !isdigit(data[6]) || !isdigit(data[7]) || !isdigit(data[8]) || !isdigit(data[9])) {
        return 0;
    }

    // Converte partes da data para números inteiros
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = atoi(data + 6);

    // Verifica os limites de dia, mês e ano
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > 31) return 0;

    // Verifica dias válidos para cada mês
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta para anos bissextos
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasNoMes[1] = 29;
    }

    if (dia > diasNoMes[mes - 1]) return 0;

    return 1;
}