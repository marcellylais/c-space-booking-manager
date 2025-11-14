/************************************************
*                                               *
* Nome: Marcelly Lais Ferreira de Almeida       *
* Trabalho Prático                              *
* Disciplinas: Algoritmos e Programação II      *
* Laboratório de Algoritmos e Programação II    *
* Professores: Ivone e Ronaldo                  *
* Data: 14/11/2025                              *
* Versão: 1                                     *
* Descrição: Arquivo principal do sistema.      *
* Contem a funcao 'main', o loop do menu        *
* principal, a inicializacao e a finalizacao    *
* (salvamento/liberacao) das listas.            *
*                                               *
*************************************************/ 

/* Bibliotecas principais */
#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <time.h> 
#include <locale.h> 

/* INCLUI TODAS BIBLIOTECAS (.h) */
#include "datas.h"
#include "agendamento.h"
#include "solicitantes.h"
#include "espacocomum.h"
#include "relatorios.h"
#include "persistencia.h"


int main()
{    
    int opcao, salvar;
    
    /* Declara os ponteiros para as listas */
    solicitante *lista_solicitantes;
    espacocomum *lista_espacos;
    agendamento *lista_agendamentos;

    /* Criação das listas*/
    lista_solicitantes = criaListaSolicitantes();
    lista_espacos = criaListaEspacos();
    lista_agendamentos = criaListaAgendamentos();
    
    /* Checagem para verificar se todas listas foram criadas */
    if (lista_solicitantes == NULL || lista_espacos == NULL || lista_agendamentos == NULL)
    {
        printf("ERRO 1: Falha ao alocar memoria para as listas.\n");
        return 1; /* Encerra o programa*/
    }
    
    /* Carrega os dados salvos em disco */
    carregarDados(lista_espacos, lista_solicitantes,  lista_agendamentos);

    do{
        printf("== SISTEMA DE CONTROLE AGENDAMENTOS DE AREAS ==\nO que voce deseja fazer?\n");
        printf("[1] Agendamentos\n[2] Gerenciar Espacos\n[3] Gerenciar Solicitantes\n[4] Relatorios\n[0] Sair\n");
        scanf("%d", &opcao); 

        switch (opcao)
        {
            case 1:
                menuagendamento(lista_agendamentos, lista_espacos, lista_solicitantes);
                break;
            case 2:
                menuEspacos(lista_espacos, lista_agendamentos);
                break;
            case 3:
                menuSolicitantes(lista_solicitantes, lista_agendamentos);
                break;
            case 4:
                menuRelatorios(lista_agendamentos, lista_solicitantes, lista_espacos);
                break;
            case 0:
                salvar = salvarDados(lista_espacos, lista_solicitantes, lista_agendamentos);
                if (salvar != 0)
                {
                    printf("ERRO 2: Falha ao salvar os dados no disco.\n");
                    opcao = -1; /* Mantem o loop para tentar salvar novamente */
                }
                else
                {
                    printf("Saindo do sistema.\n");
                }
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }while(opcao != 0);
    
    /* ASQUIIIIIIIIIIIIII Libera a memoria alocada para as listas antes de encerrar o programa */
    /*liberaListaAgendamentos(lista_agendamentos);*/

    return 0;
}