#ifndef SOLICITANTE_H
#define SOLICITANTE_H


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
void menuSolicitantes(solicitante *lista_solicitantes);
void cadastrarNovoSolicitante(solicitante *listaCabeca);
void alterarSolicitante(solicitante *listaCabeca);
void listarTodosSolicitantes(solicitante *listaCabeca);


#endif