#include <stdio.h> 
#include <string.h> /* Para manipulação de strings*/
#include <stdlib.h> /* Para malloc e free*/
  
typedef struct 
{ 
    int dia;
    int mes;
    int ano;
} data;

typedef struct solicitante
{
    int unidade;
    char nome[100];
    char email[100];
    char telefone[15];
    struct solicitante *ant;
    struct solicitante *prox;
} solicitante;

typedef struct espacocomum
{
    int id_espaco;
    char nome[100];
    char descricao[255];
    int capacidade;
    struct espacocomum *ant;
    struct espacocomum *prox;
} espacocomum;

typedef struct agendamento
{
    int unidade_solicitante; /* <-- Guarda o ID do solicitante*/
    int id_do_espaco;        /* <-- Guarda o ID do espaco*/
    data data_agendamento;
    struct agendamento *ant;
    struct agendamento *prox;
} agendamento;

/*Criação de nó "cabeça" para a lista de espaços*/
espacocomum* criaListaEspacos()
{
    /*Aloca memória para a cabeça*/
    espacocomum *no = (espacocomum*) malloc(sizeof(espacocomum));
    
    if (no != NULL) {
        /*A lista começa vazia, apontando para nada dos dois lados.*/
        no->prox = NULL;
        no->ant = NULL; 
    }
    return no;
}

/* Cria e retorna o nó para uma lista de agendamentos.*/
agendamento* criaListaAgendamentos() {
    /*Aloca memória para a cabeça*/
    agendamento *no = (agendamento*) malloc(sizeof(agendamento));
    
    if (no != NULL) {
        /* A lista começa vazia, apontando para nada dos dois lados.*/
        no->prox = NULL;
        no->ant = NULL; 
    }
    return no;
}

/* Cria e retorna o nó para uma lista de solicitantes.*/
solicitante* criaListaSolicitantes() {
    /* Aloca memória para a cabeça*/
    solicitante *no = (solicitante*) malloc(sizeof(solicitante));
    
    if (no != NULL) {
        /* A lista começa vazia, apontando para nada dos dois lados.*/
        no->prox = NULL;
        no->ant = NULL; 
    }
    return no;
}

/* Compara duas 'struct data'.
 * Retorna:
   -1  se data1 < data2
   0  se data1 == data2
   1  se data1 > data2
 */
int compararDatas(data data1, data data2)
{
    /* Checa o ano primeiro */
    if (data1.ano < data2.ano) return -1;
    if (data1.ano > data2.ano) return 1;

    /* Anos iguais, checa o mês*/
    if (data1.mes < data2.mes) return -1;
    if (data1.mes > data2.mes) return 1;

    /* Meses iguais, checa o dia*/
    if (data1.dia < data2.dia) return -1;
    if (data1.dia > data2.dia) return 1;

    return 0; /* São iguais*/
}

/* Verifica se um espaço já está ocupado em uma data específica.
 * Retorna 1 se estiver LIVRE.
 * Retorna 0 se estiver OCUPADO.
 */
int verificarDisponibilidade(agendamento *lst, int idEspaco, data dataCheck)
{
    /*Começa a busca no PRIMEIRO NÓ DE DADOS (pula o nó-cabeça)*/
    agendamento *atual = lst->prox;

    /* Verifica a lista de agendamentos */
    while (atual != NULL)
    {
        /*Compara a data do agendamento 'atual' com a data que queremos (dataCheck)*/
        int comp = compararDatas(atual->data_agendamento, dataCheck);

        /*As datas são IDÊNTICAS*/
        if (comp == 0)
        {
            /*Se as datas são iguais, checa se o ESPAÇO também é igual*/
            if (atual->id_do_espaco == idEspaco)
            {
                return 0; /* OCUPADO!*/
            }
            /*Se as datas são iguais, mas o espaço é outro,
            continuamos procurando (pode ter outro agendamento na msm data)*/ 
        } 
        
        /*2. A data do 'atual' já é MAIOR que a data que buscamos*/
        else if (comp > 0)
        {
            /*Como a lista está ordenada, já passamos do ponto.*/
            /* Não há mais como achar a data.*/
            return 1; /*LIVRE!*/
        }

        /* Se comp < 0, a data do 'atual' é antiga. Continua para o próximo.*/
        atual = atual->prox;
    }

    /* Se o loop terminou (chegou ao fim da lista), não achamos nada.*/
    return 1; /*LIVRE!*/ 
}

/* Insere um novo agendamento na lista (com cabeça),
 * mantendo a ordem crescente pela 'data_agendamento'.
 * no é o ponteiro para o nó cabeça.
 */
void insereAgendamentoOrdenado(agendamento *no, agendamento *novoAgendamento)
{
    agendamento *anterior = no; 
    agendamento *atual = no->prox; 

    novoAgendamento->prox = NULL;
    novoAgendamento->ant = NULL;

    /*Procura a posição: (Usando nossa função auxiliar)*/ 
    while (atual != NULL && compararDatas(novoAgendamento->data_agendamento, atual->data_agendamento) > 0) {
        anterior = atual;
        atual = atual->prox;
    }

    /* Novo agendamento será inserido entre 'anterior' e 'atual'*/
    novoAgendamento->prox = atual;
    novoAgendamento->ant = anterior;
    anterior->prox = novoAgendamento;
    if (atual != NULL) {
        atual->ant = novoAgendamento;
    }
}

/* Mostra uma lista com ID e Nome de todos os espaços cadastrados. */
void listarEspacosSimples(espacocomum *listaCabeca)
{
    espacocomum *atual = listaCabeca->prox; /* Começa no primeiro item após cabeça */

    if (atual == NULL) {
        printf("\nAVISO: Nenhum espaco comum foi cadastrado ainda.\n");
        return;
    }

    printf("\n--- Espacos Disponiveis ---\n");
    while (atual != NULL) {
        printf("  ID: %d - Nome: %s\n", atual->id_espaco, atual->nome);
        atual = atual->prox;
    }
    printf("---------------------------\n");
}

/* Função principal para cadastrar um novo agendamento.
 * Pede os dados ao usuário, VERIFICA, aloca memória e insere na lista se disponivel.
 */
void cadastrarNovoAgendamento(agendamento *listaCabeca, espacocomum *listarespacos)
{   
    /* Aloca memória para o novo nó*/
    agendamento *novo = (agendamento*) malloc(sizeof(agendamento));
    if (novo == NULL) /*verificação se memória foi alocada*/
    {
        printf("ERRO: Falha de alocacao de memoria!\n");
        return; 
    }

    /*Coleta os dados do usuário*/
    printf("\n== Novo Agendamento ==\n");
    printf("\nDigite a unidade do solicitante:\n");
    scanf("%d", &novo->unidade_solicitante);

    /* Mostra a lista de espaços para o usuário */
    listarEspacosSimples(listarespacos);

    printf("Digite o ID do espaco desejado: ");
    scanf("%d", &novo->id_do_espaco);

    printf("\nDigite a data do agendamento (DD/MM/AAAA):\n");
    scanf("%d/%d/%d", &novo->data_agendamento.dia, &novo->data_agendamento.mes, &novo->data_agendamento.ano);
    
    /*Verifica se o espaço está disponível na data desejada*/
    if (verificarDisponibilidade(listaCabeca, novo->id_do_espaco, novo->data_agendamento) == 0)
    {
        /*Se a função retornar 0, está ocupado.*/ 
        printf("\nERRO: O espaco %d já esta reservado no dia %02d/%02d/%d.\n", novo->id_do_espaco,
               novo->data_agendamento.dia,
               novo->data_agendamento.mes,
               novo->data_agendamento.ano);
        free(novo); /* libera memoria alocada para agendamento novo!*/
        return;
    }
    
    /* Está livre. Insere o nó na lista ordenada.*/
    insereAgendamentoOrdenado(listaCabeca, novo);

    printf("\nAgendamento para %02d/%02d/%d cadastrado com sucesso!\n",
           novo->data_agendamento.dia,
           novo->data_agendamento.mes,
           novo->data_agendamento.ano);
}

/* Exibe o menu de agendamentos e chama as funções correspondentes.*/
void menuagendamento(agendamento *lista_agendamentos, espacocomum *listarespacos) 
{
    int opcoesubmenu;
    do
    {
        printf("\n== Menu de agendamentos ==\nO que você deseja fazer?\n"
               "[1] Novo agendamento\n"
               "[2] Consultar / Cancelar agendamento\n"
               "[3] Ver Calendário do Dia\n"
               "[0] Voltar ao Menu Principal\n");
        scanf("%d", &opcoesubmenu);
        
        switch (opcoesubmenu)
        {
            case 1:
                /*Chama a função de cadastro, passando a lista */
                cadastrarNovoAgendamento(lista_agendamentos, listarespacos);
                break;
            case 2:
                /* code */
                break;
            case 3:
                /* code */
                break;
            case 0:
                break; /* Para não mostrar "opção inválida" ao sair */
            default:
                printf("Opção inválida. Tente novamente.\n");
            break;
        }
    } while (opcoesubmenu != 0);
}

int main()
{
    int opcao, opcoesubmenu;
    solicitante *lista_solicitantes;
    espacocomum *lista_espacos;
    agendamento *lista_agendamentos;

    /*Criação de lista com cabeça para melhorar funções de inserção*/
    lista_solicitantes = criaListaSolicitantes();
    lista_espacos = criaListaEspacos();
    lista_agendamentos = criaListaAgendamentos();
    
    /*Checagem de segurança se as lista foram iniciadas coma cabeça*/
    if (lista_solicitantes == NULL || lista_espacos == NULL || lista_agendamentos == NULL) {
        printf("ERRO 1: Falha ao alocar memoria para as listas.\n");
        return 1; /* Encerra o programa*/
    }
    
    do{
        printf("== SISTEMA DE CONTROLE agendamentoS DE ÁREAS ==\nO que você deseja fazer?\n");
        printf("[1] agendamentos\n[2] Gerenciar Espaços\n[3] Gerenciar solicitantes\n[4] Relatórios\n[0] Sair\n");
        scanf("%d", &opcao); 

        switch (opcao)
            {
            case 1:
                menuagendamento(lista_agendamentos, lista_espacos);
                break;
            case 2:
                do
                {
                    printf("== Menu de Espaços Comuns ==\nO que você deseja fazer?\n[1] Cadastrar Novo Espaço\n[2] Alterar Espaço\n[3] Listar Todos os Espaços\n[0] Voltar ao Menu Principal\n");
                    scanf("%d", &opcoesubmenu);
                    switch (opcoesubmenu)
                    {
                        case 1:
                            printf("\n== Novo agendamento ==\n");
                            break;
                        case 2:
                            /* code */
                            break;
                        case 3:
                            /* code */
                            break;
                        default:
                        printf("Opção inválida. Tente novamente.\n");
                        break;
                    }
                } while (opcoesubmenu != 0);
                break;
            case 3:
                do
                {
                    printf("\n== Menu de solicitantes ==\nO que você deseja fazer?\n[1] Cadastrar Novo solicitante\n[2] Alterar solicitante\n[3] Listar solicitantes\n[0] Voltar ao Menu Principal\n");
                    scanf("%d", &opcoesubmenu);
                    switch (opcoesubmenu)
                    {
                        case 1:
                            printf("\n== Novo agendamento ==\n");
                            break;
                        case 2:
                            /* code */
                            break;
                        case 3:
                            /* code */
                            break;
                        default:
                        printf("Opção inválida. Tente novamente.\n");
                        break;
                    }
                } while (opcoesubmenu != 0);
                break;
            case 4:
                /* code */
                break;
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
            }
    }while(opcao != 0);
    
    return 0;
}