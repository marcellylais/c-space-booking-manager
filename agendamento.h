#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#include "datas.h" /* Inclui a struct data e funções relacionadas */
#include "espacocomum.h"  /* Inclui a struct espacocomum e funções relacionadas */


/* Registro para armazenar os agendamentos */
typedef struct agendamento
{
    int unidade_solicitante; 
    int id_do_espaco;
    data data_agendamento;
    struct agendamento *ant;
    struct agendamento *prox;
} agendamento;


agendamento* criaListaAgendamentos();
int verificarDisponibilidade(agendamento *listaCabeca, int idEspaco, data dataCheck);
void insereAgendamentoOrdenado(agendamento *listaCabeca, agendamento *novoAgendamento);
void cadastrarNovoAgendamento(agendamento *listaCabecaAg, espacocomum *listaCabecaEsp);
void listarAgendamentosPorPeriodo(agendamento *listaCabeca, data dataInicio, data dataFim);
void verCalendarioDoDia(agendamento *listaCabeca);
void removeAgendamento(agendamento *noParaApagar);
void consultarECancelarAgendamento(agendamento *listaCabeca);
void menuagendamento(agendamento *lista_agendamentos, espacocomum *lista_espacos);

#endif /* Fim do agendamento.h */