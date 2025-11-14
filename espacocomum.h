#ifndef ESPACOCOMUM_H
#define ESPACOCOMUM_H

struct agendamento;  /*Declaração antecipada para evitar dependências circulares*/ 


/*Registro dos dados para espaços*/
typedef struct espacocomum
{
    int id_espaco;
    char nome[100];
    char descricao[300];
    int capacidade;
    struct espacocomum *ant;
    struct espacocomum *prox;
} espacocomum;

/*funções internas para criação e organização da lista de espaços*/
espacocomum* criaListaEspacos();
void insereEspacoOrdenado(espacocomum *listaCabeca, espacocomum *novoEspaco);
espacocomum* buscarEspacoPorID(espacocomum *listaCabeca, int idBusca);

/* Funções de "menu" (interação com usuário) */
void cadastrarNovoEspaco(espacocomum *listaCabeca);
void alterarEspaco(espacocomum *listaCabeca);
void listarEspacosSimples(espacocomum *listaCabeca);
void removeEspaco(espacocomum *noParaApagar);
void menuExcluirEspaco(espacocomum *listaCabecaEsp, struct agendamento *listaCabecaAg);
void menuEspacos(espacocomum *lista_espacos, struct agendamento *lista_agendamentos);

#endif