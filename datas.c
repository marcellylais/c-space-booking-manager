/************************************************
*                                               *
* Nome: Marcelly Lais Ferreira de Almeida       *
* Trabalho Prático                              *
* Disciplinas: Algoritmos e Programação II      *
* Laboratório de Algoritmos e Programação II    *
* Professores: Ivone e Ronaldo                  *
* Data: 14/11/2025                              *
* Versão: 1                                     *
* Descrição: Implementa as funcoes de operacao  *
* do TAD 'data'. Contem a funcao 'compararDatas'*
* essencial para a ordenacao de agendamentos.   *
*                                               *
*************************************************/ 
#include <time.h>
#include "datas.h"

int compararDatas(data data1, data data2)
{
    /* Checa o ano primeiro */
    if (data1.ano < data2.ano) return 1;
    if (data1.ano > data2.ano) return -1;

    /* Anos iguais, checa o mês*/
    if (data1.mes < data2.mes) return 1;
    if (data1.mes > data2.mes) return -1;

    /* Meses iguais, checa o dia*/
    if (data1.dia < data2.dia) return 1;
    if (data1.dia > data2.dia) return -1;

    return 0; /* São iguais*/
}

data somarDias(data dataInicial, int diasASomar)
{
    /* Converte a 'struct data' para 'struct tm' da biblioteca time.h*/
    struct tm t = {0}/* Inicializa todos os campos com 0*/, *nova_t; 
    data nova_data;
    time_t data_em_segundos;
    
    t.tm_year = dataInicial.ano - 1900;  /* time.h conta a partir de 1900 */
    t.tm_mon = dataInicial.mes - 1;      /* time.h usa 0-11 para mes */
    t.tm_mday = dataInicial.dia;
    
    /* Converte a data para segundos (timestamp) */
    data_em_segundos = mktime(&t);
    
    /* Soma os dias (em segundos) (1 dia = 86400 seg) */
    data_em_segundos += diasASomar * 86400;
    
    /* Converte os segundos de volta para uma struct tm */
    nova_t = localtime(&data_em_segundos);
    
    /* Converte a struct tm de volta para a SUA struct data */
 
    nova_data.dia = nova_t->tm_mday;
    nova_data.mes = nova_t->tm_mon + 1;
    nova_data.ano = nova_t->tm_year + 1900;
    
    return nova_data;
}