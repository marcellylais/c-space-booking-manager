#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "agendamento.h"
#include "solicitantes.h"
#include "espacocomum.h"
#include "datas.h"

typedef struct relatorio
{
    struct agendamento *listaAgendamentos;
    struct solicitante *listaSolicitantes;
    struct espacocomum *listaEspacos;
    struct relatorio *prox;
} relatorio;

/* Relatórios específicos */
void impressaoRelatorio(relatorio *rel);
void relatorioPorData(agendamento *listaAg, solicitante *listaSol, espacocomum *listaEsp);
void relatorioPorSolicitante(agendamento *listaAg, solicitante *listaSol, espacocomum *listaEsp);
void relatorioPorEspaco(agendamento *listaAg, solicitante *listaSol, espacocomum *listaEsp);


/* Menu principal de relatórios */
void menuRelatorios(agendamento *listaAg, solicitante *listaSol, espacocomum *listaEsp);

#endif