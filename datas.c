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

#include "datas.h"

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
