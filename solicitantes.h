#ifndef SOLICITANTE_H
#define SOLICITANTE_H

struct agendamento;  /*Declaração antecipada para evitar dependências circulares*/ 

/*Registro dos dados para solicitantes*/
typedef struct solicitante
{
    int unidade;
    char nome[100];
    char email[100];
    char telefone[15];
    struct solicitante *ant;
    struct solicitante *prox;
} solicitante;


/*funções internas para criação e organização dos solicitantes*/
solicitante* criaListaSolicitantes();
void insereSolicitanteOrdenado(solicitante *listaCabeca, solicitante *novoSolicitante);
solicitante* buscarSolicitantePorUnidade(solicitante *listaCabeca, int unidadeBusca);

/* Funções de "menu" (interação com usuário) */
void cadastrarNovoSolicitante(solicitante *listaCabeca);
void alterarSolicitante(solicitante *listaCabeca);
void listarTodosSolicitantes(solicitante *listaCabeca);
void menuSolicitantes(solicitante *lista_solicitantes, struct agendamento *listaCabecaAg);
void removeSolicitante(solicitante *noParaApagar);
void menuExcluirSolicitante(solicitante* listaCabecaSol, struct agendamento *listaCabecaAg);


#endif