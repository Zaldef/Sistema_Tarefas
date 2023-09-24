#ifndef TAREFA_H_INCLUDED
#define TAREFA_H_INCLUDED

#define NUM_CHAR 30

typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

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
    fflush(stdin);
    gets(T.name);
    printf("\n\tDigite o nome do projeto que a tarefa pertence: ");
    fflush(stdin);
    gets(T.proj);
    printf("\n\tDigite a data de inicio da tarefa: ");
    printf("\n\tDigite o dia: ");
    scanf("%d",&T.ini.dia);
    printf("\tDigite o mes: ");
    scanf("%d",&T.ini.mes);
    printf("\tDigite o ano: ");
    scanf("%d",&T.ini.ano);
    printf("\n\tDigite a data de termino: ");
    printf("\n\tDigite o dia: ");
    scanf("%d",&T.ter.dia);
    printf("\tDigite o mes: ");
    scanf("%d",&T.ter.mes);
    printf("\tDigite o ano: ");
    scanf("%d",&T.ter.ano);
    T.status = 0;
    return T;
}

void imprimirTarefa(Tarefa T){
    printf("\n\tCodigo da tarefa: %d",T.cod);
    printf("\n\tNome da tarefa: %s",T.name);
    printf("\n\tNome do projeto: %s",T.proj);
    printf("\n\tData de Inicio: %d/%d/%d",T.ini.dia,T.ini.mes,T.ini.ano);
    printf("\n\tData de Termino: %d/%d/%d",T.ter.dia,T.ter.mes,T.ter.ano);
    if(T.status == 0){
        printf("\n\tTarefa em dia");
    }else if(T.status == 1){
        printf("\n\tTarefa atrasada");
    }else{
        printf("\n\tTarefa pendente");
    }
}

#endif // TAREFA_H_INCLUDED
