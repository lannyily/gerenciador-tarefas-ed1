#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/listaDuplamente.h"
#include "../include/listaEncadeada.h"

TarefasOrdenadas* meio(TarefasOrdenadas* inicio, TarefasOrdenadas* fim){
    if (inicio == NULL) return NULL;

    if (inicio == fim) return inicio;       // Se o início e o fim são o mesmo, retorna o nó inicial

    TarefasOrdenadas* lento = inicio;
    TarefasOrdenadas* rapido = inicio->prox;

    while(rapido != fim){                   // Procura o ponto médio
        rapido = rapido->prox;
        lento = lento->prox;
        if (rapido != fim){
            rapido = rapido->prox;
        }
    }
    return lento;
}

int buscaBinaria(TarefasOrdenadas* ordenadas, int idBusca){
    TarefasOrdenadas* inicio = ordenadas;
    TarefasOrdenadas* fim = NULL;

    while(1){
        TarefasOrdenadas* meioLista = meio(inicio, fim);

        if (meioLista == NULL) return 0;

        if(meioLista->tarefa->id == idBusca) {
            printf("\n----------------- TAREFA %d -----------------\n", idBusca);
            printf("ID: %d\nTarefa: %s\nPrioridade: %d\nStatus: %s\n\n",
                meioLista->tarefa->id, meioLista->tarefa->descricao, meioLista->tarefa->prioridade, meioLista->tarefa->status);
            return 1;                               // Retorna 1 se a tarefa foi encontrada
        } 
        else if (inicio == fim){
            break;                                  // Se chegou ao fim da lista, sai do loop
        } 
        else if (meioLista->tarefa->id < idBusca){  // Se o ID da tarefa no meio for menor que o ID procurado
            inicio = meioLista->prox;               // Move o início para a parte maior
        } 
        else if (meioLista->tarefa->id > idBusca){  // Se o ID da tarefa no meio for maior que o ID procurado
            fim = meioLista;                        // Move o fim para a parte menor
        }
    }
    return 0;                                       // Retorna 0 se a tarefa não for encontrada
}

TarefasOrdenadas* concatenar(TarefasOrdenadas* menor, TarefasOrdenadas* pivo, TarefasOrdenadas* maior) {
    TarefasOrdenadas* resultado = menor;

    if (resultado != NULL) {
        TarefasOrdenadas* atual = resultado;
        while (atual->prox != NULL) {
            atual = atual->prox;        // Vai até o final da lista 'menor'
        }
        atual->prox = pivo;             // Concatena o pivo no final da lista
        pivo->ant = atual;              // Ajusta o ponteiro 'ant' do pivo
    } else {
        resultado = pivo;               // Se 'menor' for NULL, o resultado é o pivo
    }

   
    pivo->prox = maior;                 // Concatena a lista 'maior' após o pivo
    if(maior != NULL) {
        maior->ant = pivo;              // Ajusta o ponteiro 'ant' da lista 'maior'
    }
    
    return resultado;                   // Retorna a lista concatenada
}

TarefasOrdenadas* particionar(TarefasOrdenadas* ordenadas, TarefasOrdenadas** menor, TarefasOrdenadas** maior) {
    
    TarefasOrdenadas* pivo = ordenadas;
    TarefasOrdenadas* atual = ordenadas->prox;

    *menor = NULL;
    *maior = NULL;

    while (atual != NULL)
    {
        TarefasOrdenadas* proxima = atual->prox;
        atual->ant = NULL;                                          // Desconecta o nó atual da lista original
        if(atual->tarefa->prioridade >= pivo->tarefa->prioridade) { // Se a prioridade for maior ou igual ao pivô
           
            atual->prox = *menor;
            if (*menor != NULL) {
                (*menor)->ant = atual;
            }
            *menor = atual;             
        } 
        else{
            
            atual->prox = *maior;
            if (*maior != NULL) {
                (*maior)->ant = atual;
            }
            *maior = atual;
        }

        atual = proxima;
    }

    pivo->prox = NULL;
    pivo->ant = NULL;

    return pivo;
}

TarefasOrdenadas* quickSort(TarefasOrdenadas* ordenadas) {
    if (ordenadas == NULL || ordenadas->prox == NULL) {
        return ordenadas;
    }

    TarefasOrdenadas *menor, *maior;
    TarefasOrdenadas* pivo = particionar(ordenadas, &menor, &maior); // Particionar a lista de tarefas

    menor = quickSort(menor);                   // Ordena a lista 'menor'
    maior = quickSort(maior);                   // Ordena a lista 'maior'
    
    return concatenar(menor, pivo, maior);      // Concatena as listas ordenadas
}


TarefasOrdenadas* mesclar(TarefasOrdenadas* lista1, TarefasOrdenadas* lista2) {
    TarefasOrdenadas* resultado = NULL;

    if (lista1 == NULL) return lista2;       // Se lista1 for vazia, retorna lista2
    if (lista2 == NULL) return lista1;       // Se lista2 for vazia, retorna lista1

    if (lista1->tarefa->prioridade <= lista2->tarefa->prioridade) {
        resultado = lista1;
        resultado->prox = mesclar(lista1->prox, lista2);    // Mescla o próximo nó da lista1 com lista2
        if (resultado->prox != NULL) {
            resultado->prox->ant = resultado;
        }
    } else {
        resultado = lista2;
        resultado->prox = mesclar(lista1, lista2->prox);    // Mescla o próximo nó da lista2 com lista1
        if (resultado->prox != NULL) {
            resultado->prox->ant = resultado;
        }
    }
    return resultado;           // Retorna a lista mesclada
}

TarefasOrdenadas* dividir(TarefasOrdenadas* ordenadas) {
    TarefasOrdenadas* meio = ordenadas;
    TarefasOrdenadas* fim = ordenadas;

    while (fim != NULL && fim->prox != NULL) {
        fim = fim->prox->prox;                  // Avança dois nós de cada vez
        if (fim != NULL) {
            meio = meio->prox; 
        }
    }

    TarefasOrdenadas* segundaMetade = meio->prox;   // Divide a lista
    if (segundaMetade != NULL) {
        segundaMetade->ant = NULL;                  // Desconecta a segunda metade da lista original
    }
    meio->prox = NULL;                              // Desconecta a primeira metade da lista

    return segundaMetade;                           // Retorna a segunda metade da lista
}

TarefasOrdenadas* mergeSort(TarefasOrdenadas* ordenadas) {
    if (ordenadas == NULL || ordenadas->prox == NULL)  return ordenadas; 
    
    TarefasOrdenadas* segundaMetade = dividir(ordenadas);   // Divide a lista ao meio

    ordenadas = mergeSort(ordenadas);                       // Ordena a primeira metade
    segundaMetade = mergeSort(segundaMetade);               // Ordena a segunda metade

    return mesclar(ordenadas, segundaMetade);               // Mescla as duas metades ordenadas
}


void insertionSort(TarefasOrdenadas** todasTarefasOrdenadas){
    if (*todasTarefasOrdenadas == NULL) return;

    TarefasOrdenadas* atual = *todasTarefasOrdenadas;
    TarefasOrdenadas* ordenar = NULL;

    while(atual != NULL) {
        TarefasOrdenadas* proximo = atual->prox;
        atual->ant = atual->prox = NULL;                            // Desconecta o nó atual da lista original

        if(ordenar == NULL || ordenar->tarefa->id >= atual->tarefa->id) {
            atual->prox = ordenar;
            if (ordenar != NULL){
                ordenar->ant = atual;
            }
            ordenar = atual;                             // Insere o nó atual no início da lista ordenada
        } else{
            TarefasOrdenadas* temp = ordenar;
            while(temp->prox != NULL && temp->prox->tarefa->id < atual->tarefa->id){
                temp = temp->prox;                      // Encontra a posição correta para o nó atual
            }

            atual->prox = temp->prox;
            if (temp->prox != NULL){
                temp->prox->ant = atual;
            }
            temp->prox = atual;
            atual->ant = temp;
        }
        atual = proximo;
    }
    *todasTarefasOrdenadas = ordenar;
}

void transferirTodasTarefas(DataTarefa* lista, TarefasOrdenadas** todasTarefasOrdenadas) {
    DataTarefa* dataAtual = lista;

    while (dataAtual != NULL) {
        TAREFA* tarefaAtual = dataAtual->tarefas;

        while (tarefaAtual != NULL) {
            TarefasOrdenadas* novaTarefa = transferirTarefas(tarefaAtual->id, tarefaAtual->descricao, tarefaAtual->prioridade, tarefaAtual->status);

            if (*todasTarefasOrdenadas == NULL) {
                *todasTarefasOrdenadas = novaTarefa;
            } else {
                TarefasOrdenadas* temp = *todasTarefasOrdenadas;

                while (temp->prox != NULL) {
                    temp = temp->prox;
                }
                temp->prox = novaTarefa;        // Insere a nova tarefa no final
                novaTarefa->ant = temp;
            }
            tarefaAtual = tarefaAtual->prox;
        }
        dataAtual = dataAtual->prox;
    }
}

void bubblesort(TarefasOrdenadas* ordenadas) {
    int troca;
    TarefasOrdenadas *noAtual, *noProximo;
    troca = 1;

    while (troca) {
        troca = 0;
        noAtual = ordenadas;

        while (noAtual != NULL && noAtual->prox != NULL) {
            noProximo = noAtual->prox;

            if (noAtual->tarefa->prioridade > noProximo->tarefa->prioridade) {
                // Troca os elementos de lugar se a prioridade da tarefa anterior for maior
                TAREFA tempTarefa = *(noAtual->tarefa);
                *(noAtual->tarefa) = *(noProximo->tarefa);
                *(noProximo->tarefa) = tempTarefa;

                troca = 1;  // Indica que houve uma troca
            }
            noAtual = noAtual->prox;
        }
    }
}

TarefasOrdenadas* transferirTarefas(int tarefaID, char* descricao, int prioridade, char* status) {
    TarefasOrdenadas* novaTarefa = (TarefasOrdenadas*)malloc(sizeof(TarefasOrdenadas));
    novaTarefa->tarefa = (TAREFA*)malloc(sizeof(TAREFA));
    // Preenche os dados da tarefa
    novaTarefa->tarefa->id = tarefaID;
    strcpy(novaTarefa->tarefa->descricao, descricao);
    novaTarefa->tarefa->prioridade = prioridade;
    strcpy(novaTarefa->tarefa->status, status);
    novaTarefa->prox = NULL;
    novaTarefa->ant = NULL;
    return novaTarefa;      // Retorna o novo nó criado
}


void inserirTarefasOrdenadas(DataTarefa* listaData, TarefasOrdenadas** ordenadas) {
    DataTarefa* dataAtual = listaData;

    while (dataAtual != NULL) {
        TAREFA* tarefaAtual = dataAtual->tarefas;
        while (tarefaAtual != NULL) {
            // Cria uma nova tarefa ordenada a partir da tarefa atual
            TarefasOrdenadas* novaTarefa = transferirTarefas(tarefaAtual->id, tarefaAtual->descricao, tarefaAtual->prioridade, tarefaAtual->status);

            // Se a lista de tarefas ordenadas estiver vazia, insere a nova tarefa
            if (*ordenadas == NULL) {
                *ordenadas = novaTarefa;
            } else {
                // Caso contrário, vai até o final da lista e insere a nova tarefa
                TarefasOrdenadas* temp = *ordenadas;
                while (temp->prox != NULL) {
                    temp = temp->prox;
                }
                // Conecta a nova tarefa ao final da lista
                temp->prox = novaTarefa;
                novaTarefa->ant = temp;
            }
            tarefaAtual = tarefaAtual->prox;
        }
        dataAtual = dataAtual->prox;
    }
}


void imprimirTarefasOrdenadas(TarefasOrdenadas* ordenadas) {
    TarefasOrdenadas* atual = ordenadas;
    while (atual != NULL) {
        printf("ID: %d\nTarefa: %s\nPrioridade: %d\nStatus: %s\n\n",
               atual->tarefa->id, atual->tarefa->descricao, atual->tarefa->prioridade, atual->tarefa->status);
        atual = atual->prox;
    }
}

void liberarTarefasOrdenadas(TarefasOrdenadas* ordenadas) {
    TarefasOrdenadas* atual = ordenadas;
    while (atual != NULL) {
        TarefasOrdenadas* temp = atual;
        atual = atual->prox;
        free(temp);         
    }
}