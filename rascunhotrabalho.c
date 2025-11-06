#include <stdio.h> 
#include <string.h> // Para manipulação de strings
#include <stdlib.h> // Para malloc e free
  
typedef struct 
{ 
    int dia;
    int mes;
    int ano;
} data;

typedef struct solicitante
{
    int unidade;
    char nome[100];
    char email[100];
    char telefone[15];
    struct solicitante *ant;
    struct solicitante *prox;
} solicitante;

typedef struct espacocomum
{
    int id_espaco;
    char nome[100];
    char descricao[255];
    int capacidade;
    struct espacocomum *ant;
    struct espacocomum *prox;
} espacocomum;

typedef struct agendamento
{
    int unidade_solicitante; // <-- Guarda o ID do solicitante
    int id_do_espaco;        // <-- Guarda o ID do espaco
    data data_agendamento;
    struct agendamento *ant;
    struct agendamento *prox;
} agendamento;

/*Criação de nó "cabeça" para a lista de espaços*/
espacocomum* criaListaEspacos()
{
    // Aloca memória para a cabeça
    espacocomum *sentinela = (espacocomum*) malloc(sizeof(espacocomum));
    
    if (sentinela != NULL) {
        // A lista começa vazia, apontando para nada dos dois lados.
        sentinela->prox = NULL;
        sentinela->ant = NULL; 
    }
    return sentinela;
}

/* Cria e retorna o nó sentinela para uma lista de agendamentos.*/
agendamento* criaListaAgendamentos() {
    // Aloca memória para a cabeça
    agendamento *sentinela = (agendamento*) malloc(sizeof(agendamento));
    
    if (sentinela != NULL) {
        // A lista começa vazia, apontando para nada dos dois lados.
        sentinela->prox = NULL;
        sentinela->ant = NULL; 
    }
    return sentinela;
}

/* Cria e retorna o nó sentinela para uma lista de solicitantes.*/
solicitante* criaListaSolicitantes() {
    // Aloca memória para a cabeça
    solicitante *sentinela = (solicitante*) malloc(sizeof(solicitante));
    
    if (sentinela != NULL) {
        // A lista começa vazia, apontando para nada dos dois lados.
        sentinela->prox = NULL;
        sentinela->ant = NULL; 
    }
    return sentinela;
}

int main()
{
    int opcao, opcoesubmenu;
    solicitante *lista_solicitantes;
    espacocomum *lista_espacos;
    agendamento *lista_agendamentos;

    /*Criação de lista com cabeça para melhorar funções de inserção*/
    lista_solicitantes = criaListaSolicitantes();
    lista_espacos = criaListaEspacos();
    lista_agendamentos = criaListaAgendamentos();
    
    /*Checagem de segurança se as lista foram iniciadas coma cabeça*/
    if (lista_solicitantes == NULL || lista_espacos == NULL || lista_agendamentos == NULL) {
        printf("ERRO 1: Falha ao alocar memoria para as listas.\n");
        return 1; // Encerra o programa
    }
    
    do{
        printf("== SISTEMA DE CONTROLE agendamentoS DE ÁREAS ==\nO que você deseja fazer?\n");
        printf("[1] agendamentos\n[2] Gerenciar Espaços\n[3] Gerenciar solicitantes\n[4] Relatórios\n[0] Sair\n");
        scanf("%d", &opcao); 

        switch (opcao)
            {
            case 1:
                do
                {
                    printf("\n== Menu de agendamentos ==\nO que você deseja fazer?\n[1] Novo agendamento\n[2] Consultar / Cancelar agendamento\n[3] Ver Calendário do Dia\n[0] Voltar ao Menu Principal\n");
                    scanf("%d", &opcoesubmenu);
                    switch (opcoesubmenu)
                    {
                        case 1:
                            printf("\n== Novo agendamento ==\n");
                            break;
                        case 2:
                            /* code */
                            break;
                        case 3:
                            /* code */
                            break;
                        default:
                        printf("Opção inválida. Tente novamente.\n");
                        break;
                    }
                } while (opcoesubmenu != 0);
                break;
            case 2:
                do
                {
                    printf("== Menu de Espaços Comuns ==\nO que você deseja fazer?\n[1] Cadastrar Novo Espaço\n[2] Alterar Espaço\n[3] Listar Todos os Espaços\n[0] Voltar ao Menu Principal\n");
                    scanf("%d", &opcoesubmenu);
                    switch (opcoesubmenu)
                    {
                        case 1:
                            printf("\n== Novo agendamento ==\n");
                            break;
                        case 2:
                            /* code */
                            break;
                        case 3:
                            /* code */
                            break;
                        default:
                        printf("Opção inválida. Tente novamente.\n");
                        break;
                    }
                } while (opcoesubmenu != 0);
                break;
            case 3:
                do
                {
                    printf("\n== Menu de solicitantes ==\nO que você deseja fazer?\n[1] Cadastrar Novo solicitante\n[2] Alterar solicitante\n[3] Listar solicitantes\n[0] Voltar ao Menu Principal\n");
                    scanf("%d", &opcoesubmenu);
                    switch (opcoesubmenu)
                    {
                        case 1:
                            printf("\n== Novo agendamento ==\n");
                            break;
                        case 2:
                            /* code */
                            break;
                        case 3:
                            /* code */
                            break;
                        default:
                        printf("Opção inválida. Tente novamente.\n");
                        break;
                    }
                } while (opcoesubmenu != 0);
                break;
            case 4:
                /* code */
                break;
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
            }
    }while(opcao != 0);
    
    return 0;
}