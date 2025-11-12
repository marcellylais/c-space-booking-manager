/************************************************
*                                               *
* Nome: Marcelly Lais Ferreira de Almeida       *
* Trabalho Prático                              *
* Disciplinas: Algoritmos e Programação II      *
* Laboratório de Algoritmos e Programação II    *
* Professores: Ivone e Ronaldo                  *
* Data: 14/11/2025                              *
* Versão: 1                                     *
* Descrição:                                    *
*                                               *
*************************************************/ 
#include "solicitantes.h"
#include <stdio.h>
#include <stdlib.h>

/*Cria ponteiro para lista de solicitantes, ponteiro vazio pois será uma lista com cabeça*/
solicitante* criaListaSolicitantes()
{
    /* Aloca memoria para a cabeca */
    solicitante *no = (solicitante*) malloc(sizeof(solicitante));
    
    if (no != NULL) {
        /* A lista comeca vazia */
        no->prox = NULL;
        no->ant = NULL; 
    }
    return no;
}

/* Insere uma novo solicitante na lista (com cabeça), mantendo a ordem crescente pelo 'id_espaco'
   Utilizado Insertion Sort com eficiencia O(n) pois a lista já está ordenada*/
void insereSolicitanteOrdenado(solicitante *listaCabeca, solicitante *novoSolicitante) 
{
    solicitante *anterior = listaCabeca; 
    solicitante *atual = listaCabeca->prox; 

    novoSolicitante->prox = NULL;
    novoSolicitante->ant = NULL;

    /* Procura a posicao pela 'unidade' */
    while (atual != NULL && novoSolicitante->unidade > atual->unidade)
    {
        anterior = atual;
        atual = atual->prox;
    }

    /* Novo solicitante será inserido entre 'anterior' e 'atual'*/
    novoSolicitante->prox = atual;
    novoSolicitante->ant = anterior;
    anterior->prox = novoSolicitante;

    if (atual != NULL)
    {
        atual->ant = novoSolicitante;
    }
}

/* Busca um solicitante pela unidade, retorna um ponteiro para o nó se achar e retorna NULL se não achar.
   Pior caso: O(n)*/
solicitante* buscarSolicitantePorUnidade(solicitante *listaCabeca, int unidadeBusca) 
{
    solicitante *atual = listaCabeca->prox; /* Pula o no-cabeca */
    int continuarProcurando = 1; /*variavel de parada acaso já encontrar espaço*/

    while (atual != NULL && continuarProcurando == 1) {
        if (atual->unidade == unidadeBusca)
        {
            /* Encontrado! */
            return atual;
        } 
        
        if (atual->unidade > unidadeBusca)
        {
            /* A ID do 'atual' já é maior que a ID buscada, como a lista é ordenada, não será encontrado*/
            continuarProcurando = 0;
        }

        if (continuarProcurando == 1) {
            atual = atual->prox;
        }
    }
    return NULL; /* Nao encontrou */
}

/* Pergunta ao usuario os dados de um novo solicitante,
 * verifica se a 'unidade' ja existe, e o cadastra. */
void cadastrarNovoSolicitante(solicitante *listaCabeca) 
{
    int idunidade;
    solicitante *novo;
    
    printf("\n== Cadastrar Novo Solicitante ==\n");
    printf("Digite a Unidade (ex: 101, 202): ");
    scanf("%d", &idunidade);

    /* Checa se a Unidade ja esta em uso */
    if (buscarSolicitantePorUnidade(listaCabeca, idunidade) != NULL)
    {
        printf("ERRO: A Unidade %d ja esta cadastrada.\n", idunidade);
        return; /* sai do cadastramento */
    }

    /* Aloca memoria para unidade*/
    novo = (solicitante*) malloc(sizeof(solicitante));
    if (novo == NULL) {
        printf("ERRO CRITICO: Falha de alocacao de memoria!\n");
        return;
    }

    /* 3. Preenche os dados */
    novo->unidade = idunidade;

    /* Usa o " truque do espaco" para limpar o buffer do scanf */
    printf("Digite o Nome do responsavel: ");
    scanf(" %[^\n]", novo->nome); 

    printf("Digite o E-mail de contato: ");
    scanf(" %[^\n]", novo->email);

    printf("Digite o Telefone de contato (com DDD): ");
    scanf(" %[^\n]", novo->telefone);

    /*Insere na lista ordenada */
    insereSolicitanteOrdenado(listaCabeca, novo);

    printf("\nSolicitante '%s' (Unidade: %d) cadastrado com sucesso!\n", novo->nome, novo->unidade);
}

/* Pede uma 'unidade', busca o solicitante, e permite alterar
 * campos especificos atraves de um sub-menu. */
void alterarSolicitante(solicitante *listaCabeca) 
{
    int idunidade;
    solicitante *noParaAlterar;
    int opcaoAlterar;

    printf("\n== Alterar Solicitante ==\n");
    printf("Digite a Unidade do solicitante que deseja alterar (ou 0 para cancelar): ");
    scanf("%d", &idunidade);

    if (idunidade == 0)
    {
        return; /* Sai da funcao */
    }

    /*Busca a unidade */
    noParaAlterar = buscarSolicitantePorUnidade(listaCabeca, idunidade);

    if (noParaAlterar == NULL) {
        printf("ERRO: Solicitante da Unidade %d nao encontrado.\n", idunidade);
        return;
    }

    /* 2. Se encontrou, inicia o sub-menu de alteracao */
    do {
        printf("\n--- Alterando Solicitante (Unidade: %d) ---\n", noParaAlterar->unidade);
        printf(" [1] Nome: \t%s\n", noParaAlterar->nome);
        printf(" [2] E-mail: \t%s\n", noParaAlterar->email);
        printf(" [3] Telefone: \t%s\n", noParaAlterar->telefone);
        printf(" [0] Concluir Alteracoes (Voltar)\n");
        printf("----------------------------------\n");
        printf("Qual campo deseja alterar? ");
        scanf("%d", &opcaoAlterar);

        switch (opcaoAlterar)
        {
            case 1:
                printf("Digite o NOVO Nome: ");
                scanf(" %[^\n]", noParaAlterar->nome); 
                printf("Nome alterado.\n");
                break;
            case 2:
                printf("Digite o NOVO E-mail: ");
                scanf(" %[^\n]", noParaAlterar->email);
                printf("E-mail alterado.\n");
                break;
            case 3:
                printf("Digite o NOVO Telefone: ");
                scanf(" %[^\n]", noParaAlterar->telefone);
                printf("Telefone alterado.\n");
                break;
            case 0:
                printf("Alteracoes concluidas para a Unidade %d.\n", idunidade);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcaoAlterar != 0);
}

/* Mostra a lista de solicitantes e todos os dados. */
void listarTodosSolicitantes(solicitante *listaCabeca) 
{
    solicitante *atual = listaCabeca->prox; /* Pula o no-cabeca */

    printf("\n== Lista de Todos os Solicitantes Cadastrados ==\n");

    if (atual == NULL)
    {
        printf("Nenhum solicitante cadastrado.\n");
        return;
    }

    while (atual != NULL) {
        printf("----------------------------------------\n");
        printf(" Unidade: \t%d\n", atual->unidade);
        printf(" Nome: \t\t%s\n", atual->nome);
        printf(" E-mail: \t%s\n", atual->email);
        printf(" Telefone: \t%s\n", atual->telefone);
        
        atual = atual->prox;
    }
    printf("----------------------------------------\n");
}

/* Exibe o menu de gerenciamento de solicitantes e chama as funcoes.*/
void menuSolicitantes(solicitante *lista_solicitantes) 
{
    int opcoesubmenu;

    do {
        printf("\n== Menu de Solicitantes ==\nO que voce deseja fazer?\n"
               "[1] Cadastrar Novo Solicitante\n"
               "[2] Alterar Solicitante\n"
               "[3] Listar Todos os Solicitantes\n"
               "[0] Voltar ao Menu Principal\n");
        scanf("%d", &opcoesubmenu);

        switch (opcoesubmenu)
        {
            case 1:
                cadastrarNovoSolicitante(lista_solicitantes);
                break;
            case 2:
                alterarSolicitante(lista_solicitantes);
                break;
            case 3:
                listarTodosSolicitantes(lista_solicitantes);
                break;
            case 0:
                /* encerra o loop */
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcoesubmenu != 0);
}