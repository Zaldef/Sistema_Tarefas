#ifndef TAREFA_H_INCLUDED
#define TAREFA_H_INCLUDED
#include "DATA.h"
#define NUM_CHAR 30

typedef struct info{
    int cod; //codigo da tarefa
    char name[NUM_CHAR]; // nome da tarefa
    char proj[NUM_CHAR]; // á qual projeto a tarefa pertence
    Data ini; //data de inicio
    Data ter; //data de termino
    int status; //1 atrasada e 0 em dia e -1 pendente
}Tarefa;

Tarefa novaTarefa(){
    Tarefa T;
    printf("\n\tDigite o codigo da tarefa: ");
    scanf("%d", &T.cod);
    printf("\n\tDigite o nome da tarefa: ");
    scanf("%s", T.name);
    printf("\n\tDigite o nome do projeto que a tarefa pertence: ");
    scanf("%s", T.proj);
    printf("\n\tDigite a data de inicio da tarefa: ");
    T.ini = InsereData();
    printf("\n\tDigite a data de termino: ");
    T.ter = InsereData();
    return T;
}

#endif // TAREFA_H_INCLUDED
