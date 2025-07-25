# Gerenciador de Tarefas em C

Projeto desenvolvido como trabalho final da disciplina **Estrutura de Dados I**, com o objetivo de implementar um sistema completo de gerenciamento de tarefas, utilizando diversas estruturas de dados clássicas da linguagem C.

## Funcionalidades

O sistema permite que tarefas sejam:

* Criadas, editadas, concluídas e removidas
* Organizadas por data, prioridade e estado
* Buscadas por palavra-chave ou ID (busca binária)
* Transferidas para outra data
* Desfeitas (última operação)
* Visualizadas por dia, vencidas ou completas

## Estruturas de Dados Utilizadas

* **Lista Encadeada**: Armazena as tarefas pendentes.
* **Lista Encadeada Circular**: Guarda o histórico das 10 últimas tarefas concluídas.
* **Lista Duplamente Encadeada**: Utilizada para ordenações por prioridade.
* **Pilha**: Implementa a funcionalidade de “desfazer” ações.
* **Fila**: Armazena as tarefas do dia, organizadas por chegada.
* **Recursividade**: Utilizada em buscas por palavra-chave.
* **Ordenações**: Insertion Sort, Merge Sort e Quick Sort aplicadas em tarefas.
* **Busca Binária**: Usada para encontrar tarefas específicas por ID após ordenação.

## Estrutura de Pastas

```bash
.
├── include/            # Arquivos de cabeçalho (.h)
│   ├── fila.h
│   ├── listaCircular.h
│   ├── listaDuplamente.h
│   ├── listaEncadeada.h
│   └── pilha.h
├── src/                # Implementações (.c)
│   ├── fila.c
│   ├── listaCircular.c
│   ├── listaDuplamente.c
│   ├── listaEncadeada.c
│   ├── main.c
│   └── pilha.c
├── output/             # Saída de testes ou execução
└── README.md
```

## Menu de Funcionalidades (`main.c`)

O sistema possui um menu interativo com as seguintes opções:

```
1 - Adicionar tarefa
2 - Imprimir todas as tarefas
3 - Remover tarefa
4 - Concluir uma tarefa
5 - Histórico de tarefas concluídas
6 - Ordenar tarefas (ID, prioridade crescente/decrescente)
7 - Editar tarefa
8 - Desfazer última operação
9 - Ver tarefas do dia
10 - Buscar tarefa (por nome)
11 - Buscar tarefa (busca binária)
12 - Ver tarefas vencidas
13 - Transferir tarefa para outra data
0 - Sair
```

## Como Executar

### Compilação

Você pode compilar o projeto com `gcc` diretamente:

```bash
gcc -o tarefas src/*.c -Iinclude
```

### Execução

```bash
./tarefas
```

## Autoria

Desenvolvido por Erlanny Rodrigues — Disciplina de Estrutura de Dados I

Curso de Sistemas de Informação - UFPI - CSHNB
