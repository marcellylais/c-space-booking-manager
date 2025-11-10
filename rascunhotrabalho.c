#include <stdio.h> 
#include <string.h> /* Para manipulação de strings*/
#include <stdlib.h> /* Para malloc e free*/
#include <time.h> /* Para manipulação de datas e horas*/
  
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

    /*Procura a posição*/ 
    while (atual != NULL && compararDatas(novoAgendamento->data_agendamento, atual->data_agendamento) > 0)
    {
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

/* Insere um novo espaco na lista (com cabeça), mantendo a ordem crescente pelo 'id_espaco'*/
void insereEspacoOrdenado(espacocomum *listaCabeca, espacocomum *novoEspaco)
{
    espacocomum *anterior = listaCabeca; 
    espacocomum *atual = listaCabeca->prox; 

    novoEspaco->prox = NULL;
    novoEspaco->ant = NULL;

    /*Procura a posição*/ 
    while (atual != NULL && novoEspaco->id_espaco > atual->id_espaco)
    {
        anterior = atual;
        atual = atual->prox;
    }

    /* Novo agendamento será inserido entre 'anterior' e 'atual'*/
    novoEspaco->prox = atual;
    novoEspaco->ant = anterior;
    anterior->prox = novoEspaco;

    if (atual != NULL)
    {
        atual->ant = novoEspaco;
    }
}

/* Busca um espaco pelo ID, retorna um ponteiro para o nó se achar e retorna NULL se não achar.*/
espacocomum* buscarEspacoPorID(espacocomum *listaCabeca, int idBusca)
{
    espacocomum *atual = listaCabeca->prox; /* Pula o nó-cabeça */
    int continuarProcurando = 1; /*variavel de parada acaso já encontrar espaço*/

    while (atual != NULL && continuarProcurando == 1)
    {
        if (atual->id_espaco == idBusca)
        {
            /* Encontrado!*/
            return atual;
        } 
        
        if (atual->id_espaco > idBusca)
        {
            /* A ID do 'atual' já é maior que a ID buscada, como a lista é ordenada, não será encontrado*/
            continuarProcurando = 0;
        }

        if (continuarProcurando == 1)
        {
            atual = atual->prox;
        }
    }

    /* Se saiu do loop não encontrou */
    return NULL; 
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
        printf("  ID: %d - Nome: %s - Descrição: %s - Capacidade: %d\n", atual->id_espaco, atual->nome, atual->descricao, atual->capacidade);
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

/* Lista todos os agendamentos entre duas datas (inclusive).*/
void listarAgendamentosPorPeriodo(agendamento *listaCabeca, data dataInicio, data dataFim)
{
    agendamento *atual = listaCabeca->prox; /* Pula o nó-cabeça */
    int encontrou = 0;

    /* Imprime o cabeçalho do relatório */
    printf("\n== Relatorio de Agendamentos de %02d/%02d/%d ate %02d/%02d/%d ==\n",
           dataInicio.dia, dataInicio.mes, dataInicio.ano,
           dataFim.dia, dataFim.mes, dataFim.ano);

    while (atual != NULL)
    {
        /* Compara a data do 'atual' com o INÍCIO do período */
        int comp_inicio = compararDatas(atual->data_agendamento, dataInicio);
        
        /* Compara a data do 'atual' com o FIM do período */
        int comp_fim = compararDatas(atual->data_agendamento, dataFim);

        /* Se comp_inicio >= 0 (data >= inicio) E comp_fim <= 0 (data <= fim),
         * então o agendamento está DENTRO do período.*/
        if (comp_inicio >= 0 && comp_fim <= 0)
        {
            printf("  - Data: %02d/%02d/%d | Unidade: %d | Espaco: %d\n",
                   atual->data_agendamento.dia,
                   atual->data_agendamento.mes,
                   atual->data_agendamento.ano,
                   atual->unidade_solicitante,
                   atual->id_do_espaco);
            encontrou = 1;
        } 

        /* Se a data do 'atual' já é MAIOR que a data FIM,
        * como a lista é ordenada, podemos parar a busca.*/
        else if (comp_fim > 0)
        {
            if (encontrou == 0)
            {
                printf("Nenhum agendamento encontrado neste periodo.\n");
            }
        }

        /* Se comp_inicio < 0, a data é anterior ao período, continua */
        atual = atual->prox;
    }

    /*acaso o usuário coloque uma data de fim que seja mais dos agendamentos já feitos*/
    if (encontrou == 0)
    {
        printf("Nenhum agendamento encontrado neste periodo.\n");
    }
  
}

/* Lista todos os agendamentos marcados para a data ATUAL do sistema.
 * A função descobre a data de "hoje" e chama a funcao 'listarAgendamentosPorPeriodo'. */
void verCalendarioDoDia(agendamento *listaCabeca)
{
    time_t tempo_bruto;
    struct tm *info_tempo;
    data data_hoje;

    /* Pega a data atual do sistema */
    time(&tempo_bruto);
    info_tempo = localtime(&tempo_bruto);

    /* Converte para a nossa struct 'data' */
    data_hoje.dia = info_tempo->tm_mday;
    data_hoje.mes = info_tempo->tm_mon + 1;     /* tm_mon é 0-11, por isso +1 */
    data_hoje.ano = info_tempo->tm_year + 1900; /* tm_year é anos desde 1900 */

    /* Chama a busca por periodo, usando HOJE como data de inicio E data de fim.*/
    listarAgendamentosPorPeriodo(listaCabeca, data_hoje, data_hoje);
}

/* Remove um nó agendamento da lista;
 * 'noParaApagar' é o ponteiro direto para o nó a ser removido.
 * (Assume que 'noParaApagar' NUNCA é o nó-cabeça).*/
void removeAgendamento(agendamento *noParaApagar)
{
    if (noParaApagar == NULL)
    {
        return;
    }

    /* O nó anterior a ele agora aponta para o próximo */
    noParaApagar->ant->prox = noParaApagar->prox;

    /* O anterior ao nó seguinte (se existir) agora aponta para o anterior do 'noParaApagar'*/
    if (noParaApagar->prox != NULL)
    {
        noParaApagar->prox->ant = noParaApagar->ant;
    }

    printf("\nAgendamento para %02d/%02d/%d da unidade %d no espaço %d cancelado com sucesso!\n",
           noParaApagar->data_agendamento.dia,
           noParaApagar->data_agendamento.mes,
           noParaApagar->data_agendamento.ano,
           noParaApagar->unidade_solicitante,
           noParaApagar->id_do_espaco);
    /* Libera a memória do nó removido */
    free(noParaApagar);
}

/* Lista todos os agendamentos cadastrados e oferece a opção de
 * cancelar um deles selecionando pelo índice.*/
void consultarECancelarAgendamento(agendamento *listaCabeca) {
    agendamento *atual = listaCabeca->prox; /* Pula o nó-cabeça */
    int contador = 1, numeroParaCancelar, totalItens = 0 /* Para contar o total de agendamentos */; 

    printf("\n== Consultar / Cancelar Agendamentos ==\n");

    /* Lista todos os agendamentos */
    if (atual == NULL) {
        printf("Nenhum agendamento cadastrado no sistema.\n");
        return; /* Sai da função se a lista está vazia */
    }

    printf("Lista de Agendamentos (Ordenados por Data):\n");
    while (atual != NULL) {
        /* Imprime os dados que estão na struct agendamento */
        printf("  [%d] Data: %02d/%02d/%d | Unidade Solicitante: %d | ID Espaco: %d\n",
               contador,
               atual->data_agendamento.dia,
               atual->data_agendamento.mes,
               atual->data_agendamento.ano,
               atual->unidade_solicitante,
               atual->id_do_espaco);
        
        atual = atual->prox;
        contador++;
    }

    /* Guarda o número total de itens que foram listados */
    totalItens = contador - 1; 

    /* Pede ao usuário para escolher qual cancelar */
    printf("\nDigite o numero do agendamento para CANCELAR (ou 0 para voltar): \n");
    scanf("%d", &numeroParaCancelar);

    /* Validação da escolha do usuário */
    if (numeroParaCancelar == 0) {
        return; /* Usuário quer voltar */
    }

    /* Checa se o número é válido (não menor que 1 e não maior que o total) */
    if (numeroParaCancelar < 1 || numeroParaCancelar > totalItens) {
        printf("ERRO: Numero invalido. Nenhum agendamento foi cancelado.\n");
        return;
    }

    /* Se o número é válido, acha o N-ésimo nó para remover */
    atual = listaCabeca->prox; /* Reinicia a busca do início */
    contador = 1; /* Reinicia o contador */

    /* Anda na lista até parar no nó escolhido */
    while (contador < numeroParaCancelar) {
        atual = atual->prox;
        contador++;
    }

    /* 'atual' agora é o ponteiro para o nó que o usuário quer apagar */
    removeAgendamento(atual); /* Chama a função de remoção */
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
                /*Chama a função de consulta e cancelamento*/
                consultarECancelarAgendamento(lista_agendamentos);
                break;
            case 3:
                /*Chama a função de ver calendário do dia*/
                verCalendarioDoDia(lista_agendamentos);
                break;
            case 0:
                break; /* Para não mostrar "opção inválida" ao sair */
            default:
                printf("Opção inválida. Tente novamente.\n");
            break;
        }
    } while (opcoesubmenu != 0);
}

/* Pergunta ao usuário os dados de um novo espaço,
 * verifica se o ID já existe, e o cadastra. */
void cadastrarNovoEspaco(espacocomum *listaCabeca)
{
    int idespaco;
    espacocomum *novo; /* Ponteiro para o novo nó */
    
    printf("\n== Cadastrar Novo Espaco ==\n");
    printf("Digite o ID (numerico) para o novo espaco:\n");
    scanf("%d", &idespaco);

    /*Checa se o ID já está em uso e sai da função*/
    if (buscarEspacoPorID(listaCabeca, idespaco) != NULL)
    {
        printf("ERRO: O ID %d ja esta sendo usado por outro espaco.\n", idespaco);
        return;
    }

    /*Se o ID está livre, aloca memória */
    novo = (espacocomum*) malloc(sizeof(espacocomum));
    if (novo == NULL)/*verificação se memória foi alocada*/
    {
        printf("ERRO CRITICO: Falha de alocacao de memoria para espaço!\n");
        return;
    }

    /*Preenche os dados */
    novo->id_espaco = idespaco; /* Guarda o ID que já validamos */

    printf("Digite o Nome do espaco:\n");
    scanf(" %[^\n]", novo->nome); 

    printf("Digite uma breve Descricao:\n");
    scanf(" %[^\n]", novo->descricao);

    printf("Digite a Capacidade (numero de pessoas):\n");
    scanf("%d", &novo->capacidade);

    /*Insere na lista ordenada */
    insereEspacoOrdenado(listaCabeca, novo);

    printf("\nEspaco '%s' (ID: %d) cadastrado com sucesso!\n", novo->nome, novo->id_espaco);
}

/* Exibe o menu de gerenciamento de espaços e chama as funções correspondentes */
void menuEspacos(espacocomum *lista_espacos)
{
    int opcoesubmenu;

    do
    {
        printf("\n== Menu de Espacos Comuns ==\nO que voce deseja fazer?\n"
               "[1] Cadastrar Novo Espaco\n"
               "[2] Alterar Espaco\n"
               "[3] Listar Todos os Espacos\n"
               "[0] Voltar ao Menu Principal\n");
        scanf("%d", &opcoesubmenu);

        switch (opcoesubmenu)
        {
            case 1:
                cadastrarNovoEspaco(lista_espacos);
                break;
            case 2:
                /*alterarEspaco(lista_espacos);*/
                break;
            case 3:
                /* Chama a função de listar todos os espaços */
                listarEspacosSimples(lista_espacos);
                break;
            case 0:
                /* Não faz nada, só para o loop não dar "opção inválida" */
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
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
                menuEspacos(lista_espacos);
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