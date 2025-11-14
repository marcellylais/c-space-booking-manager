/*********************************************************************
*                                                                    *
* Nome: Marcelly Lais Ferreira de Almeida                            *
* Trabalho Prático                                                   *
* Disciplinas: Algoritmos e Programação II                           *
* Laboratório de Algoritmos e Programação II                         *
* Professores: Ivone e Ronaldo                                       *
* Data: 14/11/2025                                                   *
* Versão: 1                                                          *
* Descrição: Implementa as funcoes de persistencia de dados.         *
* Contem as rotinas 'salvarDados' (fwrite) e 'carregarDados' (fread) *
* para salvar e ler o estado do sistema em arquivos binarios (.dat). *
*                                                                    *
**********************************************************************/  

#include <stdio.h>
#include <stdlib.h>
#include "persistencia.h"


int salvarEspacos(espacocomum *lista)
{
    FILE *arquivo = fopen("espacos.dat", "wb"); /* escrita em binário */
    espacocomum *atual = lista->prox; /* Pula a cabeça */

    if (arquivo == NULL)
    {
        printf("Erro ao abrir 'espacos.dat' para gravacao.\n");
        return 1;
    }

    while (atual != NULL)
    {
        /* Grava o conteudo do no (struct) direto no arquivo binario */
        fwrite(atual, sizeof(espacocomum), 1, arquivo);
        atual = atual->prox;
    }
    fclose(arquivo);
    return 0;
}

int salvarSolicitantes(solicitante *lista)
{
    FILE *arquivo = fopen("solicitantes.dat", "wb"); /* escrita em binário */
    solicitante *atual = lista->prox;

    if (arquivo == NULL)
    {
        printf("Erro ao abrir 'solicitantes.dat' para gravacao.\n");
        return 1;
    }

    while (atual != NULL) {
        fwrite(atual, sizeof(solicitante), 1, arquivo);
        atual = atual->prox;
    }
    fclose(arquivo);
    return 0;
}

int salvarAgendamentos(agendamento *lista)
{
    FILE *arquivo = fopen("agendamentos.dat", "wb"); /* escrita em binário */
    agendamento *atual = lista->prox;

    if (arquivo == NULL)
    {
        printf("Erro ao abrir 'agendamentos.dat' para gravacao.\n");
        return 1;
    }

    while (atual != NULL)
    {
        fwrite(atual, sizeof(agendamento), 1, arquivo);
        atual = atual->prox;
    }
    fclose(arquivo);
    return 0;
}

void carregarEspacos(espacocomum *listaCabeca) {
    FILE *arquivo = fopen("espacos.dat", "rb"); /* Ler Binário */
    espacocomum temp; /* Variavel temporaria para ler do disco */
    
    if (arquivo == NULL) return; /* Arquivo nao existe (primeira vez), segue o jogo */

    /* Enquanto conseguir ler 1 struct inteira */
    while (fread(&temp, sizeof(espacocomum), 1, arquivo) == 1)
    {
        /* Cria um NOVO no na memoria */
        espacocomum *novo = (espacocomum*) malloc(sizeof(espacocomum));
        
        /* Copia os DADOS (ID, nome, etc) */
        *novo = temp; 
        
        /* Limpa os ponteiros (que vieram com lixo do arquivo) */
        novo->prox = NULL;
        novo->ant = NULL;

        /* Usa funcao para inserir na lista corretamente */
        insereEspacoOrdenado(listaCabeca, novo);
    }
    fclose(arquivo);
    printf("Espacos carregados com sucesso.\n");
}

void carregarSolicitantes(solicitante *listaCabeca) {
    FILE *arquivo = fopen("solicitantes.dat", "rb");
    solicitante temp;
    
    if (arquivo == NULL) return;

    while (fread(&temp, sizeof(solicitante), 1, arquivo) == 1) {
        solicitante *novo = (solicitante*) malloc(sizeof(solicitante));
        *novo = temp;
        novo->prox = NULL;
        novo->ant = NULL;
        insereSolicitanteOrdenado(listaCabeca, novo);
    }
    fclose(arquivo);
    printf("Solicitantes carregados com sucesso.\n");
}

void carregarAgendamentos(agendamento *listaCabeca) {
    FILE *arquivo = fopen("agendamentos.dat", "rb");
    agendamento temp;
    
    if (arquivo == NULL) return;

    while (fread(&temp, sizeof(agendamento), 1, arquivo) == 1) {
        agendamento *novo = (agendamento*) malloc(sizeof(agendamento));
        *novo = temp;
        novo->prox = NULL;
        novo->ant = NULL;
        insereAgendamentoOrdenado(listaCabeca, novo);
    }
    fclose(arquivo);
    printf("Agendamentos carregados com sucesso.\n");
}

int salvarDados(espacocomum *listaEsp, solicitante *listaSol, agendamento *listaAg)
{
    int result;
    printf("\nSalvando dados...\n");
    result = salvarEspacos(listaEsp) + salvarSolicitantes(listaSol) + salvarAgendamentos(listaAg);
    printf("Dados salvos com sucesso!\n");
    return result;
}

void carregarDados(espacocomum *listaEsp, solicitante *listaSol, agendamento *listaAg) {
    printf("\nCarregando dados do sistema...\n");
    carregarEspacos(listaEsp);
    carregarSolicitantes(listaSol);
    carregarAgendamentos(listaAg);
    printf("Inicializacao concluida.\n");
}