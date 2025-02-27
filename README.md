# Gerenciador de Tarefas em C 

Este projeto foi desenvolvido como trabalho final da disciplina de **Estrutura de Dados 1** e tem como objetivo a criação de um **sistema de gerenciamento de tarefas**. O sistema permite que tarefas sejam atribuídas a diferentes usuários, levando em consideração **prioridades e deadlines**. Além disso, os usuários podem organizar e buscar suas tarefas de diversas maneiras.  

## Funcionalidades e Estruturas Utilizadas  

1. **Lista Encadeada:** As tarefas são armazenadas em uma lista encadeada básica, onde cada nó representa uma tarefa contendo informações como nome, prioridade e deadline.  

2. **Lista Encadeada Circular:** Para manter um histórico das tarefas concluídas, foi implementada uma lista encadeada circular com capacidade limitada (por exemplo, armazenando as últimas 10 tarefas finalizadas).  

3. **Lista Duplamente Encadeada:** Utilizada para organizar tarefas por prioridade, permitindo a reordenação dinâmica com base em critérios definidos.  

4. **Pilha:** Permite desfazer uma ação recente, como reverter a remoção de uma tarefa ou a alteração de sua prioridade.  

5. **Fila:** Gerencia uma fila de tarefas pendentes, organizando-as pela ordem de chegada ou outro critério.  

6. **Recursividade:** Implementação de uma funcionalidade de busca recursiva para localizar tarefas específicas com base em palavras-chave no nome ou descrição.  

7. **Algoritmos de Ordenação:** As tarefas podem ser ordenadas de diferentes maneiras (por data de criação, prioridade, etc.), utilizando diversos algoritmos de ordenação, que devem ser aplicados pelo menos uma vez no projeto.  

8. **Algoritmos de Busca:** Após a ordenação das tarefas, a busca binária é utilizada para localizar rapidamente uma tarefa específica.  
