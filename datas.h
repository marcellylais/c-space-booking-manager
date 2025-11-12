#ifndef DATAS_H
#define DATAS_H

typedef struct 
{ 
    int dia;
    int mes;
    int ano;
} data;

/* Compara duas 'struct data'.
    Retorna:
   -1  se data1 < data2
   0  se data1 == data2
   1  se data1 > data2 */
int compararDatas(data data1, data data2);

#endif