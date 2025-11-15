/*****************************************************************
*                                                                *
* Nome: Marcelly Lais Ferreira de Almeida                        *
* Trabalho Prático                                               *
* Disciplinas: Algoritmos e Programação II                       *
* Laboratório de Algoritmos e Programação II                     *
* Professores: Ivone e Ronaldo                                   *
* Data: 14/11/2025                                               *
* Versão: 1                                                      *
* Descrição: Implementa o modulo de geracao de relatorios.       *
* Contem as funcoes para cruzar dados (JOIN manual) das listas   *
* e exibir relatorios por Data, Solicitante e Espaco.            *
*                                                                *
******************************************************************/ 

#include "relatorios.h"
#include "agendamento.h"
#include "solicitantes.h"
#include "espacocomum.h"
#include "datas.h"
#include <stdio.h>
#include <stdlib.h>

void impressaoRelatorio(relatorio *rel, char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    relatorio *atual = rel, *aux;
    if (arquivo == NULL)
    {
        printf("ERRO: Nao foi possivel criar o arquivo %s para salvar o relatorio.\n", nome_arquivo);
        return;
    }

    if (atual == NULL)
    {
        return;
    }

    fprintf(arquivo, "== Relatorio de Agendamentos ==\n");
    printf("\n== Relatorio de Agendamentos ==\n");

    while (atual != NULL)
    {
        /*ESCREVE NO ARQUIVO*/
        fprintf(arquivo, "----------------------------------------\n");
        fprintf(arquivo, " Unidade Solicitante: %d\n", atual->listaSolicitantes->unidade);
        fprintf(arquivo, " Nome Solicitante: %s\n", atual->listaSolicitantes->nome);
        fprintf(arquivo, " Espaco Comum: %s (ID: %d)\n", atual->listaEspacos->nome, atual->listaEspacos->id_espaco);
        fprintf(arquivo, " Data do Agendamento: %02d/%02d/%d\n",
                atual->listaAgendamentos->data_agendamento.dia,
                atual->listaAgendamentos->data_agendamento.mes,
                atual->listaAgendamentos->data_agendamento.ano);
        /*IMPRIME NA TELA*/
        printf("----------------------------------------\n");
        printf(" Unidade Solicitante: %d\n", atual->listaSolicitantes->unidade);
        printf(" Nome Solicitante: %s\n", atual->listaSolicitantes->nome);
        printf(" Espaco Comum: %s (ID: %d)\n", atual->listaEspacos->nome, atual->listaEspacos->id_espaco);
        printf(" Data do Agendamento: %02d/%02d/%d\n",
               atual->listaAgendamentos->data_agendamento.dia,
               atual->listaAgendamentos->data_agendamento.mes,
               atual->listaAgendamentos->data_agendamento.ano);
        aux = atual;
        atual = atual->prox;
        /* Libera o nó atual */
        free(aux);
    }
    fprintf(arquivo, "----------------------------------------\n");
    fclose(arquivo);
    printf("----------------------------------------\n");
    printf("Relatorio salvo no arquivo %s com sucesso.\n", nome_arquivo);

}

/* Implementação do relatório por data */
void relatorioPorData(agendamento *listaAg, solicitante *listaSol, espacocomum *listaEsp)
{
    data data_inicio, data_fim;
    printf("Qual será a data início? (DD/MM/AAAA)\n");
    scanf("%d/%d/%d", &data_inicio.dia, &data_inicio.mes, &data_inicio.ano);
    printf("Qual será a data fim? (DD/MM/AAAA)\n");
    scanf("%d/%d/%d", &data_fim.dia, &data_fim.mes, &data_fim.ano);

    listarAgendamentosPorPeriodo(listaAg, data_inicio, data_fim);

}

/* Implementação do relatório por solicitante */
void relatorioPorSolicitante(agendamento *listaAg, solicitante *listaSol, espacocomum *listaEsp)
{
    relatorio *rel, *nova, *no_para_liberar;
    char nome_arquivo[100];
    int unidade_solicitante, auxverifica = 0;
    solicitante *solicitanteauxiliar;
    agendamento *agenda = listaAg->prox; /* Pula o nó-cabeça */

    rel = NULL;

    printf("Digite a unidade do solicitante para gerar o relatorio:\n");
    scanf("%d", &unidade_solicitante);
    solicitanteauxiliar = buscarSolicitantePorUnidade(listaSol, unidade_solicitante);
    if (solicitanteauxiliar == NULL)
    {
        printf("ERRO: Solicitante da Unidade %d nao encontrado.\n", unidade_solicitante);
        return;
    }
    if (agenda == NULL)
    {
        printf("Não há nenhum agendamento registrado para nenhuma unidade.\n");
        return;
    }

    printf("Digite o nome do arquivo para salvar o relatorio:\n");
    scanf("%s", nome_arquivo);

    while (agenda != NULL)
    {
        if (agenda->unidade_solicitante == unidade_solicitante)
        {
            auxverifica = 1;
            nova = (relatorio*) malloc(sizeof(relatorio));
            if (nova == NULL)
            {
                printf("ERRO: Falha ao alocar memoria para o relatorio.\n");
                return;  
            }
            nova->listaAgendamentos = agenda;
            nova->listaSolicitantes = solicitanteauxiliar;
            /* Busca o espaço comum relacionado ao agendamento */
            nova->listaEspacos = buscarEspacoPorID(listaEsp, agenda->id_do_espaco);
            nova->prox = rel;
            rel = nova;
        }
        agenda = agenda->prox;
    }

    if(auxverifica != 1)
    {
        printf("Nao ha agendamentos para a unidade %d.\n", unidade_solicitante);
        return;
    }

    impressaoRelatorio(rel, nome_arquivo);

    while (rel != NULL)
    {
        no_para_liberar = rel;      /* Guarda o nó atual */
        rel = rel->prox;            /* Avança a cabeça da pilha */
        free(no_para_liberar);      /* Libera o nó guardado */
    }

}

void relatorioPorEspaco(agendamento *listaAg, solicitante *listaSol, espacocomum *listaEsp)
{
    relatorio *rel, *nova, *no_para_liberar;
    char nome_arquivo[100];
    int espacosolicitante, auxverifica = 0;
    espacocomum *espacoauxiliar;
    agendamento *agenda = listaAg->prox; /* Pula o nó-cabeça */

    rel = NULL;

    printf("Digite o id do espaco para gerar o relatorio:\n");
    scanf("%d", &espacosolicitante);
    espacoauxiliar = buscarEspacoPorID(listaEsp, espacosolicitante);
    if (espacoauxiliar == NULL)
    {
        printf("Espaco %d nao encontrado.\n", espacosolicitante);
        return;
    }
    if (agenda == NULL)
    {
        printf("Não há nenhum agendamento registrado para nenhum espaço.\n");
        return;
    }

    printf("Digite o nome do arquivo para salvar o relatorio:\n");
    scanf("%s", nome_arquivo);
    /*aqui irei perguntar o nome do arquivo do relatorio que a pessoa deseja salvar, mando como pareamento
    para função de impressão e salvo o arquivo com o nome indicado em txt*/

    while (agenda != NULL)
    {
        if (agenda->id_do_espaco == espacosolicitante)
        {
            auxverifica = 1;
            nova = (relatorio*) malloc(sizeof(relatorio));
            if (nova == NULL)
            {
                printf("ERRO: Falha ao alocar memoria para o relatorio.\n");
                return;  
            }
            nova->listaAgendamentos = agenda;
            /* Busca o solicitante relacionado ao agendamento */
            nova->listaSolicitantes = buscarSolicitantePorUnidade(listaSol, agenda->unidade_solicitante);
            nova->listaEspacos = espacoauxiliar;
            nova->prox = rel;
            rel = nova;
        }
        agenda = agenda->prox;
    }

    if(auxverifica != 1)
    {
        printf("Nao ha agendamentos para o espaco %d.\n", espacosolicitante);
        return;
    }

    impressaoRelatorio(rel, nome_arquivo);

    while (rel != NULL)
    {
        no_para_liberar = rel;      /* Guarda o nó atual */
        rel = rel->prox;            /* Avança a cabeça da pilha */
        free(no_para_liberar);      /* Libera o nó guardado */
    }

}

/* Menu principal de relatórios */
void menuRelatorios(agendamento *listaAg, solicitante *listaSol, espacocomum *listaEsp)
{
    int opcoesubmenu;
    do
    {
        printf("\n== Menu de Relatorios ==\nO que você deseja fazer?\n"
               "[1] Relatorio por Data\n"
               "[2] Relatorio por Solicitante\n"
               "[3] Relatorio por Espaco Comum\n"
               "[0] Voltar ao Menu Principal\n");
        scanf("%d", &opcoesubmenu);
        
        switch (opcoesubmenu)
        {
            case 1:
                relatorioPorData(listaAg, listaSol, listaEsp);
                break;
            case 2:
                relatorioPorSolicitante(listaAg, listaSol, listaEsp);
                break;
            case 3:
                relatorioPorEspaco(listaAg, listaSol, listaEsp);
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
