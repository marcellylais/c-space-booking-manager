# Sistema de Reserva de Espaços Comuns (C-Space Manager)

Este projeto foi desenvolvido como parte da disciplina de **Algoritmos e Programação II**. Trata-se de um sistema completo para gestão de reservas de áreas comuns (como salões de festas, churrasqueiras e quadras), focando em eficiência de busca e organização de dados.

## Funcionalidades

- **Gestão de Espaços:** Cadastro, alteração e listagem de áreas comuns.
- **Gestão de Solicitantes:** Controle de unidades e responsáveis.
- **Sistema de Agendamentos:** Criação e cancelamento de reservas com verificação automática de disponibilidade.
- **Relatórios:** Consulta de reservas por período e visualização do calendário do dia atual.
- **Persistência de Dados:** Salvamento automático em arquivos binários (`.dat`) e suporte a importação/exportação em formato universal (`.csv`).

## Conceitos de Estrutura de Dados Aplicados

Para garantir a performance do sistema, foram aplicados conceitos avançados de Computação:

* **Listas Duplamente Encadeadas com Nó-Cabeça:** Utilizadas para gerenciar Espaços, Solicitantes e Agendamentos, permitindo inserção e remoção eficiente em qualquer ponto da lista.
* **Algoritmo de Ordenação Híbrido:**
    * **Insertion Sort (O(n)):** Para manter a lista ordenada durante cadastros manuais.
    * **Merge Sort (O(n log n)):** Utilizado para carga em massa de arquivos externos, garantindo rapidez mesmo com grandes volumes de dados.
* **Manipulação de Arquivos Binários:** Otimização de leitura e escrita para garantir que os dados não sejam perdidos ao fechar o programa.

## Estrutura do projeto

* **main.c:** Ponto de entrada e menus principais.
* **agendamento.c/h:** Lógica de reservas e verificação de datas.
* **solicitantes.c/h:** Gerenciamento de usuários/unidades.
* **espacocomum.c/h:** Controle de áreas físicas.
* **datas.c/h:** Funções auxiliares de comparação de tempo.
