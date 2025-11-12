#include <stdio.h> 
#include <string.h> /*para alterar nome e descrição dos espaços*/
#include <stdlib.h> /* Para malloc e free*/
#include "espacocomum.h"

/*Cria ponteiro para lista de espaços, ponteiro vazio pois será uma lista com cabeça*/
espacocomum* criaListaEspacos()
{
    /*Aloca memória para a cabeça*/
    espacocomum *no = (espacocomum*) malloc(sizeof(espacocomum));
    
    if (no != NULL) {
        /*A lista começa vazia, apontando para nada dos dois lados.*/
        no->prox = NULL;
        no->ant = NULL; 
    }
    return no;
}

/* Insere um novo espaco na lista (com cabeça), mantendo a ordem crescente pelo 'id_espaco'
   Utilizado Insertion Sort com eficiencia O(n) pois a lista já está ordenada*/
void insereEspacoOrdenado(espacocomum *listaCabeca, espacocomum *novoEspaco)
{
    espacocomum *anterior = listaCabeca; 
    espacocomum *atual = listaCabeca->prox; 

    novoEspaco->prox = NULL;
    novoEspaco->ant = NULL;

    /*Procura a posição*/ 
    while (atual != NULL && novoEspaco->id_espaco > atual->id_espaco)
    {
        anterior = atual;
        atual = atual->prox;
    }

    /* Novo agendamento será inserido entre 'anterior' e 'atual'*/
    novoEspaco->prox = atual;
    novoEspaco->ant = anterior;
    anterior->prox = novoEspaco;

    if (atual != NULL)
    {
        atual->ant = novoEspaco;
    }
}

/* Busca um espaco pelo ID, retorna um ponteiro para o nó se achar e retorna NULL se não achar.
   Pior caso: O(n)*/
espacocomum* buscarEspacoPorID(espacocomum *listaCabeca, int idBusca)
{
    espacocomum *atual = listaCabeca->prox; /* Pula a cabeça */
    int continuarProcurando = 1; /*variavel de parada acaso já encontrar espaço*/

    while (atual != NULL && continuarProcurando == 1)
    {
        if (atual->id_espaco == idBusca)
        {
            /* Encontrado!*/
            return atual;
        } 
        
        if (atual->id_espaco > idBusca)
        {
            /* A ID do 'atual' já é maior que a ID buscada, como a lista é ordenada, não será encontrado*/
            continuarProcurando = 0;
        }

        if (continuarProcurando == 1)
        {
            atual = atual->prox;
        }
    }

    /* Se saiu do loop não encontrou */
    return NULL; 
}

/* Pergunta ao usuário os dados de um novo espaço,
 verifica se o ID já existe e se não existe o cadastra. */
void cadastrarNovoEspaco(espacocomum *listaCabeca)
{
    int idespaco;
    espacocomum *novo; /* Ponteiro para o novo nó */
    
    printf("\n== Cadastrar Novo Espaco ==\n");
    printf("Digite o ID (numerico) para o novo espaco:\n");
    scanf("%d", &idespaco);

    /*Checa se o ID já está em uso e sai da função*/
    if (buscarEspacoPorID(listaCabeca, idespaco) != NULL)
    {
        printf("ERRO: O ID %d ja esta sendo usado por outro espaco.\n", idespaco);
        return;
    }

    /*Se o ID está livre, aloca memória */
    novo = (espacocomum*) malloc(sizeof(espacocomum));
    if (novo == NULL)/*verificação se memória foi alocada*/
    {
        printf("ERRO CRITICO: Falha de alocacao de memoria para espaço!\n");
        return;
    }

    /*Preenche os dados*/
    novo->id_espaco = idespaco; /* Guarda o ID que já validamos */

    printf("Digite o Nome do espaco:\n");
    scanf(" %[^\n]", novo->nome); 

    printf("Digite uma breve Descricao:\n");
    scanf(" %[^\n]", novo->descricao);

    printf("Digite a Capacidade (numero de pessoas):\n");
    scanf("%d", &novo->capacidade);

    /*Insere na lista ordenada */
    insereEspacoOrdenado(listaCabeca, novo);

    printf("\nEspaco '%s' (ID: %d) cadastrado com sucesso!\n", novo->nome, novo->id_espaco);
}

/* Permite alterar os dados de um espaço existente, através de um sub-menu */
void alterarEspaco(espacocomum *listaCabeca)
{
    int idespaco;
    espacocomum *noParaAlterar;
    int opcaoAlterar; /* Variavel para o sub-menu */

    printf("\n== Alterar Espaco ==\n");
    /* Pessoa digita o ID do espaco */
    printf("Digite o ID do espaco que deseja alterar (ou 0 para cancelar): ");
    scanf("%d", &idespaco);

    if (idespaco == 0)
    {
        return; /* Sai da função */
    }

    /* Busca o espaço */
    noParaAlterar = buscarEspacoPorID(listaCabeca, idespaco);

    if (noParaAlterar == NULL)
    {
        printf("ERRO: Espaco com ID %d nao encontrado.\n", idespaco);
        return;
    }

    /* Se encontrou, inicia o sub-menu de alteração */
    do
    {
        /* Informa o espaço a ser alterado e mostra as opções */
        printf("\n--- Alterando Espaco (ID: %d) ---\n", noParaAlterar->id_espaco);
        printf(" [1] Nome: \t\t%s\n", noParaAlterar->nome);
        printf(" [2] Descricao: \t%s\n", noParaAlterar->descricao);
        printf(" [3] Capacidade: \t%d pessoas\n", noParaAlterar->capacidade);
        printf(" [0] Concluir (Cancelar operacao de alteracao)\n");
        printf("----------------------------------\n");
        printf("Qual campo deseja alterar? ");
        scanf("%d", &opcaoAlterar);

        /* A pessoa decide e pode digitar a alteração */
        switch (opcaoAlterar) {
            case 1:
                printf("Digite o NOVO Nome: ");
                scanf(" %[^\n]", noParaAlterar->nome); 
                printf("Nome alterado.\n");
                break;
            case 2:
                printf("Digite a NOVA Descricao: ");
                scanf(" %[^\n]", noParaAlterar->descricao);
                printf("Descricao alterada.\n");
                break;
            case 3:
                printf("Digite a NOVA Capacidade: ");
                scanf("%d", &noParaAlterar->capacidade);
                printf("Capacidade alterada.\n");
                break;
            case 0:
                printf("Alteracoes concluidas para o ID %d.\n", idespaco
        );
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcaoAlterar != 0); /* O loop continua até o usuário digitar 0 */
}

/* Mostra uma lista com ID e Nome de todos os espaços cadastrados. */
void listarEspacosSimples(espacocomum *listaCabeca)
{
    espacocomum *atual = listaCabeca->prox; /* Começa no primeiro item após cabeça */

    if (atual == NULL) {
        printf("\nAVISO: Nenhum espaco comum foi cadastrado ainda.\n");
        return;
    }

    printf("\n--- Espacos Disponiveis ---\n");
    while (atual != NULL) {
        printf("  ID: %d - Nome: %s - Descri??o: %s - Capacidade: %d\n", atual->id_espaco, atual->nome, atual->descricao, atual->capacidade);
        atual = atual->prox;
    }
    printf("---------------------------\n");
}

/* Exibe o menu de gerenciamento de espaços e chama as funções correspondentes */
void menuEspacos(espacocomum *lista_espacos)
{
    int opcoesubmenu;

    do
    {
        printf("\n== Menu de Espacos Comuns ==\nO que voce deseja fazer?\n"
               "[1] Cadastrar Novo Espaco\n"
               "[2] Alterar Espaco\n"
               "[3] Listar Todos os Espacos\n"
               "[0] Voltar ao Menu Principal\n");
        scanf("%d", &opcoesubmenu);

        switch (opcoesubmenu)
        {
            case 1:
                /* Chama a função de cadastrar novo espaço */
                cadastrarNovoEspaco(lista_espacos);
                break;
            case 2:
                /* Chama a função de alterar espaço */
                alterarEspaco(lista_espacos);
                break;
            case 3:
                /* Chama a função de listar todos os espaços */
                listarEspacosSimples(lista_espacos);
                break;
            case 0:
                /* Finaliza o loop */
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcoesubmenu != 0);
}

