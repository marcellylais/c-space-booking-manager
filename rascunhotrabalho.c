#include <stdio.h>
#include <string.h>

typedef struct 
{ 
    int dia;
    int mes;
    int ano;
} Data;

typedef struct solicitante
{
    int unidade;
    char nome[100];
    char email[100];
    char telefone[15];
    struct solicitante *prox;
} Solicitante;

typedef struct espacoComum
{
    int id_espaco;
    char nome[100];
    char descricao[255];
    int capacidade;
    struct espacoComum *prox;
} EspacoComum;

typedef struct agendamento
{
    Solicitante solicitante;
    EspacoComum espaco;
    Data data_agendamento;
    struct agendamento *prox;
} Agendamento;


int main()
{
    int opcao, opcoesubmenu;
    

    do{
        printf("== SISTEMA DE CONTROLE AGENDAMENTOS DE ÁREAS ==\nO que você deseja fazer?\n");
        printf("[1] Agendamentos\n[2] Gerenciar Espaços\n[3] Gerenciar Solicitantes\n[4] Relatórios\n[0] Sair\n");
        scanf("%d", &opcao); 

        switch (opcao)
            {
            case 1:
                do
                {
                    printf("\n== Menu de Agendamentos ==\nO que você deseja fazer?\n[1] Novo Agendamento\n[2] Consultar / Cancelar Agendamento\n[3] Ver Calendário do Dia\n[0] Voltar ao Menu Principal\n");
                    scanf("%d", &opcoesubmenu);
                    switch (opcoesubmenu)
                    {
                        case 1:
                            printf("\n== Novo Agendamento ==\n");
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
                            printf("\n== Novo Agendamento ==\n");
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
                    printf("\n== Menu de Solicitantes ==\nO que você deseja fazer?\n[1] Cadastrar Novo Solicitante\n[2] Alterar Solicitante\n[3] Listar Solicitantes\n[0] Voltar ao Menu Principal\n");
                    scanf("%d", &opcoesubmenu);
                    switch (opcoesubmenu)
                    {
                        case 1:
                            printf("\n== Novo Agendamento ==\n");
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