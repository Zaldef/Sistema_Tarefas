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
    char proj[NUM_CHAR]; // � qual projeto a tarefa pertence
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

Tarefa editarTarefa(Tarefa old){
    Tarefa new;
    new.cod = old.cod;
    
    printf("\n\tDigite o novo nome da tarefa:\n ");
    printf("\tnome anterior :%s\n",old.name);
    printf("\t");
    fflush(stdin);
    gets(new.name);
    printf("\n\tDigite o novo nome do projeto que a tarefa pertence: \n");
    printf("\tnome anterior:%s\n",old.proj);
    printf("\t");
    fflush(stdin);
    gets(new.proj);
    printf("\n\tDigite a nova data de inicio da tarefa: ");
    printf("\n\tData anterior:%d/%d/%d \n",old.ini.dia,old.ini.mes,old.ini.ano);
    printf("\n\tDigite o novo dia:");
    scanf("%d",&new.ini.dia);
    printf("\tDigite o novo mes: ");
    scanf("%d",&new.ini.mes);
    printf("\tDigite o novo ano: ");
    scanf("%d",&new.ini.ano);
    printf("\n\tDigite a nova data de termino:\n ");
    printf("\n\tData anterior :%d/%d/%d \n",old.ter.dia,old.ter.mes,old.ter.ano);
    printf("\tDigite o novo dia:");
    scanf("%d",&new.ter.dia);
    printf("\tDigite o mes: ");
    scanf("%d",&new.ter.mes);
    printf("\tDigite o ano: ");
    scanf("%d",&new.ter.ano);
    return new;
}

Tarefa novaTarefaTeste(){
    Tarefa T;
    char a = 'a';
    T.cod = 1;
    T.name[0] = a;
    T.proj[0] = a;
    T.ini.ano = 2000;
    T.ini.mes = 01;
    T.ini.dia = 01;
    T.ter.ano = 2000;
    T.ter.mes = 02;
    T.ter.dia = 02;
    return T;
}

void ImprimirTarefa(Tarefa T){
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
