/************************************************
*                                               *
* Nome: Marcelly Lais Ferreira de Almeida       *
* Trabalho Pr?tico                              *
* Disciplinas: Algoritmos e Programa??o II      *
* Laborat?rio de Algoritmos e Programa??o II    *
* Professores: Ivone e Ronaldo                  *
* Data: 14/11/2025                              *
* Vers?o: 1                                     *
* Descri??o:                                    *
*                                               *
*************************************************/

#include <stdio.h> 
#include <string.h> /* Para manipula??o de strings*/
#include <stdlib.h> /* Para malloc e free*/
#include <time.h> /* Para manipula??o de datas e horas*/
  
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

/*Cria??o de n? "cabe?a" para a lista de espa?os*/
espacocomum* criaListaEspacos()
{
    /*Aloca mem?ria para a cabe?a*/
    espacocomum *no = (espacocomum*) malloc(sizeof(espacocomum));
    
    if (no != NULL) {
        /*A lista come?a vazia, apontando para nada dos dois lados.*/
        no->prox = NULL;
        no->ant = NULL; 
    }
    return no;
}

/* Cria e retorna o n? para uma lista de agendamentos.*/
agendamento* criaListaAgendamentos() {
    /*Aloca mem?ria para a cabe?a*/
    agendamento *no = (agendamento*) malloc(sizeof(agendamento));
    
    if (no != NULL) {
        /* A lista come?a vazia, apontando para nada dos dois lados.*/
        no->prox = NULL;
        no->ant = NULL; 
    }
    return no;
}

/* Cria e retorna o n? para uma lista de solicitantes.*/
solicitante* criaListaSolicitantes() {
    /* Aloca mem?ria para a cabe?a*/
    solicitante *no = (solicitante*) malloc(sizeof(solicitante));
    
    if (no != NULL) {
        /* A lista come?a vazia, apontando para nada dos dois lados.*/
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

    /* Anos iguais, checa o m?s*/
    if (data1.mes < data2.mes) return -1;
    if (data1.mes > data2.mes) return 1;

    /* Meses iguais, checa o dia*/
    if (data1.dia < data2.dia) return -1;
    if (data1.dia > data2.dia) return 1;

    return 0; /* S?o iguais*/
}

/* Verifica se um espa?o j? est? ocupado em uma data espec?fica.
 * Retorna 1 se estiver LIVRE.
 * Retorna 0 se estiver OCUPADO.
 */
int verificarDisponibilidade(agendamento *lst, int idEspaco, data dataCheck)
{
    /*Come?a a busca no PRIMEIRO N? DE DADOS (pula o n?-cabe?a)*/
    agendamento *atual = lst->prox;

    /* Verifica a lista de agendamentos */
    while (atual != NULL)
    {
        /*Compara a data do agendamento 'atual' com a data que queremos (dataCheck)*/
        int comp = compararDatas(atual->data_agendamento, dataCheck);

        /*As datas s?o ID?NTICAS*/
        if (comp == 0)
        {
            /*Se as datas s?o iguais, checa se o ESPA?O tamb?m ? igual*/
            if (atual->id_do_espaco == idEspaco)
            {
                return 0; /* OCUPADO!*/
            }
            /*Se as datas s?o iguais, mas o espa?o ? outro,
            continuamos procurando (pode ter outro agendamento na msm data)*/ 
        } 
        
        /*2. A data do 'atual' j? ? MAIOR que a data que buscamos*/
        else if (comp > 0)
        {
            /*Como a lista est? ordenada, j? passamos do ponto.*/
            /* N?o h? mais como achar a data.*/
            return 1; /*LIVRE!*/
        }

        /* Se comp < 0, a data do 'atual' ? antiga. Continua para o pr?ximo.*/
        atual = atual->prox;
    }

    /* Se o loop terminou (chegou ao fim da lista), n?o achamos nada.*/
    return 1; /*LIVRE!*/ 
}

/* Insere um novo agendamento na lista (com cabe?a),
 * mantendo a ordem crescente pela 'data_agendamento'.
 * no ? o ponteiro para o n? cabe?a.
 */
void insereAgendamentoOrdenado(agendamento *no, agendamento *novoAgendamento)
{
    agendamento *anterior = no; 
    agendamento *atual = no->prox; 

    novoAgendamento->prox = NULL;
    novoAgendamento->ant = NULL;

    /*Procura a posi??o*/ 
    while (atual != NULL && compararDatas(novoAgendamento->data_agendamento, atual->data_agendamento) > 0)
    {
        anterior = atual;
        atual = atual->prox;
    }

    /* Novo agendamento ser? inserido entre 'anterior' e 'atual'*/
    novoAgendamento->prox = atual;
    novoAgendamento->ant = anterior;
    anterior->prox = novoAgendamento;
    if (atual != NULL) {
        atual->ant = novoAgendamento;
    }
}

/* Insere um novo espaco na lista (com cabe?a), mantendo a ordem crescente pelo 'id_espaco'*/
void insereEspacoOrdenado(espacocomum *listaCabeca, espacocomum *novoEspaco)
{
    espacocomum *anterior = listaCabeca; 
    espacocomum *atual = listaCabeca->prox; 

    novoEspaco->prox = NULL;
    novoEspaco->ant = NULL;

    /*Procura a posi??o*/ 
    while (atual != NULL && novoEspaco->id_espaco > atual->id_espaco)
    {
        anterior = atual;
        atual = atual->prox;
    }

    /* Novo agendamento ser? inserido entre 'anterior' e 'atual'*/
    novoEspaco->prox = atual;
    novoEspaco->ant = anterior;
    anterior->prox = novoEspaco;

    if (atual != NULL)
    {
        atual->ant = novoEspaco;
    }
}

/* Busca um espaco pelo ID, retorna um ponteiro para o n? se achar e retorna NULL se n?o achar.*/
espacocomum* buscarEspacoPorID(espacocomum *listaCabeca, int idBusca)
{
    espacocomum *atual = listaCabeca->prox; /* Pula o n?-cabe?a */
    int continuarProcurando = 1; /*variavel de parada acaso j? encontrar espa?o*/

    while (atual != NULL && continuarProcurando == 1)
    {
        if (atual->id_espaco == idBusca)
        {
            /* Encontrado!*/
            return atual;
        } 
        
        if (atual->id_espaco > idBusca)
        {
            /* A ID do 'atual' j? ? maior que a ID buscada, como a lista ? ordenada, n?o ser? encontrado*/
            continuarProcurando = 0;
        }

        if (continuarProcurando == 1)
        {
            atual = atual->prox;
        }
    }

    /* Se saiu do loop n?o encontrou */
    return NULL; 
}

/* Mostra uma lista com ID e Nome de todos os espa?os cadastrados. */
void listarEspacosSimples(espacocomum *listaCabeca)
{
    espacocomum *atual = listaCabeca->prox; /* Come?a no primeiro item ap?s cabe?a */

    if (atual == NULL) {
        printf("\nAVISO: Nenhum espaco comum foi cadastrado ainda.\n");
        return;
    }

    printf("\n--- Espacos Disponiveis ---\n");
    while (atual != NULL) {
        printf("  ID: %d - Nome: %s - Descri??o: %s - Capacidade: %d\n", atual->id_espaco, atual->nome, atual->descricao, atual->capacidade);
        atual = atual->prox;
    }
    printf("---------------------------\n");
}

/* Fun??o principal para cadastrar um novo agendamento.
 * Pede os dados ao usu?rio, VERIFICA, aloca mem?ria e insere na lista se disponivel.
 */
void cadastrarNovoAgendamento(agendamento *listaCabeca, espacocomum *listarespacos)
{   
    /* Aloca mem?ria para o novo n?*/
    agendamento *novo = (agendamento*) malloc(sizeof(agendamento));
    if (novo == NULL) /*verifica??o se mem?ria foi alocada*/
    {
        printf("ERRO: Falha de alocacao de memoria!\n");
        return; 
    }

    /*Coleta os dados do usu?rio*/
    printf("\n== Novo Agendamento ==\n");
    printf("\nDigite a unidade do solicitante:\n");
    scanf("%d", &novo->unidade_solicitante);

    /* Mostra a lista de espa?os para o usu?rio */
    listarEspacosSimples(listarespacos);

    printf("Digite o ID do espaco desejado: ");
    scanf("%d", &novo->id_do_espaco);

    printf("\nDigite a data do agendamento (DD/MM/AAAA):\n");
    scanf("%d/%d/%d", &novo->data_agendamento.dia, &novo->data_agendamento.mes, &novo->data_agendamento.ano);
    
    /*Verifica se o espa?o est? dispon?vel na data desejada*/
    if (verificarDisponibilidade(listaCabeca, novo->id_do_espaco, novo->data_agendamento) == 0)
    {
        /*Se a fun??o retornar 0, est? ocupado.*/ 
        printf("\nERRO: O espaco %d j? esta reservado no dia %02d/%02d/%d.\n", novo->id_do_espaco,
               novo->data_agendamento.dia,
               novo->data_agendamento.mes,
               novo->data_agendamento.ano);
        free(novo); /* libera memoria alocada para agendamento novo!*/
        return;
    }
    
    /* Est? livre. Insere o n? na lista ordenada.*/
    insereAgendamentoOrdenado(listaCabeca, novo);

    printf("\nAgendamento para %02d/%02d/%d cadastrado com sucesso!\n",
           novo->data_agendamento.dia,
           novo->data_agendamento.mes,
           novo->data_agendamento.ano);
}

/* Lista todos os agendamentos entre duas datas (inclusive).*/
void listarAgendamentosPorPeriodo(agendamento *listaCabeca, data dataInicio, data dataFim)
{
    agendamento *atual = listaCabeca->prox; /* Pula o n?-cabe?a */
    int encontrou = 0;

    /* Imprime o cabe?alho do relat?rio */
    printf("\n== Relatorio de Agendamentos de %02d/%02d/%d ate %02d/%02d/%d ==\n",
           dataInicio.dia, dataInicio.mes, dataInicio.ano,
           dataFim.dia, dataFim.mes, dataFim.ano);

    while (atual != NULL)
    {
        /* Compara a data do 'atual' com o IN?CIO do per?odo */
        int comp_inicio = compararDatas(atual->data_agendamento, dataInicio);
        
        /* Compara a data do 'atual' com o FIM do per?odo */
        int comp_fim = compararDatas(atual->data_agendamento, dataFim);

        /* Se comp_inicio >= 0 (data >= inicio) E comp_fim <= 0 (data <= fim),
         * ent?o o agendamento est? DENTRO do per?odo.*/
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

        /* Se a data do 'atual' j? ? MAIOR que a data FIM,
        * como a lista ? ordenada, podemos parar a busca.*/
        else if (comp_fim > 0)
        {
            if (encontrou == 0)
            {
                printf("Nenhum agendamento encontrado neste periodo.\n");
            }
        }

        /* Se comp_inicio < 0, a data ? anterior ao per?odo, continua */
        atual = atual->prox;
    }

    /*acaso o usu?rio coloque uma data de fim que seja mais dos agendamentos j? feitos*/
    if (encontrou == 0)
    {
        printf("Nenhum agendamento encontrado neste periodo.\n");
    }
  
}

/* Lista todos os agendamentos marcados para a data ATUAL do sistema.
 * A fun??o descobre a data de "hoje" e chama a funcao 'listarAgendamentosPorPeriodo'. */
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
    data_hoje.mes = info_tempo->tm_mon + 1;     /* tm_mon ? 0-11, por isso +1 */
    data_hoje.ano = info_tempo->tm_year + 1900; /* tm_year ? anos desde 1900 */

    /* Chama a busca por periodo, usando HOJE como data de inicio E data de fim.*/
    listarAgendamentosPorPeriodo(listaCabeca, data_hoje, data_hoje);
}

/* Remove um n? agendamento da lista;
 * 'noParaApagar' ? o ponteiro direto para o n? a ser removido.
 * (Assume que 'noParaApagar' NUNCA ? o n?-cabe?a).*/
void removeAgendamento(agendamento *noParaApagar)
{
    if (noParaApagar == NULL)
    {
        return;
    }

    /* O n? anterior a ele agora aponta para o pr?ximo */
    noParaApagar->ant->prox = noParaApagar->prox;

    /* O anterior ao n? seguinte (se existir) agora aponta para o anterior do 'noParaApagar'*/
    if (noParaApagar->prox != NULL)
    {
        noParaApagar->prox->ant = noParaApagar->ant;
    }

    printf("\nAgendamento para %02d/%02d/%d da unidade %d no espa?o %d cancelado com sucesso!\n",
           noParaApagar->data_agendamento.dia,
           noParaApagar->data_agendamento.mes,
           noParaApagar->data_agendamento.ano,
           noParaApagar->unidade_solicitante,
           noParaApagar->id_do_espaco);
    /* Libera a mem?ria do n? removido */
    free(noParaApagar);
}

/* Lista todos os agendamentos cadastrados e oferece a op??o de
 * cancelar um deles selecionando pelo ?ndice.*/
void consultarECancelarAgendamento(agendamento *listaCabeca) {
    agendamento *atual = listaCabeca->prox; /* Pula o n?-cabe?a */
    int contador = 1, numeroParaCancelar, totalItens = 0 /* Para contar o total de agendamentos */; 

    printf("\n== Consultar / Cancelar Agendamentos ==\n");

    /* Lista todos os agendamentos */
    if (atual == NULL) {
        printf("Nenhum agendamento cadastrado no sistema.\n");
        return; /* Sai da fun??o se a lista est? vazia */
    }

    printf("Lista de Agendamentos (Ordenados por Data):\n");
    while (atual != NULL) {
        /* Imprime os dados que est?o na struct agendamento */
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

    /* Guarda o n?mero total de itens que foram listados */
    totalItens = contador - 1; 

    /* Pede ao usu?rio para escolher qual cancelar */
    printf("\nDigite o numero do agendamento para CANCELAR (ou 0 para voltar): \n");
    scanf("%d", &numeroParaCancelar);

    /* Valida??o da escolha do usu?rio */
    if (numeroParaCancelar == 0) {
        return; /* Usu?rio quer voltar */
    }

    /* Checa se o n?mero ? v?lido (n?o menor que 1 e n?o maior que o total) */
    if (numeroParaCancelar < 1 || numeroParaCancelar > totalItens) {
        printf("ERRO: Numero invalido. Nenhum agendamento foi cancelado.\n");
        return;
    }

    /* Se o n?mero ? v?lido, acha o N-?simo n? para remover */
    atual = listaCabeca->prox; /* Reinicia a busca do in?cio */
    contador = 1; /* Reinicia o contador */

    /* Anda na lista at? parar no n? escolhido */
    while (contador < numeroParaCancelar) {
        atual = atual->prox;
        contador++;
    }

    /* 'atual' agora ? o ponteiro para o n? que o usu?rio quer apagar */
    removeAgendamento(atual); /* Chama a fun??o de remo??o */
}

/* Pede um ID, busca o espa?o, e permite alterar campos especificos atraves de um sub-menu. */
void alterarEspaco(espacocomum *listaCabeca)
{
    int idespaco;
    espacocomum *noParaAlterar;
    int opcaoAlterar; /* Variavel para o sub-menu */

    printf("\n== Alterar Espaco ==\n");
    /* Pessoa digita o ID do espaco */
    printf("Digite o ID do espaco que deseja alterar (ou 0 para cancelar): ");
    scanf("%d", &idespaco);

    if (idespaco == 0)
    {
        return; /* Sai da fun??o */
    }

    /* Busca o n? */
    noParaAlterar = buscarEspacoPorID(listaCabeca, idespaco);

    if (noParaAlterar == NULL)
    {
        printf("ERRO: Espaco com ID %d nao encontrado.\n", idespaco);
        return;
    }

    /* Se encontrou, inicia o sub-menu de altera??o */
    do
    {
        /* Informa o espa?o a ser alterado e mostra as op??es */
        printf("\n--- Alterando Espaco (ID: %d) ---\n", noParaAlterar->id_espaco);
        printf(" [1] Nome: \t\t%s\n", noParaAlterar->nome);
        printf(" [2] Descricao: \t%s\n", noParaAlterar->descricao);
        printf(" [3] Capacidade: \t%d pessoas\n", noParaAlterar->capacidade);
        printf(" [0] Concluir (Cancelar operacao de alteracao)\n");
        printf("----------------------------------\n");
        printf("Qual campo deseja alterar? ");
        scanf("%d", &opcaoAlterar);

        /* 3. A pessoa decide e pode digitar a altera??o */
        switch (opcaoAlterar) {
            case 1:
                printf("Digite o NOVO Nome: ");
                scanf(" %[^\n]", noParaAlterar->nome); 
                printf("Nome alterado.\n");
                break;
            case 2:
                printf("Digite a NOVA Descricao: ");
                scanf(" %[^\n]", noParaAlterar->descricao);
                printf("Descricao alterada.\n");
                break;
            case 3:
                printf("Digite a NOVA Capacidade: ");
                scanf("%d", &noParaAlterar->capacidade);
                printf("Capacidade alterada.\n");
                break;
            case 0:
                printf("Alteracoes concluidas para o ID %d.\n", idespaco
        );
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcaoAlterar != 0); /* O loop continua at? o usu?rio digitar 0 */
}

/* Exibe o menu de agendamentos e chama as fun??es correspondentes.*/
void menuagendamento(agendamento *lista_agendamentos, espacocomum *listarespacos) 
{
    int opcoesubmenu;
    do
    {
        printf("\n== Menu de agendamentos ==\nO que voc? deseja fazer?\n"
               "[1] Novo agendamento\n"
               "[2] Consultar / Cancelar agendamento\n"
               "[3] Ver Calend?rio do Dia\n"
               "[0] Voltar ao Menu Principal\n");
        scanf("%d", &opcoesubmenu);
        
        switch (opcoesubmenu)
        {
            case 1:
                /*Chama a fun??o de cadastro, passando a lista */
                cadastrarNovoAgendamento(lista_agendamentos, listarespacos);
                break;
            case 2:
                /*Chama a fun??o de consulta e cancelamento*/
                consultarECancelarAgendamento(lista_agendamentos);
                break;
            case 3:
                /*Chama a fun??o de ver calend?rio do dia*/
                verCalendarioDoDia(lista_agendamentos);
                break;
            case 0:
                break; /* Para n?o mostrar "op??o inv?lida" ao sair */
            default:
                printf("Op??o inv?lida. Tente novamente.\n");
            break;
        }
    } while (opcoesubmenu != 0);
}

/* Pergunta ao usu?rio os dados de um novo espa?o,
 * verifica se o ID j? existe, e o cadastra. */
void cadastrarNovoEspaco(espacocomum *listaCabeca)
{
    int idespaco;
    espacocomum *novo; /* Ponteiro para o novo n? */
    
    printf("\n== Cadastrar Novo Espaco ==\n");
    printf("Digite o ID (numerico) para o novo espaco:\n");
    scanf("%d", &idespaco);

    /*Checa se o ID j? est? em uso e sai da fun??o*/
    if (buscarEspacoPorID(listaCabeca, idespaco) != NULL)
    {
        printf("ERRO: O ID %d ja esta sendo usado por outro espaco.\n", idespaco);
        return;
    }

    /*Se o ID est? livre, aloca mem?ria */
    novo = (espacocomum*) malloc(sizeof(espacocomum));
    if (novo == NULL)/*verifica??o se mem?ria foi alocada*/
    {
        printf("ERRO CRITICO: Falha de alocacao de memoria para espa?o!\n");
        return;
    }

    /*Preenche os dados */
    novo->id_espaco = idespaco; /* Guarda o ID que j? validamos */

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

/* Exibe o menu de gerenciamento de espa?os e chama as fun??es correspondentes */
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
                /* Chama a fun??o de alterar espa?o */
                alterarEspaco(lista_espacos);
                break;
            case 3:
                /* Chama a fun??o de listar todos os espa?os */
                listarEspacosSimples(lista_espacos);
                break;
            case 0:
                /* N?o faz nada, s? para o loop n?o dar "op??o inv?lida" */
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

    /*Cria??o de lista com cabe?a para melhorar fun??es de inser??o*/
    lista_solicitantes = criaListaSolicitantes();
    lista_espacos = criaListaEspacos();
    lista_agendamentos = criaListaAgendamentos();
    
    /*Checagem de seguran?a se as lista foram iniciadas coma cabe?a*/
    if (lista_solicitantes == NULL || lista_espacos == NULL || lista_agendamentos == NULL) {
        printf("ERRO 1: Falha ao alocar memoria para as listas.\n");
        return 1; /* Encerra o programa*/
    }
    
    do{
        printf("== SISTEMA DE CONTROLE agendamentoS DE ?REAS ==\nO que voc? deseja fazer?\n");
        printf("[1] agendamentos\n[2] Gerenciar Espa?os\n[3] Gerenciar solicitantes\n[4] Relat?rios\n[0] Sair\n");
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
                    printf("\n== Menu de solicitantes ==\nO que voc? deseja fazer?\n[1] Cadastrar Novo solicitante\n[2] Alterar solicitante\n[3] Listar solicitantes\n[0] Voltar ao Menu Principal\n");
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
                        printf("Op??o inv?lida. Tente novamente.\n");
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
                printf("Op??o inv?lida. Tente novamente.\n");
                break;
            }
    }while(opcao != 0);
    
    return 0;
}