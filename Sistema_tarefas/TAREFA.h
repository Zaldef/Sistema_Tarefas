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

#endif // TAREFA_H_INCLUDED
