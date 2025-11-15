/*****************************************************************
*                                                                *
* Nome: Marcelly Lais Ferreira de Almeida                        *
* Trabalho Prático                                               *
* Disciplinas: Algoritmos e Programação II                       *
* Laboratório de Algoritmos e Programação II                     *
* Professores: Ivone e Ronaldo                                   *
* Data: 14/11/2025                                               *
* Versão: 1                                                      *
* Descrição: Implementa o modulo de agendamentos.                *
* Contem as funcoes de cadastro, cancelamento, verificacao de    *
* disponibilidade, listagem e o 'motor' da exclusao em cascata.  *
*                                                                *
******************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "agendamento.h" 
#include "espacocomum.h"
#include "solicitantes.h"

agendamento* criaListaAgendamentos()
{
    /*Aloca memória para a cabeça*/
    agendamento *no = (agendamento*) malloc(sizeof(agendamento));
    
    if (no != NULL) {
        /* A lista começa vazia, apontando para nada dos dois lados.*/
        no->prox = NULL;
        no->ant = NULL; 
    }
    return no;
}

/* Verifica se um espaço já está ocupado em uma data específica.
 * Retorna 1 se estiver LIVRE.
 * Retorna 0 se estiver OCUPADO.*/
int verificarDisponibilidade(agendamento *lst, int idEspaco, data dataCheck)
{
    /*Começa no primeiro agendamento após a cabeça*/
    agendamento *atual = lst->prox;

    /* Verifica a lista de agendamentos */
    while (atual != NULL)
    {
        /*Compara a data do agendamento 'atual' com a data que queremos (dataCheck)*/
        int comp = compararDatas(atual->data_agendamento, dataCheck);

        /*Análise dos resultados da comparação*/
        if (comp == 0)
        {
            /*Se as datas s?o iguais, checa se o espaço é igual*/
            if (atual->id_do_espaco == idEspaco)
            {
                return 0; /* OCUPADO!*/
            }
            /*Se as datas são iguais mas o espaço é diferente,
            continuamos procurando (pode ter outro agendamento na msm data e espaço)*/ 
        } 
        
        /*A data do 'atual' já é MAIOR que a data que buscamos*/
        else if (comp > 0)
        {
            /*Como a lista está ordenada o espaço está livre*/
            return 1;
        }

        /*Continua para o próximo.*/
        atual = atual->prox;
    }

    /* Se o loop terminou (chegou ao fim da lista), não há nada agendado.*/
    return 1; /*LIVRE!*/ 
}

/* Insere um novo agendamento na lista (com cabeça),
 * mantendo a ordem crescente pela 'data_agendamento'*/
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
    if (atual != NULL)
    {
        atual->ant = novoAgendamento;
    }
}

/* Função principal para cadastrar um novo agendamento.
 * Pede os dados ao usuário, VERIFICA, aloca memória e insere na lista se disponivel.*/
void cadastrarNovoAgendamento(agendamento *listaCabeca, espacocomum *listarespacos, solicitante *listasolicitantes)
{   
    int aux_espaco_id, aux_solicitante_unidade;
    espacocomum *espacoselecionado;
    solicitante *solicitanteselecionado;
    /* Aloca memória para o novo nó*/
    agendamento *novo = (agendamento*) malloc(sizeof(agendamento));
    if (novo == NULL) /*verificação se memória foi alocada*/
    {
        printf("ERRO: Falha de alocacao de memoria! para agendamento\n");
        return; 
    }

    /*Coleta os dados do usuário*/
    printf("\n== Novo Agendamento ==\n");
    printf("\nDigite a unidade do solicitante:\n");
    scanf("%d", &aux_solicitante_unidade);

    solicitanteselecionado = buscarSolicitantePorUnidade(listasolicitantes, aux_solicitante_unidade);
    if(solicitanteselecionado == NULL)
    {
        printf("\nERRO: nidade %d nao encontrada. Cancelando cadastro de agendamento.\n", aux_solicitante_unidade);
        free(novo); /* libera memoria alocada para novo agendamento!*/
        return;
    }
    else
    {
        novo->unidade_solicitante = solicitanteselecionado->unidade;
    }

    /* Mostra a lista de espaços para o usuário */
    listarEspacosSimples(listarespacos);

    printf("Digite o ID do espaco desejado: ");
    scanf("%d", &aux_espaco_id);

    /* Verifica se o espaço existe */
    espacoselecionado = buscarEspacoPorID(listarespacos, aux_espaco_id);

    if(espacoselecionado == NULL)
    {
        printf("\nERRO: Espaco com ID %d nao encontrado. Cancelando cadastro de agendamento.\n", aux_espaco_id);
        free(novo); /* libera memoria alocada para novo agendamento!*/
        return;
    }
    else
    {
        novo->id_do_espaco = espacoselecionado->id_espaco;
    }

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
        free(novo); /* libera memoria alocada para novo agendamento!*/
        return;
    }
    
    /* Está livre. Insere o nó na lista ordenada.*/
    insereAgendamentoOrdenado(listaCabeca, novo);

    printf("\nAgendamento para o dia %02d/%02d/%d no espaço %d cadastrado com sucesso!\n",
           novo->data_agendamento.dia,
           novo->data_agendamento.mes,
           novo->data_agendamento.ano,
           novo->id_do_espaco);
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
        /* Compara a data do 'atual' com o inicio do período */
        int comp_inicio = compararDatas(atual->data_agendamento, dataInicio);
        
        /* Compara a data do 'atual' com o fim do período */
        int comp_fim = compararDatas(atual->data_agendamento, dataFim);

        /* Se comp_inicio <= 0 (data <= inicio) E comp_fim >= 0 (data >= fim),
         * então o agendamento está DENTRO do período.*/
        if (comp_inicio <= 0 && comp_fim >= 0)
        {
            printf("  - Data: %02d/%02d/%d | Unidade: %d | Espaco: %d\n",
                   atual->data_agendamento.dia,
                   atual->data_agendamento.mes,
                   atual->data_agendamento.ano,
                   atual->unidade_solicitante,
                   atual->id_do_espaco);
            encontrou = 1;
        } 

        /* Se a data do 'atual' já é maior que a data FIM,
        * como a lista é ordenada, podemos parar a busca.*/
        else if (comp_fim < 0)
        {
            if (encontrou == 0)
            {
                printf("Nenhum agendamento encontrado neste periodo.\n");
            }
            return;
        }

        /* Se comp_fim < 0, a data é anterior ao período final, continua */
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
    data_hoje.mes = info_tempo->tm_mon + 1;     /* tm_mon 0-11, por isso +1 */
    data_hoje.ano = info_tempo->tm_year + 1900; /* tm_year anos desde 1900 */

    /* Chama a busca por periodo, usando HOJE como data de inicio E data de fim.*/
    listarAgendamentosPorPeriodo(listaCabeca, data_hoje, data_hoje);
}

/* Remove um nó agendamento da lista;
 * 'noParaApagar' é o ponteiro direto para o nó a ser removido.*/
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

/* Lista todos os agendamentos cadastrados e oferece a opção de cancelar um deles selecionando pelo índice.*/
void consultarECancelarAgendamento(agendamento *listaCabeca)
{
    agendamento *atual = listaCabeca->prox; /* Pula o nó-cabeça */
    int contador = 1, numeroParaCancelar, totalItens = 0 /* Para contar o total de agendamentos */; 

    printf("\n== Consultar / Cancelar Agendamentos ==\n");

    /* Lista todos os agendamentos */
    if (atual == NULL)
    {
        printf("Nenhum agendamento cadastrado no sistema.\n");
        return; /* Sai da funçãoo se a lista está vazia */
    }

    printf("Lista de Agendamentos (Ordenados por Data: da mais recente a mais antiga):\n");
    while (atual != NULL)
    {
        /* Imprime os dados que estão nos registros de agendamento */
        printf(" [%d] Data: %02d/%02d/%d | Unidade Solicitante: %d | ID Espaco: %d\n",
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
    if (numeroParaCancelar == 0)
    {
        return; /* Usuário quer voltar */
    }

    /* Checa se o número é válido*/
    if (numeroParaCancelar < 1 || numeroParaCancelar > totalItens) {
        printf("ERRO: Numero invalido. Nenhum agendamento foi cancelado.\n");
        return;
    }

    /* Se o número é válido */
    atual = listaCabeca->prox; /* Reinicia a busca do início*/
    contador = 1; /* Reinicia o contador */

    /* Anda na lista até parar no nó escolhido */
    while (contador < numeroParaCancelar)
    {
        atual = atual->prox;
        contador++;
    }

    /* 'atual' agora é o ponteiro para o nó que o usuário quer cancelar */
    removeAgendamento(atual); /* Chama a funçãoo de remoção */
}

void excluirAgendamentosEmCascata(agendamento *listaCabecaAg, int idparaexclusao, char tipoexclusao)
{
    agendamento *aux, *aux2;
 
    aux = listaCabecaAg->prox;

    /* Verifica o tipo de exclusão: 'S' para solicitante, 'E' para espaço comum */
    if (tipoexclusao == 'S')
    {
        /* Exclusão em cascata dos agendamentos para solicitante */
        while (aux != NULL)
        {
            aux2 = aux->prox; /* Armazena o próximo nó antes de possivelmente remover o atual */
            if (aux->unidade_solicitante == idparaexclusao)
            {
                removeAgendamento(aux);
            }

            aux = aux2; /* Move para o próximo nó */
        }
    }

    else if (tipoexclusao == 'E')
    {
        /* Exclusão em cascata de agendamentos no espaço comum excluido */
        while (aux != NULL)
        {
            aux2 = aux->prox; /* Armazena o próximo nó antes de possivelmente remover o atual */
            if (aux->id_do_espaco == idparaexclusao)
            {
                removeAgendamento(aux);
            }

            aux = aux2; /* Move para o próximo nó */
        }
    }
}

/* função de agendamento recorrente tenta agendar UMA data e chama a si mesma para a proxima data, N-1 vezes. */
void agendarRecorrenteRecursivo(agendamento *listaAg, int idEspaco, int idSolicitante, data dataAtual, int diasIntervalo, int repeticoesRestantes)
{
    data proximaData;
    /* Parada da recursao) */
    if (repeticoesRestantes <= 0)
    {
        return;
    }

    /* Verifica se a data está disponível */
    if (verificarDisponibilidade(listaAg, idEspaco, dataAtual) == 1) 
    {
        /* Disponivel. Cria o no. */
        agendamento *novo = (agendamento*) malloc(sizeof(agendamento));
        if (novo != NULL)
        {
            novo->unidade_solicitante = idSolicitante;
            novo->id_do_espaco = idEspaco;
            novo->data_agendamento = dataAtual;
            
            insereAgendamentoOrdenado(listaAg, novo);
            printf("Agendamento para o dia %02d/%02d/%d no espaco %d cadastrado com sucesso!\n",
           novo->data_agendamento.dia,
           novo->data_agendamento.mes,
           novo->data_agendamento.ano,
           novo->id_do_espaco);
        }
        else
        {
            printf("Falha no agendamento para o dia %02d/%02d/%d no espaco %d!(erro de memoria)\n", 
            dataAtual.dia, dataAtual.mes, dataAtual.ano, idEspaco);
        }
    }
    else
    {
        printf("No dia %02d/%02d/%d o espaco %d ja esta ocupado!\n", 
        dataAtual.dia, dataAtual.mes, dataAtual.ano, idEspaco);
    }

    
    /* Calcula a proxima data */
    proximaData = somarDias(dataAtual, diasIntervalo);
    
    /* Chama a si mesma com 1 repeticao a menos */
    agendarRecorrenteRecursivo(listaAg, idEspaco, idSolicitante, proximaData, diasIntervalo, repeticoesRestantes - 1);
}

void menuAgendamentoRecorrente(agendamento *listaAg, espacocomum *listaEsp, solicitante *listaSol)
{
    int idEspaco, idSol, intervalo, repeticoes;
    data dataInicial;
    
    printf("\n== Novo Agendamento Recorrente ==\n");
    
    /* Pede os dados basicos */
    printf("Digite a unidade do solicitante: ");
    scanf("%d", &idSol);
    /* Valida o solicitante */
    if (buscarSolicitantePorUnidade(listaSol, idSol) == NULL)
    {
        printf("ERRO: Solicitante nao encontrado.\n");
        return;
    }

    listarEspacosSimples(listaEsp);
    printf("Digite o ID do espaco: ");
    scanf("%d", &idEspaco);
    /* Valida o espaco */
    if (buscarEspacoPorID(listaEsp, idEspaco) == NULL)
    {
        printf("ERRO: Espaco nao encontrado.\n");
        return;
    }

    printf("Data do PRIMEIRO agendamento (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &dataInicial.dia, &dataInicial.mes, &dataInicial.ano);

    printf("Intervalo em dias (ex: 1=diario, 7=semanal, 30=mensal): ");
    scanf("%d", &intervalo);

    printf("Quantas vezes deseja repetir? ");
    scanf("%d", &repeticoes);

    if (intervalo <= 0 || repeticoes <= 0)
    {
        printf("ERRO: Intervalo e repeticoes devem ser maiores que zero.\n");
        return;
    }

    /* Dispara a recursao */
    agendarRecorrenteRecursivo(listaAg, idEspaco, idSol, dataInicial, intervalo, repeticoes);
}

void menuagendamento(agendamento *lista_agendamentos, espacocomum *listarespacos, solicitante *listasolicitantes) 
{
    int opcoesubmenu;
    do
    {
        printf("\n== Menu de agendamentos ==\nO que você deseja fazer?\n"
               "[1] Novo agendamento\n"
               "[2] Consultar / Cancelar agendamento\n"
               "[3] Ver Calendário do Dia\n"
               "[4] Agendamento recorrente\n"
               "[0] Voltar ao Menu Principal\n");
        scanf("%d", &opcoesubmenu);
        
        switch (opcoesubmenu)
        {
            case 1:
                /*Chama a função de cadastro, passando a lista */
                cadastrarNovoAgendamento(lista_agendamentos, listarespacos, listasolicitantes);
                break;
            case 2:
                /*Chama a função de consulta e cancelamento*/
                consultarECancelarAgendamento(lista_agendamentos);
                break;
            case 3:
                /*Chama a função de ver calendário do dia*/
                verCalendarioDoDia(lista_agendamentos);
                break;
            case 4:
                /*Chama a função de agendamento recorrente*/
                menuAgendamentoRecorrente(lista_agendamentos, listarespacos, listasolicitantes);
                break;
            case 0:
                break; /* Para não mostrar "opção inválida" ao sair */
            default:
                printf("Opção inválida. Tente novamente.\n");
            break;
        }
    } while (opcoesubmenu != 0);
}
