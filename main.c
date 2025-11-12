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


int main()
{    
    int opcao;
    
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
    
    do{
        printf("== SISTEMA DE CONTROLE AGENDAMENTOS DE AREAS ==\nO que voce deseja fazer?\n");
        printf("[1] Agendamentos\n[2] Gerenciar Espacos\n[3] Gerenciar Solicitantes\n[4] Relatorios\n[0] Sair\n");
        scanf("%d", &opcao); 

        switch (opcao)
        {
            case 1:
                menuagendamento(lista_agendamentos, lista_espacos);
                break;
            case 2:
                menuEspacos(lista_espacos);
                break;
            case 3:
                menuSolicitantes(lista_solicitantes);
                break;
            case 4:
                menuRelatorios(lista_agendamentos, lista_solicitantes, lista_espacos);
                break;
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }while(opcao != 0);
    
    return 0;
}