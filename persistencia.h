#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

/* Inclui os cardápios para conhecer as structs */
#include "espacocomum.h"
#include "solicitantes.h"
#include "agendamento.h"

int salvarEspacos(espacocomum *lista);
int salvarSolicitantes(solicitante *lista);
int salvarAgendamentos(agendamento *lista);
void carregarEspacos(espacocomum *listaCabeca);
void carregarSolicitantes(solicitante *listaCabeca);
void carregarAgendamentos(agendamento *listaCabeca);
int salvarDados(espacocomum *listaEsp, solicitante *listaSol, agendamento *listaAg);
void carregarDados(espacocomum *listaEsp, solicitante *listaSol, agendamento *listaAg);

#endif